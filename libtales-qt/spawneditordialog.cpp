#include "spawneditordialog.h"
#include "ui_spawneditordialog.h"
#include "util/StringConversion.h"

using namespace Tales;
using namespace Luncheon;

SpawnEditorDialog::SpawnEditorDialog(Tales::LevelSpawnGraphicSceneLayer&
                                     levelSpawnGraphicSceneLayer__,
                                     Tales::SpawnPoint& spawnPoint__,
                                     QWidget *parent) :
    QDialog(parent),
    levelSpawnGraphicSceneLayer_(levelSpawnGraphicSceneLayer__),
    spawnPoint_(spawnPoint__),
    ui(new Ui::SpawnEditorDialog)
{
    ui->setupUi(this);

    refreshDisplay();
}

SpawnEditorDialog::~SpawnEditorDialog()
{
    delete ui;
}

void SpawnEditorDialog::refreshDisplay() {
    ui->spawnNumberLabel->setText(
                (std::string("Spawn ")
                + StringConversion::toString(
                    levelSpawnGraphicSceneLayer_
                        .selectedSpawnNumber())).c_str());
    ui->tailsXBox->setValue(spawnPoint_.tailsX());
    ui->tailsYBox->setValue(spawnPoint_.tailsY());
    ui->camXBox->setValue(
                 spawnPoint_.camX() - spawnPoint_.tailsX());
    ui->camYBox->setValue(
                 spawnPoint_.camY() - spawnPoint_.tailsY());
}

void SpawnEditorDialog::on_tailsXBox_valueChanged(int arg1)
{
    spawnPoint_.setCamX(spawnPoint_.camX()
                        + (arg1 - spawnPoint_.tailsX()));
    spawnPoint_.setTailsX(arg1);
}

void SpawnEditorDialog::on_tailsYBox_valueChanged(int arg1)
{
    spawnPoint_.setCamY(spawnPoint_.camY()
                        + (arg1 - spawnPoint_.tailsY()));
    spawnPoint_.setTailsY(arg1);
}

void SpawnEditorDialog::on_camXBox_valueChanged(int arg1)
{
    spawnPoint_.setCamX(spawnPoint_.tailsX() + arg1);
}

void SpawnEditorDialog::on_camYBox_valueChanged(int arg1)
{
    spawnPoint_.setCamY(spawnPoint_.tailsY() + arg1);
}
