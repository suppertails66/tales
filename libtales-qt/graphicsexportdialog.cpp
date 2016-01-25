#include "graphicsexportdialog.h"
#include "ui_graphicsexportdialog.h"
#include "talesqtstatevar.h"
#include "talesqtformatconversion.h"
#include "util/StringConversion.h"
#include "gamedata/PrimaryMaps.h"
#include "gamedata/SubMaps.h"
#include "editors/GraphicToMappings.h"
#include <QFileDialog>
#include <iostream>

using namespace Tales;
using namespace Luncheon;

GraphicsExportDialog::GraphicsExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphicsExportDialog)
{
    ui->setupUi(this);
}

GraphicsExportDialog::~GraphicsExportDialog()
{
    delete ui;
}

void GraphicsExportDialog::on_mapExportButton_clicked(bool checked)
{
    QString foldername = QFileDialog::getExistingDirectory(
                this, tr("Choose map export directory"),
                "");

    if (foldername.size() == 0) {
        return;
    }

    int numIndices = appState_.editor().levelEditor()
            .levelHeaders().size();

    ui->progressBar->setRange(0, numIndices - 1);
    ui->progressBar->setValue(0);

    for (int i = 0; i < numIndices; i++) {
        if (ui->levelVisualBox->isChecked()) {
            exportMap(i, ResourceExportIDs::mapVisual, foldername.toStdString());
        }

        if (ui->levelBehaviorBox->isChecked()) {
            exportMap(i, ResourceExportIDs::mapBehavior, foldername.toStdString());
        }

        if (ui->levelBehaviorBox->isChecked()) {
            exportMap(i, ResourceExportIDs::mapVertSolidity, foldername.toStdString());
        }

        if (ui->levelBehaviorBox->isChecked()) {
            exportMap(i, ResourceExportIDs::mapHorizSolidity, foldername.toStdString());
        }

        ui->progressBar->setValue(i);
    }

//    std::cout << foldername.toStdString() << std::endl;
}

void GraphicsExportDialog::on_graphicExportButton_clicked(bool checked)
{
    QString foldername = QFileDialog::getExistingDirectory(
                this, tr("Choose graphics export directory"),
                "");

    if (foldername.size() == 0) {
        return;
    }

    int compressed = appState_.editor().graphicsEditor().numCompressedGraphics();
    int uncompressed = appState_.editor().graphicsEditor().numUncompressedGraphics();
    int total = compressed + uncompressed;

    Graphic g;

    ui->progressBar->setRange(0, total);
    ui->progressBar->setValue(0);

    int count = 0;

    for (int i = 0; i < compressed; i++) {
        if (ui->rawGraphicsBox->isChecked()) {
            appState_.editor().exportTileGraphic(
                        g,
                        GraphicsEditor::compressed,
                        i,
                        ui->transparencyBox->isChecked());

            std::string filename = foldername.toStdString()
                    + "/"
                    + "grp-tiles-compressed-"
                    + StringConversion::toString(i)
                    + ".png";

            exportGraphic(g,filename);
        }

        int numMappings = GraphicToMappings::numMappingsForGraphic(
                    GraphicToMappings::compressed, i);

        if (ui->spriteMappingsBox->isChecked()) {
            for (int j = 0; j < numMappings; j++) {
                appState_.editor().exportSpriteMapping(
                            g,
                            GraphicsEditor::compressed,
                            i,
                            j);

                std::string filename = foldername.toStdString()
                        + "/"
                        + "grp-spritemap-compressed-"
                        + StringConversion::toString(i)
                        + "-"
                        + StringConversion::toString(j)
                        + ".png";

                exportGraphic(g,filename);
            }
        }

        if (ui->alignedSpriteMappingsBox->isChecked()) {
            for (int j = 0; j < numMappings; j++) {
                appState_.editor().exportAlignedSpriteMapping(
                            g,
                            GraphicsEditor::compressed,
                            i,
                            j);

                std::string filename = foldername.toStdString()
                        + "/"
                        + "grp-aligned-spritemap-compressed-"
                        + StringConversion::toString(i)
                        + "-"
                        + StringConversion::toString(j)
                        + ".png";

                exportGraphic(g,filename);
            }
        }

        ++count;
        ui->progressBar->setValue(count);
    }

    for (int i = 0; i < uncompressed; i++) {
        if (ui->rawGraphicsBox->isChecked()) {
            appState_.editor().exportTileGraphic(
                        g,
                        GraphicsEditor::uncompressed,
                        i,
                        ui->transparencyBox->isChecked());

            std::string filename = foldername.toStdString()
                    + "/"
                    + "grp-tiles-uncompressed-"
                    + StringConversion::toString(i)
                    + ".png";

            exportGraphic(g, filename);
        }

        int numMappings = GraphicToMappings::numMappingsForGraphic(
                    GraphicToMappings::uncompressed, i);

        if (ui->spriteMappingsBox->isChecked()) {
            for (int j = 0; j < numMappings; j++) {
                appState_.editor().exportSpriteMapping(
                            g,
                            GraphicsEditor::uncompressed,
                            i,
                            j);

                std::string filename = foldername.toStdString()
                        + "/"
                        + "grp-spritemap-uncompressed-"
                        + StringConversion::toString(i)
                        + "-"
                        + StringConversion::toString(j)
                        + ".png";

                exportGraphic(g,filename);
            }
        }

        if (ui->alignedSpriteMappingsBox->isChecked()) {
            for (int j = 0; j < numMappings; j++) {
                appState_.editor().exportAlignedSpriteMapping(
                            g,
                            GraphicsEditor::uncompressed,
                            i,
                            j);

                std::string filename = foldername.toStdString()
                        + "/"
                        + "grp-aligned-spritemap-uncompressed-"
                        + StringConversion::toString(i)
                        + "-"
                        + StringConversion::toString(j)
                        + ".png";

                exportGraphic(g,filename);
            }
        }

        ++count;
        ui->progressBar->setValue(count);
    }
}

void GraphicsExportDialog::exportMap(int index,
               Tales::ResourceExportIDs::MapExportID exportID,
                                     std::string foldername) {
    AreaMapReference areaNums
            = appState_.editor().levelEditor()
                .levelHeaders().areaMapNumOfIndex(index);

    Graphic g;

    appState_.editor().exportMap(g,
                                 index,
                                 exportID,
                                 ui->levelObjectsBox->isChecked(),
                                 ui->levelSpawnsBox->isChecked(),
                                 ui->levelCameraBoundsBox->isChecked());

    std::string exportFileName = foldername
            + "/"
            + "map_"
            + StringConversion::toString(areaNums.areaNum())
            + "-"
            + StringConversion::toString(areaNums.mapNum())
            + "_index-"
            + StringConversion::toString(index);

    switch (exportID) {
    case ResourceExportIDs::mapVisual:
        exportFileName += "_visual";
        break;
    case ResourceExportIDs::mapBehavior:
        exportFileName += "_behavior";
        break;
    case ResourceExportIDs::mapVertSolidity:
        exportFileName += "_vertsolidity";
        break;
    case ResourceExportIDs::mapHorizSolidity:
        exportFileName += "_horizsolidity";
        break;
    default:
        break;
    }

    exportFileName += ".png";

//        std::cout << exportFileName << std::endl;

    exportGraphic(g, exportFileName.c_str());
}

void GraphicsExportDialog::exportGraphic(Tales::Graphic graphic,
                   std::string filename) {
    QImage exportImage;
    TalesQtFormatConversion::drawGraphicToImageWithAlpha(exportImage, graphic);
    exportImage.save(filename.c_str(), 0);
}

void GraphicsExportDialog::on_metatileExportButton_clicked(bool checked)
{
    QString foldername = QFileDialog::getExistingDirectory(
                this, tr("Choose metatile export directory"),
                "");

    if (foldername.size() == 0) {
        return;
    }

    int numSets = appState_.editor().metatileStructureEditor()
            .numMetatileStructureSets();

    ui->progressBar->setRange(0, numSets - 1);
    ui->progressBar->setValue(0);

    Graphic g;

    for (int i = 0; i < numSets; i++) {
        if (ui->metatileAggregateBox->isChecked()) {
            appState_.editor().exportMetatileSet(
                        g, i);

            std::string exportFileName = foldername.toStdString()
                    + "/"
                    + "tileset-"
                    + StringConversion::toString(i)
                    + ".png";

            exportGraphic(g, exportFileName);
        }

        if (ui->metatileIndividualBox->isChecked()) {
            for (int j = 0; j < MetatileStructures::numMetatilesPerTable; j++) {
                appState_.editor().exportMetatile(
                            g, i, j);

                std::string exportFileName = foldername.toStdString()
                        + "/"
                        + "tileset-"
                        + StringConversion::toString(i)
                        + "-tile-"
                        + StringConversion::toString(j)
                        + ".png";

                exportGraphic(g, exportFileName);
            }
        }

        ui->progressBar->setValue(i);
    }
}

void GraphicsExportDialog::on_tilemapExportButton_clicked(bool checked)
{
    QString foldername = QFileDialog::getExistingDirectory(
                this, tr("Choose tilemap export directory"),
                "");

    if (foldername.size() == 0) {
        return;
    }

    int numSets = appState_.editor().tileMapEditor()
            .numTileMaps();

    ui->progressBar->setRange(0, numSets - 1);
    ui->progressBar->setValue(0);

    Graphic g;

    for (int i = 0; i < numSets; i++) {
        appState_.editor().exportTileMap(
                    g, i);

        std::string exportFileName = foldername.toStdString()
                + "/"
                + "tilemap-"
                + StringConversion::toString(i)
                + ".png";

        exportGraphic(g, exportFileName);

        ui->progressBar->setValue(i);
    }
}
