// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "../../include/namespace.h"
#include "../../include/daccountstypes.h"
#include <QString>
#include <QDir>
#include <QMimeDatabase>
#include <QList>
#include <QTextStream>
#include <QRegularExpression>

DACCOUNTS_BEGIN_NAMESPACE

struct Dutils
{
    static QString encryptPassword(const QString &password);
    static QList<QByteArray> getImageFromDir(const QDir &dir);
    static QString getUserConfigValue(const QByteArray &username, keyType key);
    static QString getUserConfigKey(keyType type);
    static qint64 setUserConfigValue(const QByteArray &username, keyType key, const QByteArray &value);
    static qint64 getCreatedTimeFromFile(const QString &file);
};

DACCOUNTS_END_NAMESPACE
