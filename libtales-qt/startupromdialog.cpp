#include "startupromdialog.h"
#include "ui_startupromdialog.h"
#include "talesqtstatevar.h"
#include "confirmationdialog.h"
//#include "util/md5sum.h"
#include "util/StringConversion.h"
#include <QFileDialog>

StartupROMDialog::StartupROMDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartupROMDialog)
{
    ui->setupUi(this);
}

StartupROMDialog::~StartupROMDialog()
{
    delete ui;
}

void StartupROMDialog::on_buttonBox_accepted()
{
/*    // validate rom
    // ...

    // pop warning if rom not valid
    ConfirmationDialog confirmationDialog(
                std::string("WARNING: The MD5 sum of the given ROM does not match"
                "the expected value for a clean ROM!\n\n"
                "MD5 of a clean ROM: ") + ) */

    appState_.startEditor(ui->romPathLineEdit->text().toStdString());

    accept();
}

void StartupROMDialog::on_browseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                            this,
                            "Open Tails Adventures ROM",
                            "",
                            "All files (*.*)");

    ui->romPathLineEdit->setText(fileName);
}

std::string StartupROMDialog::selectedFileName() {
    return ui->romPathLineEdit->text().toStdString();
}
