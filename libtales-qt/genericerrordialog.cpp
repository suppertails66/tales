#include "genericerrordialog.h"
#include "ui_genericerrordialog.h"

GenericErrorDialog::GenericErrorDialog(
        const std::string& errorText,
        QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenericErrorDialog)
{
    ui->setupUi(this);

    ui->textLabel->setText(errorText.c_str());
}

GenericErrorDialog::~GenericErrorDialog()
{
    delete ui;
}
