#ifndef QNDEFNFCSMARTPOSTERRECORD_P_H
#define QNDEFNFCSMARTPOSTERRECORD_P_H

namespace QtMobilitySubset {

#define Q_DECLARE_ISRECORDTYPE_FOR_MIME_NDEF_RECORD(className) \
    template<> inline bool QNdefRecord::isRecordType<className>() const\
    { \
        return (typeNameFormat() == QNdefRecord::Mime); \
    }

#define Q_DECLARE_MIME_NDEF_RECORD(className, initialPayload) \
    className() : QNdefRecord(QNdefRecord::Mime, "") { setPayload(initialPayload); } \
    className(const QNdefRecord &other) : QNdefRecord(other, QNdefRecord::Mime, "", true) { }
	
class QNdefNfcActRecord : public QNdefRecord
{
public:
    Q_DECLARE_NDEF_RECORD(QNdefNfcActRecord, QNdefRecord::NfcRtd, "act", QByteArray(0, char(0)))

    void setAction(QNdefNfcSmartPosterRecord::ActionValue actionValue);
    QNdefNfcSmartPosterRecord::ActionValue action() const;
};

Q_DECLARE_ISRECORDTYPE_FOR_NDEF_RECORD(QNdefNfcActRecord, QNdefRecord::NfcRtd, "act")

class QNdefNfcIconRecord : public QNdefRecord
{
public:
    Q_DECLARE_MIME_NDEF_RECORD(QNdefNfcIconRecord, QByteArray(0, char(0)))

    void setData(const QByteArray& data);
    QByteArray data() const;
};

Q_DECLARE_ISRECORDTYPE_FOR_MIME_NDEF_RECORD(QNdefNfcIconRecord)

class QNdefNfcSizeRecord : public QNdefRecord
{
public:
    Q_DECLARE_NDEF_RECORD(QNdefNfcSizeRecord, QNdefRecord::NfcRtd, "s", QByteArray(0, char(0)))

    void setSize(quint32 size);
    quint32 size() const;
};

Q_DECLARE_ISRECORDTYPE_FOR_NDEF_RECORD(QNdefNfcSizeRecord, QNdefRecord::NfcRtd, "s")

class QNdefNfcTypeRecord : public QNdefRecord
{
public:
    Q_DECLARE_NDEF_RECORD(QNdefNfcTypeRecord, QNdefRecord::NfcRtd, "t", QByteArray(0, char(0)))

    void setTypeInfo(const QByteArray &type);
    QByteArray typeInfo() const;
};

Q_DECLARE_ISRECORDTYPE_FOR_NDEF_RECORD(QNdefNfcTypeRecord, QNdefRecord::NfcRtd, "t")

} // namespace QtMobilitySubset

#endif // QNDEFNFCSMARTPOSTERRECORD_P_H
