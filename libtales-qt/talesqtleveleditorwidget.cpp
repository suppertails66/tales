#include "talesqtleveleditorwidget.h"
#include "ui_talesqtleveleditorwidget.h"
#include "talesqtstatevar.h"
#include "talesqtformatconversion.h"
#include "objecteditdialog.h"
#include "levelpropertiesdialog.h"
#include "warpeditdialog.h"
#include "spawneditordialog.h"
#include "util/StringConversion.h"
#include <iostream>

using namespace Tales;
using namespace Luncheon;

bool TalesQtLevelEditorWidget::objectEditDialogCallback(
        Tales::LevelObjectGraphicSceneLayer& layer,
        Tales::LevelObjectEntry& levelObjectEntry,
        void* obj) {
    TalesQtLevelEditorWidget* widget
            = (TalesQtLevelEditorWidget*)(obj);

    ObjectEditDialog dialog(layer, levelObjectEntry, widget);
    int result = dialog.exec();
    if (result == QDialog::Accepted) {
        return true;
    }
    else {
        return false;
    }
}

void TalesQtLevelEditorWidget::objectUpdateCallback(
        Tales::LevelObjectGraphicSceneLayer& layer,
        void* obj) {
    TalesQtLevelEditorWidget* widget
            = (TalesQtLevelEditorWidget*)(obj);

    widget->reloadObjects();
}

void TalesQtLevelEditorWidget::objectSelectionCallback(
        Tales::LevelObjectGraphicSceneLayer& layer,
        Tales::LevelObjectEntryCollection::iterator,
        void* obj) {
    TalesQtLevelEditorWidget* widget
            = (TalesQtLevelEditorWidget*)(obj);

    widget->updateObjectSelection();
}

bool TalesQtLevelEditorWidget::spawnEditDialogCallback(
        Tales::LevelSpawnGraphicSceneLayer& layer,
        Tales::SpawnPoint& spawnPoint,
        void* obj) {
    TalesQtLevelEditorWidget* widget
            = (TalesQtLevelEditorWidget*)(obj);

    SpawnEditorDialog dialog(layer, spawnPoint, widget);
    int result = dialog.exec();
    if (result == QDialog::Accepted) {
        return true;
    }
    else {
        return false;
    }
}

TalesQtLevelEditorWidget::TalesQtLevelEditorWidget(QWidget *parent) :
    QWidget(parent),
    levelEditor_(appState_.editor().levelEditor()),
    previewQImageBuffer_(1, 1, QImage::Format_RGB32),
    metatilePickerQImageBuffer_(1, 1, QImage::Format_RGB32),
    ui(new Ui::TalesQtLevelEditorWidget)
{
    ui->setupUi(this);

    levelEditor_.setObjectEditDialogCallback(&objectEditDialogCallback,
                                             (void*)this);
    levelEditor_.setObjectUpdateCallback(&objectUpdateCallback,
                                         (void*)this);
    levelEditor_.setObjectSelectionCallback(&objectSelectionCallback,
                                            (void*)this);
    levelEditor_.setSpawnEditDialogCallback(&spawnEditDialogCallback,
                                             (void*)this);

    // Populate map selector
    ui->mapSelectorWidget->repopulate(levelEditor_.levelHeaders(),
                                      SubMaps::subMapCountsSize,
                                      SubMaps::subMapCounts,
                                      levelEditor_.metadata().areaMetadataMap());

//    Graphic g = levelEditor_.previewGraphic();
    previewBuffer_ = Graphic(ui->levelEditorLabel->width(),
                      ui->levelEditorLabel->height());
//    Graphic scaled(ui->levelEditorLabel->width(),
//                   ui->levelEditorLabel->height());
//    g.scale(previewBuffer_,
//            Graphic::noTransUpdate);
    levelEditor_.drawPreviewGraphic(previewBuffer_);
    ui->levelEditorLabel->setPixmap(
                TalesQtFormatConversion::graphicToPixmap(previewBuffer_));

    reloadAndRefresh();
}

TalesQtLevelEditorWidget::~TalesQtLevelEditorWidget()
{
    delete ui;
}

void TalesQtLevelEditorWidget::refreshDisplay() {

//    Graphic g = levelEditor_.previewGraphic();
//    Graphic scaled(ui->levelEditorLabel->width(),
//                   ui->levelEditorLabel->height());
//    g.scale(previewBuffer_,
//            Graphic::noTransUpdate);

    // Draw level editor
    refreshLevelEditorDisplay();

    // Draw metatile picker
    refreshMetatilePickerDisplay();

    refreshToolbox();

    ui->cameraBoundTopBox->setValue(
                levelEditor_.cameraTopBound());
    ui->cameraBoundBottomBox->setValue(
                levelEditor_.cameraBottomBound());
    ui->cameraBoundLeftBox->setValue(
                levelEditor_.cameraLeftBound());
    ui->cameraBoundRightBox->setValue(
                levelEditor_.cameraRightBound());

//    ui->levelEditorLabel->setPixmap(
//                TalesQtFormatConversion::graphicToPixmap(previewBuffer_));

//    ui->levelEditorLabel->setPixmap(
//                ui->levelEditorLabel->pixmap()->scaled(
//                        ui->levelEditorLabel->width(),
//                    ui->levelEditorLabel->height()));
}

void TalesQtLevelEditorWidget::refreshLevelEditorDisplay() {
    // Update scroll settings of level scrollbars
    ui->levelHorizontalScrollBar->setRange(0,
                levelEditor_.maxScrollX()
                  - (ui->levelEditorLabel->width()
                        / levelEditor_.scale()));
    ui->levelHorizontalScrollBar->setPageStep(ui->levelEditorLabel->width()
                                              / levelEditor_.scale() / 3);

    ui->levelVerticalScrollBar->setRange(0,
                levelEditor_.maxScrollY()
                    - ui->levelEditorLabel->height()
                        / levelEditor_.scale());
    ui->levelVerticalScrollBar->setPageStep(ui->levelEditorLabel->height()
                                              / levelEditor_.scale() / 3);

    // If label has changed size, generate resized preview buffer
    if ((previewBuffer_.w() != ui->levelEditorLabel->width())
         || (previewBuffer_.h() != ui->levelEditorLabel->height())) {
        previewBuffer_ = Graphic(ui->levelEditorLabel->width(),
                          ui->levelEditorLabel->height());
    }

    if ((previewQImageBuffer_.width() != previewBuffer_.w())
        || (previewQImageBuffer_.height() != previewBuffer_.h())) {
//        previewQImageBuffer_ = QImage(previewBuffer_.w(),
//                                      previewBuffer_.h(),
//                                      QImage::Format_RGB32);
        previewQImageBuffer_ = QImage((const uchar*)previewBuffer_.const_imgdat(),
                                      previewBuffer_.w(),
                                      previewBuffer_.h(),
                                      QImage::Format_ARGB32);
    }

    levelEditor_.drawPreviewGraphic(previewBuffer_);
//    TalesQtFormatConversion::drawGraphicToImage(previewQImageBuffer_,
//                                                previewBuffer_);
//    previewQImageBuffer_ = QImage((const uchar*)previewBuffer_.const_imgdat(),
//                                  previewBuffer_.w(),
//                                  previewBuffer_.h(),
//                                  QImage::Format_ARGB32);
    ui->levelEditorLabel->setPixmap(
                ui->levelEditorLabel->pixmap()->fromImage(previewQImageBuffer_));
}

void TalesQtLevelEditorWidget::refreshMetatilePickerDisplay() {
    // If metatile picker label has changed size, generate resized preview buffer
    if ((metatilePickerBuffer_.w() != ui->metatilePickerLabel->width())
         || (metatilePickerBuffer_.h() != ui->metatilePickerLabel->height())) {
        metatilePickerBuffer_ = Graphic(ui->metatilePickerLabel->width(),
                                  ui->metatilePickerLabel->height());
    }

    if ((metatilePickerQImageBuffer_.width() != metatilePickerBuffer_.w())
        || (metatilePickerQImageBuffer_.height() != metatilePickerBuffer_.h())) {
//        metatilePickerQImageBuffer_ = QImage(metatilePickerBuffer_.w(),
//                                      metatilePickerBuffer_.h(),
//                                      QImage::Format_RGB32);
        metatilePickerQImageBuffer_
                = QImage((const uchar*)metatilePickerBuffer_.const_imgdat(),
                                      metatilePickerBuffer_.w(),
                                      metatilePickerBuffer_.h(),
                                      QImage::Format_ARGB32);
    }

    levelEditor_.drawMetatilePickerGraphic(metatilePickerBuffer_);
//    TalesQtFormatConversion::drawGraphicToImage(metatilePickerQImageBuffer_,
//                                                metatilePickerBuffer_);
//    metatilePickerQImageBuffer_
//            = QImage((const uchar*)metatilePickerBuffer_.const_imgdat(),
//                                  metatilePickerBuffer_.w(),
//                                  metatilePickerBuffer_.h(),
//                                  QImage::Format_ARGB32);
    ui->metatilePickerLabel->setPixmap(
        ui->metatilePickerLabel->pixmap()->fromImage(metatilePickerQImageBuffer_));
}

void TalesQtLevelEditorWidget::refreshToolbox() {
    // Deselect all tool buttons
    ui->metatilePaintToolButton->setChecked(false);
    ui->objectEditorButton->setChecked(false);
    ui->spawnEditorButton->setChecked(false);
    ui->metatileAreaCloneButton->setChecked(false);

    // Select the current tool
    switch (levelEditor_.currentTool()) {
    case LevelEditorTools::none:
        break;
    case LevelEditorTools::metatilePaint:
        ui->metatilePaintToolButton->setChecked(true);
        break;
    case LevelEditorTools::metatileAreaClone:
        ui->metatileAreaCloneButton->setChecked(true);
        break;
    case LevelEditorTools::objectEditor:
        ui->objectEditorButton->setChecked(true);
        break;
    case LevelEditorTools::spawnEditor:
        ui->spawnEditorButton->setChecked(true);
        break;
    default:
        break;
    }
}

void TalesQtLevelEditorWidget::refreshNumObjects() {
    std::string str;
    if (levelEditor_.currentObjectGroup() == 0) {
        str += "0 / 0";
    }
    else {
        // Level total
        str += StringConversion::toString(
                    levelEditor_.currentObjectGroup()->size());
        str += " / ";
        str += StringConversion::toString(
                    LevelObjectEntryGroup::maxGroupSize);
    }

    // All objects total
    str += "   (";
    str += StringConversion::toString(
                levelEditor_.totalObjectCount());
    str += " / ";
    str += StringConversion::toString(
                levelEditor_.maxTotalObjects());
    str += ")";

    ui->mapNumObjectsLabel->setText(str.c_str());
}

void TalesQtLevelEditorWidget::reloadObjects() {
    ui->objectListWidget->repopulate();
    refreshNumObjects();
}

void TalesQtLevelEditorWidget::updateObjectSelection() {
    ui->objectListWidget->updateObjectSelection();
}

void TalesQtLevelEditorWidget::reloadAndRefresh() {
    levelEditor_.refresh();

    ui->objectListWidget->assignGroup(
                levelEditor_.currentObjectGroup(),
                levelEditor_.toolManager());

    refreshNumObjects();

    refreshDisplay();
}

void TalesQtLevelEditorWidget::setScrollX(int scrollX) {
    ui->levelHorizontalScrollBar->setValue(scrollX);
    levelEditor_.setScrollX(scrollX);
    refreshLevelEditorDisplay();
}

void TalesQtLevelEditorWidget::setScrollY(int scrollY) {
    ui->levelVerticalScrollBar->setValue(scrollY);
    levelEditor_.setScrollY(scrollY);
    refreshLevelEditorDisplay();
}

void TalesQtLevelEditorWidget::changeEditorTool(
        LevelEditorTools::LevelEditorTool tool) {
    levelEditor_.changeTool(tool);

    refreshDisplay();
}

LevelPreviewScrollBar& TalesQtLevelEditorWidget
    ::levelHorizontalScrollBar() {
    return *(ui->levelHorizontalScrollBar);
}

LevelPreviewScrollBar& TalesQtLevelEditorWidget
    ::levelVerticalScrollBar() {
    return *(ui->levelVerticalScrollBar);
}

void TalesQtLevelEditorWidget::on_mapSelectorWidget_currentItemChanged(
        QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    // Ignore clicks on area names
    if (current->parent() == NULL) {
        return;
    }

    levelEditor_.changeMap(current->data(0, Qt::UserRole).toInt());

    // Reset scroll position
    ui->levelHorizontalScrollBar->setValue(0);
    ui->levelVerticalScrollBar->setValue(0);

    reloadAndRefresh();
//    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_levelHorizontalScrollBar_valueChanged(int value)
{
    levelEditor_.setScrollX(value);
    refreshLevelEditorDisplay();
}

void TalesQtLevelEditorWidget::on_levelVerticalScrollBar_valueChanged(int value)
{
    levelEditor_.setScrollY(value);
    refreshLevelEditorDisplay();
}

void TalesQtLevelEditorWidget::on_zoomComboBox_activated(int index)
{
    double zoomAmount = (index - 1);

    if (index == 0) {
        zoomAmount = 0.25;
    }
    else if (index == 1) {
        zoomAmount = 0.50;
    }

    levelEditor_.setScale(zoomAmount);
    refreshLevelEditorDisplay();
}

void TalesQtLevelEditorWidget::on_gridCheckBox_clicked(bool checked)
{
    levelEditor_.setGridEnabled(checked);
    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_levelVisualViewButton_clicked()
{
    levelEditor_.setLevelViewMode(LevelEditor::viewLevelVisual);
    ui->bgCheckBox->setEnabled(true);
    ui->fgCheckBox->setEnabled(true);
    ui->bgCheckBox->setChecked(true);
    ui->fgCheckBox->setChecked(true);
    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_levelEffectViewButton_clicked()
{
    levelEditor_.setLevelViewMode(LevelEditor::viewLevelEffect);
    ui->bgCheckBox->setEnabled(false);
    ui->fgCheckBox->setEnabled(false);
    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_bgCheckBox_clicked(bool checked)
{
    levelEditor_.setBGEnabled(checked);
    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_fgCheckBox_clicked(bool checked)
{
    levelEditor_.setFGEnabled(checked);
    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_metatilePaintToolButton_clicked()
{
    changeEditorTool(LevelEditorTools::metatilePaint);
}

void TalesQtLevelEditorWidget::on_metatileAreaCloneButton_clicked()
{
    changeEditorTool(LevelEditorTools::metatileAreaClone);
}

void TalesQtLevelEditorWidget::on_objectEditorButton_clicked()
{
    changeEditorTool(LevelEditorTools::objectEditor);
}

void TalesQtLevelEditorWidget::on_objectsCheckBox_clicked(bool checked)
{
    levelEditor_.setObjectsEnabled(checked);
    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_objectListWidget_currentRowChanged(int currentRow)
{
/*    if (ui->objectListWidget->hasGroup()) {
        levelEditor_.selectObjectAtIndex(currentRow);
        setScrollX(levelEditor_.scrollX());
        setScrollY(levelEditor_.scrollY());
        refreshDisplay();
    } */
}

void TalesQtLevelEditorWidget::on_objectListWidget_doubleClicked(const QModelIndex &index)
{
    if (ui->objectListWidget->hasGroup()) {
        levelEditor_.editSelectedObject();
    }
}

void TalesQtLevelEditorWidget::on_objectAddWidget_clicked(bool checked)
{
    if (ui->objectListWidget->hasGroup()) {
        if (levelEditor_.editAndAppendObject()) {
//            ui->objectListWidget->repopulate();
            setScrollX(levelEditor_.scrollX());
            setScrollY(levelEditor_.scrollY());
        }

        refreshDisplay();
    }
}

void TalesQtLevelEditorWidget::on_objectListWidget_clicked(const QModelIndex &index)
{
    if (ui->objectListWidget->hasGroup()) {
        levelEditor_.selectObjectAtIndex(index.row());
        setScrollX(levelEditor_.scrollX());
        setScrollY(levelEditor_.scrollY());
        refreshDisplay();
    }
}

void TalesQtLevelEditorWidget::on_objectRemoveWidget_clicked(bool checked)
{
    if ((ui->objectListWidget->hasGroup())
            && (ui->objectListWidget->currentRow() >= 0)) {
        levelEditor_.eraseObjectAtIndex(ui->objectListWidget->currentRow());
        delete (ui->objectListWidget->takeItem(ui->objectListWidget->currentRow()));
        refreshDisplay();
    }
}

void TalesQtLevelEditorWidget::on_cameraBoundTopBox_valueChanged(int arg1)
{
    levelEditor_.setCameraTopBound(arg1);
    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_cameraBoundBottomBox_valueChanged(int arg1)
{
    levelEditor_.setCameraBottomBound(arg1);
    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_cameraBoundLeftBox_valueChanged(int arg1)
{
    levelEditor_.setCameraLeftBound(arg1);
    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_cameraBoundRightBox_valueChanged(int arg1)
{
    levelEditor_.setCameraRightBound(arg1);
    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_levelPropertiesButton_clicked(bool checked)
{
    LevelPropertiesDialog dialog(levelEditor_, this);
    int result = dialog.exec();
    reloadAndRefresh();
}

void TalesQtLevelEditorWidget::on_autofillAllButton_clicked(bool checked)
{
    levelEditor_.refreshAllObjectVRAMOffsets();
    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_cameraBoundsShowBox_clicked(bool checked)
{
    levelEditor_.setBoundsEnabled(checked);
    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_warpsButton_clicked(bool checked)
{
    if (!levelEditor_.currentLevelHasWarps()) {
        return;
    }

    WarpEditDialog dialog(
                levelEditor_.currentLevelWarps(),
                levelEditor_.spawnPoints());
    int result = dialog.exec();
    if (result == QDialog::Accepted) {
        levelEditor_.currentLevelWarps() = dialog.warps();
    }
}

void TalesQtLevelEditorWidget::on_spawnsCheckBox_clicked(bool checked)
{
    levelEditor_.setSpawnsEnabled(checked);
    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_spawnEditorButton_clicked(bool checked)
{
    changeEditorTool(LevelEditorTools::spawnEditor);
}

void TalesQtLevelEditorWidget::on_levelVertSolidityButton_clicked(bool checked)
{
    levelEditor_.setLevelViewMode(LevelEditor::viewLevelVerticalSolidity);
    ui->bgCheckBox->setEnabled(false);
    ui->fgCheckBox->setEnabled(false);
    refreshDisplay();
}

void TalesQtLevelEditorWidget::on_levelHorizSolidityButton_clicked(bool checked)
{
    levelEditor_.setLevelViewMode(LevelEditor::viewLevelHorizontalSolidity);
    ui->bgCheckBox->setEnabled(false);
    ui->fgCheckBox->setEnabled(false);
    refreshDisplay();
}
