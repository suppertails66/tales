#ifndef SLOPESPEEDSELECTORWIDGET_H
#define SLOPESPEEDSELECTORWIDGET_H

#include <QWidget>
#include <string>

namespace Ui {
class SlopeSpeedSelectorWidget;
}

class SlopeSpeedSelectorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SlopeSpeedSelectorWidget(QWidget *parent = 0);
    ~SlopeSpeedSelectorWidget();

    void setLabel(const std::string& label__);
    void setValue(int value);
    void setNumber(int number__);
    int value();

protected:
    int number_;

signals:
    void valueChanged(int number, int value);
    
private slots:
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::SlopeSpeedSelectorWidget *ui;
};

#endif // SLOPESPEEDSELECTORWIDGET_H
