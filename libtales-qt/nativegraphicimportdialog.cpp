#include "nativegraphicimportdialog.h"
#include "ui_nativegraphicimportdialog.h"
#include "talesqtstatevar.h"
#include <QFileDialog>

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

void NativeGraphicImportDialog::on_importButton_clicked(bool checked)
{
    QString filepath =
            QFileDialog::getExistingDirectory(
                this,
                "Choose import directory");

    if (filepath.compare("") == 0) {
        return;
    }

    if (ui->rawTilesButton->isChecked()) {
        appState_.editor().graphicsEditor().importAllTiles(
                    filepath.toStdString() + "/");
    }

    if (ui->mappingsButton->isChecked()) {
        appState_.editor().graphicsEditor().importAllMappings(
                    filepath.toStdString() + "/");
    }
}
