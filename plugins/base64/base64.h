#ifndef BASE64_H
#define BASE64_H

#include "base64_global.h"
#include "blobinterface.h"
#include <QVector>

class BASE64SHARED_EXPORT Pixmap : public QObject, public BlobInterface
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

#endif // BASE64_H
