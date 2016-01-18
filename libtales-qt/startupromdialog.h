#ifndef STARTUPROMDIALOG_H
#define STARTUPROMDIALOG_H

#include <QDialog>

namespace Ui {
class StartupROMDialog;
}

class StartupROMDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit StartupROMDialog(QWidget *parent = 0);
    ~StartupROMDialog();

    std::string selectedFileName();
    
private slots:
    void on_buttonBox_accepted();

    void on_browseButton_clicked();

private:
    Ui::StartupROMDialog *ui;
};

#endif // STARTUPROMDIALOG_H
