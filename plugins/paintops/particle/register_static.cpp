/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Static registration for the particlebrush paintop, callable from external code
 * without QPluginLoader (same pattern as defaultpaintops register_static).
 */

#include <brushengine/kis_paintop_registry.h>
#include <brushengine/kis_paintop_factory.h>
#include <klocalizedstring.h>
#include <kis_simple_paintop_factory.h>
#include "kis_particle_paintop.h"
#include "kis_particle_paintop_settings.h"
#include "kis_particle_paintop_settings_widget.h"

extern "C" __attribute__((visibility("default"))) void krita_register_particle_paintop()
{
    KisPaintOpRegistry::instance()->add(
        new KisSimplePaintOpFactory<KisParticlePaintOp, KisParticlePaintOpSettings, KisParticlePaintOpSettingsWidget>(
            "particlebrush", i18n("Particle"), KisPaintOpFactory::categoryStable(),
            "krita-particle.png", QString(), QStringList(), 11));
}
