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

private:
    Ui::TalesQtTileMapEditorWidget *ui;
};

#endif // TALESQTTILEMAPEDITORWIDGET_H
