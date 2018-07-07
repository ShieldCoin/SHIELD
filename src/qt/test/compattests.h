// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2018-2018 The SHIELD Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SHIELD_QT_TEST_COMPATTESTS_H
#define SHIELD_QT_TEST_COMPATTESTS_H

#include <QObject>
#include <QTest>

class CompatTests : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void bswapTests();
};

#endif // SHIELD_QT_TEST_COMPATTESTS_H
