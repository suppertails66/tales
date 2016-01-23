#include "talesqttilemapeditorwidget.h"
#include "ui_talesqttilemapeditorwidget.h"
#include "talesqtformatconversion.h"
#include "talesqtstatevar.h"
#include "util/StringConversion.h"

using namespace Tales;
using namespace Luncheon;

TalesQtTileMapEditorWidget::TalesQtTileMapEditorWidget(QWidget *parent) :
    QWidget(parent),
    tileMapEditor_(appState_.editor().tileMapEditor()),
    ui(new Ui::TalesQtTileMapEditorWidget)
{
    ui->setupUi(this);

    ui->subtileEditorWidget->setNameLabel("Selected tile");

    for (int i = 0; i < tileMapEditor_.numTileMaps(); i++) {
        ui->tileMapComboBox->addItem(
                    (StringConversion::toString(i)
                     + ": "
                     + tileMapEditor_.nameOfTileMap(i)).c_str(),
                    i);
    }

    QObject::connect(ui->tileMapPreviewLabel,
                     SIGNAL(pickerEnter()),
                     this,
                     SLOT(tileMapEnter()));
    QObject::connect(ui->tileMapPreviewLabel,
                     SIGNAL(pickerLeave()),
                     this,
                     SLOT(tileMapLeave()));
    QObject::connect(ui->tileMapPreviewLabel,
                     SIGNAL(pickerMouseMove(Tales::InputEventData)),
                     this,
                     SLOT(tileMapMouseMove(Tales::InputEventData)));
    QObject::connect(ui->tileMapPreviewLabel,
                     SIGNAL(pickerMousePress(Tales::InputEventData)),
                     this,
                     SLOT(tileMapMousePress(Tales::InputEventData)));
    QObject::connect(ui->tileMapPreviewLabel,
                     SIGNAL(pickerMouseRelease(Tales::InputEventData)),
                     this,
                     SLOT(tileMapMouseRelease(Tales::InputEventData)));
    QObject::connect(ui->tileMapPreviewLabel,
                     SIGNAL(pickerMouseDoubleClick(Tales::InputEventData)),
                     this,
                     SLOT(tileMapMouseDoubleClick(Tales::InputEventData)));

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

    refreshDisplay();
}

TalesQtTileMapEditorWidget::~TalesQtTileMapEditorWidget()
{
    delete ui;
}

void TalesQtTileMapEditorWidget::refreshDisplay() {
    Graphic g;
    tileMapEditor_.drawTileMapPreview(g);
    ui->tileMapPreviewLabel->setPixmap(
                TalesQtFormatConversion::graphicToPixmap(g));

    Graphic g2;
    tileMapEditor_.drawTilePicker(g2);
    ui->tilePickerPreviewLabel->setPixmap(
                TalesQtFormatConversion::graphicToPixmap(g2));
}

void TalesQtTileMapEditorWidget::on_tileMapComboBox_activated(int index)
{
    tileMapEditor_.changeTileMap(index);
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::tileMapEnter() {
    tileMapEditor_.tileMapEnter();
}

void TalesQtTileMapEditorWidget::tileMapLeave() {
    tileMapEditor_.tileMapExit();
}

void TalesQtTileMapEditorWidget::tileMapMouseMove(Tales::InputEventData data) {
    tileMapEditor_.tileMapMouseMove(data);
}

void TalesQtTileMapEditorWidget::tileMapMousePress(Tales::InputEventData data) {
    tileMapEditor_.tileMapMousePress(data);
}

void TalesQtTileMapEditorWidget::tileMapMouseRelease(Tales::InputEventData data) {
    tileMapEditor_.tileMapMouseRelease(data);
}

void TalesQtTileMapEditorWidget::tileMapMouseDoubleClick(Tales::InputEventData data) {
    tileMapEditor_.tileMapMouseDoubleClick(data);
}

void TalesQtTileMapEditorWidget::tilePickerEnter() {
    tileMapEditor_.tilePickerEnter();
}

void TalesQtTileMapEditorWidget::tilePickerLeave() {
    tileMapEditor_.tilePickerExit();
}

void TalesQtTileMapEditorWidget::tilePickerMouseMove(Tales::InputEventData data) {
    tileMapEditor_.tilePickerMouseMove(data);
}

void TalesQtTileMapEditorWidget::tilePickerMousePress(Tales::InputEventData data) {
    tileMapEditor_.tilePickerMousePress(data);
}

void TalesQtTileMapEditorWidget::tilePickerMouseRelease(Tales::InputEventData data) {
    tileMapEditor_.tilePickerMouseRelease(data);
}

void TalesQtTileMapEditorWidget::tilePickerMouseDoubleClick(Tales::InputEventData data) {
    tileMapEditor_.tilePickerMouseDoubleClick(data);
}
