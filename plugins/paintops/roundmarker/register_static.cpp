/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Static registration for the roundmarker paintop, callable from external code
 * without QPluginLoader (same pattern as defaultpaintops register_static).
 */

#include <brushengine/kis_paintop_registry.h>
#include <brushengine/kis_paintop_factory.h>
#include <klocalizedstring.h>
#include <kis_simple_paintop_factory.h>
#include "kis_roundmarkerop.h"
#include "kis_roundmarkerop_settings.h"
#include "kis_roundmarkerop_settings_widget.h"

extern "C" __attribute__((visibility("default"))) void krita_register_roundmarker_paintop()
{
    KisPaintOpRegistry::instance()->add(
        new KisSimplePaintOpFactory<KisRoundMarkerOp, KisRoundMarkerOpSettings, KisRoundMarkerOpSettingsWidget>(
            "roundmarker", i18n("Quick Brush"), KisPaintOpFactory::categoryStable(),
            "krita_roundmarkerop.svg", QString(), QStringList(), 3));
}
