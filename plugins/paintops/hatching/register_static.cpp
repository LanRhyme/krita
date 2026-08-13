/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Static registration for the hatchingbrush paintop, callable from external code
 * without QPluginLoader (same pattern as defaultpaintops register_static).
 */

#include <brushengine/kis_paintop_registry.h>
#include <brushengine/kis_paintop_factory.h>
#include <klocalizedstring.h>
#include <kis_simple_paintop_factory.h>
#include "kis_hatching_paintop.h"
#include "kis_hatching_paintop_settings.h"
#include "kis_hatching_paintop_settings_widget.h"

extern "C" __attribute__((visibility("default"))) void krita_register_hatching_paintop()
{
    KisPaintOpRegistry::instance()->add(
        new KisSimplePaintOpFactory<KisHatchingPaintOp, KisHatchingPaintOpSettings, KisHatchingPaintOpSettingsWidget>(
            "hatchingbrush", i18n("Hatching"), KisPaintOpFactory::categoryStable(),
            "krita-hatching.png", QString(), QStringList(), 7));
}
