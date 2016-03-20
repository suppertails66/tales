#ifndef WARPEDITDIALOG_H
#define WARPEDITDIALOG_H

#include <QDialog>
#include "gamedata/EditableWarpDestinations.h"
#include "gamedata/EditableSpawnPoints.h"

namespace Ui {
class WarpEditDialog;
}

class WarpEditDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit WarpEditDialog(Tales::WarpDestinationCollection warps__,
                            Tales::EditableSpawnPoints& spawnPoints__,
                            QWidget *parent = 0);
    ~WarpEditDialog();

    Tales::WarpDestinationCollection warps();

    void loadWarp(Tales::WarpDestination& warp);

protected:
    void reloadWarpNumberBox();
    void reloadAreaBox();
    void reloadMapBox();
    void reloadSpawnBox();

    void turnOnMapOverride(int mapNum,
                           int spawnNum);
    void turnOffMapOverride();

    bool selectCurrentMap();
    bool selectCurrentSpawn();

    Tales::WarpDestinationCollection warps_;
    Tales::WarpDestination* activeWarp_;
    Tales::EditableSpawnPoints& spawnPoints_;
    
private slots:
    void on_warpNumberBox_activated(int index);

    void on_areaBox_1_clicked(bool checked);

    void on_areaBox_2_clicked(bool checked);

    void on_areaBox_3_clicked(bool checked);

    void on_areaBox_4_clicked(bool checked);

    void on_areaBox_5_clicked(bool checked);

    void on_areaBox_6_clicked(bool checked);

    void on_areaBox_7_clicked(bool checked);

    void on_areaBox_8_clicked(bool checked);

    void on_areaBox_9_clicked(bool checked);

    void on_areaBox_10_clicked(bool checked);

    void on_areaBox_11_clicked(bool checked);

    void on_areaBox_12_clicked(bool checked);

    void on_areaBox_activated(int index);

    void on_mapBox_activated(int index);

    void on_spawnBox_activated(int index);

    void on_mapOverrideEnabledBox_clicked(bool checked);

    void on_mapOverrideNumBox_valueChanged(int arg1);

    void on_spawnOverrideNumBox_valueChanged(int arg1);

    void on_mapOverrideEnabledBox_toggled(bool checked);

private:
    Ui::WarpEditDialog *ui;
};

#endif // WARPEDITDIALOG_H
