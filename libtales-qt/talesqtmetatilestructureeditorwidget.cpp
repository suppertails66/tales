#include "talesqtmetatilestructureeditorwidget.h"
#include "ui_talesqtmetatilestructureeditorwidget.h"
#include "talesqtstatevar.h"
#include "talesqtformatconversion.h"
#include "util/StringConversion.h"
#include "editors/GraphicToInfo.h"
#include "editors/PaletteEditor.h"
#include <iostream>

using namespace Tales;
using namespace Luncheon;

TalesQtMetatileStructureEditorWidget::TalesQtMetatileStructureEditorWidget(QWidget *parent) :
    QWidget(parent),
    metatileStructureEditor_(appState_.editor().metatileStructureEditor()),
    ui(new Ui::TalesQtMetatileStructureEditorWidget)
{
    ui->setupUi(this);

    QObject::connect(ui->metatilePickerPreviewLabel,
                     SIGNAL(pickerEnter()),
                     this,
                     SLOT(metatilePickerEnter()));
    QObject::connect(ui->metatilePickerPreviewLabel,
                     SIGNAL(pickerLeave()),
                     this,
                     SLOT(metatilePickerLeave()));
    QObject::connect(ui->metatilePickerPreviewLabel,
                     SIGNAL(pickerMouseMove(Tales::InputEventData)),
                     this,
                     SLOT(metatilePickerMouseMove(Tales::InputEventData)));
    QObject::connect(ui->metatilePickerPreviewLabel,
                     SIGNAL(pickerMousePress(Tales::InputEventData)),
                     this,
                     SLOT(metatilePickerMousePress(Tales::InputEventData)));
    QObject::connect(ui->metatilePickerPreviewLabel,
                     SIGNAL(pickerMouseRelease(Tales::InputEventData)),
                     this,
                     SLOT(metatilePickerMouseRelease(Tales::InputEventData)));
    QObject::connect(ui->metatilePickerPreviewLabel,
                     SIGNAL(pickerMouseDoubleClick(Tales::InputEventData)),
                     this,
                     SLOT(metatilePickerMouseDoubleClick(Tales::InputEventData)));

    QObject::connect(ui->tilePickerPreviewLabel,
                     SIGNAL(pickerEnter()),
                     this,
                     SLOT(tilePickerEnter()));
    QObject::connect(ui->tilePickerPreviewLabel,
                     SIGNAL(pickerLeave()),
                     this,
                     SLOT(tilePickerLeave()));
    QObject::connect(ui->tilePickerPreviewLabel,
                     SIGNAL(pickerMouseMove(Tales::InputEventData)),
                     this,
                     SLOT(tilePickerMouseMove(Tales::InputEventData)));
    QObject::connect(ui->tilePickerPreviewLabel,
                     SIGNAL(pickerMousePress(Tales::InputEventData)),
                     this,
                     SLOT(tilePickerMousePress(Tales::InputEventData)));
    QObject::connect(ui->tilePickerPreviewLabel,
                     SIGNAL(pickerMouseRelease(Tales::InputEventData)),
                     this,
                     SLOT(tilePickerMouseRelease(Tales::InputEventData)));
    QObject::connect(ui->tilePickerPreviewLabel,
                     SIGNAL(pickerMouseDoubleClick(Tales::InputEventData)),
                     this,
                     SLOT(tilePickerMouseDoubleClick(Tales::InputEventData)));

    QObject::connect(ui->subtilePickerPreviewLabel,
                     SIGNAL(pickerEnter()),
                     this,
                     SLOT(subtilePickerEnter()));
    QObject::connect(ui->subtilePickerPreviewLabel,
                     SIGNAL(pickerLeave()),
                     this,
                     SLOT(subtilePickerLeave()));
    QObject::connect(ui->subtilePickerPreviewLabel,
                     SIGNAL(pickerMouseMove(Tales::InputEventData)),
                     this,
                     SLOT(subtilePickerMouseMove(Tales::InputEventData)));
    QObject::connect(ui->subtilePickerPreviewLabel,
                     SIGNAL(pickerMousePress(Tales::InputEventData)),
                     this,
                     SLOT(subtilePickerMousePress(Tales::InputEventData)));
    QObject::connect(ui->subtilePickerPreviewLabel,
                     SIGNAL(pickerMouseRelease(Tales::InputEventData)),
                     this,
                     SLOT(subtilePickerMouseRelease(Tales::InputEventData)));
    QObject::connect(ui->subtilePickerPreviewLabel,
                     SIGNAL(pickerMouseDoubleClick(Tales::InputEventData)),
                     this,
                     SLOT(subtilePickerMouseDoubleClick(Tales::InputEventData)));

    QObject::connect(ui->ulSubtileWidget,
                     SIGNAL(valueModified()),
                     this,
                     SLOT(ulValueModified()));
    QObject::connect(ui->urSubtileWidget,
                     SIGNAL(valueModified()),
                     this,
                     SLOT(urValueModified()));
    QObject::connect(ui->llSubtileWidget,
                     SIGNAL(valueModified()),
                     this,
                     SLOT(llValueModified()));
    QObject::connect(ui->lrSubtileWidget,
                     SIGNAL(valueModified()),
                     this,
                     SLOT(lrValueModified()));

    ui->ulSubtileWidget->setNameLabel("Upper-left");
    ui->urSubtileWidget->setNameLabel("Upper-right");
    ui->llSubtileWidget->setNameLabel("Lower-left");
    ui->lrSubtileWidget->setNameLabel("Lower-right");

    for (int i = 0; i < metatileStructureEditor_.numMetatileStructureSets(); i++) {
        ui->metatileSetComboBox->addItem(
                    (StringConversion::toString(i)).c_str(), i);
    }

    // Level graphics first
    for (int i = 0; i < metatileStructureEditor_.numGraphics(); i++) {
        GraphicInfo info = GraphicToInfo::compressedGraphicInfo(i);

        if (info.graphicCategory() != GraphicCategories::level) {
            continue;
        }

        ui->previewGraphicComboBox->addItem(
                    (StringConversion::toString(i)
                    + ": "
                    + info.name()).c_str(), i);
    }

    // Other graphics after level graphics
    for (int i = 0; i < metatileStructureEditor_.numGraphics(); i++) {
        GraphicInfo info = GraphicToInfo::compressedGraphicInfo(i);

        if (info.graphicCategory() == GraphicCategories::level) {
            continue;
        }

        ui->previewGraphicComboBox->addItem(
                    (StringConversion::toString(i)
                    + ": "
                    + info.name()).c_str(), i);
    }

    for (int i = 0; i < metatileStructureEditor_.numPalettes(); i++) {
        ui->previewPaletteComboBox->addItem(
                    (StringConversion::toString(i)
                     + ": "
                     + PaletteEditor::nameOfPalette(i)).c_str(), i);
        ui->previewPalette2ComboBox->addItem(
                    (StringConversion::toString(i)
                     + ": "
                     + PaletteEditor::nameOfPalette(i)).c_str(), i);
    }

    selectStructureSet(0);
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget::selectStructureSet(int index) {
    ui->metatileSetComboBox->setCurrentIndex(index);

    MetatileStructureDefault defaultPreview
            = metatileStructureEditor_.defaultPreview(index);

    for (int i = 0; i < ui->previewGraphicComboBox->count(); i++) {
        if (ui->previewGraphicComboBox->itemData(i).toInt()
                == defaultPreview.graphicIndex_) {
            ui->previewGraphicComboBox->setCurrentIndex(i);
            break;
        }
    }

    ui->previewPaletteComboBox->setCurrentIndex(defaultPreview.paletteIndex_);
    ui->previewPalette2ComboBox->setCurrentIndex(defaultPreview.palette1Index_);

    metatileStructureEditor_.loadNewCurrentSet(index);
}

TalesQtMetatileStructureEditorWidget::~TalesQtMetatileStructureEditorWidget()
{
    delete ui;
}

void TalesQtMetatileStructureEditorWidget::refreshDisplay() {
//    selectStructureSet(ui->metatileSetComboBox->currentIndex());
    metatileStructureEditor_.loadPickedSubtile();

    ui->ulSubtileWidget->setTile(
                metatileStructureEditor_.currentMetatileStructure()
                    .upperLeft());
    ui->urSubtileWidget->setTile(
                metatileStructureEditor_.currentMetatileStructure()
                    .upperRight());
    ui->llSubtileWidget->setTile(
                metatileStructureEditor_.currentMetatileStructure()
                    .lowerLeft());
    ui->lrSubtileWidget->setTile(
                metatileStructureEditor_.currentMetatileStructure()
                    .lowerRight());

    Graphic tmp(256, 256);
    metatileStructureEditor_.drawMetatilePickerGraphic(tmp);
    ui->metatilePickerPreviewLabel->setPixmap(
                TalesQtFormatConversion::graphicToPixmap(tmp));

    Graphic tmp2(256, 256);
    metatileStructureEditor_.drawTilePickerGraphic(tmp2);
    ui->tilePickerPreviewLabel->setPixmap(
                TalesQtFormatConversion::graphicToPixmap(tmp2));

    Graphic tmp3(128, 128);
    metatileStructureEditor_.drawSubtilePickerGraphic(tmp3);
    ui->subtilePickerPreviewLabel->setPixmap(
                TalesQtFormatConversion::graphicToPixmap(tmp3));
}

void TalesQtMetatileStructureEditorWidget::saveCurrentAsDefaults() {
    MetatileStructureDefault defaults(
            ui->previewGraphicComboBox->itemData(
                ui->previewGraphicComboBox->currentIndex()).toInt(),
        ui->previewPaletteComboBox->itemData(
            ui->previewPaletteComboBox->currentIndex()).toInt(),
        ui->previewPalette2ComboBox->itemData(
            ui->previewPalette2ComboBox->currentIndex()).toInt());

    metatileStructureEditor_.setCurrentDefaults(defaults);
}

void TalesQtMetatileStructureEditorWidget::on_metatileSetComboBox_activated(int index)
{
    selectStructureSet(index);
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::metatilePickerEnter() {
    metatileStructureEditor_.metatilePickerEnterMouse();
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::metatilePickerLeave() {
    metatileStructureEditor_.metatilePickerExitMouse();
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::metatilePickerMouseMove(Tales::InputEventData data) {
    metatileStructureEditor_.metatilePickerMoveMouse(data);
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::metatilePickerMousePress(Tales::InputEventData data) {
    metatileStructureEditor_.metatilePickerPressMouse(data);
    // this should use a callback but I'm tired
    metatileStructureEditor_.loadPickedMetatile();
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::metatilePickerMouseRelease(Tales::InputEventData data) {
    metatileStructureEditor_.metatilePickerReleaseMouse(data);
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::metatilePickerMouseDoubleClick(Tales::InputEventData data) {
    metatileStructureEditor_.metatilePickerDoubleClickMouse(data);
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::tilePickerEnter() {
    metatileStructureEditor_.tilePickerEnterMouse();
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::tilePickerLeave() {
    metatileStructureEditor_.tilePickerExitMouse();
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::tilePickerMouseMove(Tales::InputEventData data) {
    metatileStructureEditor_.tilePickerMoveMouse(data);
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::tilePickerMousePress(Tales::InputEventData data) {
    metatileStructureEditor_.tilePickerPressMouse(data);
    metatileStructureEditor_.updatePickedTile();
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::tilePickerMouseRelease(Tales::InputEventData data) {
    metatileStructureEditor_.tilePickerReleaseMouse(data);
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::tilePickerMouseDoubleClick(Tales::InputEventData data) {
    metatileStructureEditor_.tilePickerDoubleClickMouse(data);
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::subtilePickerEnter() {
    metatileStructureEditor_.subtilePickerEnterMouse();
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::subtilePickerLeave() {
    metatileStructureEditor_.subtilePickerExitMouse();
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::subtilePickerMouseMove(Tales::InputEventData data) {
    metatileStructureEditor_.subtilePickerMoveMouse(data);
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::subtilePickerMousePress(Tales::InputEventData data) {
    metatileStructureEditor_.subtilePickerPressMouse(data);
    // this should also use a callback
    metatileStructureEditor_.loadPickedSubtile();
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::subtilePickerMouseRelease(Tales::InputEventData data) {
    metatileStructureEditor_.subtilePickerReleaseMouse(data);
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget
    ::subtilePickerMouseDoubleClick(Tales::InputEventData data) {
    metatileStructureEditor_.subtilePickerDoubleClickMouse(data);
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget::on_previewPalette2ComboBox_activated(int index)
{
    metatileStructureEditor_.changeCurrentPalette1(index);
    saveCurrentAsDefaults();
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget::on_gridCheckBox_clicked(bool checked)
{
    metatileStructureEditor_.setGridEnabled(checked);
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget::on_previewGraphicComboBox_activated(int index)
{
    metatileStructureEditor_.changeCurrentGraphic(
                ui->previewGraphicComboBox->itemData(index).toInt());
    saveCurrentAsDefaults();
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget::on_previewPaletteComboBox_activated(int index)
{
    metatileStructureEditor_.changeCurrentPalette0(index);
    saveCurrentAsDefaults();
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget::ulValueModified() {
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget::urValueModified() {
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget::llValueModified() {
    refreshDisplay();
}

void TalesQtMetatileStructureEditorWidget::lrValueModified() {
    refreshDisplay();
}
