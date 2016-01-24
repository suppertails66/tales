#ifndef TALESQTTILEMAPEDITORWIDGET_H
#define TALESQTTILEMAPEDITORWIDGET_H

#include <QWidget>
#include "editors/TileMapEditor.h"
#include "structs/InputEventData.h"

namespace Ui {
class TalesQtTileMapEditorWidget;
}

class TalesQtTileMapEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TalesQtTileMapEditorWidget(QWidget *parent = 0);
    ~TalesQtTileMapEditorWidget();

    void refreshDisplay();

protected:
    void changeTileMap(int index);

    Tales::TileMapEditor& tileMapEditor_;
    
private slots:
    void on_tileMapComboBox_activated(int index);

    void tileMapEnter();
    void tileMapLeave();
    void tileMapMouseMove(Tales::InputEventData data);
    void tileMapMousePress(Tales::InputEventData data);
    void tileMapMouseRelease(Tales::InputEventData data);
    void tileMapMouseDoubleClick(Tales::InputEventData data);

    void tilePickerEnter();
    void tilePickerLeave();
    void tilePickerMouseMove(Tales::InputEventData data);
    void tilePickerMousePress(Tales::InputEventData data);
    void tilePickerMouseRelease(Tales::InputEventData data);
    void tilePickerMouseDoubleClick(Tales::InputEventData data);

    void subtileEditorValueModified();

    void on_gridCheckBox_clicked(bool checked);

    void on_regularButton_clicked(bool checked);

    void on_pencilButton_clicked(bool checked);

    void on_areaCloneButton_clicked(bool checked);

private:
    Ui::TalesQtTileMapEditorWidget *ui;
};

#endif // TALESQTTILEMAPEDITORWIDGET_H
