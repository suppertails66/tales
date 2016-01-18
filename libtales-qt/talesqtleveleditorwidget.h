#ifndef TALESQTLEVELEDITORWIDGET_H
#define TALESQTLEVELEDITORWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include "levelheadermapselectortreewidget.h"
#include "levelpreviewscrollbar.h"
#include "editors/LevelObjectGraphicSceneLayer.h"
#include "editors/LevelSpawnGraphicSceneLayer.h"
#include "editors/LevelEditor.h"
#include "editors/LevelEditorTool.h"
#include "structs/Graphic.h"

class LevelEditorPreviewLabel;

namespace Ui {
class TalesQtLevelEditorWidget;
}

class TalesQtLevelEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    static bool spawnEditDialogCallback(Tales::LevelSpawnGraphicSceneLayer& layer,
            Tales::SpawnPoint& spawnPoint,
            void* obj);

    static bool objectEditDialogCallback(Tales::LevelObjectGraphicSceneLayer& layer,
            Tales::LevelObjectEntry& levelObjectEntry,
            void* obj);

    static void objectUpdateCallback(
            Tales::LevelObjectGraphicSceneLayer& layer,
            void* obj);

    static void objectSelectionCallback(
            Tales::LevelObjectGraphicSceneLayer& layer,
            Tales::LevelObjectEntryCollection::iterator,
            void* obj);

    explicit TalesQtLevelEditorWidget(QWidget *parent = 0);
    ~TalesQtLevelEditorWidget();

    void refreshDisplay();

    void refreshLevelEditorDisplay();

    void refreshMetatilePickerDisplay();

    void refreshToolbox();

    void refreshNumObjects();

    void reloadObjects();
    void updateObjectSelection();

    void reloadAndRefresh();

    void setScrollX(int scrollX);
    void setScrollY(int scrollY);

    friend class LevelEditorPreviewLabel;
    
protected:

    void changeEditorTool(Tales::LevelEditorTools::LevelEditorTool tool);

    LevelPreviewScrollBar& levelHorizontalScrollBar();
    LevelPreviewScrollBar& levelVerticalScrollBar();

    Tales::LevelEditor& levelEditor_;

    Tales::Graphic previewBuffer_;
    QImage previewQImageBuffer_;

    Tales::Graphic metatilePickerBuffer_;
    QImage metatilePickerQImageBuffer_;

private slots:
    void on_mapSelectorWidget_currentItemChanged(
            QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_levelHorizontalScrollBar_valueChanged(int value);

    void on_levelVerticalScrollBar_valueChanged(int value);

    void on_zoomComboBox_activated(int index);

    void on_gridCheckBox_clicked(bool checked);

    void on_levelVisualViewButton_clicked();

    void on_levelEffectViewButton_clicked();

    void on_bgCheckBox_clicked(bool checked);

    void on_fgCheckBox_clicked(bool checked);

    void on_metatilePaintToolButton_clicked();

    void on_metatileAreaCloneButton_clicked();

    void on_objectEditorButton_clicked();

    void on_objectsCheckBox_clicked(bool checked);

    void on_objectListWidget_currentRowChanged(int currentRow);

    void on_objectListWidget_doubleClicked(const QModelIndex &index);

    void on_objectAddWidget_clicked(bool checked);

    void on_objectListWidget_clicked(const QModelIndex &index);

    void on_objectRemoveWidget_clicked(bool checked);

    void on_cameraBoundTopBox_valueChanged(int arg1);

    void on_cameraBoundBottomBox_valueChanged(int arg1);

    void on_cameraBoundLeftBox_valueChanged(int arg1);

    void on_cameraBoundRightBox_valueChanged(int arg1);

    void on_levelPropertiesButton_clicked(bool checked);

    void on_autofillAllButton_clicked(bool checked);

    void on_cameraBoundsShowBox_clicked(bool checked);

    void on_warpsButton_clicked(bool checked);

    void on_spawnsCheckBox_clicked(bool checked);

    void on_spawnEditorButton_clicked(bool checked);

    void on_levelVertSolidityButton_clicked(bool checked);

    void on_levelHorizSolidityButton_clicked(bool checked);

private:
    Ui::TalesQtLevelEditorWidget *ui;
};

#endif // TALESQTLEVELEDITORWIDGET_H
