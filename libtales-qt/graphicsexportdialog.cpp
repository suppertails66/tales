#include "graphicsexportdialog.h"
#include "ui_graphicsexportdialog.h"
#include <QFileDialog>

GraphicsExportDialog::GraphicsExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphicsExportDialog)
{
    ui->setupUi(this);
}

GraphicsExportDialog::~GraphicsExportDialog()
{
    delete ui;
}

void GraphicsExportDialog::on_mapExportButton_clicked(bool checked)
{
    QString foldername = QFileDialog::getExistingDirectory(
                this, tr("Choose map export directory"),
                "");

    if (foldername.size() == 0) {
        return;
    }


}

void GraphicsExportDialog::on_graphicExportButton_clicked(bool checked)
{
    QString foldername = QFileDialog::getExistingDirectory(
                this, tr("Choose graphics export directory"),
                "");

    if (foldername.size() == 0) {
        return;
    }


}
