#include "graphicsexportdialog.h"
#include "ui_graphicsexportdialog.h"
#include "talesqtstatevar.h"
#include "talesqtformatconversion.h"
#include "util/StringConversion.h"
#include "gamedata/PrimaryMaps.h"
#include "gamedata/SubMaps.h"
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

    for (int i = 0; i < appState_.editor().levelEditor()
                            .levelHeaders().size(); i++) {
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

    QImage exportImage;
    TalesQtFormatConversion::drawGraphicToImageWithAlpha(exportImage, g);

    exportImage.save(exportFileName.c_str(), 0);
}
