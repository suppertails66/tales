#ifndef TALESQTMETATILEBEHAVIOREDITORWIDGET_H
#define TALESQTMETATILEBEHAVIOREDITORWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QEvent>
#include <QMouseEvent>
#include "structs/Graphic.h"
#include "editors/MetatileBehaviorEditor.h"
#include "structs/InputEventData.h"
#include "emeraldeditorwidget.h"

namespace Ui {
class TalesQtMetatileBehaviorEditorWidget;
}

class TalesQtMetatileBehaviorEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    static void metatilePickedCallback(int tileNum,
                                       void* editorWidget);

    explicit TalesQtMetatileBehaviorEditorWidget(QWidget *parent = 0);
    ~TalesQtMetatileBehaviorEditorWidget();

    void refreshDisplay();

    void reloadAndRefresh();

    void refreshMetatilePicker();

    void refreshDisplayedMetatile();

    void changeCurrentMetatile(int tileNum);

protected:
    void initializeEmeraldEditor(EmeraldEditorWidget* widget,
                                 int emeraldNum);

private slots:
    void pickerEnter();
    void pickerLeave();
    void pickerMouseMove(Tales::InputEventData data);
    void pickerMousePress(Tales::InputEventData data);
    void pickerMouseRelease(Tales::InputEventData data);
    void pickerMouseDoubleClick(Tales::InputEventData data);

    void on_pickerBehaviorButton_clicked(bool checked);

    void on_pickerVertSolidityButton_clicked(bool checked);

    void on_pickerHorizSolidityButton_clicked(bool checked);

    void on_gridCheckBox_clicked(bool checked);

    void on_behaviorComboBox_activated(int index);

    void on_vertSolidityComboBox_activated(int index);

    void on_horizSolidityComboBox_activated(int index);

    void on_fullySolidButton_clicked(bool checked);

    void on_solidOnTopButton_clicked(bool checked);

    void on_nonsolidButton_clicked(bool checked);

    void on_slopeSpeedComboBox_activated(int index);

protected:
    void initializeComboBoxes();

    Tales::MetatileBehaviorEditor& metatileBehaviorEditor_;

    Tales::Graphic metatilePickerBuffer_;
    QImage metatilePickerQImageBuffer_;

    QImage metatileEffectQImageBuffer_;
    QImage metatileVerticalSolidityQImageBuffer_;
    QImage metatileHorizontalSolidityQImageBuffer_;
    
private:
    Ui::TalesQtMetatileBehaviorEditorWidget *ui;
};

#endif // TALESQTMETATILEBEHAVIOREDITORWIDGET_H
