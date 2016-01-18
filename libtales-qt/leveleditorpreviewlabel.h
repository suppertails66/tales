#ifndef LEVELEDITORPREVIEWLABEL_H
#define LEVELEDITORPREVIEWLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include "talesqtleveleditorwidget.h"

class LevelEditorPreviewLabel : public QLabel
{
    Q_OBJECT
public:
    explicit LevelEditorPreviewLabel(QWidget *parent = 0);
    
protected:

    TalesQtLevelEditorWidget& parentEditor_;

    void resizeEvent(QResizeEvent* event);

    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

signals:
    
public slots:
    
};

#endif // LEVELEDITORPREVIEWLABEL_H
