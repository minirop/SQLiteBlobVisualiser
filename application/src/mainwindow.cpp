#include "mainwindow.h"
#include "variantdialog.h"
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QSqlRecord>
#include <QSqlField>
#include <QSettings>
#include <QApplication>
#include <QPluginLoader>

MainWindow::MainWindow()
{
	// CREATE MENUS
	QMenu * fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction("&Open Database", this, SLOT(onOpenDatabase()), QKeySequence::Open);

    // CREATE WIDGETS
    QWidget * widget = new QWidget(this);
    QHBoxLayout * layout = new QHBoxLayout(widget);

    tablesView = new QListView(this);
    tablesView->setEditTriggers(QListView::NoEditTriggers);
    connect(tablesView, &QListView::doubleClicked, this, &MainWindow::onTableClicked);
    tablesView->setModel(&tablesModel);
    layout->addWidget(tablesView);

    rowsView = new QTableView(this);
    connect(rowsView, &QTableView::doubleClicked, this, &MainWindow::onCellDoubleClicked);
    layout->addWidget(rowsView, 1);

    setCentralWidget(widget);

    // LOAD PLUGINS
    QDir pluginsDir(qApp->applicationDirPath() + "/plugins");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files | QDir::NoSymLinks))
    {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin)
        {
            BlobInterface * iBlob = qobject_cast<BlobInterface *>(plugin);
            if (iBlob)
            {
                // skip plugins that support nothing.
                if (iBlob->supportedTypes().size() > 0)
                {
                    QString name = iBlob->name();

                    if (!plugins.contains(name))
                    {
                        plugins[name] = iBlob;
                    }
                    else
                    {
                        QMessageBox::warning(this, "Duplicate plugin", QString("There is already a plugin with the name '%1'. Skipping this one.").arg(name));
                    }
                }
            }
        }
    }

    // LOAD SETTINGS
    QSettings settings(qApp->applicationDirPath() + "/plugins.ini", QSettings::IniFormat);
    foreach(QString table, settings.childGroups())
    {
        settings.beginGroup(table);

        foreach(QString field, settings.allKeys())
        {
            foreach (QString type, settings.value(field).toStringList())
            {
                pluginsData[QString("%1/%2").arg(table).arg(field)].push_back(type);
            }
        }

        settings.endGroup();
    }
}

void MainWindow::load(QString filename)
{
    if (QFile::exists(filename))
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setConnectOptions("QSQLITE_OPEN_READONLY=1");
        db.setDatabaseName(filename);
        if (!db.open())
        {
            QMessageBox::critical(this, "Error", QString("Can't open '%1'.").arg(filename));
        }

        tablesModel.setStringList(db.tables());
        rowsView->setModel(nullptr);
    }
    else
    {
        QMessageBox::critical(this, "Error", QString("'%1' does not seem to exist.").arg(filename));
    }
}

void MainWindow::onOpenDatabase()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open a database...", QString(), "SQLite (*.db)");
    if (!filename.isEmpty())
    {
        load(filename);
    }
}

void MainWindow::onTableClicked(const QModelIndex &index)
{
    QString table = tablesModel.data(index, Qt::DisplayRole).toString();
    QString queryString = QString("SELECT * FROM %1").arg(table);
    queryModel.setQuery(queryString);
    rowsView->setModel(&queryModel);
}

void MainWindow::onCellDoubleClicked(const QModelIndex &index)
{
    QSqlRecord rec = queryModel.record(index.row());
    QSqlField field = rec.field(index.column());
    QString name = field.name();
    if (field.isNull())
    {
        QMessageBox::information(this, "No preview", QString("The field '%1' is NULL.").arg(name));
        return;
    }

    QVariant varData = field.value();

    if (field.type() == QVariant::ByteArray)
    {
        if (varData.type() != QVariant::ByteArray)
        {
            // by default, get byte array for blob fields (instead of string)
            varData = varData.toByteArray();
        }

        QModelIndex tableIndex  = tablesView->currentIndex();
        QString tableName = tablesModel.data(tableIndex, Qt::DisplayRole).toString();
        QString fullName = QString("%1/%2").arg(tableName).arg(name);

        if (pluginsData.contains(fullName))
        {
            foreach (QString pluginName, pluginsData[fullName])
            {
                if (plugins.contains(pluginName))
                {
                    BlobInterface * blobInt = plugins[pluginName];
                    QVector<QVariant::Type> supported = blobInt->supportedTypes();
                    if (supported.contains(varData.type()))
                    {
                        varData = blobInt->process(varData);
                    }
                    else
                    {
                        QStringList expectedList;
                        foreach (QVariant::Type t, supported)
                        {
                            expectedList += QString("'%1'").arg(QVariant::typeToName(t));
                        }

                        QString txt = expectedList.join(", ");
                        if (expectedList.size() > 1)
                        {
                            txt = QString("one of ") + txt;
                        }

                        QMessageBox::information(this, "invalid data", QString("the plugin '%1' does not accept '%2', he accepts %3.").arg(pluginName).arg(QVariant::typeToName(varData.type())).arg(txt));
                        return;
                    }
                }
                else
                {
                    QMessageBox::information(this, "invalid plugin", QString("the plugin '%1' does not exist.").arg(pluginName));
                    return;
                }
            }
        }
        else
        {
            QMessageBox::information(this, "missing plugin", "plugin does NOT exist for this field");
            return;
        }
    }

    VariantDialog dial(varData, this);
    dial.setWindowTitle(QString("Field: '%1'").arg(name));
    dial.exec();
}
