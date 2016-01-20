#ifndef LEVELPREVIEWSCROLLBAR_H
#define LEVELPREVIEWSCROLLBAR_H

#include <QScrollBar>

class LevelEditorPreviewLabel;

class LevelPreviewScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit LevelPreviewScrollBar(QWidget *parent = 0);

    friend class LevelEditorPreviewLabel;
    
signals:
    
public slots:
    
};

#endif // LEVELPREVIEWSCROLLBAR_H
