#ifndef CONFIRMATIONDIALOG_H
#define CONFIRMATIONDIALOG_H

#include <QDialog>
#include <string>

namespace Ui {
class ConfirmationDialog;
}

class ConfirmationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConfirmationDialog(
            const std::string& textLabel__,
            QWidget *parent = 0);
    ~ConfirmationDialog();
    
private:
    Ui::ConfirmationDialog *ui;
};

#endif // CONFIRMATIONDIALOG_H
