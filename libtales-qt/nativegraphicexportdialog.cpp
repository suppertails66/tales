#include "nativegraphicexportdialog.h"
#include "ui_nativegraphicexportdialog.h"
#include "talesqtstatevar.h"
#include <QFileDialog>

NativeGraphicExportDialog::NativeGraphicExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NativeGraphicExportDialog)
{
    ui->setupUi(this);
}

NativeGraphicExportDialog::~NativeGraphicExportDialog()
{
    delete ui;
}

void NativeGraphicExportDialog::on_pushButton_clicked(bool checked)
{
    QString filepath =
            QFileDialog::getExistingDirectory(
                this,
                "Choose export directory");

    if (filepath.compare("") == 0) {
        return;
    }

    if (ui->rawTilesCheckBox->isChecked()) {
        appState_.editor().graphicsEditor().exportAllTiles(
                    filepath.toStdString() + "/",
                    ui->transparencyCheckBox->isChecked());
    }

    if (ui->spriteMappingsCheckBox->isChecked()) {
        appState_.editor().graphicsEditor().exportAllMappings(
                    filepath.toStdString() + "/");
    }
}
