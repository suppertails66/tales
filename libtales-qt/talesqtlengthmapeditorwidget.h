#ifndef TALESQTLENGTHMAPEDITORWIDGET_H
#define TALESQTLENGTHMAPEDITORWIDGET_H

#include <QWidget>
#include <QModelIndex>
#include "structs/InputEventData.h"
#include "structs/Graphic.h"
#include "editors/LengthMapEditor.h"

namespace Ui {
class TalesQtLengthMapEditorWidget;
}

class TalesQtLengthMapEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    static bool editDialogCallback(int index,
                                   Tales::LengthMapValue* value,
                                   void* editorWidget);

    explicit TalesQtLengthMapEditorWidget(QWidget *parent = 0);
    ~TalesQtLengthMapEditorWidget();

    void refreshDisplay();

protected:
    Tales::LengthMapEditor& lengthMapEditor_;

    Tales::Graphic previewBuffer_;

private slots:
    void slopeSpeedValueChanged(int number, int value);

    void editLabelEnter();
    void editLabelLeave();
    void editLabelMouseMove(Tales::InputEventData data);
    void editLabelMousePress(Tales::InputEventData data);
    void editLabelMouseRelease(Tales::InputEventData data);
    void editLabelMouseDoubleClick(Tales::InputEventData data);
    
    void on_normalizeButton_clicked(bool checked);

    void on_reverseButton_clicked(bool checked);

    void on_widthMapList_clicked(const QModelIndex &index);

    void on_heightMapList_clicked(const QModelIndex &index);

    void on_gridCheckBox_clicked(bool checked);

private:
    Ui::TalesQtLengthMapEditorWidget *ui;
};

#endif // TALESQTLENGTHMAPEDITORWIDGET_H
