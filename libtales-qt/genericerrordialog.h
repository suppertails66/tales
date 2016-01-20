#ifndef GENERICERRORDIALOG_H
#define GENERICERRORDIALOG_H

#include <QDialog>
#include <string>

namespace Ui {
class GenericErrorDialog;
}

class GenericErrorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GenericErrorDialog(
            const std::string& errorText,
            QWidget *parent = 0);
    ~GenericErrorDialog();
    
private:
    Ui::GenericErrorDialog *ui;
};

#endif // GENERICERRORDIALOG_H
