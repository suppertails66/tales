#ifndef LEVELPROPERTIESDIALOG_H
#define LEVELPROPERTIESDIALOG_H

#include <QDialog>
#include "editors/LevelEditor.h"
namespace Ui {
class LevelPropertiesDialog;
}

class LevelPropertiesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LevelPropertiesDialog(Tales::LevelEditor& levelEditor__,
                                   QWidget *parent = 0);
    ~LevelPropertiesDialog();
    
protected:
    Tales::LevelEditor& levelEditor_;

    void reload();

private slots:
    void on_levelWidthBox_activated(int index);

    void on_levelEffect1Box_activated(int index);

    void on_levelEffect2Box_activated(int index);

    void on_levelEffect3Box_activated(int index);

    void on_levelEffect4Box_activated(int index);

    void on_palette0ComboBox_activated(int index);

    void on_palette1ComboBox_activated(int index);

    void on_metatileStructureSetComboBox_activated(int index);

    void on_removeAllObjectsButton_clicked(bool checked);

    void on_importObjectLayoutButton_clicked(bool checked);

private:
    Ui::LevelPropertiesDialog *ui;
};

#endif // LEVELPROPERTIESDIALOG_H
