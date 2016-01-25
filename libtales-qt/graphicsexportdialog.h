#ifndef GRAPHICSEXPORTDIALOG_H
#define GRAPHICSEXPORTDIALOG_H

#include <QDialog>
#include "editors/ResourceExportID.h"
#include "structs/Graphic.h"

namespace Ui {
class GraphicsExportDialog;
}

class GraphicsExportDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GraphicsExportDialog(QWidget *parent = 0);
    ~GraphicsExportDialog();

protected:
    void exportMap(int index,
                   Tales::ResourceExportIDs::MapExportID exportID,
                   std::string foldername);

    void exportGraphic(Tales::Graphic graphic,
                       std::string filename);
    
private slots:
    void on_mapExportButton_clicked(bool checked);

    void on_graphicExportButton_clicked(bool checked);

    void on_metatileExportButton_clicked(bool checked);

    void on_tilemapExportButton_clicked(bool checked);

private:
    Ui::GraphicsExportDialog *ui;
};

#endif // GRAPHICSEXPORTDIALOG_H
