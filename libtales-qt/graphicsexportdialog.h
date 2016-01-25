#ifndef GRAPHICSEXPORTDIALOG_H
#define GRAPHICSEXPORTDIALOG_H

#include <QDialog>

namespace Ui {
class GraphicsExportDialog;
}

class GraphicsExportDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GraphicsExportDialog(QWidget *parent = 0);
    ~GraphicsExportDialog();
    
private slots:
    void on_mapExportButton_clicked(bool checked);

    void on_graphicExportButton_clicked(bool checked);

private:
    Ui::GraphicsExportDialog *ui;
};

#endif // GRAPHICSEXPORTDIALOG_H
