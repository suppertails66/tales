#ifndef TALESQTMUSICEDITORWIDGET_H
#define TALESQTMUSICEDITORWIDGET_H

#include <QWidget>
#include "musicselectorwidget.h"
#include "editors/MusicEditor.h"

namespace Ui {
class TalesQtMusicEditorWidget;
}

class TalesQtMusicEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TalesQtMusicEditorWidget(QWidget *parent = 0);
    ~TalesQtMusicEditorWidget();

    void refreshDisplay();

protected:
    Tales::MusicEditor& musicEditor_;

public slots:
    void areaMusicActivated(int trackNum, int value);
    void radioMusicActivated(int trackNum, int value);
    
private:
    Ui::TalesQtMusicEditorWidget *ui;
};

#endif // TALESQTMUSICEDITORWIDGET_H
