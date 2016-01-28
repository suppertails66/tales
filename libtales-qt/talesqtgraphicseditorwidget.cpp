#include "talesqtgraphicseditorwidget.h"
#include "ui_talesqtgraphicseditorwidget.h"
#include "talesqtformatconversion.h"
#include "talesqtstatevar.h"
#include "nativegraphicexportdialog.h"
#include "editors/PaletteEditor.h"
#include "editors/GraphicToInfo.h"
#include "util/StringConversion.h"
#include "editors/GraphicToMappings.h"
#include <iostream>

using namespace Tales;
using namespace Luncheon;

TalesQtGraphicsEditorWidget::TalesQtGraphicsEditorWidget(QWidget *parent) :
    QWidget(parent),
    graphicsEditor_(appState_.editor().graphicsEditor()),
    ui(new Ui::TalesQtGraphicsEditorWidget)
{
    ui->setupUi(this);

//    ui->tilesScrollArea->takeWidget();
//    ui->tilesScrollArea->setWidget(ui->tilesLabel);

    QObject::connect(ui->tilesLabel,
                     SIGNAL(pickerEnter()),
                     this,
                     SLOT(tileEditorMouseEnter()));
    QObject::connect(ui->tilesLabel,
                     SIGNAL(pickerLeave()),
                     this,
                     SLOT(tileEditorMouseExit()));
    QObject::connect(ui->tilesLabel,
                     SIGNAL(pickerMouseMove(Tales::InputEventData)),
                     this,
                     SLOT(tileEditorMouseMove(Tales::InputEventData)));
    QObject::connect(ui->tilesLabel,
                     SIGNAL(pickerMousePress(Tales::InputEventData)),
                     this,
                     SLOT(tileEditorMousePress(Tales::InputEventData)));
    QObject::connect(ui->tilesLabel,
                     SIGNAL(pickerMouseRelease(Tales::InputEventData)),
                     this,
                     SLOT(tileEditorMouseRelease(Tales::InputEventData)));
    QObject::connect(ui->tilesLabel,
                     SIGNAL(pickerMouseDoubleClick(Tales::InputEventData)),
                     this,
                     SLOT(tileEditorMouseDoubleClick(Tales::InputEventData)));

    QObject::connect(ui->mappingLabel,
                     SIGNAL(pickerEnter()),
                     this,
                     SLOT(mappingEditorMouseEnter()));
    QObject::connect(ui->mappingLabel,
                     SIGNAL(pickerLeave()),
                     this,
                     SLOT(mappingEditorMouseExit()));
    QObject::connect(ui->mappingLabel,
                     SIGNAL(pickerMouseMove(Tales::InputEventData)),
                     this,
                     SLOT(mappingEditorMouseMove(Tales::InputEventData)));
    QObject::connect(ui->mappingLabel,
                     SIGNAL(pickerMousePress(Tales::InputEventData)),
                     this,
                     SLOT(mappingEditorMousePress(Tales::InputEventData)));
    QObject::connect(ui->mappingLabel,
                     SIGNAL(pickerMouseRelease(Tales::InputEventData)),
                     this,
                     SLOT(mappingEditorMouseRelease(Tales::InputEventData)));
    QObject::connect(ui->mappingLabel,
                     SIGNAL(pickerMouseDoubleClick(Tales::InputEventData)),
                     this,
                     SLOT(mappingEditorMouseDoubleClick(Tales::InputEventData)));

    QObject::connect(ui->paletteLabel,
                     SIGNAL(pickerEnter()),
                     this,
                     SLOT(colorPickerMouseEnter()));
    QObject::connect(ui->paletteLabel,
                     SIGNAL(pickerLeave()),
                     this,
                     SLOT(colorPickerMouseExit()));
    QObject::connect(ui->paletteLabel,
                     SIGNAL(pickerMouseMove(Tales::InputEventData)),
                     this,
                     SLOT(colorPickerMouseMove(Tales::InputEventData)));
    QObject::connect(ui->paletteLabel,
                     SIGNAL(pickerMousePress(Tales::InputEventData)),
                     this,
                     SLOT(colorPickerMousePress(Tales::InputEventData)));
    QObject::connect(ui->paletteLabel,
                     SIGNAL(pickerMouseRelease(Tales::InputEventData)),
                     this,
                     SLOT(colorPickerMouseRelease(Tales::InputEventData)));
    QObject::connect(ui->paletteLabel,
                     SIGNAL(pickerMouseDoubleClick(Tales::InputEventData)),
                     this,
                     SLOT(colorPickerMouseDoubleClick(Tales::InputEventData)));

    for (int i = 0; i < graphicsEditor_.numCompressedGraphics(); i++) {
        ui->graphicComboBox->addItem(
                    (std::string("Compressed ")
                     + StringConversion::toString(i)
                     + ": "
                     + GraphicToInfo::nameOfCompressedGraphic(i)).c_str(),
                    i);
    }

    for (int i = 0; i < graphicsEditor_.numUncompressedGraphics(); i++) {
        ui->graphicComboBox->addItem(
                    (std::string("Uncompressed ")
                     + StringConversion::toString(i)
                     + ": "
                     + GraphicToInfo::nameOfUncompressedGraphic(i)).c_str(),
                    i);
    }

    for (int i = 0; i < graphicsEditor_.numPalettes(); i++) {
        ui->paletteComboBox->addItem(
                    (StringConversion::toString(i)
                     + ": "
                     + PaletteEditor::nameOfPalette(i)).c_str(),
                    i);
    }

    changeGraphic(
                GraphicsEditor::compressed,
                0);

    refreshDisplay();
}

TalesQtGraphicsEditorWidget::~TalesQtGraphicsEditorWidget()
{
    delete ui;
}

void TalesQtGraphicsEditorWidget::refreshDisplay() {

    refreshTileDisplay();

    refreshPaletteDisplay();

    refreshMappingDisplay();
}

void TalesQtGraphicsEditorWidget::refreshPaletteDisplay() {
    if ((colorPickerBuffer_.w() != graphicsEditor_.colorPickerWidth())
            || (colorPickerBuffer_.h() != graphicsEditor_.colorPickerHeight())) {
        colorPickerBuffer_ = Graphic(graphicsEditor_.colorPickerWidth(),
                                    graphicsEditor_.colorPickerHeight());
        colorPickerQImageBuffer_ = QImage(colorPickerBuffer_.w(),
                                         colorPickerBuffer_.h(),
                                         QImage::Format_RGB32);
/*        colorPickerQImageBuffer_ = QImage(colorPickerBuffer_.const_imgdat(),
                                         colorPickerBuffer_.w(),
                                         colorPickerBuffer_.h(),
                                         QImage::Format_RGB32); */
    }

    ui->paletteComboBox->setCurrentIndex(
                graphicsEditor_.currentPaletteIndex());

//    Graphic g2(graphicsEditor_.colorPickerWidth(),
//               graphicsEditor_.colorPickerHeight());
    graphicsEditor_.drawColorPickerGraphic(colorPickerBuffer_);
    TalesQtFormatConversion::drawGraphicToImage(colorPickerQImageBuffer_,
                                                colorPickerBuffer_);
    ui->paletteLabel->setPixmap(
                QPixmap().fromImage(colorPickerQImageBuffer_));
//    ui->paletteLabel->adjustSize();
}

void TalesQtGraphicsEditorWidget::refreshTileDisplay() {
    if ((tileEditorBuffer_.w() != graphicsEditor_.tileEditorWidth())
            || (tileEditorBuffer_.h() != graphicsEditor_.tileEditorHeight())) {
        tileEditorBuffer_ = Graphic(graphicsEditor_.tileEditorWidth(),
                                    graphicsEditor_.tileEditorHeight());
        tileEditorQImageBuffer_ = QImage(tileEditorBuffer_.w(),
                                         tileEditorBuffer_.h(),
                                         QImage::Format_RGB32);
/*        tileEditorQImageBuffer_ = QImage(tileEditorBuffer_.const_imgdat(),
                                         tileEditorBuffer_.w(),
                                         tileEditorBuffer_.h(),
                                         QImage::Format_RGB32); */
    }

    graphicsEditor_.drawTileGraphic(tileEditorBuffer_);
    TalesQtFormatConversion::drawGraphicToImage(tileEditorQImageBuffer_,
                                                tileEditorBuffer_);
    ui->tilesLabel->setPixmap(
                QPixmap().fromImage(tileEditorQImageBuffer_));
//    ui->tilesLabel->adjustSize();
}

void TalesQtGraphicsEditorWidget::refreshMappingDisplay() {
    if (!(graphicsEditor_.mappingExists())) {
        ui->mappingLabel->clear();

        ui->collisionCheckBox->setEnabled(false);
        ui->xOffsetBox->setEnabled(false);
        ui->yOffsetBox->setEnabled(false);
        ui->widthBox->setEnabled(false);
        ui->heightBox->setEnabled(false);

        return;
    }
    else {
        ui->collisionCheckBox->setEnabled(true);
        ui->xOffsetBox->setEnabled(true);
        ui->yOffsetBox->setEnabled(true);
        ui->widthBox->setEnabled(true);
        ui->heightBox->setEnabled(true);
    }

    ui->xOffsetBox->setValue(
                graphicsEditor_.currentMapping().offsetX());
    ui->yOffsetBox->setValue(
                graphicsEditor_.currentMapping().offsetY());
    ui->widthBox->setValue(
                graphicsEditor_.currentMapping().collisionXLength());
    ui->heightBox->setValue(
                graphicsEditor_.currentMapping().collisionYLength());

    if ((mappingEditorBuffer_.w() != graphicsEditor_.mappingEditorWidth())
            || (mappingEditorBuffer_.h() != graphicsEditor_.mappingEditorHeight())) {
        mappingEditorBuffer_ = Graphic(graphicsEditor_.mappingEditorWidth(),
                                    graphicsEditor_.mappingEditorHeight());
        mappingEditorQImageBuffer_ = QImage(mappingEditorBuffer_.w(),
                                         mappingEditorBuffer_.h(),
                                         QImage::Format_ARGB32);
/*        mappingEditorQImageBuffer_ = QImage(mappingEditorBuffer_.const_imgdat(),
                                         mappingEditorBuffer_.w(),
                                         mappingEditorBuffer_.h(),
                                         QImage::Format_RGB32); */
    }

    graphicsEditor_.drawMappingGraphic(mappingEditorBuffer_);
    TalesQtFormatConversion::drawGraphicToImage(mappingEditorQImageBuffer_,
                                                mappingEditorBuffer_);
    ui->mappingLabel->setPixmap(
                QPixmap().fromImage(mappingEditorQImageBuffer_));
}

void TalesQtGraphicsEditorWidget::on_zoomComboBox_activated(int index)
{
    double scale = 1.00;

//    if (index < 2) {
//        scale /= ((2 - index) * 2);
//    }
//    else if (index > 2) {
        switch (index) {
        case 1:
            scale = 2.00;
            break;
        case 2:
            scale = 3.00;
            break;
        case 3:
            scale = 4.00;
            break;
        case 4:
            scale = 8.00;
            break;
        case 5:
            scale = 16.00;
            break;
        default:
            break;
        }
//    }

    graphicsEditor_.setScale(scale);

    refreshDisplay();
}

/*void TalesQtGraphicsEditorWidget::on_areaCloneToolButton_clicked()
{
    refreshDisplay();
} */

void TalesQtGraphicsEditorWidget::on_paintToolButton_clicked()
{
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::on_checkBox_2_clicked(bool checked)
{
    graphicsEditor_.setGridEnabled(checked);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::on_graphicComboBox_activated(int index)
{
    // lazy and bad compressed/uncompressed detection: compressed always
    // comes before uncompressed
    if (index < graphicsEditor_.numCompressedGraphics()) {
        changeGraphic(
                    GraphicsEditor::compressed,
                    ui->graphicComboBox->itemData(index).toInt());
    }
    else {
        changeGraphic(
                    GraphicsEditor::uncompressed,
                    ui->graphicComboBox->itemData(index).toInt());
    }
}

void TalesQtGraphicsEditorWidget::changeGraphic(
        Tales::GraphicsEditor::GraphicCompressionType compressionType,
        int index) {
    graphicsEditor_.changeGraphic(
                compressionType,
                index);

    repopulateMappingBox(compressionType,
                         index);

    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::repopulateMappingBox(
        GraphicsEditor::GraphicCompressionType compressionType,
        int index) {
    ui->mappingComboBox->clear();

    GraphicToMappings::CompressionType localType
            = GraphicToMappings::compressed;

    if (compressionType == GraphicsEditor::uncompressed) {
        localType = GraphicToMappings::uncompressed;
    }

    int numMappings = GraphicToMappings::numMappingsForGraphic(
                localType, index);

    if (numMappings == 0) {
        return;
    }

    for (int i = 0; i < numMappings; i++) {
        GraphicToMappingEntry entry = GraphicToMappings::graphicMapping(
                    localType,
                    index,
                    i);

        ui->mappingComboBox->addItem(
                    (StringConversion::toString(i)
                     + ": "
                     + entry.name).c_str(),
                    i);
    }
}

void TalesQtGraphicsEditorWidget::on_transparencyCheckBox_clicked(bool checked)
{
    graphicsEditor_.setTransparencyEnabled(checked);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::on_paletteComboBox_activated(int index)
{
    graphicsEditor_.setCurrentPaletteIndex(index);
    graphicsEditor_.setCurrentPaletteDefault(index);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::tileEditorMouseEnter() {
    graphicsEditor_.tileEditorEnterMouse();
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::tileEditorMouseExit() {
    graphicsEditor_.tileEditorExitMouse();
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::tileEditorMouseMove(InputEventData eventData) {
    graphicsEditor_.tileEditorMoveMouse(eventData);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::tileEditorMousePress(InputEventData eventData) {
    graphicsEditor_.tileEditorPressMouse(eventData);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::tileEditorMouseRelease(InputEventData eventData) {
    graphicsEditor_.tileEditorReleaseMouse(eventData);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::tileEditorMouseDoubleClick(InputEventData eventData) {
    graphicsEditor_.tileEditorDoubleClickMouse(eventData);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::mappingEditorMouseEnter() {
    graphicsEditor_.mappingEditorEnterMouse();
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::mappingEditorMouseExit() {
    graphicsEditor_.mappingEditorExitMouse();
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::mappingEditorMouseMove(InputEventData eventData) {
    graphicsEditor_.mappingEditorMoveMouse(eventData);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::mappingEditorMousePress(InputEventData eventData) {
    graphicsEditor_.mappingEditorPressMouse(eventData);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::mappingEditorMouseRelease(InputEventData eventData) {
    graphicsEditor_.mappingEditorReleaseMouse(eventData);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::mappingEditorMouseDoubleClick(InputEventData eventData) {
    graphicsEditor_.mappingEditorDoubleClickMouse(eventData);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::colorPickerMouseEnter() {
    graphicsEditor_.colorPickerEnterMouse();
    refreshPaletteDisplay();
}

void TalesQtGraphicsEditorWidget::colorPickerMouseExit() {
    graphicsEditor_.colorPickerExitMouse();
    refreshPaletteDisplay();
}

void TalesQtGraphicsEditorWidget::colorPickerMouseMove(InputEventData eventData) {
    graphicsEditor_.colorPickerMoveMouse(eventData);
    refreshPaletteDisplay();
}

void TalesQtGraphicsEditorWidget::colorPickerMousePress(InputEventData eventData) {
    graphicsEditor_.colorPickerPressMouse(eventData);
    graphicsEditor_.setCurrentColorIndex(
                graphicsEditor_.colorPickerCurrentIndex());
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::colorPickerMouseRelease(InputEventData eventData) {
    graphicsEditor_.colorPickerReleaseMouse(eventData);
    refreshPaletteDisplay();
}

void TalesQtGraphicsEditorWidget::colorPickerMouseDoubleClick(InputEventData eventData) {
    graphicsEditor_.colorPickerDoubleClickMouse(eventData);
    refreshPaletteDisplay();
}

void TalesQtGraphicsEditorWidget::on_paintToolButton_clicked(bool checked)
{
//    if (checked) {
        ui->paintToolButton->setChecked(true);
//        ui->areaCloneToolButton->setChecked(false);
        graphicsEditor_.changeTool(GraphicsEditorTools::pencil);
//    }

    refreshDisplay();
}

/*void TalesQtGraphicsEditorWidget::on_areaCloneToolButton_clicked(bool checked)
{
    if (checked) {
        ui->paintToolButton->setChecked(false);
//        ui->areaCloneToolButton->setChecked(true);
        graphicsEditor_.changeTool(GraphicsEditorTools::areaClone);
    }

    refreshDisplay();
} */

void TalesQtGraphicsEditorWidget::on_mappingComboBox_activated(int index)
{
    graphicsEditor_.changeMapping(index);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::on_collisionCheckBox_clicked(bool checked)
{
    graphicsEditor_.setCollisionViewEnabled(checked);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::on_xOffsetBox_valueChanged(int arg1)
{
    graphicsEditor_.currentMapping().setOffsetX(arg1);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::on_yOffsetBox_valueChanged(int arg1)
{
    graphicsEditor_.currentMapping().setOffsetY(arg1);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::on_widthBox_valueChanged(int arg1)
{
    graphicsEditor_.currentMapping().setCollisionXLength(arg1);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::on_heightBox_valueChanged(int arg1)
{
    graphicsEditor_.currentMapping().setCollisionYLength(arg1);
    refreshDisplay();
}

void TalesQtGraphicsEditorWidget::on_exportButton_clicked()
{
//    graphicsEditor_.exportAllMappings();
    NativeGraphicExportDialog(this).exec();
}

void TalesQtGraphicsEditorWidget::on_importButton_clicked(bool checked)
{
    graphicsEditor_.importAllTiles("graphicsnative/");
    graphicsEditor_.importAllMappings("graphicsnative/");
    refreshDisplay();
}
