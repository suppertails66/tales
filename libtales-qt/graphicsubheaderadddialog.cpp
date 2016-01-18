#include "graphicsubheaderadddialog.h"
#include "ui_graphicsubheaderadddialog.h"
#include "talesqtformatconversion.h"
#include "editors/GraphicToInfo.h"
#include "gamegear/GGTileSet.h"
#include <string>
#include <iostream>

using namespace Tales;

GraphicSubheaderAddDialog::GraphicSubheaderAddDialog(
        Tales::ObjectGraphicsHeader& srcData__,
        Tales::EditableLevelGraphicsData& levelGraphicsData__,
        Tales::GGPalette objectPalette__,
        QWidget *parent) :
    QDialog(parent),
    srcData_(srcData__),
    levelGraphicsData_(levelGraphicsData__),
    objectPalette_(objectPalette__),
    graphicIndex_(0),
    regularAndFlipped_(false),
    flipped_(false),
    ui(new Ui::GraphicSubheaderAddDialog)
{
    ui->setupUi(this);
    ui->regularRadioButton->setChecked(true);

    repopulate();

    updatePreview();
}

GraphicSubheaderAddDialog::~GraphicSubheaderAddDialog()
{
    delete ui;
}

void GraphicSubheaderAddDialog::repopulate() {
    ui->graphicSelectorTree->clear();

    for (int i = 0; i < GraphicToInfo::numCompressedGraphicInfos; i++) {
        GraphicInfo info = GraphicToInfo::compressedGraphicInfo(i);

        std::string categoryName
                = GraphicCategories::nameOfCategory(info.graphicCategory());

        // Find category
        QList<QTreeWidgetItem*> items
                = ui->graphicSelectorTree->findItems(QString(categoryName.c_str()),
                                                     Qt::MatchExactly);

        if (items.empty()) {
            // Add new category if needed
            QTreeWidgetItem* item = new QTreeWidgetItem(
                        ui->graphicSelectorTree);
            item->setText(0,
                          categoryName.c_str());
            ui->graphicSelectorTree->addTopLevelItem(item);

            items = ui->graphicSelectorTree->findItems(QString(categoryName.c_str()),
                                                       Qt::MatchExactly);
        }

        if (items.empty()) {
//            std::cerr << "error" << std::endl;
            continue;
        }

        QTreeWidgetItem* item = new QTreeWidgetItem(
                    items.at(0));
        item->setText(0,
                      info.name().c_str());
        item->setData(0, Qt::UserRole, QVariant(i));

        items.at(0)->addChild(item);
    }

    // Sort alphabetically
    ui->graphicSelectorTree->sortItems(0, Qt::AscendingOrder);
}

void GraphicSubheaderAddDialog::updatePreview() {
    GGTileSet tiles
            = levelGraphicsData_.compressedGraphic(graphicIndex_);

    if (flipped_) {
        for (int i = 0; i < tiles.numTiles(); i++) {
            tiles[i].flipHorizontal();
        }
    }

    Graphic graphic
            = tiles.toPalettizedGraphic(16,
                                        objectPalette_,
                                        Color(0, 0, 0, Color::fullAlphaOpacity));
    Graphic scaledGraphic(graphic.w() * 2,
                          graphic.h() * 2);
    graphic.scale(scaledGraphic);

    ui->graphicPreview->setPixmap(
                TalesQtFormatConversion::graphicToPixmap(scaledGraphic));

    ui->previewNumTilesLabel->setText(
                (StringConversion::toString(tiles.numTiles()) + " tiles").c_str());
}

int GraphicSubheaderAddDialog::graphicIndex() const {
    return graphicIndex_;
}

bool GraphicSubheaderAddDialog::regularAndFlipped() const {
    return regularAndFlipped_;
}

bool GraphicSubheaderAddDialog::flipped() const {
    return flipped_;
}

void GraphicSubheaderAddDialog::on_regularRadioButton_clicked(bool checked)
{
    flipped_ = !checked;
    regularAndFlipped_ = false;
    updatePreview();
}

void GraphicSubheaderAddDialog::on_flippedRadioButton_clicked(bool checked)
{
    flipped_ = checked;
    regularAndFlipped_ = false;
    updatePreview();
}

void GraphicSubheaderAddDialog::on_regularAndFlippedRadioButton_clicked(bool checked)
{
    flipped_ = !checked;
    regularAndFlipped_ = checked;
    updatePreview();
}

void GraphicSubheaderAddDialog::on_graphicSelectorTree_itemClicked(QTreeWidgetItem *item, int column)
{
    if (item->parent() == 0) {
        return;
    }

    graphicIndex_ = item->data(0, Qt::UserRole).toInt();

    updatePreview();
}
