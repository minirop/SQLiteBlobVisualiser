#include "base64.h"

Pixmap::Pixmap()
{
}

QString Pixmap::name() const
{
    return QString("base64");
}

QVector<QVariant::Type> Pixmap::supportedTypes() const
{
    return QVector<QVariant::Type>() << QVariant::ByteArray;
}

QVariant Pixmap::process(const QVariant & data)
{
    if (!supportedTypes().contains(data.type()))
        return QVariant();

    return QByteArray::fromBase64(data.toByteArray());
}
