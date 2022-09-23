// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daccountsmanager_p.h"

DACCOUNTS_BEGIN_NAMESPACE

DAccountsManagerPrivate::DAccountsManagerPrivate(DAccountsManager *parent)
    : q_ptr(parent)
    , m_dAccountsInter(new DAccountsInterface(this))
    , m_dSystemAccountsInter(new DSystemAccountsInterface(this))
{
}

DAccountsManagerPrivate::~DAccountsManagerPrivate()
{
    delete m_dAccountsInter;
    delete m_dSystemAccountsInter;
}

DACCOUNTS_END_NAMESPACE