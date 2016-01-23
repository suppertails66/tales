#ifndef SUBTILEEDITORWIDGET_H
#define SUBTILEEDITORWIDGET_H

#include <QWidget>
#include <QFrame>
#include "gamegear/TileReference.h"
#include <string>

namespace Ui {
class SubtileEditorWidget;
}

class SubtileEditorWidget : public QFrame
{
    Q_OBJECT
    
public:
    explicit SubtileEditorWidget(QWidget *parent = 0);
    ~SubtileEditorWidget();

    void setTile(Tales::TileReference& tile__);

    void refreshDisplay();

    void setNameLabel(const std::string& nameLabel);

    void enableAll();
    void disableAllButTileNum();

    void setTileRange(int lower, int upper);

protected:
    Tales::TileReference* tile_;

signals:
    void valueModified();
    
private slots:
    void on_ulTileBox_valueChanged(int arg1);

    void on_ulHFlipBox_clicked(bool checked);

    void on_ulVFlipBox_clicked(bool checked);

    void on_ulBGButton_clicked(bool checked);

    void on_ulFGButton_clicked(bool checked);

    void on_ulPal1Button_clicked(bool checked);

    void on_ulPal2Button_clicked(bool checked);

private:
    Ui::SubtileEditorWidget *ui;
};

#endif // SUBTILEEDITORWIDGET_H
