// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "daccountstypes.h"
#include <QSharedPointer>
#include "namespace.h"

DACCOUNTS_BEGIN_NAMESPACE

class DAccountsManagerPrivate;
class DAccountsUser;

class DAccountsManager : public QObject
{
    Q_OBJECT

public:
    explicit DAccountsManager(QObject *parent = nullptr);
    ~DAccountsManager() override;

    Q_PROPERTY(QStringList userList READ userList)

    QStringList userList() const;

public slots:

    QSharedPointer<DAccountsUser> createUser(const QString &name, const QString &fullName, AccountTypes type);
    void deleteUser(const QString &name, bool rmFiles);
    QSharedPointer<DAccountsUser> findUserByName(const QString &name);
    QSharedPointer<DAccountsUser> findUserById(qint64 uid);
    QStringList groups();
    QStringList presetGroups(AccountTypes type);
    ValidMsg isPasswordValid(const QString &password);
    ValidMsg isUsernameValid(const QString &name);

signals:
    void UserAdded(QString path);
    void UserDeleted(QString path);

private:
    QScopedPointer<DAccountsManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DAccountsManager)
};

DACCOUNTS_END_NAMESPACE
