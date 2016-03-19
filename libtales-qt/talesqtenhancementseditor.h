#ifndef TALESQTENHANCEMENTSEDITOR_H
#define TALESQTENHANCEMENTSEDITOR_H

#include <QWidget>
#include "editors/EnhancementsEditor.h"

namespace Ui {
class TalesQtEnhancementsEditor;
}

class TalesQtEnhancementsEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit TalesQtEnhancementsEditor(QWidget *parent = 0);
    ~TalesQtEnhancementsEditor();

    void refreshDisplay();

protected:
    Tales::EnhancementsEditor& enhancementsEditor_;

    void refreshStartLevelDisplay();

    void reloadStartLevelDisplayValues();
    
private slots:
    void on_doubleJumpFixBox_clicked(bool checked);

    void on_maxHeightFixBox_clicked(bool checked);

    void on_bombJumpFixBox_clicked(bool checked);

    void on_inventoryHackOffBox_clicked(bool checked);

    void on_inventoryHackHotswapOnlyBox_clicked(bool checked);

    void on_inventoryHackBasicBox_clicked(bool checked);

    void on_inventoryHackFullBox_clicked(bool checked);

    void on_flightHackOffBox_clicked(bool checked);

    void on_flightLimitedBox_clicked(bool checked);

    void on_flightDisabledBox_clicked(bool checked);

    void on_gameOverStandardBox_clicked(bool checked);

    void on_gameOverNoneBox_clicked(bool checked);

    void on_saveHackOffBox_clicked(bool checked);

    void on_autoSaveHackOnBox_clicked(bool checked);

    void on_manualSaveHackOnBox_clicked(bool checked);

    void on_startLevelEnabledBox_clicked(bool checked);

    void on_startAreaBox_activated(int index);

    void on_startMapBox_activated(int index);

    void on_startSpawnBox_activated(int index);

private:
    Ui::TalesQtEnhancementsEditor *ui;
};

#endif // TALESQTENHANCEMENTSEDITOR_H
