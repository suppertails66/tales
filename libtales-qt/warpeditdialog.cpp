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

    bool mapFound = selectCurrentMap();

    bool spawnFound = false;
    if (mapFound) {
        spawnFound = selectCurrentSpawn();
    }

    if (!mapFound || !spawnFound) {
        if (!ui->mapOverrideEnabledBox->isChecked()) {
            turnOnMapOverride(activeWarp_->subMapDestination(),
                              activeWarp_->destinationSpawnIndex());
        }
    }
    else {
        if (ui->mapOverrideEnabledBox->isChecked()) {
            turnOffMapOverride();
        }

//        reloadMapBox();
//        reloadSpawnBox();
//        selectCurrentMap();
//        selectCurrentSpawn();
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
        for (int i = 0; i <= 0x0C; i++) {
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
        try {
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
        catch (OutOfRangeIndexException& e) {

        }
    }
}

void WarpEditDialog::turnOnMapOverride(int mapNum,
                                       int spawnNum) {
    ui->mapOverrideEnabledBox->setChecked(true);
    ui->mapOverrideNumBox->setEnabled(true);
    ui->mapOverrideNumBox->setValue(mapNum);
    ui->spawnOverrideNumBox->setEnabled(true);
    ui->spawnOverrideNumBox->setValue(spawnNum);

    ui->mapBox->setEnabled(false);
    ui->spawnBox->setEnabled(false);

    activeWarp_->setSubMapDestination(mapNum);
    activeWarp_->setDestinationSpawnIndex(spawnNum);
}

void WarpEditDialog::turnOffMapOverride() {
    ui->mapBox->setEnabled(true);
    ui->spawnBox->setEnabled(true);

    ui->mapOverrideEnabledBox->setChecked(false);
    ui->mapOverrideNumBox->setEnabled(false);
    activeWarp_->setSubMapDestination(
                ui->mapBox->itemData(
                    ui->mapBox->currentIndex()).toInt());
    ui->spawnOverrideNumBox->setEnabled(false);
    activeWarp_->setDestinationSpawnIndex(
                ui->spawnBox->itemData(
                    ui->spawnBox->currentIndex()).toInt());

    reloadMapBox();
    reloadSpawnBox();
}

bool WarpEditDialog::selectCurrentMap() {
    for (int i = 0; i < ui->mapBox->count(); i++) {
        if (ui->mapBox->itemData(i).toInt()
                == activeWarp_->subMapDestination()) {
            ui->mapBox->setCurrentIndex(i);
            return true;
        }
    }
}

bool WarpEditDialog::selectCurrentSpawn() {
    for (int i = 0; i < ui->spawnBox->count(); i++) {
        if (ui->spawnBox->itemData(i).toInt()
                == activeWarp_->destinationSpawnIndex()) {
            ui->spawnBox->setCurrentIndex(i);
            return true;
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

void WarpEditDialog::on_mapOverrideEnabledBox_clicked(bool checked)
{
/*    if (checked) {
        turnOnMapOverride(activeWarp_->subMapDestination(),
                          activeWarp_->destinationSpawnIndex());
    }
    else {
        turnOffMapOverride();
    } */
}

void WarpEditDialog::on_mapOverrideNumBox_valueChanged(int arg1)
{
    activeWarp_->setSubMapDestination(arg1);
}

void WarpEditDialog::on_spawnOverrideNumBox_valueChanged(int arg1)
{
    activeWarp_->setDestinationSpawnIndex(arg1);
}

void WarpEditDialog::on_mapOverrideEnabledBox_toggled(bool checked)
{
    if (checked) {
        turnOnMapOverride(activeWarp_->subMapDestination(),
                          activeWarp_->destinationSpawnIndex());
    }
    else {
        turnOffMapOverride();
    }
}
