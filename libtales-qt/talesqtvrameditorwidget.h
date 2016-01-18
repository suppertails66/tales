#ifndef TALESQTVRAMEDITORWIDGET_H
#define TALESQTVRAMEDITORWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "editors/LevelVRAMEditor.h"

namespace Ui {
class TalesQtVRAMEditorWidget;
}

class TalesQtVRAMEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TalesQtVRAMEditorWidget(QWidget *parent = 0);
    ~TalesQtVRAMEditorWidget();

    void reloadAndRefresh();

    void refreshDisplay();

    void refreshSelectedObject();

    void refreshVRAMIndices();

    void resetInputMode();

    double scale() const;
    
private slots:

    void on_objectUpButton_clicked();

    void on_objectDownButton_clicked();

    void on_mapSelectorTree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_leafIndexSpinBox_editingFinished();

    void on_smokePuffSpinBox_editingFinished();

    void on_waterSplashSpinBox_editingFinished();

    void on_objectIndexSpinBox_editingFinished();

    void on_objectSelectorList_activated(const QModelIndex &index);

    void on_objectSelectorList_clicked(const QModelIndex &index);

    void on_objectIndexSpinBox_valueChanged(int arg1);

    void on_flippedCheckBox_toggled(bool checked);

    void on_flippedCheckBox_clicked(bool checked);

    void on_objectRemoveButton_clicked();

    void on_mapGraphicComboBox_currentIndexChanged(int index);

    void on_objectHeaderComboBox_currentIndexChanged(int index);

    void on_objectHeaderEditButton_clicked();

    void on_objectHeaderComboBox_activated(int index);

    void on_objectAddButton_clicked();

    void on_leafIndexSelectButton_clicked();

    void on_leafShowCheckBox_clicked(bool checked);

    void on_smokeShowCheckBox_clicked(bool checked);

    void on_waterShowCheckBox_clicked(bool checked);

    void on_leafIndexSpinBox_valueChanged(int arg1);

    void on_smokePuffSpinBox_valueChanged(int arg1);

    void on_waterSplashSpinBox_valueChanged(int arg1);

    void on_smokePuffSelectButton_clicked();

    void on_waterSplashSelectButton_clicked();

    void on_objectIndexSelecButton_clicked();

private:
    Ui::TalesQtVRAMEditorWidget *ui;

protected:

    void insertSubheaderSomewhere(Tales::ObjectGraphicSubheader subheader);

    void mouseClickEvent(QMouseEvent* event);

    void mouseMoveEvent(QMouseEvent* event);

    Tales::LevelVRAMEditor& vramEditor_;

};

#endif // TALESQTVRAMEDITORWIDGET_H
