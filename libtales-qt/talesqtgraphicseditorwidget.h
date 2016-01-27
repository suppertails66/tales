#ifndef TALESQTGRAPHICSEDITORWIDGET_H
#define TALESQTGRAPHICSEDITORWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include "editors/GraphicsEditor.h"

namespace Ui {
class TalesQtGraphicsEditorWidget;
}

class TalesQtGraphicsEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TalesQtGraphicsEditorWidget(QWidget *parent = 0);
    ~TalesQtGraphicsEditorWidget();

    void refreshDisplay();

    void refreshPaletteDisplay();
    void refreshTileDisplay();
    void refreshMappingDisplay();

protected:
    void changeGraphic(
            Tales::GraphicsEditor::GraphicCompressionType compressionType,
            int index);

    void repopulateMappingBox(
            Tales::GraphicsEditor::GraphicCompressionType compressionType,
            int index);

    Tales::GraphicsEditor& graphicsEditor_;

    Tales::Graphic tileEditorBuffer_;
    QImage tileEditorQImageBuffer_;

    Tales::Graphic mappingEditorBuffer_;
    QImage mappingEditorQImageBuffer_;

    Tales::Graphic colorPickerBuffer_;
    QImage colorPickerQImageBuffer_;

public slots:
    void tileEditorMouseEnter();
    void tileEditorMouseExit();
    void tileEditorMouseMove(Tales::InputEventData eventData);
    void tileEditorMousePress(Tales::InputEventData eventData);
    void tileEditorMouseRelease(Tales::InputEventData eventData);
    void tileEditorMouseDoubleClick(Tales::InputEventData eventData);

    void mappingEditorMouseEnter();
    void mappingEditorMouseExit();
    void mappingEditorMouseMove(Tales::InputEventData eventData);
    void mappingEditorMousePress(Tales::InputEventData eventData);
    void mappingEditorMouseRelease(Tales::InputEventData eventData);
    void mappingEditorMouseDoubleClick(Tales::InputEventData eventData);

    void colorPickerMouseEnter();
    void colorPickerMouseExit();
    void colorPickerMouseMove(Tales::InputEventData eventData);
    void colorPickerMousePress(Tales::InputEventData eventData);
    void colorPickerMouseRelease(Tales::InputEventData eventData);
    void colorPickerMouseDoubleClick(Tales::InputEventData eventData);
    
private slots:
    void on_zoomComboBox_activated(int index);

//    void on_areaCloneToolButton_clicked();

    void on_paintToolButton_clicked();

    void on_checkBox_2_clicked(bool checked);

    void on_graphicComboBox_activated(int index);

    void on_transparencyCheckBox_clicked(bool checked);

    void on_paletteComboBox_activated(int index);

    void on_paintToolButton_clicked(bool checked);

//    void on_areaCloneToolButton_clicked(bool checked);

    void on_mappingComboBox_activated(int index);

    void on_collisionCheckBox_clicked(bool checked);

    void on_xOffsetBox_valueChanged(int arg1);

    void on_yOffsetBox_valueChanged(int arg1);

    void on_widthBox_valueChanged(int arg1);

    void on_heightBox_valueChanged(int arg1);

    void on_exportButton_clicked();

private:
    Ui::TalesQtGraphicsEditorWidget *ui;
};

#endif // TALESQTGRAPHICSEDITORWIDGET_H
