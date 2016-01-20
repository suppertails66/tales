#include "confirmationdialog.h"
#include "ui_confirmationdialog.h"

ConfirmationDialog::ConfirmationDialog(
        const std::string& textLabel__,
        QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmationDialog)
{
    ui->setupUi(this);

    ui->textLabel->setText(textLabel__.c_str());
}

ConfirmationDialog::~ConfirmationDialog()
{
    delete ui;
}
