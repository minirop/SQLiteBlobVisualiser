#include "pixmap.h"
#include <QPixmap>

Pixmap::Pixmap()
{
}

QString Pixmap::name() const
{
    return QString("picture");
}

QVector<QVariant::Type> Pixmap::supportedTypes() const
{
    return QVector<QVariant::Type>() << QVariant::ByteArray;
}

QVariant Pixmap::process(const QVariant & data)
{
    if (!supportedTypes().contains(data.type()))
        return QVariant();

    QPixmap pix;
    pix.loadFromData(data.toByteArray());
    return pix;
}
