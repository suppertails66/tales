#ifndef OBJECTHEADEREDITDIALOG_H
#define OBJECTHEADEREDITDIALOG_H

#include <QDialog>
#include "gamedata/EditableLevelGraphicsData.h"

namespace Ui {
class ObjectHeaderEditDialog;
}

class ObjectHeaderEditDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ObjectHeaderEditDialog(Tales::EditableLevelGraphicsData& srcData__,
                                    QWidget *parent = 0);
    ~ObjectHeaderEditDialog();

protected:

    Tales::EditableLevelGraphicsData& srcData_;

    void repopulate();
    
private slots:
    void on_okButton_clicked();

    void on_headerAddButton_clicked();

    void on_headerRemoveButton_clicked();

private:
    Ui::ObjectHeaderEditDialog *ui;
};

#endif // OBJECTHEADEREDITDIALOG_H
