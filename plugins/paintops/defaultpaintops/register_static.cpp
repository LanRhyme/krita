/*
 * SPDX-FileCopyrightText: 2026 ReveriePaint
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Static registration for the default paintop factories, callable from
 * external code (ReveriePaint) without going through QPluginLoader.
 * Instantiating KisSimplePaintOpFactory inside this library keeps the
 * vtable layout identical to libkritaimage's view of KisPaintOpFactory.
 */

#include "kritadefaultpaintops_export.h"

#include <brushengine/kis_paintop_registry.h>
#include <brushengine/kis_paintop_factory.h>
#include <kis_simple_paintop_factory.h>
#include <klocalizedstring.h>
#include <KoCompositeOpRegistry.h>

#include "brush/kis_brushop.h"
#include "brush/KisBrushOpSettings.h"
#include "brush/kis_brushop_settings_widget.h"
#include "duplicate/kis_duplicateop.h"
#include "duplicate/kis_duplicateop_settings.h"
#include "duplicate/kis_duplicateop_settings_widget.h"

extern "C" KRITADEFAULTPAINTOPS_EXPORT void krita_register_default_paintops()
{
    KisPaintOpRegistry *r = KisPaintOpRegistry::instance();
    r->add(new KisSimplePaintOpFactory<KisBrushOp, KisBrushOpSettings, KisBrushOpSettingsWidget>(
        "paintbrush", i18nc("Pixel paintbrush", "Pixel"), KisPaintOpFactory::categoryStable(),
        "krita-paintbrush.png", QString(), QStringList(), 1));
    r->add(new KisSimplePaintOpFactory<KisDuplicateOp, KisDuplicateOpSettings, KisDuplicateOpSettingsWidget>(
        "duplicate", i18nc("clone paintbrush (previously \"Duplicate\")", "Clone"),
        KisPaintOpFactory::categoryStable(), "krita-duplicate.png", QString(),
        QStringList(COMPOSITE_COPY), 15));
}
