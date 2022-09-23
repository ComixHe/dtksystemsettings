// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daccountsuser_p.h"

DACCOUNTS_BEGIN_NAMESPACE

DAccountsUserPrivate::DAccountsUserPrivate(const QString &path, const QString &systemPath, DAccountsUser *parent)
    : q_ptr(parent)
    , m_dUserInter(new DUserInterface(path, this))
    , m_dSystemUserInter(new DSystemUserInterface(systemPath, this))
{
}

DAccountsUserPrivate::~DAccountsUserPrivate()
{
    delete m_dUserInter;
    delete m_dSystemUserInter;
}

DACCOUNTS_END_NAMESPACE
