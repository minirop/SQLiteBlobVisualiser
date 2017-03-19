#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "blobinterface.h"
#include "sqlitequerymodel.h"

#include <QMainWindow>
#include <QSqlDatabase>
#include <QListView>
#include <QTableView>
#include <QStringListModel>
#include <QMap>
#include <QVector>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
    MainWindow();

private slots:
    void onOpenDatabase();
    void onTableClicked(const QModelIndex &index);
    void onCellDoubleClicked(const QModelIndex &index);
	
private:
    QSqlDatabase db;
    QListView * tablesView;
    QStringListModel tablesModel;
    QTableView * rowsView;
    SqliteQueryModel queryModel;
    QMap<QString, BlobInterface *> plugins;
    QMap<QString, QVector<QString>> pluginsData;
    void load(QString filename);
};

#endif // MAINWINDOW_H
