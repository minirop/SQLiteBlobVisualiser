#include "base64.h"

Base64::Base64()
{
}

QString Base64::name() const
{
    return QString("base64");
}

QVector<QVariant::Type> Base64::supportedTypes() const
{
    return QVector<QVariant::Type>() << QVariant::ByteArray;
}

QVariant Base64::process(const QVariant & data)
{
    if (!supportedTypes().contains(data.type()))
        return QVariant();

    if (data.type() == QVariant::String)
        return QByteArray::fromBase64(data.toString().toLatin1());
    return QByteArray::fromBase64(data.toByteArray());
}
