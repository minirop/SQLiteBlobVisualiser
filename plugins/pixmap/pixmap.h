#ifndef PIXMAP_H
#define PIXMAP_H

#include "pixmap_global.h"
#include "blobinterface.h"
#include <QVector>

class PIXMAPSHARED_EXPORT Pixmap : public QObject, public BlobInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.various-tools.sqlitebrowser")
    Q_INTERFACES(BlobInterface)

public:
    Pixmap();

    QString name() const;
    QVector<QVariant::Type> supportedTypes() const;
    QVariant process(const QVariant & data);
};

#endif // PIXMAP_H
