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

    ui->gridCheckBox->setChecked(tileMapEditor_.gridEnabled());

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

    QObject::connect(ui->subtileEditorWidget,
                     SIGNAL(valueModified()),
                     this,
                     SLOT(subtileEditorValueModified()));

    changeTileMap(0);
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

    ui->subtileEditorWidget->setTile(
                tileMapEditor_.currentTile());

    ui->regularButton->setChecked(false);
    ui->pencilButton->setChecked(false);
    ui->areaCloneButton->setChecked(false);

    switch (tileMapEditor_.currentTool()) {
    case TileMapEditorTools::regular:
        ui->regularButton->setChecked(true);
        break;
    case TileMapEditorTools::pencil:
        ui->pencilButton->setChecked(true);
        break;
    case TileMapEditorTools::areaClone:
        ui->areaCloneButton->setChecked(true);
        break;
    default:
        break;
    }
}

void TalesQtTileMapEditorWidget::changeTileMap(int index) {
    tileMapEditor_.changeTileMap(index);

    if (tileMapEditor_.currentEditingLimited()) {
        ui->subtileEditorWidget->disableAllButTileNum();
    }
    else {
        ui->subtileEditorWidget->enableAll();
    }

    ui->subtileEditorWidget->setTileRange(
                tileMapEditor_.currentTileMap().lowerLimit(),
                tileMapEditor_.currentTileMap().upperLimit() - 1);
}

void TalesQtTileMapEditorWidget::on_tileMapComboBox_activated(int index)
{
    changeTileMap(index);

    refreshDisplay();
}

void TalesQtTileMapEditorWidget::tileMapEnter() {
    tileMapEditor_.tileMapEnter();
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::tileMapLeave() {
    tileMapEditor_.tileMapExit();
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::tileMapMouseMove(Tales::InputEventData data) {
    tileMapEditor_.tileMapMouseMove(data);
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::tileMapMousePress(Tales::InputEventData data) {
    tileMapEditor_.tileMapMousePress(data);
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::tileMapMouseRelease(Tales::InputEventData data) {
    tileMapEditor_.tileMapMouseRelease(data);
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::tileMapMouseDoubleClick(Tales::InputEventData data) {
    tileMapEditor_.tileMapMouseDoubleClick(data);
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::tilePickerEnter() {
    tileMapEditor_.tilePickerEnter();
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::tilePickerLeave() {
    tileMapEditor_.tilePickerExit();
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::tilePickerMouseMove(Tales::InputEventData data) {
    tileMapEditor_.tilePickerMouseMove(data);
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::tilePickerMousePress(Tales::InputEventData data) {
    tileMapEditor_.tilePickerMousePress(data);
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::tilePickerMouseRelease(Tales::InputEventData data) {
    tileMapEditor_.tilePickerMouseRelease(data);
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::tilePickerMouseDoubleClick(Tales::InputEventData data) {
    tileMapEditor_.tilePickerMouseDoubleClick(data);
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::subtileEditorValueModified() {
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::on_gridCheckBox_clicked(bool checked)
{
    tileMapEditor_.setGridEnabled(checked);
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::on_regularButton_clicked(bool checked)
{
    tileMapEditor_.changeTool(TileMapEditorTools::regular);
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::on_pencilButton_clicked(bool checked)
{
    tileMapEditor_.changeTool(TileMapEditorTools::pencil);
    refreshDisplay();
}

void TalesQtTileMapEditorWidget::on_areaCloneButton_clicked(bool checked)
{
    tileMapEditor_.changeTool(TileMapEditorTools::areaClone);
    refreshDisplay();
}
