/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Static registration for the spraybrush paintop, callable from external code
 * without QPluginLoader (same pattern as defaultpaintops register_static).
 */

#include <brushengine/kis_paintop_registry.h>
#include <brushengine/kis_paintop_factory.h>
#include <klocalizedstring.h>
#include <kis_simple_paintop_factory.h>
#include "kis_spray_paintop.h"
#include "kis_spray_paintop_settings.h"
#include "kis_spray_paintop_settings_widget.h"

extern "C" __attribute__((visibility("default"))) void krita_register_spray_paintop()
{
    KisPaintOpRegistry::instance()->add(
        new KisSimplePaintOpFactory<KisSprayPaintOp, KisSprayPaintOpSettings, KisSprayPaintOpSettingsWidget>(
            "spraybrush", i18n("Spray"), KisPaintOpFactory::categoryStable(),
            "krita-spray.png", QString(), QStringList(), 6));
}
