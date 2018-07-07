// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2018-2018 The SHIELD Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SHIELD_QT_SHIELDADDRESSVALIDATOR_H
#define SHIELD_QT_SHIELDADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class SHIELDAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit SHIELDAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** SHIELD address widget validator, checks for a valid shield address.
 */
class SHIELDAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit SHIELDAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // SHIELD_QT_SHIELDADDRESSVALIDATOR_H
