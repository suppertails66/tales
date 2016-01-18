#ifndef MUSICSELECTORWIDGET_H
#define MUSICSELECTORWIDGET_H

#include <QWidget>
#include <string>

namespace Ui {
class MusicSelectorWidget;
}

class MusicSelectorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MusicSelectorWidget(QWidget *parent = 0);
    ~MusicSelectorWidget();

    void setNumber(int number__);
    void setCurrentTrack(int index);
    void setLabel(const std::string& labelText);

protected:
    int number_;

signals:
    void activated(int trackNum, int index);
    
private slots:
    void on_trackComboBox_activated(int index);

private:
    Ui::MusicSelectorWidget *ui;
};

#endif // MUSICSELECTORWIDGET_H
