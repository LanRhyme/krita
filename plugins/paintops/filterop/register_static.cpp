/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Static registration for the filter paintop, callable from external code
 * without QPluginLoader (same pattern as defaultpaintops register_static).
 */

#include <brushengine/kis_paintop_registry.h>
#include <brushengine/kis_paintop_factory.h>
#include <klocalizedstring.h>
#include <kis_simple_paintop_factory.h>
#include <KoCompositeOpRegistry.h>
#include "kis_filterop.h"
#include "kis_filterop_settings.h"
#include "kis_filterop_settings_widget.h"

extern "C" __attribute__((visibility("default"))) void krita_register_filter_paintop()
{
    QStringList whiteList;
    whiteList << COMPOSITE_COPY;
    KisPaintOpRegistry::instance()->add(
        new KisSimplePaintOpFactory<KisFilterOp, KisFilterOpSettings, KisFilterOpSettingsWidget>(
            "filter", i18n("Filter"), KisPaintOpFactory::categoryStable(),
            "krita-filterop.png", QString(), whiteList, 17));
}
