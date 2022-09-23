// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "systemuserinterface.h"

DACCOUNTS_BEGIN_NAMESPACE

DSystemUserInterface::DSystemUserInterface(const QString &path, QObject *parent)
    : QObject(parent)
{
    const QString &Service = QStringLiteral("com.deepin.daemon.Accounts");
    const QString &Interface = QStringLiteral("com.deepin.daemon.Accounts.User");

    ReminderInfo_p::registerMetaType();

    m_inter.reset(new DDBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this));
};

bool DSystemUserInterface::automaticLogin() const
{
    return qdbus_cast<bool>(m_inter->property("AutomaticLogin"));
}

bool DSystemUserInterface::noPasswdLogin() const
{
    return qdbus_cast<bool>(m_inter->property("NoPasswdLogin"));
}

qint32 DSystemUserInterface::accountType() const
{
    return qdbus_cast<qint32>(m_inter->property("AccountType"));
}

qint32 DSystemUserInterface::maxPasswordAge() const
{
    return qdbus_cast<qint32>(m_inter->property("MaxPasswordAge"));
}

QStringList DSystemUserInterface::iconList() const
{
    return qdbus_cast<QStringList>(m_inter->property("IconList"));
}

QStringList DSystemUserInterface::historyLayout() const
{
    return qdbus_cast<QStringList>(m_inter->property("HistoryLayout"));
}

QStringList DSystemUserInterface::groups() const
{
    return qdbus_cast<QStringList>(m_inter->property("Groups"));
}

QString DSystemUserInterface::iconFile() const
{
    return qdbus_cast<QString>(m_inter->property("IconFile"));
}

QString DSystemUserInterface::layout() const
{
    return qdbus_cast<QString>(m_inter->property("Layout"));
}

QString DSystemUserInterface::locale() const
{
    return qdbus_cast<QString>(m_inter->property("Locale"));
}

QString DSystemUserInterface::passwordHint() const
{
    return qdbus_cast<QString>(m_inter->property("PasswordHint"));
}

QDBusPendingReply<ReminderInfo_p> DSystemUserInterface::getReminderInfo() const
{
    return m_inter->asyncCall("GetReminderinfo");
}

QDBusPendingReply<QList<qint32>> DSystemUserInterface::getSecretQuestions() const
{
    return m_inter->asyncCall("GetSecretQuestions");
}

QDBusPendingReply<void> DSystemUserInterface::addGroup(const QString &group)
{
    return m_inter->asyncCallWithArgumentList("AddGroup", {QVariant::fromValue(group)});
}

QDBusPendingReply<void> DSystemUserInterface::deleteGroup(const QString &group)
{
    return m_inter->asyncCallWithArgumentList("DeleteGroup", {QVariant::fromValue(group)});
}

QDBusPendingReply<void> DSystemUserInterface::deleteIconFile(const QString &icon)
{
    return m_inter->asyncCallWithArgumentList("DeleteIconFile", {QVariant::fromValue(icon)});
}

QDBusPendingReply<void> DSystemUserInterface::enableNoPasswdLogin(const bool enabled)
{
    return m_inter->asyncCallWithArgumentList("EnableNoPasswdLogin", {QVariant::fromValue(enabled)});
}

QDBusPendingReply<void> DSystemUserInterface::setAutomaticLogin(const bool enabled)
{
    return m_inter->asyncCallWithArgumentList("SetAutomaticLogin", {QVariant::fromValue(enabled)});
}

QDBusPendingReply<void> DSystemUserInterface::setHistoryLayout(const QStringList &list)
{
    return m_inter->asyncCallWithArgumentList("SetHistoryLayout", {QVariant::fromValue(list)});
}

QDBusPendingReply<void> DSystemUserInterface::setIconFile(const QString &iconURI)
{
    return m_inter->asyncCallWithArgumentList("SetIconFile", {QVariant::fromValue(iconURI)});
}

QDBusPendingReply<void> DSystemUserInterface::setLayout(const QString &layout)
{
    return m_inter->asyncCallWithArgumentList("SetLayout", {QVariant::fromValue(layout)});
}

QDBusPendingReply<void> DSystemUserInterface::setGroups(const QStringList &groups)
{
    return m_inter->asyncCallWithArgumentList("SetGroups", {QVariant::fromValue(groups)});
}

QDBusPendingReply<void> DSystemUserInterface::setLocale(const QString &locale)
{
    return m_inter->asyncCallWithArgumentList("SetLocale", {QVariant::fromValue(locale)});
}

QDBusPendingReply<void> DSystemUserInterface::setMaxPasswordAge(qint32 nDays)
{
    return m_inter->asyncCallWithArgumentList("SetPasswordAge", {QVariant::fromValue(nDays)});
}

QDBusPendingReply<void> DSystemUserInterface::setPassword(const QString &password)
{
    return m_inter->asyncCallWithArgumentList("SetPassword", {QVariant::fromValue(password)});
}

QDBusPendingReply<void> DSystemUserInterface::setPasswordHint(const QString &hint)
{
    return m_inter->asyncCallWithArgumentList("SetPasswordHint", {QVariant::fromValue(hint)});
}

QDBusPendingReply<void> DSystemUserInterface::setSecretQuestions(const QMap<qint32, QByteArray> &list)
{
    return m_inter->asyncCallWithArgumentList("SetSecretQuestions", {QVariant::fromValue(list)});
}

QDBusPendingReply<QList<qint32>> DSystemUserInterface::verifySecretQuestions(const QMap<qint32, QString> &anwsers)
{
    return m_inter->asyncCallWithArgumentList("VerifySecretQuestions", {QVariant::fromValue(anwsers)});
}
DACCOUNTS_END_NAMESPACE
