#include "layoutimportdialog.h"
#include "ui_layoutimportdialog.h"
#include "talesqtstatevar.h"
#include "gamedata/PrimaryMaps.h"
#include "gamedata/SubMaps.h"

using namespace Tales;

LayoutImportDialog::LayoutImportDialog(QWidget *parent) :
    QDialog(parent),
    selectedMapIndex_(0),
    ui(new Ui::LayoutImportDialog)
{
    ui->setupUi(this);

    ui->mapSelector->repopulate(appState_.editor().levelEditor().levelHeaders(),
                                  SubMaps::subMapCountsSize,
                                  SubMaps::subMapCounts,
                                  appState_.editor().levelEditor()
                                        .metadata().areaMetadataMap());
}

LayoutImportDialog::~LayoutImportDialog()
{
    delete ui;
}

int LayoutImportDialog::selectedMapIndex() {
    return selectedMapIndex_;
}

void LayoutImportDialog::on_mapSelector_currentItemChanged(QTreeWidgetItem *current,
                                                           QTreeWidgetItem *previous)
{
    if (current->parent() == NULL) {
        return;
    }

    selectedMapIndex_ = current->data(0, Qt::UserRole).toInt();
}
