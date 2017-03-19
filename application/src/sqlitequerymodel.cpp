#include "sqlitequerymodel.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QModelIndex>

QVariant SqliteQueryModel::data(const QModelIndex & item, int role) const
{
    if (item.isValid() && role == Qt::DisplayRole)
    {
        QSqlField field = record(item.row()).field(item.column());
        if (field.isNull())
        {
            return QString("NULL");
        }
        else
        {
            if (blobFields.contains(item.column()))
            {
                return QString("BLOB");
            }
        }
    }
    return QSqlQueryModel::data(item, role);
}

void SqliteQueryModel::queryChange()
{
    QSqlRecord rec = record();

    for (int i = 0;i < rec.count();i++)
    {
        if (rec.field(i).type() == QVariant::ByteArray)
        {
            blobFields.push_back(i);
        }
    }
}
