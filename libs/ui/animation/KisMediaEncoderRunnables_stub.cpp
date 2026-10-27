/*
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 *  ReveriePaint: Android 构建没有 MLT 与 FFmpeg 开发库, 因此不编译上游的
 *  KisAndroidMediaEncoderRunnable / KisLibavMediaEncoderRunnable 实现 (它们硬包含
 *  mlt++/Mlt.h 与 libav 头), 只在这里提供 KisMediaEncoderWrapper 用到的四个静态
 *  入口的空实现, 让 kritaui 正常链接。
 *
 *  Android 端的 MP4 导出由应用侧 Kotlin MediaCodec 实现, Krita 侧的视频导出入口
 *  在本 fork 里返回空格式列表 + create() 返回 nullptr, 界面上表现为"无可用格式"。
 */

#include "KisAndroidMediaEncoderRunnable.h"
#include "KisLibavMediaEncoderRunnable.h"

KisAndroidMediaEncoderRunnable *
KisAndroidMediaEncoderRunnable::create(const KisMediaEncoderWrapperSettings &, QObject *)
{
    return nullptr;
}

void KisAndroidMediaEncoderRunnable::getSupportedFormats(QVector<KisMediaEncoderFormat *> &)
{
}

KisLibavMediaEncoderRunnable *
KisLibavMediaEncoderRunnable::create(const KisMediaEncoderWrapperSettings &, QObject *)
{
    return nullptr;
}

void KisLibavMediaEncoderRunnable::getSupportedFormats(QVector<KisMediaEncoderFormat *> &)
{
}
