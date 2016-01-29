#ifndef LAYOUTIMPORTDIALOG_H
#define LAYOUTIMPORTDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class LayoutImportDialog;
}

class LayoutImportDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LayoutImportDialog(QWidget *parent = 0);
    ~LayoutImportDialog();

    int selectedMapIndex();

protected:
    int selectedMapIndex_;
    
private slots:
    void on_mapSelector_currentItemChanged(QTreeWidgetItem *current,
                                           QTreeWidgetItem *previous);

private:
    Ui::LayoutImportDialog *ui;
};

#endif // LAYOUTIMPORTDIALOG_H
