#include "objectheadereditdialog.h"
#include "ui_objectheadereditdialog.h"
#include "util/StringConversion.h"
#include <string>

using namespace Tales;

ObjectHeaderEditDialog::ObjectHeaderEditDialog(
        Tales::EditableLevelGraphicsData& srcData__,
        QWidget *parent) :
    QDialog(parent),
    srcData_(srcData__),
    ui(new Ui::ObjectHeaderEditDialog)
{
    ui->setupUi(this);

    // Populate list of user headers
    repopulate();
}

ObjectHeaderEditDialog::~ObjectHeaderEditDialog()
{
    delete ui;
}

void ObjectHeaderEditDialog::repopulate() {
    ui->headerList->clear();

    for (int i = srcData_.numBaseObjectGraphicsHeaders();
         i < srcData_.objectGraphicsHeadersSize();
         i++) {
        QListWidgetItem* item = new QListWidgetItem(
                    (std::string("Custom object group ")
                    + StringConversion::toString(
                         i - srcData_.numBaseObjectGraphicsHeaders())).c_str(),
                    ui->headerList);
        item->setData(Qt::UserRole,
                      QVariant(i));
        ui->headerList->addItem(item);
    }
}

void ObjectHeaderEditDialog::on_okButton_clicked()
{
    accept();
}

void ObjectHeaderEditDialog::on_headerAddButton_clicked()
{
    ObjectGraphicsHeader header;

    srcData_.insertObjectGraphicsHeader(header);

    repopulate();
}

void ObjectHeaderEditDialog::on_headerRemoveButton_clicked()
{
    if ((ui->headerList->count() <= 0)
        || (ui->headerList->currentRow() < 0)) {
        return;
    }

//    int targetRow = ui->headerList->currentRow();
    int index = ui->headerList->currentItem()->data(Qt::UserRole).toInt();

    // Remove from source model
    srcData_.eraseObjectGraphicsHeader(index);

    // Repopulate (renumbering so indices remain valid)
    repopulate();

    // Correct headers affected by the removal
    for (int i = 0; i < srcData_.levelGraphicsHeadersSize(); i++) {
        LevelGraphicsHeader& header
                = srcData_.levelGraphicsHeader(i);
        if (header.objectGraphicsHeaderIndex() > index) {
            // If index is greater, decrement so target remains the same
            header.setObjectGraphicsHeaderIndex(
                        header.objectGraphicsHeaderIndex() - 1);
        }
        else if (header.objectGraphicsHeaderIndex() == index) {
            // If index is equal (removed header), set to 0 as default
            header.setObjectGraphicsHeaderIndex(0);
        }
    }
}
