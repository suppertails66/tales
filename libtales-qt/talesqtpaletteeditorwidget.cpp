#include "talesqtpaletteeditorwidget.h"
#include "ui_talesqtpaletteeditorwidget.h"
#include "talesqtstatevar.h"
#include "talesqtformatconversion.h"
#include "util/StringConversion.h"
#include "util/MiscMath.h"
#include <QPixmap>

using namespace Tales;
using namespace Luncheon;

TalesQtPaletteEditorWidget::TalesQtPaletteEditorWidget(QWidget *parent) :
    QWidget(parent),
    paletteEditor_(appState_.editor().paletteEditor()),
    previewBuffer_(64, 64),
    previewQImageBuffer_(64, 64, QImage::Format_ARGB32),
    ui(new Ui::TalesQtPaletteEditorWidget)
{
    ui->setupUi(this);

    for (int i = 0; i < paletteEditor_.numPalettes(); i++) {
        ui->paletteComboBox->addItem(
                    (StringConversion::toString(i)
                     + ": "
                     + paletteEditor_.nameOfPalette(i)).c_str(),
                    i);
    }

    QObject::connect(ui->palettePickerLabel,
                     SIGNAL(pickerEnter()),
                     this,
                     SLOT(pickerEnter()));
    QObject::connect(ui->palettePickerLabel,
                     SIGNAL(pickerLeave()),
                     this,
                     SLOT(pickerLeave()));
    QObject::connect(ui->palettePickerLabel,
                     SIGNAL(pickerMouseMove(Tales::InputEventData)),
                     this,
                     SLOT(pickerMouseMove(Tales::InputEventData)));
    QObject::connect(ui->palettePickerLabel,
                     SIGNAL(pickerMousePress(Tales::InputEventData)),
                     this,
                     SLOT(pickerMousePress(Tales::InputEventData)));
    QObject::connect(ui->palettePickerLabel,
                     SIGNAL(pickerMouseRelease(Tales::InputEventData)),
                     this,
                     SLOT(pickerMouseRelease(Tales::InputEventData)));
    QObject::connect(ui->palettePickerLabel,
                     SIGNAL(pickerMouseDoubleClick(Tales::InputEventData)),
                     this,
                     SLOT(pickerMouseDoubleClick(Tales::InputEventData)));

    paletteEditor_.setScale(2.00);

    paletteEditor_.selectPalette(0);
    refreshDisplay();
}

TalesQtPaletteEditorWidget::~TalesQtPaletteEditorWidget()
{
    delete ui;
}

void TalesQtPaletteEditorWidget::refreshDisplay() {
    if ((pickerBuffer_.w() != paletteEditor_.pickerPreviewWidth())
            || (pickerBuffer_.h()
                    != paletteEditor_.pickerPreviewHeight())) {
        pickerBuffer_ = Graphic(paletteEditor_.pickerPreviewWidth(),
                                paletteEditor_.pickerPreviewHeight());
    }

    if ((pickerQImageBuffer_.width() != paletteEditor_.pickerPreviewWidth())
            || (pickerQImageBuffer_.height()
                    != paletteEditor_.pickerPreviewHeight())) {
        pickerQImageBuffer_ = QImage((const uchar*)pickerBuffer_.imgdat(),
                                     pickerBuffer_.w(),
                                     pickerBuffer_.h(),
                                     QImage::Format_ARGB32);
    }

    paletteEditor_.drawPickerGraphic(pickerBuffer_);
    ui->palettePickerLabel->setPixmap(
                QPixmap().fromImage(pickerQImageBuffer_));

    paletteEditor_.drawPreviewGraphic(previewBuffer_);
    previewQImageBuffer_ = QImage((const uchar*)previewBuffer_.imgdat(),
                                 previewBuffer_.w(),
                                 previewBuffer_.h(),
                                 QImage::Format_ARGB32);
    ui->colorPreviewLabel->setPixmap(
                QPixmap().fromImage(
                    previewQImageBuffer_));

    setCurrentR(paletteEditor_.currentColor().realR());
    setCurrentG(paletteEditor_.currentColor().realG());
    setCurrentB(paletteEditor_.currentColor().realB());

    paletteEditor_.refresh();
}

void TalesQtPaletteEditorWidget::setCurrentR(int r) {
    MiscMath::clamp(r, 0, 255);
    paletteEditor_.currentColor().setRGB(
                r,
                paletteEditor_.currentColor().realG(),
                paletteEditor_.currentColor().realB());
    ui->redSlider->setValue(r);
    ui->redSpinBox->setValue(r);
}

void TalesQtPaletteEditorWidget::setCurrentG(int g) {
    MiscMath::clamp(g, 0, 255);
    paletteEditor_.currentColor().setRGB(
                paletteEditor_.currentColor().realR(),
                g,
                paletteEditor_.currentColor().realB());
    ui->greenSlider->setValue(g);
    ui->greenSpinBox->setValue(g);
}

void TalesQtPaletteEditorWidget::setCurrentB(int b) {
    MiscMath::clamp(b, 0, 255);
    paletteEditor_.currentColor().setRGB(
                paletteEditor_.currentColor().realR(),
                paletteEditor_.currentColor().realG(),
                b);
    ui->blueSlider->setValue(b);
    ui->blueSpinBox->setValue(b);
}

void TalesQtPaletteEditorWidget::pickerEnter() {
    paletteEditor_.pickerEnterMouse();
    refreshDisplay();
}

void TalesQtPaletteEditorWidget::pickerLeave() {
    paletteEditor_.pickerExitMouse();
    refreshDisplay();
}

void TalesQtPaletteEditorWidget::pickerMouseMove(Tales::InputEventData data) {
    paletteEditor_.pickerMoveMouse(data);
    refreshDisplay();
}

void TalesQtPaletteEditorWidget::pickerMousePress(Tales::InputEventData data) {
    paletteEditor_.pickerPressMouse(data);
    refreshDisplay();
}

void TalesQtPaletteEditorWidget::pickerMouseRelease(Tales::InputEventData data) {
    paletteEditor_.pickerReleaseMouse(data);
    refreshDisplay();
}

void TalesQtPaletteEditorWidget::pickerMouseDoubleClick(Tales::InputEventData data) {
    paletteEditor_.pickerDoubleClickMouse(data);
    refreshDisplay();
}

void TalesQtPaletteEditorWidget::on_paletteComboBox_activated(int index)
{
    paletteEditor_.selectPalette(index);
    refreshDisplay();
}

void TalesQtPaletteEditorWidget::on_redSpinBox_editingFinished()
{
    setCurrentR(ui->redSpinBox->value());
    refreshDisplay();
}

void TalesQtPaletteEditorWidget::on_greenSpinBox_editingFinished()
{
    setCurrentG(ui->greenSpinBox->value());
    refreshDisplay();
}

void TalesQtPaletteEditorWidget::on_blueSpinBox_editingFinished()
{
    setCurrentB(ui->blueSpinBox->value());
    refreshDisplay();
}

void TalesQtPaletteEditorWidget::on_redSlider_sliderMoved(int position)
{
    setCurrentR(position);
    refreshDisplay();
}

void TalesQtPaletteEditorWidget::on_greenSlider_sliderMoved(int position)
{
    setCurrentG(position);
    refreshDisplay();
}

void TalesQtPaletteEditorWidget::on_blueSlider_sliderMoved(int position)
{
    setCurrentB(position);
    refreshDisplay();
}
