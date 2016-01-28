#include "nativegraphicimportdialog.h"
#include "ui_nativegraphicimportdialog.h"

NativeGraphicImportDialog::NativeGraphicImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NativeGraphicImportDialog)
{
    ui->setupUi(this);
}

NativeGraphicImportDialog::~NativeGraphicImportDialog()
{
    delete ui;
}
