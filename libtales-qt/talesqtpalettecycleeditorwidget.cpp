#include "talesqtpalettecycleeditorwidget.h"
#include "ui_talesqtpalettecycleeditorwidget.h"
#include "talesqtformatconversion.h"
#include "talesqtstatevar.h"
#include "util/StringConversion.h"

using namespace Tales;
using namespace Luncheon;

TalesQtPaletteCycleEditorWidget::TalesQtPaletteCycleEditorWidget(QWidget *parent) :
    QWidget(parent),
    paletteCycleEditor_(appState_.editor().paletteCycleEditor()),
    ui(new Ui::TalesQtPaletteCycleEditorWidget)
{
    ui->setupUi(this);

    ui->cycleComboBox->addItem(
                paletteCycleEditor_.nameOfCycle(
                    PaletteCycleEditor::torch).c_str(),
                PaletteCycleEditor::torch);
    ui->cycleComboBox->addItem(
                paletteCycleEditor_.nameOfCycle(
                    PaletteCycleEditor::lakeRocky1).c_str(),
                PaletteCycleEditor::lakeRocky1);
    ui->cycleComboBox->addItem(
                paletteCycleEditor_.nameOfCycle(
                    PaletteCycleEditor::lakeRocky2).c_str(),
                PaletteCycleEditor::lakeRocky2);
    ui->cycleComboBox->addItem(
                paletteCycleEditor_.nameOfCycle(
                    PaletteCycleEditor::lakeRocky3).c_str(),
                PaletteCycleEditor::lakeRocky3);
    ui->cycleComboBox->addItem(
                paletteCycleEditor_.nameOfCycle(
                    PaletteCycleEditor::lakeRocky4).c_str(),
                PaletteCycleEditor::lakeRocky4);
    ui->cycleComboBox->addItem(
                paletteCycleEditor_.nameOfCycle(
                    PaletteCycleEditor::lakeRocky5).c_str(),
                PaletteCycleEditor::lakeRocky5);
    ui->cycleComboBox->addItem(
                paletteCycleEditor_.nameOfCycle(
                    PaletteCycleEditor::lakeRocky6).c_str(),
                PaletteCycleEditor::lakeRocky6);
    ui->cycleComboBox->addItem(
                paletteCycleEditor_.nameOfCycle(
                    PaletteCycleEditor::cavernIsland).c_str(),
                PaletteCycleEditor::cavernIsland);
    ui->cycleComboBox->addItem(
                paletteCycleEditor_.nameOfCycle(
                    PaletteCycleEditor::poloyForest).c_str(),
                PaletteCycleEditor::poloyForest);
    ui->cycleComboBox->addItem(
                paletteCycleEditor_.nameOfCycle(
                    PaletteCycleEditor::worldMap).c_str(),
                PaletteCycleEditor::worldMap);

    changeCycle(PaletteCycleEditor::torch);

    QObject::connect(ui->colorEditorWidget,
                     SIGNAL(colorChanged(int,int,int)),
                     this,
                     SLOT(colorChanged(int,int,int)));

    QObject::connect(ui->paletteLabel,
                     SIGNAL(pickerEnter()),
                     this,
                     SLOT(pickerEnter()));
    QObject::connect(ui->paletteLabel,
                     SIGNAL(pickerLeave()),
                     this,
                     SLOT(pickerLeave()));
    QObject::connect(ui->paletteLabel,
                     SIGNAL(pickerMouseMove(Tales::InputEventData)),
                     this,
                     SLOT(pickerMouseMove(Tales::InputEventData)));
    QObject::connect(ui->paletteLabel,
                     SIGNAL(pickerMousePress(Tales::InputEventData)),
                     this,
                     SLOT(pickerMousePress(Tales::InputEventData)));
    QObject::connect(ui->paletteLabel,
                     SIGNAL(pickerMouseRelease(Tales::InputEventData)),
                     this,
                     SLOT(pickerMouseRelease(Tales::InputEventData)));
    QObject::connect(ui->paletteLabel,
                     SIGNAL(pickerMouseDoubleClick(Tales::InputEventData)),
                     this,
                     SLOT(pickerMouseDoubleClick(Tales::InputEventData)));

    refreshDisplay();
}

TalesQtPaletteCycleEditorWidget::~TalesQtPaletteCycleEditorWidget()
{
    delete ui;
}

void TalesQtPaletteCycleEditorWidget::refreshDisplay() {
    refreshPalette();
    refreshPreview();
}

void TalesQtPaletteCycleEditorWidget::refreshPalette() {
    Graphic g;
    paletteCycleEditor_.drawColorPickerGraphic(g);
    ui->paletteLabel->setPixmap(
                TalesQtFormatConversion::graphicToPixmap(g));
}

void TalesQtPaletteCycleEditorWidget::refreshPreview() {
    Color color = paletteCycleEditor_.currentColor();
    ui->colorEditorWidget->setColor(
                color.r(), color.g(), color.b());

    Graphic g;
    paletteCycleEditor_.drawColorPreviewGraphic(g);
    ui->colorPreviewLabel->setPixmap(
                TalesQtFormatConversion::graphicToPixmap(g));
}

void TalesQtPaletteCycleEditorWidget::colorChanged(int r, int g, int b) {
    paletteCycleEditor_.changeCurrentColor(r, g, b);
    refreshDisplay();
}

void TalesQtPaletteCycleEditorWidget::pickerEnter() {
    paletteCycleEditor_.colorPickerEnterMouse();
    refreshDisplay();
}

void TalesQtPaletteCycleEditorWidget::pickerLeave() {
    paletteCycleEditor_.colorPickerExitMouse();
    refreshDisplay();
}

void TalesQtPaletteCycleEditorWidget::pickerMouseMove(Tales::InputEventData data) {
    paletteCycleEditor_.colorPickerMoveMouse(data);
    refreshDisplay();
}

void TalesQtPaletteCycleEditorWidget::pickerMousePress(Tales::InputEventData data) {
    paletteCycleEditor_.colorPickerPressMouse(data);
    refreshDisplay();
}

void TalesQtPaletteCycleEditorWidget::pickerMouseRelease(Tales::InputEventData data) {
    paletteCycleEditor_.colorPickerReleaseMouse(data);
    refreshDisplay();
}

void TalesQtPaletteCycleEditorWidget::pickerMouseDoubleClick(Tales::InputEventData data) {
    paletteCycleEditor_.colorPickerDoubleClickMouse(data);
    refreshDisplay();
}

void TalesQtPaletteCycleEditorWidget::on_cycleComboBox_activated(int index)
{
    changeCycle(static_cast<PaletteCycleEditor::CycleID>(
                    ui->cycleComboBox->itemData(index).toInt()));
}

void TalesQtPaletteCycleEditorWidget::changeCycle(PaletteCycleEditor::CycleID cycleID) {
    paletteCycleEditor_.changeCycle(cycleID);
    ui->cycleComboBox->setCurrentIndex(cycleID);

    ui->stateComboBox->clear();

    for (int i = 0; i < paletteCycleEditor_.numCurrentCycleStates(); i++) {
        ui->stateComboBox->addItem(
                    (StringConversion::toString(i)).c_str(),
                    i);
    }

    changeState(0);

    refreshDisplay();
}

void TalesQtPaletteCycleEditorWidget::changeState(int stateNum) {
    ui->stateComboBox->setCurrentIndex(stateNum);
    paletteCycleEditor_.changeCycleState(stateNum);

    refreshDisplay();
}

void TalesQtPaletteCycleEditorWidget::on_stateComboBox_activated(int index)
{
    changeState(ui->stateComboBox->itemData(index).toInt());
}
