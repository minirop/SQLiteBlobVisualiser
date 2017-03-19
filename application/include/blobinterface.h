#ifndef BLOBINTERFACE_H
#define BLOBINTERFACE_H

#include <QString>
#include <QByteArray>
#include <QtPlugin>
#include <QMetaType>
#include <QVariant>

/*
 * Interface for how to "process" BLOB fields
 */
class BlobInterface
{
public:
    virtual ~BlobInterface() {}

    /*
     * name of the plugin, used in plugins.ini
     */
    virtual QString name() const = 0;

    /*
     * List of types that plugin can handle
     */
    virtual QVector<QVariant::Type> supportedTypes() const = 0;

    /*
     * The processing method
     */
    virtual QVariant process(const QVariant &) = 0;
};

Q_DECLARE_INTERFACE(BlobInterface, "com.various-tools.sqlitebrowser")

#endif // BLOBINTERFACE_H
