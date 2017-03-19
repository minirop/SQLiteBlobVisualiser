#ifndef VARIANTDIALOG_H
#define VARIANTDIALOG_H

#include <QDialog>
#include <QVariant>

/*
 * Dialog that shows the content of the variant
 */
class VariantDialog : public QDialog
{
    Q_OBJECT

public:
    VariantDialog(QVariant variant, QWidget * parent = Q_NULLPTR);
};

#endif // VARIANTDIALOG_H
