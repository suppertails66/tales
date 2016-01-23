#include "talesqttilemapeditorwidget.h"
#include "ui_talesqttilemapeditorwidget.h"

TalesQtTileMapEditorWidget::TalesQtTileMapEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TalesQtTileMapEditorWidget)
{
    ui->setupUi(this);
}

TalesQtTileMapEditorWidget::~TalesQtTileMapEditorWidget()
{
    delete ui;
}

void TalesQtTileMapEditorWidget::refreshDisplay() {

}
