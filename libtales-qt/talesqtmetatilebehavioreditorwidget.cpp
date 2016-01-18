#include "talesqtmetatilebehavioreditorwidget.h"
#include "ui_talesqtmetatilebehavioreditorwidget.h"
#include "talesqtstatevar.h"
#include "createinputeventdata.h"
#include "talesqtformatconversion.h"
#include "gamedata/MetatileType.h"
#include "util/StringConversion.h"

using namespace Tales;
using namespace Luncheon;

void TalesQtMetatileBehaviorEditorWidget
    ::metatilePickedCallback(int tileNum,
                             void* editorWidget) {
    TalesQtMetatileBehaviorEditorWidget*
            widget = (TalesQtMetatileBehaviorEditorWidget*)editorWidget;

    widget->changeCurrentMetatile(tileNum);
}

TalesQtMetatileBehaviorEditorWidget
    ::TalesQtMetatileBehaviorEditorWidget(QWidget *parent) :
    QWidget(parent),
    metatileBehaviorEditor_(
        appState_.editor().metatileBehaviorEditor()),
    metatilePickerQImageBuffer_(1, 1, QImage::Format_RGB32),
    ui(new Ui::TalesQtMetatileBehaviorEditorWidget)
{
    ui->setupUi(this);

    initializeComboBoxes();

    QObject::connect(ui->metatilePickerLabel,
                     SIGNAL(pickerEnter()),
                     this,
                     SLOT(pickerEnter()));
    QObject::connect(ui->metatilePickerLabel,
                     SIGNAL(pickerLeave()),
                     this,
                     SLOT(pickerLeave()));
    QObject::connect(ui->metatilePickerLabel,
                     SIGNAL(pickerMouseMove(Tales::InputEventData)),
                     this,
                     SLOT(pickerMouseMove(Tales::InputEventData)));
    QObject::connect(ui->metatilePickerLabel,
                     SIGNAL(pickerMousePress(Tales::InputEventData)),
                     this,
                     SLOT(pickerMousePress(Tales::InputEventData)));
    QObject::connect(ui->metatilePickerLabel,
                     SIGNAL(pickerMouseRelease(Tales::InputEventData)),
                     this,
                     SLOT(pickerMouseRelease(Tales::InputEventData)));
    QObject::connect(ui->metatilePickerLabel,
                     SIGNAL(pickerMouseDoubleClick(Tales::InputEventData)),
                     this,
                     SLOT(pickerMouseDoubleClick(Tales::InputEventData)));
}

TalesQtMetatileBehaviorEditorWidget::~TalesQtMetatileBehaviorEditorWidget()
{
    delete ui;
}

void TalesQtMetatileBehaviorEditorWidget::refreshDisplay() {
    refreshMetatilePicker();
    refreshDisplayedMetatile();
}

void TalesQtMetatileBehaviorEditorWidget::reloadAndRefresh() {
    metatileBehaviorEditor_.reloadMetatileDisplay();
    initializeComboBoxes();
    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::refreshMetatilePicker() {
    // If metatile picker label has changed size, generate resized preview buffer
    if ((metatilePickerBuffer_.w() != ui->metatilePickerLabel->width())
         || (metatilePickerBuffer_.h() != ui->metatilePickerLabel->height())) {
        metatilePickerBuffer_ = Graphic(ui->metatilePickerLabel->width(),
                                  ui->metatilePickerLabel->height());
    }

    if ((metatilePickerQImageBuffer_.width() != metatilePickerBuffer_.w())
        || (metatilePickerQImageBuffer_.height() != metatilePickerBuffer_.h())) {
        metatilePickerQImageBuffer_
                = QImage((const uchar*)metatilePickerBuffer_.const_imgdat(),
                                      metatilePickerBuffer_.w(),
                                      metatilePickerBuffer_.h(),
                                      QImage::Format_ARGB32);
    }

    metatileBehaviorEditor_.drawMetatilePickerGraphic(metatilePickerBuffer_);

    ui->metatilePickerLabel->setPixmap(
        ui->metatilePickerLabel->pixmap()->fromImage(metatilePickerQImageBuffer_));
}

void TalesQtMetatileBehaviorEditorWidget::refreshDisplayedMetatile() {
    ui->metatileIDLabel->setText(
                StringConversion::toString(
                    metatileBehaviorEditor_.pickedMetatile()).c_str());

    ui->metatileBehaviorLabel->setPixmap(
                TalesQtFormatConversion::graphicToPixmap(
                    metatileBehaviorEditor_
                        .currentMetatileEffectGraphic())
                .scaled(64, 64));

    ui->metatileVertSolidityLabel->setPixmap(
                TalesQtFormatConversion::graphicToPixmap(
                    metatileBehaviorEditor_
                        .currentMetatileVerticalSolidityGraphic())
                .scaled(64, 64));

    ui->metatileHorizSolidityLabel->setPixmap(
                TalesQtFormatConversion::graphicToPixmap(
                    metatileBehaviorEditor_
                        .currentMetatileHorizontalSolidityGraphic())
                .scaled(64, 64));

    ui->behaviorComboBox->setCurrentIndex(
                metatileBehaviorEditor_.currentMetatileBehavior()
                    .metatileType());

    ui->vertSolidityComboBox->setCurrentIndex(
                metatileBehaviorEditor_.currentMetatileBehavior()
                    .heightMapIndex());

    ui->horizSolidityComboBox->setCurrentIndex(
                metatileBehaviorEditor_.currentMetatileBehavior()
                    .widthMapIndex());

    switch (metatileBehaviorEditor_.currentMetatileBehavior()
            .solidity()) {
    case MetatileSolidities::fullySolid:
        ui->fullySolidButton->setChecked(true);
        break;
    case MetatileSolidities::solidOnTop:
        ui->solidOnTopButton->setChecked(true);
        break;
    case MetatileSolidities::nonsolid:
        ui->nonsolidButton->setChecked(true);
        break;
    default:
        break;
    }

    ui->slopeSpeedComboBox->setCurrentIndex(
                metatileBehaviorEditor_.currentMetatileBehavior()
                    .slopeSpeedIndex());
}

void TalesQtMetatileBehaviorEditorWidget
    ::changeCurrentMetatile(int tileNum) {
    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::pickerEnter() {
    metatileBehaviorEditor_.metatilePickerEnterMouse();
    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::pickerLeave() {
    metatileBehaviorEditor_.metatilePickerExitMouse();
    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::pickerMouseMove(InputEventData data) {
    metatileBehaviorEditor_.metatilePickerMoveMouse(data);

    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::pickerMousePress(InputEventData data) {
    metatileBehaviorEditor_.metatilePickerPressMouse(data);

    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::pickerMouseRelease(InputEventData data) {
//    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::pickerMouseDoubleClick(InputEventData data) {
//    refreshDisplay();
}


void TalesQtMetatileBehaviorEditorWidget::on_pickerBehaviorButton_clicked(bool checked)
{
    metatileBehaviorEditor_.setEditingMode(
                MetatileBehaviorEditor::editingEffect);
    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::on_pickerVertSolidityButton_clicked(bool checked)
{
    metatileBehaviorEditor_.setEditingMode(
                MetatileBehaviorEditor::editingVerticalSolidity);
    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::on_pickerHorizSolidityButton_clicked(bool checked)
{
    metatileBehaviorEditor_.setEditingMode(
                MetatileBehaviorEditor::editingHorizontalSolidity);
    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::on_gridCheckBox_clicked(bool checked)
{
    metatileBehaviorEditor_.setGridEnabled(checked);
    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::initializeComboBoxes() {
    ui->behaviorComboBox->clear();
    ui->horizSolidityComboBox->clear();
    ui->vertSolidityComboBox->clear();
    ui->slopeSpeedComboBox->clear();

    for (int i = 0; i < MetatileTypes::numMetatileTypes; i++) {
        MetatileTypes::MetatileType metatileType
                = static_cast<MetatileTypes::MetatileType>(i);

        std::string name = MetatileTypes::nameOfType(metatileType);

        ui->behaviorComboBox->addItem(
                    (StringConversion::toString(i)
                        + ": "
                        + name).c_str(), i);
    }

    for (int i = 0; i < metatileBehaviorEditor_.numWidthMaps(); i++) {
        ui->horizSolidityComboBox->addItem(
                    StringConversion::toString(i).c_str(), i);
    }

    for (int i = 0; i < metatileBehaviorEditor_.numHeightMaps(); i++) {
        ui->vertSolidityComboBox->addItem(
                    StringConversion::toString(i).c_str(), i);
    }

    for (int i = 0; i < metatileBehaviorEditor_.numSlopeSpeedIndices(); i++) {
        ui->slopeSpeedComboBox->addItem(
                    (StringConversion::toString(i)
                     + ": "
                     + StringConversion::toString(
                         metatileBehaviorEditor_.slopeSpeedValue(i))).c_str(),
                    i);
    }
}

void TalesQtMetatileBehaviorEditorWidget::on_behaviorComboBox_activated(int index)
{
    metatileBehaviorEditor_.currentMetatileBehavior()
            .setMetatileType(static_cast<MetatileTypes::MetatileType>(
                                 index));
    metatileBehaviorEditor_.reloadMetatileDisplay();
    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::on_vertSolidityComboBox_activated(int index)
{
    metatileBehaviorEditor_.currentMetatileBehavior()
            .setHeightMapIndex(index);
    metatileBehaviorEditor_.reloadMetatileDisplay();
    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::on_horizSolidityComboBox_activated(int index)
{
    metatileBehaviorEditor_.currentMetatileBehavior()
            .setWidthMapIndex(index);
    metatileBehaviorEditor_.reloadMetatileDisplay();
    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::on_fullySolidButton_clicked(bool checked)
{
    metatileBehaviorEditor_.currentMetatileBehavior()
            .setSolidity(MetatileSolidities::fullySolid);
    metatileBehaviorEditor_.reloadMetatileDisplay();
    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::on_solidOnTopButton_clicked(bool checked)
{
    metatileBehaviorEditor_.currentMetatileBehavior()
            .setSolidity(MetatileSolidities::solidOnTop);
    metatileBehaviorEditor_.reloadMetatileDisplay();
    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::on_nonsolidButton_clicked(bool checked)
{
    metatileBehaviorEditor_.currentMetatileBehavior()
            .setSolidity(MetatileSolidities::nonsolid);
    metatileBehaviorEditor_.reloadMetatileDisplay();
    refreshDisplay();
}

void TalesQtMetatileBehaviorEditorWidget::on_slopeSpeedComboBox_activated(int index)
{
    metatileBehaviorEditor_.currentMetatileBehavior()
            .setSlopeSpeedIndex(index);
//    metatileBehaviorEditor_.reloadMetatileDisplay();
    refreshDisplay();
}
