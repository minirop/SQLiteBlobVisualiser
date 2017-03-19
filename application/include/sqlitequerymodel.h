#ifndef SQLITEQUERYMODEL
#define SQLITEQUERYMODEL

#include <QSqlQueryModel>
/*
 * Custom model that shows "BLOB" when the field is a blob and not its content.
 */
class SqliteQueryModel : public QSqlQueryModel
{
public:
    QVariant data(const QModelIndex & item, int role = Qt::DisplayRole) const;

protected:
    void queryChange();

private:
    QVector<int> blobFields;
};

#endif // SQLITEQUERYMODEL
