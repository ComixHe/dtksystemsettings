// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dbus/userinterface.h"
#include "dbus/systemuserinterface.h"

DACCOUNTS_BEGIN_NAMESPACE

class DAccountsUser;

class DAccountsUserPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DAccountsUserPrivate(const QString &path, const QString &systemPath, DAccountsUser *parent = nullptr);
    ~DAccountsUserPrivate() override;

    DAccountsUser *q_ptr;
    DUserInterface *m_dUserInter;
    DSystemUserInterface *m_dSystemUserInter;
    Q_DECLARE_PUBLIC(DAccountsUser)
};

DACCOUNTS_END_NAMESPACE
