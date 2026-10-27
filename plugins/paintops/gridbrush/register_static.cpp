/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Static registration for the gridbrush paintop, callable from external code
 * without QPluginLoader (same pattern as defaultpaintops register_static).
 */

#include <brushengine/kis_paintop_registry.h>
#include <brushengine/kis_paintop_factory.h>
#include <klocalizedstring.h>
#include <kis_simple_paintop_factory.h>
#include "kis_grid_paintop.h"
#include "kis_grid_paintop_settings.h"
#include "kis_grid_paintop_settings_widget.h"

extern "C" __attribute__((visibility("default"))) void krita_register_grid_paintop()
{
    KisPaintOpRegistry::instance()->add(
        new KisSimplePaintOpFactory<KisGridPaintOp, KisGridPaintOpSettings, KisGridPaintOpSettingsWidget>(
            "gridbrush", i18n("Grid"), KisPaintOpFactory::categoryStable(),
            "krita-grid.png", QString(), QStringList(), 8));
}
