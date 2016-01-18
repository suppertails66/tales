#ifndef TALESQTPALETTEEDITORWIDGET_H
#define TALESQTPALETTEEDITORWIDGET_H

#include <QWidget>
#include <QImage>
#include "editors/PaletteEditor.h"
#include "structs/Graphic.h"

namespace Ui {
class TalesQtPaletteEditorWidget;
}

class TalesQtPaletteEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TalesQtPaletteEditorWidget(QWidget *parent = 0);
    ~TalesQtPaletteEditorWidget();

    void refreshDisplay();

public slots:
    void pickerEnter();
    void pickerLeave();
    void pickerMouseMove(Tales::InputEventData data);
    void pickerMousePress(Tales::InputEventData data);
    void pickerMouseRelease(Tales::InputEventData data);
    void pickerMouseDoubleClick(Tales::InputEventData data);

protected:
    void setCurrentR(int r);
    void setCurrentG(int g);
    void setCurrentB(int b);

    Tales::PaletteEditor& paletteEditor_;

    Tales::Graphic pickerBuffer_;
    QImage pickerQImageBuffer_;

    Tales::Graphic previewBuffer_;
    QImage previewQImageBuffer_;
    
private slots:
    void on_paletteComboBox_activated(int index);

    void on_redSpinBox_editingFinished();

    void on_greenSpinBox_editingFinished();

    void on_blueSpinBox_editingFinished();

    void on_redSlider_sliderMoved(int position);

    void on_greenSlider_sliderMoved(int position);

    void on_blueSlider_sliderMoved(int position);

private:
    Ui::TalesQtPaletteEditorWidget *ui;
};

#endif // TALESQTPALETTEEDITORWIDGET_H
