#ifndef TALESQTMETATILESTRUCTUREEDITORWIDGET_H
#define TALESQTMETATILESTRUCTUREEDITORWIDGET_H

#include <QWidget>
#include "editors/MetatileStructureEditor.h"

namespace Ui {
class TalesQtMetatileStructureEditorWidget;
}

class TalesQtMetatileStructureEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TalesQtMetatileStructureEditorWidget(QWidget *parent = 0);
    ~TalesQtMetatileStructureEditorWidget();

    void refreshDisplay();

public slots:
    void metatilePickerEnter();
    void metatilePickerLeave();
    void metatilePickerMouseMove(Tales::InputEventData data);
    void metatilePickerMousePress(Tales::InputEventData data);
    void metatilePickerMouseRelease(Tales::InputEventData data);
    void metatilePickerMouseDoubleClick(Tales::InputEventData data);

    void tilePickerEnter();
    void tilePickerLeave();
    void tilePickerMouseMove(Tales::InputEventData data);
    void tilePickerMousePress(Tales::InputEventData data);
    void tilePickerMouseRelease(Tales::InputEventData data);
    void tilePickerMouseDoubleClick(Tales::InputEventData data);

    void subtilePickerEnter();
    void subtilePickerLeave();
    void subtilePickerMouseMove(Tales::InputEventData data);
    void subtilePickerMousePress(Tales::InputEventData data);
    void subtilePickerMouseRelease(Tales::InputEventData data);
    void subtilePickerMouseDoubleClick(Tales::InputEventData data);

    void ulValueModified();
    void urValueModified();
    void llValueModified();
    void lrValueModified();

protected:
    void selectStructureSet(int index);

    void saveCurrentAsDefaults();

    void repopulateIDList();

    void refreshIDBox();

    Tales::MetatileStructureEditor& metatileStructureEditor_;
    
private slots:
    void on_metatileSetComboBox_activated(int index);

    void on_previewPalette2ComboBox_activated(int index);

    void on_gridCheckBox_clicked(bool checked);

    void on_previewGraphicComboBox_activated(int index);

    void on_previewPaletteComboBox_activated(int index);

    void on_structureIDComboBox_activated(int index);

    void on_structureRemoveButton_clicked(bool checked);

    void on_structureAddButton_clicked(bool checked);

private:
    Ui::TalesQtMetatileStructureEditorWidget *ui;
};

#endif // TALESQTMETATILESTRUCTUREEDITORWIDGET_H
