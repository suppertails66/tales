#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "util/StringConversion.h"

using namespace Luncheon;

AboutDialog::AboutDialog(
        int versionNum__,
        QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->versionNumLabel->setText(
                StringConversion::toString(versionNum__).c_str());
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
