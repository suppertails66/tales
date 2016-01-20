#include "talesqtvrameditorwidget.h"
#include "ui_talesqtvrameditorwidget.h"
#include "talesqtformatconversion.h"
#include "talesqtstatevar.h"
#include "mapselectortreewidget.h"
#include "objectheadereditdialog.h"
#include "graphicsubheaderadddialog.h"
#include <QMouseEvent>
#include <Qt>
#include <iostream>
#include "gamedata/PrimaryMaps.h"
#include "gamedata/SubMaps.h"
#include "editors/GraphicToInfo.h"

using namespace Tales;

TalesQtVRAMEditorWidget::TalesQtVRAMEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TalesQtVRAMEditorWidget),
    vramEditor_(appState_.editor().vramEditor())
{
    ui->setupUi(this);

    // Populate map selector
    ui->mapSelectorTree->repopulate(SubMaps::subMapCountsSize,
                       SubMaps::subMapCounts,
                       vramEditor_.metadata().areaMetadataMap());

    // Populate map graphic selector
    for (int i = 0; i < GraphicToInfo::numCompressedGraphicInfos; i++) {
        if (GraphicToInfo::categoryOfCompressedGraphic(i)
                != GraphicCategories::level) {
            continue;
        }

        // Add level graphics first
        ui->mapGraphicComboBox->addItem(
                    GraphicToInfo::nameOfCompressedGraphic(i).c_str(),
                    QVariant(i));
    }
    // Add non-level graphics
    for (int i = 0; i < GraphicToInfo::numCompressedGraphicInfos; i++) {
        if (GraphicToInfo::categoryOfCompressedGraphic(i)
                == GraphicCategories::level) {
            continue;
        }

        // Add level graphics first
        ui->mapGraphicComboBox->addItem(
                    GraphicToInfo::nameOfCompressedGraphic(i).c_str(),
                    QVariant(i));
    }

    // Populate object graphics headers combo box
    ui->objectHeaderComboBox->repopulate(vramEditor_.levelGraphicsData());
}

TalesQtVRAMEditorWidget::~TalesQtVRAMEditorWidget()
{
    delete ui;
}

void TalesQtVRAMEditorWidget::reloadAndRefresh() {
    // Refresh VRAM editor object
    resetInputMode();
    vramEditor_.refresh();

    ObjectGraphicsHeader& header
            = vramEditor_.objectHeader();

    int objHeaderIndex = vramEditor_.levelHeader().objectGraphicsHeaderIndex();
    if (objHeaderIndex >= vramEditor_.levelGraphicsData().objectGraphicsHeadersSize()) {
        // If object header index out of range, default to 0
        vramEditor_.levelHeader().setObjectGraphicsHeaderIndex(0);
    }

    // Reload object graphics header
    ui->objectHeaderComboBox->setCurrentIndex(
                vramEditor_.levelHeader().objectGraphicsHeaderIndex());

    // Reload object graphic list
    ui->objectSelectorList->repopulate(header);

    // reload spin boxes
    refreshVRAMIndices();

    // Find needed position in combo box by doing a simple linear search
    // (there are only about ~80 graphics total, so this is fine)
    ui->mapGraphicComboBox->setCurrentIndex(
                ui->mapGraphicComboBox->findData(
                    vramEditor_.mapGraphicIndex()));

    // Redraw
    refreshDisplay();
}

void TalesQtVRAMEditorWidget::refreshDisplay() {
    ui->vramPreviewLabel->refreshDisplay();
    refreshSelectedObject();
    refreshVRAMIndices();
}

void TalesQtVRAMEditorWidget::refreshSelectedObject() {
    if (vramEditor_.objectIsSelected()) {
        // Select object in editor
        ui->objectSelectorList->setCurrentRow(
                    vramEditor_.selectedObjectIndex());

        ObjectGraphicSubheader& subheader
                = vramEditor_.objectHeader().subheader(
                    vramEditor_.selectedObjectIndex());

        // Load tile index
        ui->objectIndexSpinBox->setValue(subheader.tileWriteIndex());

        // Load flip state
        ui->flippedCheckBox->setChecked(
                    vramEditor_.objectSubheader().substitutionOption()
                        == ObjectGraphicSubheader::substitutionEnabled
                      ? true
                      : false);
    }
    else {
        // Deselect
        ui->objectSelectorList->clearSelection();
    }
}

void TalesQtVRAMEditorWidget::refreshVRAMIndices() {
    if (vramEditor_.hasLeafIndex()) {
        ui->leafIndexSpinBox->setValue(
                    vramEditor_.leafIndex());
        ui->leafIndexSpinBox->setEnabled(true);
        ui->leafIndexSelectButton->setEnabled(true);
        ui->leafShowCheckBox->setEnabled(true);
    }
    else {
        ui->leafIndexSpinBox->setValue(0);
        ui->leafIndexSpinBox->setEnabled(false);
        ui->leafIndexSelectButton->setEnabled(false);
        ui->leafShowCheckBox->setEnabled(false);
    }

    if (vramEditor_.hasSmokePuffIndex()) {
        ui->smokePuffSpinBox->setValue(
                    vramEditor_.smokePuffIndex());
        ui->smokePuffSpinBox->setEnabled(true);
        ui->smokePuffSelectButton->setEnabled(true);
        ui->smokeShowCheckBox->setEnabled(true);
    }
    else {
        ui->smokePuffSpinBox->setValue(0);
        ui->smokePuffSpinBox->setEnabled(false);
        ui->smokePuffSelectButton->setEnabled(false);
        ui->smokeShowCheckBox->setEnabled(false);
    }

    if (vramEditor_.hasWaterSplashIndex()) {
        ui->waterSplashSpinBox->setValue(
                    vramEditor_.waterSplashIndex());
        ui->waterSplashSpinBox->setEnabled(true);
        ui->waterSplashSelectButton->setEnabled(true);
        ui->waterShowCheckBox->setEnabled(true);
    }
    else {
        ui->waterSplashSpinBox->setValue(0);
        ui->waterSplashSpinBox->setEnabled(false);
        ui->waterSplashSelectButton->setEnabled(false);
        ui->waterShowCheckBox->setEnabled(false);
    }
}

void TalesQtVRAMEditorWidget::resetInputMode() {
    vramEditor_.resetInputMode();

    ui->objectIndexSelecButton->setChecked(false);
    ui->leafIndexSelectButton->setChecked(false);
    ui->smokePuffSelectButton->setChecked(false);
    ui->waterSplashSelectButton->setChecked(false);
}

double TalesQtVRAMEditorWidget::scale() const {
    return appState_.editor().vramEditor().scale();
}

void TalesQtVRAMEditorWidget::mouseClickEvent(QMouseEvent* event) {
/*    if (event->buttons() & Qt::LeftButton) {
        appState_.editor().vramEditor().mouseLeftClick(
                                                  event->x(),
                                                  event->y());
    } */
//    refreshDisplay();

//    std::cout << event->x() << " " << event->y() << std::endl;
}

void TalesQtVRAMEditorWidget::mouseMoveEvent(QMouseEvent* event) {
/*    appState_.editor().vramEditor().mouseMove(
                                              event->x(),
                                              event->y(),
                                              event->buttons()
                                                & Qt::LeftButton); */
//    refreshDisplay();

//    std::cout << event->x() << " " << event->y() << std::endl;
}

void TalesQtVRAMEditorWidget::on_objectUpButton_clicked()
{
    resetInputMode();
//    ui->vramPreviewLabel->refreshDisplay();
    vramEditor_.moveSelectedUp();
    // lazy ass object list update: repopulate from scratch
    ui->objectSelectorList->repopulate(vramEditor_.objectHeader());
    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_objectDownButton_clicked()
{
    resetInputMode();
//    ui->vramPreviewLabel->refreshDisplay();
    vramEditor_.moveSelectedDown();
    // lazy ass object list update: repopulate from scratch
    ui->objectSelectorList->repopulate(vramEditor_.objectHeader());
    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_mapSelectorTree_currentItemChanged(
        QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    // Ignore clicks on area names
    if (current->parent() == NULL) {
        return;
    }

    // Retrieve area and map nubmbers for clicked item
    int area = current->parent()->data(0, Qt::UserRole).toInt();
    int map = current->data(0, Qt::UserRole).toInt();

    // Change viewed map
    vramEditor_.changeMap(area, map);

    // Load data for new map and redraw
    reloadAndRefresh();
}

void TalesQtVRAMEditorWidget::on_leafIndexSpinBox_editingFinished()
{

}

void TalesQtVRAMEditorWidget::on_smokePuffSpinBox_editingFinished()
{

}

void TalesQtVRAMEditorWidget::on_waterSplashSpinBox_editingFinished()
{

}

void TalesQtVRAMEditorWidget::on_objectIndexSpinBox_editingFinished()
{

}

void TalesQtVRAMEditorWidget::on_objectSelectorList_activated(const QModelIndex &index)
{
    resetInputMode();
    vramEditor_.selectObjectAtIndex(index.row());
    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_objectSelectorList_clicked(const QModelIndex &index)
{
    resetInputMode();
    vramEditor_.selectObjectAtIndex(index.row());
    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_objectIndexSpinBox_valueChanged(int arg1)
{
    // Reset input mode only if actually selecting a tile (otherwise, we'll
    // override initial drag and drop mode selection)
    if (vramEditor_.inputMode() == LevelVRAMEditor::selectTile) {
        resetInputMode();
    }

    // Check that something is actually selected
    if (!vramEditor_.objectIsSelected()) {
        return;
    }

    ObjectGraphicSubheader& subheader
            = vramEditor_.objectHeader().subheader(
                vramEditor_.selectedObjectIndex());

    subheader.setTileWriteIndex(ui->objectIndexSpinBox->value());

    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_flippedCheckBox_toggled(bool checked)
{

}

void TalesQtVRAMEditorWidget::on_flippedCheckBox_clicked(bool checked)
{
    if (!vramEditor_.objectIsSelected()) {
        return;
    }

    if (checked) {
        vramEditor_.objectSubheader().setSubstitutionOption(
                    ObjectGraphicSubheader::substitutionEnabled);
    }
    else {
        vramEditor_.objectSubheader().setSubstitutionOption(
                    ObjectGraphicSubheader::substitutionDisabled);
    }

    // lazy ass object list update: repopulate from scratch
    ui->objectSelectorList->repopulate(vramEditor_.objectHeader());
    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_objectRemoveButton_clicked()
{
    resetInputMode();

    vramEditor_.eraseSelected();
    // lazy ass object list update: repopulate from scratch
    ui->objectSelectorList->repopulate(vramEditor_.objectHeader());
    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_mapGraphicComboBox_currentIndexChanged(int index)
{
    int value = ui->mapGraphicComboBox->itemData(index).toInt();

    vramEditor_.changeMapGraphic(value);

    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_objectHeaderComboBox_currentIndexChanged(int index)
{

}

void TalesQtVRAMEditorWidget::on_objectHeaderEditButton_clicked()
{
    resetInputMode();

    // Open object header edit dialog
    ObjectHeaderEditDialog dialog(vramEditor_.levelGraphicsData(),
                                  this);
    dialog.exec();

    // Repopulate object graphics headers combo box
    ui->objectHeaderComboBox->repopulate(vramEditor_.levelGraphicsData());

    // Reload current map
    reloadAndRefresh();
}

void TalesQtVRAMEditorWidget::on_objectHeaderComboBox_activated(int index)
{
    resetInputMode();

    int value = ui->objectHeaderComboBox->itemData(index).toInt();

    vramEditor_.levelHeader().setObjectGraphicsHeaderIndex(value);

    // Reload instead of just refreshing -- we need to update the object list
    reloadAndRefresh();
}

void TalesQtVRAMEditorWidget::insertSubheaderSomewhere(
        ObjectGraphicSubheader subheader) {
    // scan for a good place to put the subheader and set VRAM write address
    // appropriately
    // ...

    vramEditor_.objectHeader().insert(
                vramEditor_.objectHeader().size(),
                subheader);
}

void TalesQtVRAMEditorWidget::on_objectAddButton_clicked()
{
    resetInputMode();

    // Open object header edit dialog
    GraphicSubheaderAddDialog dialog(vramEditor_.objectHeader(),
                                     vramEditor_.levelGraphicsData(),
                                     vramEditor_.objectPalette(),
                                     this);
    int result = dialog.exec();

    if (result == QDialog::Rejected) {
        return;
    }

    ObjectGraphicSubheader subheader(
                0,
                dialog.graphicIndex(),
                ObjectGraphicSubheader::substitutionDisabled);

    if (dialog.regularAndFlipped()) {
        insertSubheaderSomewhere(subheader);
        subheader.setSubstitutionOption(
                    ObjectGraphicSubheader::substitutionEnabled);
        insertSubheaderSomewhere(subheader);
    }
    else {
        if (dialog.flipped()) {
            subheader.setSubstitutionOption(
                        ObjectGraphicSubheader::substitutionEnabled);
        }

        insertSubheaderSomewhere(subheader);
    }

    // Reload so items are updated
    reloadAndRefresh();

    // Select newly inserted item
    vramEditor_.selectObjectAtIndex(vramEditor_.objectHeader().size() - 1);
    refreshSelectedObject();

    // Refresh display so selected item change is reflected in preview
    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_leafIndexSelectButton_clicked()
{
    if (!(vramEditor_.hasLeafIndex())) {
        return;
    }

    ui->leafIndexSelectButton->setChecked(true);

    vramEditor_.setShowLeaf(true);
    ui->leafShowCheckBox->setChecked(true);

    vramEditor_.startSelectingTile(LevelVRAMEditor::targetLeafIndex);

    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_leafShowCheckBox_clicked(bool checked)
{
    vramEditor_.setShowLeaf(checked);
    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_smokeShowCheckBox_clicked(bool checked)
{
    vramEditor_.setShowSmokePuff(checked);
    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_waterShowCheckBox_clicked(bool checked)
{
    vramEditor_.setShowWaterSplash(checked);
    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_leafIndexSpinBox_valueChanged(int arg1)
{
    if (!EditorMetadata::areaNumHasVRAMIndices(vramEditor_.areaNum())) {
        return;
    }

    resetInputMode();

    vramEditor_.setLeafIndex(ui->leafIndexSpinBox->value());
    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_smokePuffSpinBox_valueChanged(int arg1)
{
    if (!EditorMetadata::areaNumHasVRAMIndices(vramEditor_.areaNum())) {
        return;
    }

    resetInputMode();

    vramEditor_.setSmokePuffIndex(ui->smokePuffSpinBox->value());
    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_waterSplashSpinBox_valueChanged(int arg1)
{
    if (!EditorMetadata::areaNumHasVRAMIndices(vramEditor_.areaNum())) {
        return;
    }

    resetInputMode();

    vramEditor_.setWaterSplashIndex(ui->waterSplashSpinBox->value());
    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_smokePuffSelectButton_clicked()
{
    if (!(vramEditor_.hasSmokePuffIndex())) {
        return;
    }

    vramEditor_.setShowSmokePuff(true);
    ui->smokeShowCheckBox->setChecked(true);

    ui->smokePuffSelectButton->setChecked(true);

    vramEditor_.startSelectingTile(LevelVRAMEditor::targetSmokePuffIndex);

    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_waterSplashSelectButton_clicked()
{
    if (!(vramEditor_.hasSmokePuffIndex())) {
        return;
    }

    vramEditor_.setShowWaterSplash(true);
    ui->waterShowCheckBox->setChecked(true);

    ui->waterSplashSelectButton->setChecked(true);

    vramEditor_.startSelectingTile(LevelVRAMEditor::targetWaterSplashIndex);

    refreshDisplay();
}

void TalesQtVRAMEditorWidget::on_objectIndexSelecButton_clicked()
{
    // Make sure a graphic is currently selected
    if (!vramEditor_.objectIsSelected()) {
        return;
    }

    ui->objectIndexSelecButton->setChecked(true);

    vramEditor_.startSelectingTile(LevelVRAMEditor::targetSelectedGraphicIndex);

    refreshDisplay();
}
