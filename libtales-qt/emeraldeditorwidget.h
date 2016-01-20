#ifndef EMERALDEDITORWIDGET_H
#define EMERALDEDITORWIDGET_H

#include <QWidget>
#include "gamedata/EditablePowerUpData.h"
#include "gamedata/EditableEmeraldHealthRefills.h"

namespace Ui {
class EmeraldEditorWidget;
}

class EmeraldEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit EmeraldEditorWidget(QWidget *parent = 0);
    ~EmeraldEditorWidget();

    void refreshDisplay();

    void setEmeraldNum(int emeraldNum__);
    void setPowerUpData(Tales::EditablePowerUpData& powerUpData__);
    void setEmeraldHealthRefills(
            Tales::EditableEmeraldHealthRefills& emeraldHealthRefills__);

protected:
    int emeraldNum_;
    Tales::EditablePowerUpData* powerUpData_;
    Tales::EditableEmeraldHealthRefills* emeraldHealthRefills_;
    
private slots:
    void on_flightTimeBox_editingFinished();

    void on_hpBox_editingFinished();

    void on_hpRefillBox_editingFinished();

private:
    Ui::EmeraldEditorWidget *ui;
};

#endif // EMERALDEDITORWIDGET_H
