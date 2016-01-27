#ifndef NATIVEGRAPHICEXPORTDIALOG_H
#define NATIVEGRAPHICEXPORTDIALOG_H

#include <QDialog>

namespace Ui {
class NativeGraphicExportDialog;
}

class NativeGraphicExportDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NativeGraphicExportDialog(QWidget *parent = 0);
    ~NativeGraphicExportDialog();
    
private slots:
    void on_pushButton_clicked(bool checked);

private:
    Ui::NativeGraphicExportDialog *ui;
};

#endif // NATIVEGRAPHICEXPORTDIALOG_H
