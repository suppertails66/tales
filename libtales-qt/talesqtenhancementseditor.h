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

private:
    Ui::TalesQtEnhancementsEditor *ui;
};

#endif // TALESQTENHANCEMENTSEDITOR_H
