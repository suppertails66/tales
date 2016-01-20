#include "warpeditdialog.h"
#include "ui_warpeditdialog.h"
#include "gamedata/PrimaryMaps.h"
#include "gamedata/SubMaps.h"
#include "util/StringConversion.h"

using namespace Tales;
using namespace Luncheon;

WarpEditDialog::WarpEditDialog(Tales::WarpDestinationCollection warps__,
                               Tales::EditableSpawnPoints& spawnPoints__,
                               QWidget *parent) :
    QDialog(parent),
    warps_(warps__),
    spawnPoints_(spawnPoints__),
    activeWarp_(0),
    ui(new Ui::WarpEditDialog)
{
    ui->setupUi(this);

    if (!(warps__.size())) {
        reject();
    }

    reloadWarpNumberBox();
    reloadAreaBox();

//    loadWarp(warps__[0]);
    loadWarp(warps_[0]);
}

WarpEditDialog::~WarpEditDialog()
{
    delete ui;
}

Tales::WarpDestinationCollection WarpEditDialog::warps() {
    return warps_;
}

void WarpEditDialog::loadWarp(Tales::WarpDestination& warp) {
    activeWarp_ = &warp;

    reloadMapBox();
    reloadSpawnBox();

    for (int i = 0; i < ui->areaBox->count(); i++) {
        if (ui->areaBox->itemData(i).toInt()
                == activeWarp_->primaryMapDestination()) {
            ui->areaBox->setCurrentIndex(i);
        }
    }

    for (int i = 0; i < ui->mapBox->count(); i++) {
        if (ui->mapBox->itemData(i).toInt()
                == activeWarp_->subMapDestination()) {
            ui->mapBox->setCurrentIndex(i);
        }
    }

    for (int i = 0; i < ui->spawnBox->count(); i++) {
        if (ui->spawnBox->itemData(i).toInt()
                == activeWarp_->destinationSpawnIndex()) {
            ui->spawnBox->setCurrentIndex(i);
        }
    }

    if (activeWarp_->levelUnlocked(
                PrimaryMaps::poloyForest)) {
        ui->areaBox_1->setChecked(true);
    }
    else {
        ui->areaBox_1->setChecked(false);
    }
    if (activeWarp_->levelUnlocked(
                PrimaryMaps::caronForest)) {
        ui->areaBox_2->setChecked(true);
    }
    else {
        ui->areaBox_2->setChecked(false);
    }
    if (activeWarp_->levelUnlocked(
                PrimaryMaps::volcanicTunnel)) {
        ui->areaBox_3->setChecked(true);
    }
    else {
        ui->areaBox_3->setChecked(false);
    }
    if (activeWarp_->levelUnlocked(
                PrimaryMaps::pollyMtn1)) {
        ui->areaBox_4->setChecked(true);
    }
    else {
        ui->areaBox_4->setChecked(false);
    }
    if (activeWarp_->levelUnlocked(
                PrimaryMaps::pollyMtn2)) {
        ui->areaBox_5->setChecked(true);
    }
    else {
        ui->areaBox_5->setChecked(false);
    }
    if (activeWarp_->levelUnlocked(
                PrimaryMaps::lakeRocky)) {
        ui->areaBox_6->setChecked(true);
    }
    else {
        ui->areaBox_6->setChecked(false);
    }
    if (activeWarp_->levelUnlocked(
                PrimaryMaps::lakeCrystal)) {
        ui->areaBox_7->setChecked(true);
    }
    else {
        ui->areaBox_7->setChecked(false);
    }
    if (activeWarp_->levelUnlocked(
                PrimaryMaps::greenIsland)) {
        ui->areaBox_8->setChecked(true);
    }
    else {
        ui->areaBox_8->setChecked(false);
    }
    if (activeWarp_->levelUnlocked(
                PrimaryMaps::cavernIsland)) {
        ui->areaBox_9->setChecked(true);
    }
    else {
        ui->areaBox_9->setChecked(false);
    }
    if (activeWarp_->levelUnlocked(
                PrimaryMaps::cocoIsland)) {
        ui->areaBox_10->setChecked(true);
    }
    else {
        ui->areaBox_10->setChecked(false);
    }
    if (activeWarp_->levelUnlocked(
                PrimaryMaps::battleFortressFlight)) {
        ui->areaBox_11->setChecked(true);
    }
    else {
        ui->areaBox_11->setChecked(false);
    }
    if (activeWarp_->levelUnlocked(
                PrimaryMaps::battleFortress)) {
        ui->areaBox_12->setChecked(true);
    }
    else {
        ui->areaBox_12->setChecked(false);
    }
}

void WarpEditDialog::reloadWarpNumberBox() {
    ui->warpNumberBox->clear();
    for (int i = 0; i < warps_.size(); i++) {
        std::string namestr;

        if (warps_[i].primaryMapDestination()
                == PrimaryMaps::worldMap) {
            namestr += "World map, area "
                    + StringConversion::toString(
                        warps_[i].destinationSpawnIndex());
        }
        else {
            namestr += StringConversion::toString(
                        i)
                    + ": "
                    + StringConversion::toString(
                        warps_[i].primaryMapDestination())
                    + "-"
                    + StringConversion::toString(
                        warps_[i].subMapDestination())
                    + ", spawn "
                    + StringConversion::toString(
                        warps_[i].destinationSpawnIndex());
        }

        ui->warpNumberBox->addItem(
                    namestr.c_str(),
                    i);
    }
}

void WarpEditDialog::reloadAreaBox() {
    ui->areaBox->clear();

    for (int i = 1; i <= 0x0C; i++) {
        std::string namestr;
        namestr += StringConversion::toString(
                    i);
        ui->areaBox->addItem(
                    namestr.c_str(), i);
    }

    ui->areaBox->addItem(
                "World map", PrimaryMaps::worldMap);
}

void WarpEditDialog::reloadMapBox() {
    ui->mapBox->clear();

/*    if (activeWarp_->primaryMapDestination()
            == PrimaryMaps::worldMap) {
        std::string namestr;
        namestr += StringConversion::toString(
                    1);
        ui->mapBox->addItem(
                    namestr.c_str(), 1);
    } */
//    else {
        int numMaps = SubMaps::subMapCounts[
                activeWarp_->primaryMapDestination()];
        for (int i = 0; i < numMaps; i++) {
            std::string namestr;
            namestr += StringConversion::toString(
                        i + 1);
            ui->mapBox->addItem(
                        namestr.c_str(), i + 1);
        }
//    }
}

void WarpEditDialog::reloadSpawnBox() {
    ui->spawnBox->clear();

    if (activeWarp_->primaryMapDestination()
            == PrimaryMaps::worldMap) {
        for (int i = 1; i <= 0x0C; i++) {
            std::string namestr;
            namestr += "Area "
                    + StringConversion::toString(
                        i);
            ui->spawnBox->addItem(
                        namestr.c_str(), i);
        }

        ui->spawnBox->addItem(
                    "Coco Island escape", 0xFF);
    }
    else {
        SpawnPointCollection& spawns
                = spawnPoints_.spawnsByMapnum(
                    activeWarp_->primaryMapDestination(),
                    activeWarp_->subMapDestination());

        int num = 0;
        for (SpawnPointCollection::iterator it = spawns.begin();
             it != spawns.end();
             ++it) {
            std::string namestr;
            namestr += StringConversion::toString(
                        num);
            ui->spawnBox->addItem(
                        namestr.c_str(), num);

            ++num;
        }
    }
}


void WarpEditDialog::on_warpNumberBox_activated(int index)
{
    loadWarp(warps_[index]);
}

void WarpEditDialog::on_areaBox_1_clicked(bool checked)
{
    activeWarp_->setLevelUnlocked(
                static_cast<PrimaryMaps::PrimaryMap>(1),
                checked);
}

void WarpEditDialog::on_areaBox_2_clicked(bool checked)
{
    activeWarp_->setLevelUnlocked(
                static_cast<PrimaryMaps::PrimaryMap>(2),
                checked);
}

void WarpEditDialog::on_areaBox_3_clicked(bool checked)
{
    activeWarp_->setLevelUnlocked(
                static_cast<PrimaryMaps::PrimaryMap>(3),
                checked);
}

void WarpEditDialog::on_areaBox_4_clicked(bool checked)
{
    activeWarp_->setLevelUnlocked(
                static_cast<PrimaryMaps::PrimaryMap>(4),
                checked);
}

void WarpEditDialog::on_areaBox_5_clicked(bool checked)
{
    activeWarp_->setLevelUnlocked(
                static_cast<PrimaryMaps::PrimaryMap>(5),
                checked);
}

void WarpEditDialog::on_areaBox_6_clicked(bool checked)
{
    activeWarp_->setLevelUnlocked(
                static_cast<PrimaryMaps::PrimaryMap>(6),
                checked);
}

void WarpEditDialog::on_areaBox_7_clicked(bool checked)
{
    activeWarp_->setLevelUnlocked(
                static_cast<PrimaryMaps::PrimaryMap>(7),
                checked);
}

void WarpEditDialog::on_areaBox_8_clicked(bool checked)
{
    activeWarp_->setLevelUnlocked(
                static_cast<PrimaryMaps::PrimaryMap>(8),
                checked);
}

void WarpEditDialog::on_areaBox_9_clicked(bool checked)
{
    activeWarp_->setLevelUnlocked(
                static_cast<PrimaryMaps::PrimaryMap>(9),
                checked);
}

void WarpEditDialog::on_areaBox_10_clicked(bool checked)
{
    activeWarp_->setLevelUnlocked(
                static_cast<PrimaryMaps::PrimaryMap>(10),
                checked);
}

void WarpEditDialog::on_areaBox_11_clicked(bool checked)
{
    activeWarp_->setLevelUnlocked(
                static_cast<PrimaryMaps::PrimaryMap>(11),
                checked);
}

void WarpEditDialog::on_areaBox_12_clicked(bool checked)
{
    activeWarp_->setLevelUnlocked(
                static_cast<PrimaryMaps::PrimaryMap>(12),
                checked);
}

void WarpEditDialog::on_areaBox_activated(int index)
{
    activeWarp_->setPrimaryMapDestination(
                static_cast<PrimaryMaps::PrimaryMap>
                (ui->areaBox->itemData(index).toInt()));
    activeWarp_->setSubMapDestination(1);
    activeWarp_->setDestinationSpawnIndex(0);

    reloadMapBox();
    reloadSpawnBox();
}

void WarpEditDialog::on_mapBox_activated(int index)
{
    activeWarp_->setSubMapDestination(
                ui->mapBox->itemData(index).toInt());
    activeWarp_->setDestinationSpawnIndex(0);

    reloadSpawnBox();
}

void WarpEditDialog::on_spawnBox_activated(int index)
{
    activeWarp_->setDestinationSpawnIndex(
                ui->spawnBox->itemData(index).toInt());
}
