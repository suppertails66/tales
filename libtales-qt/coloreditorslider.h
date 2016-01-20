#ifndef COLOREDITORSLIDER_H
#define COLOREDITORSLIDER_H

#include <QWidget>
#include <string>

namespace Ui {
class ColorEditorSlider;
}

class ColorEditorSlider : public QWidget
{
    Q_OBJECT
    
public:
    explicit ColorEditorSlider(QWidget *parent = 0);
    ~ColorEditorSlider();

    void setLabel(const std::string& label__);
    void setValue(int value__);
    int value();

signals:
    void valueChanged(int value);
    
private slots:
//    void on_colorSlider_sliderMoved(int position);

//    void on_colorSpinBox_editingFinished();

    void on_colorSpinBox_valueChanged(int arg1);

    void on_colorSlider_actionTriggered(int action);

private:
    Ui::ColorEditorSlider *ui;
};

#endif // COLOREDITORSLIDER_H
