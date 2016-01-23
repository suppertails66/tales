#include "subtileeditorwidget.h"
#include "ui_subtileeditorwidget.h"
#include <cstdlib>

using namespace Tales;

SubtileEditorWidget::SubtileEditorWidget(QWidget *parent) :
    QFrame(parent),
    tile_(NULL),
    ui(new Ui::SubtileEditorWidget)
{
    ui->setupUi(this);

    setFrameShape(QFrame::Box);
}

SubtileEditorWidget::~SubtileEditorWidget()
{
    delete ui;
}

void SubtileEditorWidget::setTile(TileReference& tile__) {
    tile_ = &tile__;

    refreshDisplay();
}

void SubtileEditorWidget::refreshDisplay() {
    ui->ulTileBox->setValue(
                tile_->tileNum());

    ui->ulBGButton->setChecked(
                (tile_->priorityOption() == TileReference::priorityBG)
                    ? true
                    : false);
    ui->ulFGButton->setChecked(
                (tile_->priorityOption() == TileReference::priorityBG)
                    ? false
                    : true);

    ui->ulPal1Button->setChecked(
                (tile_->paletteOption() == TileReference::palette1)
                    ? false
                    : true);
    ui->ulPal2Button->setChecked(
                (tile_->paletteOption() == TileReference::palette1)
                    ? true
                    : false);

    ui->ulHFlipBox->setChecked(
                (tile_->horizontalMirroringOption() == TileReference::horizontalMirror)
                    ? true
                    : false);
    ui->ulVFlipBox->setChecked(
                (tile_->verticalMirroringOption() == TileReference::verticalMirror)
                    ? true
                    : false);
}

void SubtileEditorWidget::enableAll() {
    ui->paletteWidget->setEnabled(true);
    ui->priorityWidget->setEnabled(true);
    ui->flipWidget->setEnabled(true);
}

void SubtileEditorWidget::disableAllButTileNum() {
    ui->paletteWidget->setEnabled(false);
    ui->priorityWidget->setEnabled(false);
    ui->flipWidget->setEnabled(false);
}

void SubtileEditorWidget::setTileRange(int lower, int upper) {
    ui->ulTileBox->setRange(lower, upper);
}

void SubtileEditorWidget::setNameLabel(const std::string& nameLabel) {
    ui->nameLabel->setText(nameLabel.c_str());
}

void SubtileEditorWidget::on_ulTileBox_valueChanged(int arg1)
{
    tile_->setTileNum(arg1);
    emit valueModified();
}

void SubtileEditorWidget::on_ulHFlipBox_clicked(bool checked)
{
    tile_->setHorizontalMirroringOption(
                checked
                    ? TileReference::horizontalMirror
                    : TileReference::noHorizontalMirror);
    emit valueModified();
}

void SubtileEditorWidget::on_ulVFlipBox_clicked(bool checked)
{
    tile_->setVerticalMirroringOption(
                checked
                    ? TileReference::verticalMirror
                    : TileReference::noVerticalMirror);
    emit valueModified();
}

void SubtileEditorWidget::on_ulBGButton_clicked(bool checked)
{
    tile_->setPriorityOption(TileReference::priorityBG);
    emit valueModified();
}

void SubtileEditorWidget::on_ulFGButton_clicked(bool checked)
{
    tile_->setPriorityOption(TileReference::priorityFG);
    emit valueModified();
}

void SubtileEditorWidget::on_ulPal1Button_clicked(bool checked)
{
    tile_->setPaletteOption(TileReference::palette0);
    emit valueModified();
}

void SubtileEditorWidget::on_ulPal2Button_clicked(bool checked)
{
    tile_->setPaletteOption(TileReference::palette1);
    emit valueModified();
}
