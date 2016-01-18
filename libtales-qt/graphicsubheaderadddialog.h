#ifndef GRAPHICSUBHEADERADDDIALOG_H
#define GRAPHICSUBHEADERADDDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "gamedata/ObjectGraphicsHeader.h"
#include "gamedata/EditableLevelGraphicsData.h"
#include "gamegear/GGPalette.h"

namespace Ui {
class GraphicSubheaderAddDialog;
}

class GraphicSubheaderAddDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GraphicSubheaderAddDialog(Tales::ObjectGraphicsHeader& srcData__,
                                       Tales::EditableLevelGraphicsData& levelGraphicsData__,
                                       Tales::GGPalette objectPalette__,
                                       QWidget *parent = 0);
    ~GraphicSubheaderAddDialog();

    int graphicIndex() const;

    bool regularAndFlipped() const;

    bool flipped() const;

protected:

    void repopulate();

    void updatePreview();

    Tales::ObjectGraphicsHeader& srcData_;

    Tales::EditableLevelGraphicsData& levelGraphicsData_;

    Tales::GGPalette& objectPalette_;

    int graphicIndex_;

    bool regularAndFlipped_;

    bool flipped_;

    
private slots:
    void on_regularRadioButton_clicked(bool checked);

    void on_flippedRadioButton_clicked(bool checked);

    void on_regularAndFlippedRadioButton_clicked(bool checked);

    void on_graphicSelectorTree_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::GraphicSubheaderAddDialog *ui;
};

#endif // GRAPHICSUBHEADERADDDIALOG_H
