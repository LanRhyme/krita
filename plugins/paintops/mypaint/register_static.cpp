/*
 * SPDX-FileCopyrightText: 2026 ReveriePaint
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Static registration for the mypaint paintop, callable from external
 * code without QPluginLoader (same pattern as defaultpaintops).
 */

#include <brushengine/kis_paintop_registry.h>
#include <klocalizedstring.h>
#include <KisResourceLoader.h>
#include <KisResourceLoaderRegistry.h>

#include "MyPaintPaintOpFactory.h"
#include "MyPaintPaintOpPreset.h"
#include "MyPaintSensorPack.h"

extern "C" __attribute__((visibility("default"))) void krita_register_mypaint_paintop()
{
    initMyPaintSensors();
    KisResourceLoaderRegistry::instance()->registerLoader(
        new KisResourceLoader<KisMyPaintPaintOpPreset>(
            ResourceSubType::MyPaintPaintOpPresets,
            ResourceType::PaintOpPresets,
            i18n("MyPaint Brush Presets"),
            QStringList() << "application/x-mypaint-brush"));
    KisPaintOpRegistry::instance()->add(new KisMyPaintOpFactory());
}

extern "C" __attribute__((visibility("default"))) KisPaintOpPreset* krita_create_mypaint_preset(const QString &fileName)
{
    return new KisMyPaintPaintOpPreset(fileName);
}
