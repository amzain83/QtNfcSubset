/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "qndefrecord.h"
#include "qndefrecord_p.h"

#include <QtCore/QHash>

namespace QtMobilitySubset {

/*!
    @class QNdefRecord
    @brief The QNdefRecord class provides an NFC NDEF record.

    @ingroup connectivity-nfc
    @since 1.2

    @xmlonly
    <apigrouping group="Device and Communication/NFC"/>
    @endxmlonly	
	
    QNdefRecord and derived classes are used to parse the contents of
    QNdefMessage NDEF messages and create new NDEF messages.

    Use typeNameFormat(), userTypeNameFormat(), setTypeNameFormat() and setUserTypeNameFormat() to
    get and set the type name format of the NDEF record.

    Use type() and setType() to get and set the type of the NDEF record.

    Use id() and setId() to get and set the id of the NDEF record.

    Use payload() and setPayload() to get and set the NDEF record payload.  isEmpty() can be used
    to test if the payload is empty.

    QNdefRecord is an implicitly shared class.  This means you can efficiently convert between
    QNdefRecord and specialized record classes.  The isRecordType() template function can be used
    to test if a conversion is possible.  The following example shows how to test if a QNdefRecord
    is an NFC RTD Text record and extract the text information from it.

    Specialized NDEF record classes can be easily created with the Q_DECLARE_NDEF_RECORD() and
    Q_DECLARE_ISRECORDTYPE_FOR_NDEF_RECORD() macros.  The following example shows the class
    declaration of the hypothetical @e {example.com:f} record type that encapsulates a single int
    property foo.

    The developer only needs to provide implementations for the @c {foo()} and @c {setFoo()}
    functions that parse and set the contents of the NDEF record's payload.
*/

/*!
    @enum QNdefRecord::TypeNameFormat
    This enum describes the type name format of an NDEF record.
*/

/*!
 *  @var QNdefNfcSmartPosterRecord::TypeNameFormat QNdefRecord::Empty
 *  An empty NDEF record, the record does not contain a payload
 *  @var QNdefNfcSmartPosterRecord::TypeNameFormat QNdefRecord::NfcRtd
 *  The NDEF record type is defined by an NFC RTD Specification
 *  @var QNdefNfcSmartPosterRecord::TypeNameFormat QNdefRecord::Mime
 *  The NDEF record type follows the construct described in RFC 2046
 *  @var QNdefNfcSmartPosterRecord::TypeNameFormat QNdefRecord::Uri
 *  The NDEF record type follows the construct described in RFC 3986
 *  @var QNdefNfcSmartPosterRecord::TypeNameFormat QNdefRecord::ExternalRtd
 *  The NDEF record type follows the construct for external type names described the NFC RTD Specification
 *  @var QNdefNfcSmartPosterRecord::TypeNameFormat QNdefRecord::Unknown
 *  The type of the record is unknown and should be treated similar to content with
 *  MIME type 'application/octet-stream' without further context
 */

/*!
    @fn bool QNdefRecord::isRecordType() const

    Returns true if the NDEF record is of the specified record type; otherwise returns false.
*/

/*!
    @fn bool QNdefRecord::operator!=(const QNdefRecord &other) const

    Returns true if this NDEF record does not equal @a other; otherwise return false.
*/

/*!
    @def Q_DECLARE_NDEF_RECORD(className, typeNameFormat, type, initialPayload)
    @relates QNdefRecord

    This macro declares default and copy constructors for specialized NDEF record classes.

    @a className is the name of the specialized class, @a typeNameFormat is the appropriate
    QNdefRecord::TypeNameFormat for the custom type and @a type is the type without the NID or NSS
    prefixes. That is @e {example.com:f} not @e {urn:nfc:ext:example.com:f}.  @a initialPayload
    is the initial payload of an empty record, it must be a QByteArray or a type that can be
    implicitly converted into a QByteArray.

    See the section on Creating specialized NDEF record classes for details.

    @sa Q_DECLARE_ISRECORDTYPE_FOR_NDEF_RECORD()
*/

/*!
    @def Q_DECLARE_ISRECORDTYPE_FOR_NDEF_RECORD(className, typeNameFormat, type)
    @relates QNdefRecord

    This macro declares a template specialization for the QNdefRecord::isRecordType() function.

    This macro should be used in the header file directly after the definition of a specialized
    NDEF record class.

    @a className is the name of the specialized class, @a typeNameFormat is the appropriate
    QNdefRecord::TypeNameFormat for the custom type and @a type is the type without the NID or NSS
    prefixes.  That is @e {example.com:f} not @e {urn:nfc:ext:example.com:f}.

    See the secton on Creating specialized NDEF record classes for details.

    @sa Q_DECLARE_NDEF_RECORD()
*/

/*!
    Returns a key hash.
*/
uint qHash(const QNdefRecord &key)
{
    return qHash(key.type() + key.id() + key.payload());
}

/*!
    Constructs a new empty NDEF record.
*/
QNdefRecord::QNdefRecord()
{
}

/*!
    Constructs a new NDEF record that is a copy of @a other.
*/
QNdefRecord::QNdefRecord(const QNdefRecord &other)
{
    d = other.d;
}

/*!
    @internal

    @brief Constructs an NDEF record that is a copy of @a other if @a other is of the expected type name
    format identified by @a typeNameFormat and type as identified by @a type. If @a ignoreType is
	set to true, then only @a typeNameFormat is checked before copying; in all other cases an empty
    NDEF record of the expected type name format and type is created.
    
    @param other The NDEF record to copy
    @param typeNameFormat The expected type name format
    @param type The expected type
    @param ignoreType If true, does not take the expected type into account
*/
QNdefRecord::QNdefRecord(const QNdefRecord &other, TypeNameFormat typeNameFormat,
                         const QByteArray &type, bool ignoreType)
{
	if (other.d->typeNameFormat == quint8(typeNameFormat) && (other.d->type == type || ignoreType)) {
        d = other.d;
    } else {
        d = new QNdefRecordPrivate;
        d->typeNameFormat = typeNameFormat;
        d->type = type;
    }
}

/*!
    @internal

    @brief Constructs an NDEF record with a type name format identified by @a typeNameFormat and type as
    identified by @a type.
    @param typeNameFormat The expected type name format
    @param type The expected type
*/
QNdefRecord::QNdefRecord(TypeNameFormat typeNameFormat, const QByteArray &type)
:   d(new QNdefRecordPrivate)
{
    d->typeNameFormat = typeNameFormat;
    d->type = type;
}

/*!
    Destroys the NDEF record.
*/
QNdefRecord::~QNdefRecord()
{
}

/*!
    Assigns this NDEF record to @a other.
*/
QNdefRecord &QNdefRecord::operator=(const QNdefRecord &other)
{
    if (this != &other)
        d = other.d;

    return *this;
}

/*!
    Sets the type name format of the NDEF record to @a typeNameFormat.
*/
void QNdefRecord::setTypeNameFormat(TypeNameFormat typeNameFormat)
{
    if (!d)
        d = new QNdefRecordPrivate;

    d->typeNameFormat = typeNameFormat;
}

/*!
    Returns the type name format of the NDEF record.
*/
QNdefRecord::TypeNameFormat QNdefRecord::typeNameFormat() const
{
    if (!d)
        return Empty;

    if (d->typeNameFormat > 0x05)
        return Unknown;

    return TypeNameFormat(d->typeNameFormat);
}

/*!
    Sets the type of the NDEF record to @a type.
*/
void QNdefRecord::setType(const QByteArray &type)
{
    if (!d)
        d = new QNdefRecordPrivate;

    d->type = type;
}

/*!
    Returns the type of the NDEF record.
*/
QByteArray QNdefRecord::type() const
{
    if (!d)
        return QByteArray();

    return d->type;
}

/*!
    Sets the id of the NDEF record to @a id.
*/
void QNdefRecord::setId(const QByteArray &id)
{
    if (!d)
        d = new QNdefRecordPrivate;

    d->id = id;
}

/*!
    Returns the id of the NDEF record.
*/
QByteArray QNdefRecord::id() const
{
    if (!d)
        return QByteArray();

    return d->id;
}

/*!
    Sets the payload of the NDEF record to @a payload.
*/
void QNdefRecord::setPayload(const QByteArray &payload)
{
    if (!d)
        d = new QNdefRecordPrivate;

    d->payload = payload;
}

/*!
    Returns the payload of the NDEF record.
*/
QByteArray QNdefRecord::payload() const
{
    if (!d)
        return QByteArray();

    return d->payload;
}

/*!
    @return Returns true if the NDEF record contains an empty payload; otherwise return false.

    This is equivalent to calling @c {payload().isEmpty()}.
*/
bool QNdefRecord::isEmpty() const
{
    if (!d)
        return true;

    return d->payload.isEmpty();
}

/*!
    Returns true if @a other and this NDEF record are the same.
*/
bool QNdefRecord::operator==(const QNdefRecord &other) const
{
    if (d == other.d)
        return true;

    if (!d || !other.d)
        return false;

    if (d->typeNameFormat != other.d->typeNameFormat)
        return false;

    if (d->type != other.d->type)
        return false;

    if (d->id != other.d->id)
        return false;

    if (d->payload != other.d->payload)
        return false;

    return true;
}

} // namespace QtMobilitySubset
