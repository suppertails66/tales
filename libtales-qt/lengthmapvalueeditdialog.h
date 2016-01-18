#ifndef LENGTHMAPVALUEEDITDIALOG_H
#define LENGTHMAPVALUEEDITDIALOG_H

#include <QDialog>
#include "gamedata/LengthMapValue.h"

namespace Ui {
class LengthMapValueEditDialog;
}

class LengthMapValueEditDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LengthMapValueEditDialog(int valueIndex__,
                                    Tales::LengthMapValue& value__,
                                    QWidget *parent = 0);
    ~LengthMapValueEditDialog();

protected:
    int valueIndex_;
    Tales::LengthMapValue& value_;
    
private slots:
    void on_magnitudeSpinBox_valueChanged(int arg1);

    void on_reversedCheckBox_clicked(bool checked);

private:
    Ui::LengthMapValueEditDialog *ui;
};

#endif // LENGTHMAPVALUEEDITDIALOG_H
