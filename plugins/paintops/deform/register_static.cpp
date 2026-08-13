/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Static registration for the deformbrush paintop, callable from external code
 * without QPluginLoader (same pattern as defaultpaintops register_static).
 */

#include <brushengine/kis_paintop_registry.h>
#include <brushengine/kis_paintop_factory.h>
#include <klocalizedstring.h>
#include <kis_simple_paintop_factory.h>
#include <KoCompositeOpRegistry.h>
#include "kis_deform_paintop.h"
#include "kis_deform_paintop_settings.h"
#include "kis_deform_paintop_settings_widget.h"

extern "C" __attribute__((visibility("default"))) void krita_register_deform_paintop()
{
    KisPaintOpRegistry::instance()->add(
        new KisSimplePaintOpFactory<KisDeformPaintOp, KisDeformPaintOpSettings, KisDeformPaintOpSettingsWidget>(
            "deformbrush", i18n("Deform"), KisPaintOpFactory::categoryStable(),
            "krita-deform.png", QString(), QStringList(COMPOSITE_COPY), 16));
}
