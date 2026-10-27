/*
 *  SPDX-FileCopyrightText: 2015 Dmitry Kazakov <dimula73@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "kis_layer_projection_plane.h"

#include <QBitArray>
#include <KoColorSpace.h>
#include <KoChannelInfo.h>
#include <KoCompositeOpRegistry.h>
#include "kis_painter.h"
#include "kis_projection_leaf.h"
#include "kis_cached_paint_device.h"
#include "kis_sequential_iterator.h"
#include "kis_paint_layer.h"
#include "kis_group_layer.h"


struct KisLayerProjectionPlane::Private
{
    KisLayer *layer;
    KisCachedPaintDevice cachedDevice;
};


KisLayerProjectionPlane::KisLayerProjectionPlane(KisLayer *layer)
    : m_d(new Private)
{
    m_d->layer = layer;
}

KisLayerProjectionPlane::~KisLayerProjectionPlane()
{
}

QRect KisLayerProjectionPlane::recalculate(const QRect& rect, KisNodeSP filthyNode, KisRenderPassFlags flags)
{
    return m_d->layer->updateProjection(rect, filthyNode, flags);
}

void KisLayerProjectionPlane::applyImpl(KisPainter *painter, const QRect &rect, KritaUtils::ThresholdMode thresholdMode)
{
    KisPaintDeviceSP device = m_d->layer->projection();
    if (!device) return;

    if (m_d->layer->clippingEnabled()) {
        return;
    }

    QRect needRect = rect;

    if (m_d->layer->compositeOpId() != COMPOSITE_COPY &&
        m_d->layer->compositeOpId() != COMPOSITE_DESTINATION_IN  &&
        m_d->layer->compositeOpId() != COMPOSITE_DESTINATION_ATOP) {

        needRect &= device->extent();
    }

    if(needRect.isEmpty()) return;

    QBitArray channelFlags = m_d->layer->projectionLeaf()->channelFlags();
    const KoColorSpace *srcCS = device->colorSpace();
    const KoColorSpace *dstCS = painter->device()->colorSpace();

    if (!channelFlags.isEmpty() && srcCS != dstCS) {
        bool alphaFlagIsSet        = (srcCS->channelFlags(false, true) & channelFlags) == srcCS->channelFlags(false, true);
        bool allColorFlagsAreSet   = (srcCS->channelFlags(true, false) & channelFlags) == srcCS->channelFlags(true, false);
        bool allColorFlagsAreUnset = (srcCS->channelFlags(true, false) & channelFlags).count(true) == 0;

        if (allColorFlagsAreSet) {
            channelFlags = dstCS->channelFlags(true, alphaFlagIsSet);
        } else if (allColorFlagsAreUnset) {
            channelFlags = dstCS->channelFlags(false, alphaFlagIsSet);
        } else {
            for (quint32 i = 0; i < dstCS->channelCount(); ++i) {
                if (dstCS->channels()[i]->channelType() == KoChannelInfo::ALPHA) {
                    channelFlags.setBit(i, alphaFlagIsSet);
                    break;
                }
            }
        }
    }

    QScopedPointer<KisCachedPaintDevice::Guard> d1;

    if (thresholdMode != KritaUtils::ThresholdNone) {
        d1.reset(new KisCachedPaintDevice::Guard(device, m_d->cachedDevice));
        KisPaintDeviceSP tmp = d1->device();
        tmp->makeCloneFromRough(device, needRect);

        KritaUtils::thresholdOpacity(tmp, needRect, thresholdMode);

        device = tmp;
    }

    QList<KisNodeSP> clippedNodes = m_d->layer->gatherClippingLayers();

    if (clippedNodes.isEmpty()) {
        painter->setChannelFlags(channelFlags);
        painter->setCompositeOpId(m_d->layer->compositeOpId());
        painter->setOpacityU8(m_d->layer->projectionLeaf()->opacity());
        painter->bitBlt(needRect.topLeft(), device, needRect);
    } else {
        KisPaintDeviceSP deviceClone = new KisPaintDevice(dstCS);
        deviceClone->makeCloneFrom(device, needRect);

        QBitArray newChannelFlags = deviceClone->colorSpace()->channelFlags(true, false);

        KisPainter clipPainter(deviceClone);
        clipPainter.setChannelFlags(newChannelFlags);

        for (KisNodeSP node : clippedNodes) {
            KisLayer *clipLayer = dynamic_cast<KisLayer*>(node.data());
            if (!clipLayer || !clipLayer->visible()) continue;

            KisPaintDeviceSP clipDev = clipLayer->projection();
            if (!clipDev) continue;

            clipPainter.setCompositeOpId(clipLayer->compositeOpId());
            clipPainter.setOpacityU8(clipLayer->projectionLeaf()->opacity());
            clipPainter.bitBlt(needRect.topLeft(), clipDev, needRect);
        }
        clipPainter.end();

        painter->setChannelFlags(channelFlags);
        painter->setCompositeOpId(m_d->layer->compositeOpId());
        painter->setOpacityU8(m_d->layer->projectionLeaf()->opacity());
        painter->bitBlt(needRect.topLeft(), deviceClone, needRect);
    }
}

void KisLayerProjectionPlane::apply(KisPainter *painter, const QRect &rect)
{
    applyImpl(painter, rect, KritaUtils::ThresholdNone);
}

void KisLayerProjectionPlane::applyMaxOutAlpha(KisPainter *painter, const QRect &rect, KritaUtils::ThresholdMode thresholdMode)
{
    applyImpl(painter, rect, thresholdMode);
}

KisPaintDeviceList KisLayerProjectionPlane::getLodCapableDevices() const
{
    return KisPaintDeviceList() << m_d->layer->projection();
}

QRect KisLayerProjectionPlane::needRect(const QRect &rect, KisLayer::PositionToFilthy pos) const
{
    return m_d->layer->needRect(rect, pos);
}

QRect KisLayerProjectionPlane::changeRect(const QRect &rect, KisLayer::PositionToFilthy pos) const
{
    return m_d->layer->changeRect(rect, pos);
}

QRect KisLayerProjectionPlane::accessRect(const QRect &rect, KisLayer::PositionToFilthy pos) const
{
    return m_d->layer->accessRect(rect, pos);
}

QRect KisLayerProjectionPlane::needRectForOriginal(const QRect &rect) const
{
    return m_d->layer->needRectForOriginal(rect);
}

QRect KisLayerProjectionPlane::tightUserVisibleBounds() const
{
    return m_d->layer->tightUserVisibleBounds();
}

QRect KisLayerProjectionPlane::looseUserVisibleBounds() const
{
    return m_d->layer->looseUserVisibleBounds();
}

