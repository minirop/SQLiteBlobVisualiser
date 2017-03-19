#include "variantdialog.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QTimer>
#include <QLabel>

VariantDialog::VariantDialog(QVariant variant, QWidget * parent) : QDialog(parent)
{
    QVBoxLayout * layout = new QVBoxLayout(this);

    QWidget * widget = nullptr;
    switch (variant.type())
    {
    case QVariant::String:
    case QVariant::ByteArray:
    case QVariant::LongLong:
    case QVariant::Double:
        widget = new QLabel(variant.toString(), this);
        break;
    case QVariant::Pixmap:
    {
        QLabel * picLabel = new QLabel(this);
        picLabel->setPixmap(qvariant_cast<QPixmap>(variant));
        widget = picLabel;
        break;
    }
    default:
        QMessageBox::critical(parent, "Unhandled type", QString("Can't render '%1'").arg(QVariant::typeToName(variant.type())));
        QTimer::singleShot(0, this, SLOT(accept()));
        return;
    }

    QDialogButtonBox * dbb = new QDialogButtonBox(this);
    connect(dbb, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(dbb, &QDialogButtonBox::rejected, this, &QDialog::reject);
    dbb->addButton(QDialogButtonBox::Close);

    layout->addWidget(widget);
    layout->addWidget(dbb);
}
