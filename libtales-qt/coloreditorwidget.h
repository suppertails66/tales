#ifndef COLOREDITORWIDGET_H
#define COLOREDITORWIDGET_H

#include <QWidget>

namespace Ui {
class ColorEditorWidget;
}

class ColorEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ColorEditorWidget(QWidget *parent = 0);
    ~ColorEditorWidget();

    void setColor(int r__, int g__, int b__);
    int r();
    int g();
    int b();
protected:

private slots:
    void rSliderChanged(int r);
    void gSliderChanged(int g);
    void bSliderChanged(int b);

signals:
    void rChanged(int r);
    void gChanged(int g);
    void bChanged(int b);
    void colorChanged(int r, int g, int b);
    
private:
    Ui::ColorEditorWidget *ui;
};

#endif // COLOREDITORWIDGET_H
