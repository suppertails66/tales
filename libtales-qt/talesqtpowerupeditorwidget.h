#ifndef TALESQTPOWERUPEDITORWIDGET_H
#define TALESQTPOWERUPEDITORWIDGET_H

#include <QWidget>
#include "editors/PowerUpEditor.h"
#include "emeraldeditorwidget.h"

namespace Ui {
class TalesQtPowerUpEditorWidget;
}

class TalesQtPowerUpEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TalesQtPowerUpEditorWidget(QWidget *parent = 0);
    ~TalesQtPowerUpEditorWidget();

    void refreshDisplay();
    
protected:
    void initializeEmeraldEditor(EmeraldEditorWidget* widget,
                                 int emeraldNum);

    Tales::PowerUpEditor& powerUpEditor_;

private:
    Ui::TalesQtPowerUpEditorWidget *ui;
};

#endif // TALESQTPOWERUPEDITORWIDGET_H
