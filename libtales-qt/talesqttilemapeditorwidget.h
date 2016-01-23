#ifndef TALESQTTILEMAPEDITORWIDGET_H
#define TALESQTTILEMAPEDITORWIDGET_H

#include <QWidget>

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
    
private:
    Ui::TalesQtTileMapEditorWidget *ui;
};

#endif // TALESQTTILEMAPEDITORWIDGET_H
