#ifndef NATIVEGRAPHICIMPORTDIALOG_H
#define NATIVEGRAPHICIMPORTDIALOG_H

#include <QDialog>

namespace Ui {
class NativeGraphicImportDialog;
}

class NativeGraphicImportDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NativeGraphicImportDialog(QWidget *parent = 0);
    ~NativeGraphicImportDialog();
    
private slots:
    void on_importButton_clicked(bool checked);

private:
    Ui::NativeGraphicImportDialog *ui;
};

#endif // NATIVEGRAPHICIMPORTDIALOG_H
