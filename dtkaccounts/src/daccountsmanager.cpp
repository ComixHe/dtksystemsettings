// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "../include/daccountsmanager.h"
#include "daccountsmanager_p.h"
#include "daccountsuser.h"
#include <qdebug.h>
#include <grp.h>

DACCOUNTS_BEGIN_NAMESPACE

DAccountsManager::DAccountsManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DAccountsManagerPrivate(this))
{
    Q_D(const DAccountsManager);
    connect(d->m_dSystemAccountsInter, &DSystemAccountsInterface::ReceivedUserAdded, this, [this](QString user) {
        emit this->UserAdded(std::move(user));
    });
    connect(d->m_dSystemAccountsInter, &DSystemAccountsInterface::ReceivedUserDeleted, this, [this](QString user) {
        emit this->UserDeleted(std::move(user));
    });
}

QStringList DAccountsManager::userList() const
{
    Q_D(const DAccountsManager);
    QStringList list;
    auto reply = d->m_dAccountsInter->listCachedUsers();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return list;
    }
    for (const auto &user : reply.value())
        list.push_back(user.path());
    return list;
}

QSharedPointer<DAccountsUser> DAccountsManager::createUser(const QString &name, const QString &fullName, AccountTypes type)
{
    Q_D(const DAccountsManager);
    auto reply = d->m_dSystemAccountsInter->createUser(name, fullName, static_cast<qint32>(type));
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return nullptr;
    }
    const auto &user = *(reply.value().path().split("/").cend());
    QSharedPointer<DAccountsUser> ptr(new DAccountsUser("/org/freedesktop/Accounts/" + user, reply.value().path(), nullptr));
    return ptr;
}

void DAccountsManager::deleteUser(const QString &name, bool rmFiles)
{
    Q_D(const DAccountsManager);
    auto reply = d->m_dSystemAccountsInter->deleteUser(name, rmFiles);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

QSharedPointer<DAccountsUser> DAccountsManager::findUserByName(const QString &name)
{
    Q_D(const DAccountsManager);
    auto reply = d->m_dAccountsInter->findUserByName(name);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return nullptr;
    }
    const auto &user = *(reply.value().path().split("/").cend());
    QSharedPointer<DAccountsUser> ptr(new DAccountsUser(reply.value().path(), "/com/deepin/daemon/" + user, nullptr));
    return ptr;
}

QSharedPointer<DAccountsUser> DAccountsManager::findUserById(qint64 uid)
{
    Q_D(const DAccountsManager);
    auto reply = d->m_dAccountsInter->findUserById(uid);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return nullptr;
    }
    const auto &user = *(reply.value().path().split("/").cend());
    QSharedPointer<DAccountsUser> ptr(new DAccountsUser(reply.value().path(), "/com/deepin/daemon/" + user, nullptr));
    return ptr;
}

QStringList DAccountsManager::groups()
{
    QStringList list;
    struct group *grp = nullptr;
    errno = 0;
    while ((grp = getgrent()) != nullptr)
        list.push_back(grp->gr_name);
    if (errno != 0) {
        list.clear();
        qWarning() << strerror(errno);
    }
    endgrent();
    return list;
}

QStringList DAccountsManager::presetGroups(AccountTypes type)
{
    Q_D(const DAccountsManager);
    auto reply = d->m_dSystemAccountsInter->getPresetGroups(static_cast<qint32>(type));
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value();
}

ValidMsg DAccountsManager::isPasswordValid(const QString &password)
{
    Q_D(const DAccountsManager);
    ValidMsg msg;
    auto reply = d->m_dSystemAccountsInter->isPasswordValid(password);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return msg;
    }
    const auto &valid = reply.argumentAt(0);
    if (valid.isNull()) {
        qWarning() << "can't get ValidMsg: valid is null";
        return msg;
    }
    msg.valid = valid.toBool();

    const auto &errmsg = reply.argumentAt(1);
    if (errmsg.isNull()) {
        qWarning() << "can't get ValidMsg: errmsg is null";
        return msg;
    }
    msg.msg = errmsg.toString();

    const auto &errcode = reply.argumentAt(2);
    if (errcode.isNull()) {
        qWarning() << "can't get ValidMsg: errcode is null";
        return msg;
    }
    msg.code = errcode.toInt();

    return msg;
}

ValidMsg DAccountsManager::isUsernameValid(const QString &username)
{
    Q_D(const DAccountsManager);
    ValidMsg msg;
    auto reply = d->m_dSystemAccountsInter->isUsernameValid(username);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return msg;
    }
    const auto &valid = reply.argumentAt(0);
    if (valid.isNull()) {
        qWarning() << "can't get ValidMsg: valid is null";
        return msg;
    }
    msg.valid = valid.toBool();

    const auto &errmsg = reply.argumentAt(1);
    if (errmsg.isNull()) {
        qWarning() << "can't get ValidMsg: errmsg is null";
        return msg;
    }
    msg.msg = errmsg.toString();

    const auto &errcode = reply.argumentAt(2);
    if (errcode.isNull()) {
        qWarning() << "can't get ValidMsg: errcode is null";
        return msg;
    }
    msg.code = errcode.toInt();

    return msg;
}

DACCOUNTS_END_NAMESPACE
