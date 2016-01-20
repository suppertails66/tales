#ifndef VRAMEDITORPREVIEWLABEL_H
#define VRAMEDITORPREVIEWLABEL_H

#include <QLabel>
#include "structs/Graphic.h"
class TalesQtVRAMEditorWidget;

class VRAMEditorPreviewLabel : public QLabel
{
    Q_OBJECT
public:
    explicit VRAMEditorPreviewLabel(QWidget* parent = 0);

    void refreshDisplay();
    
signals:
    
public slots:

protected:

    TalesQtVRAMEditorWidget& parentEditor_;

    Tales::Graphic previewBuffer_;

    void mousePressEvent(QMouseEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    void mouseMoveEvent(QMouseEvent* event);

    void enterEvent(QEvent* event);

    void leaveEvent(QEvent* event);
    
};

#endif // VRAMEDITORPREVIEWLABEL_H
