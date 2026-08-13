/*
 * SPDX-FileCopyrightText: 2026 ReveriePaint
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Static registration for the colorsmudge paintop, callable from external
 * code without QPluginLoader (same pattern as defaultpaintops).
 */

#include <brushengine/kis_paintop_registry.h>
#include <brushengine/kis_paintop_factory.h>
#include <klocalizedstring.h>
#include <kis_simple_paintop_factory.h>

#include "kis_colorsmudgeop.h"
#include "kis_colorsmudgeop_settings.h"
#include "kis_colorsmudgeop_settings_widget.h"

extern "C" __attribute__((visibility("default"))) void krita_register_colorsmudge_paintop()
{
    KisPaintOpRegistry::instance()->add(
        new KisSimplePaintOpFactory<KisColorSmudgeOp, KisColorSmudgeOpSettings, KisColorSmudgeOpSettingsWidget>(
            "colorsmudge", i18n("Color Smudge"), KisPaintOpFactory::categoryStable(),
            "krita-colorsmudge.png", QString(), QStringList(), 2));
}
