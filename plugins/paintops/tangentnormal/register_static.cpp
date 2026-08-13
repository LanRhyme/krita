/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Static registration for the tangentnormal paintop, callable from external code
 * without QPluginLoader (same pattern as defaultpaintops register_static).
 */

#include <brushengine/kis_paintop_registry.h>
#include <brushengine/kis_paintop_factory.h>
#include <klocalizedstring.h>
#include <kis_simple_paintop_factory.h>
#include <kis_brush_based_paintop_settings.h>
#include "kis_tangent_normal_paintop.h"
#include "kis_tangent_normal_paintop_settings_widget.h"

extern "C" __attribute__((visibility("default"))) void krita_register_tangentnormal_paintop()
{
    KisPaintOpRegistry::instance()->add(
        new KisSimplePaintOpFactory<KisTangentNormalPaintOp, KisBrushBasedPaintOpSettings, KisTangentNormalPaintOpSettingsWidget>(
            "tangentnormal", i18n("Tangent Normal"), KisPaintOpFactory::categoryStable(),
            "krita-tangentnormal.png", QString(), QStringList(), 16));
}
