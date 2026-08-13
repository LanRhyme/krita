/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Static registration for the hairybrush paintop, callable from external code
 * without QPluginLoader (same pattern as defaultpaintops register_static).
 */

#include <brushengine/kis_paintop_registry.h>
#include <brushengine/kis_paintop_factory.h>
#include <klocalizedstring.h>
#include <kis_simple_paintop_factory.h>
#include "kis_hairy_paintop.h"
#include "kis_hairy_paintop_settings.h"
#include "kis_hairy_paintop_settings_widget.h"

extern "C" __attribute__((visibility("default"))) void krita_register_hairy_paintop()
{
    KisPaintOpRegistry::instance()->add(
        new KisSimplePaintOpFactory<KisHairyPaintOp, KisHairyPaintOpSettings, KisHairyPaintOpSettingsWidget>(
            "hairybrush", i18n("Bristle"), KisPaintOpFactory::categoryStable(),
            "krita-sumi.png", QString(), QStringList(), 4));
}
