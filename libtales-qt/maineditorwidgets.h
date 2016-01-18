#ifndef MAINEDITORWIDGETS_H
#define MAINEDITORWIDGETS_H

#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class MainEditorWidgets;
}

class MainEditorWidgets : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainEditorWidgets(QWidget *parent = 0);
    ~MainEditorWidgets();

    QStackedWidget& stackedWidget();
    
private:
    Ui::MainEditorWidgets *ui;
};

#endif // MAINEDITORWIDGETS_H
