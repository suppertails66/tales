#ifndef TALESQTPALETTECYCLEEDITORWIDGET_H
#define TALESQTPALETTECYCLEEDITORWIDGET_H

#include <QWidget>
#include "editors/PaletteCycleEditor.h"
#include "structs/InputEventData.h"

namespace Ui {
class TalesQtPaletteCycleEditorWidget;
}

class TalesQtPaletteCycleEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TalesQtPaletteCycleEditorWidget(QWidget *parent = 0);
    ~TalesQtPaletteCycleEditorWidget();

    void refreshDisplay();

    void refreshPalette();
    void refreshPreview();

    void changeCycle(Tales::PaletteCycleEditor::CycleID cycleID);
    void changeState(int stateNum);

protected:
    Tales::PaletteCycleEditor& paletteCycleEditor_;

public slots:
    void colorChanged(int r, int g, int b);

private slots:
    void pickerEnter();
    void pickerLeave();
    void pickerMouseMove(Tales::InputEventData data);
    void pickerMousePress(Tales::InputEventData data);
    void pickerMouseRelease(Tales::InputEventData data);
    void pickerMouseDoubleClick(Tales::InputEventData data);
    
    void on_cycleComboBox_activated(int index);

    void on_stateComboBox_activated(int index);

private:
    Ui::TalesQtPaletteCycleEditorWidget *ui;
};

#endif // TALESQTPALETTECYCLEEDITORWIDGET_H
