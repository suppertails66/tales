#include "talesqtlengthmapeditorwidget.h"
#include "ui_talesqtlengthmapeditorwidget.h"
#include "talesqtstatevar.h"
#include "talesqtformatconversion.h"
#include "lengthmapvalueeditdialog.h"
#include "slopespeedselectorwidget.h"
#include "util/StringConversion.h"

using namespace Tales;
using namespace Luncheon;

bool TalesQtLengthMapEditorWidget::editDialogCallback(int index,
                               Tales::LengthMapValue* value,
                               void* editorWidget) {
    TalesQtLengthMapEditorWidget* widget
            = (TalesQtLengthMapEditorWidget*)editorWidget;

    LengthMapValueEditDialog dialog(index,
                                    *value,
                                    widget);
    int result = dialog.exec();

    if (result == QDialog::Accepted) {
        return true;
    }
    else {
        return false;
    }
}

TalesQtLengthMapEditorWidget::TalesQtLengthMapEditorWidget(QWidget *parent) :
    QWidget(parent),
    lengthMapEditor_(appState_.editor().lengthMapEditor()),
    previewBuffer_(lengthMapEditor_.previewWidth(),
                   lengthMapEditor_.previewHeight()),
    ui(new Ui::TalesQtLengthMapEditorWidget)
{
    ui->setupUi(this);

    lengthMapEditor_.setEditDialogCallback(&editDialogCallback,
                                           (void*)this);

    for (int i = 0; i < lengthMapEditor_.numWidthMaps(); i++) {
        ui->widthMapList->addItem(
                    (std::string("Width map ")
                    + StringConversion::toString(i)).c_str());
    }

    for (int i = 0; i < lengthMapEditor_.numHeightMaps(); i++) {
        ui->heightMapList->addItem(
                    (std::string("Height map ")
                    + StringConversion::toString(i)).c_str());
    }

    ui->slopeSpeedScrollAreaContents->setLayout(
                new QBoxLayout(QBoxLayout::TopToBottom,
                               ui->slopeSpeedScrollAreaContents));

    for (int i = 0;
         i < lengthMapEditor_.numSlopeSpeedValues();
         i++) {
        SlopeSpeedSelectorWidget* widget = new SlopeSpeedSelectorWidget(
                    ui->slopeSpeedScrollAreaContents);
        widget->setNumber(i);
        widget->setValue(lengthMapEditor_.slopeSpeedValue(i));
        widget->setLabel(std::string("Value ")
                    + StringConversion::toString(i));
        QObject::connect(widget,
                         SIGNAL(valueChanged(int, int)),
                         this,
                         SLOT(slopeSpeedValueChanged(int, int)));
        ui->slopeSpeedScrollAreaContents->layout()->addWidget(widget);
    }

    QObject::connect(ui->lengthMapPreviewLabel,
                     SIGNAL(pickerEnter()),
                     this,
                     SLOT(editLabelEnter()));
    QObject::connect(ui->lengthMapPreviewLabel,
                     SIGNAL(pickerLeave()),
                     this,
                     SLOT(editLabelLeave()));
    QObject::connect(ui->lengthMapPreviewLabel,
                     SIGNAL(pickerMouseMove(Tales::InputEventData)),
                     this,
                     SLOT(editLabelMouseMove(Tales::InputEventData)));
    QObject::connect(ui->lengthMapPreviewLabel,
                     SIGNAL(pickerMousePress(Tales::InputEventData)),
                     this,
                     SLOT(editLabelMousePress(Tales::InputEventData)));
    QObject::connect(ui->lengthMapPreviewLabel,
                     SIGNAL(pickerMouseRelease(Tales::InputEventData)),
                     this,
                     SLOT(editLabelMouseRelease(Tales::InputEventData)));
    QObject::connect(ui->lengthMapPreviewLabel,
                     SIGNAL(pickerMouseDoubleClick(Tales::InputEventData)),
                     this,
                     SLOT(editLabelMouseDoubleClick(Tales::InputEventData)));
}

TalesQtLengthMapEditorWidget::~TalesQtLengthMapEditorWidget()
{
    delete ui;
}

void TalesQtLengthMapEditorWidget::refreshDisplay() {
    lengthMapEditor_.drawEditorGraphic(previewBuffer_);

    ui->lengthMapPreviewLabel->setPixmap(
                TalesQtFormatConversion::graphicToPixmap(
                    previewBuffer_));
}

void TalesQtLengthMapEditorWidget::editLabelEnter() {
    lengthMapEditor_.editorEnterMouse();
}

void TalesQtLengthMapEditorWidget::editLabelLeave() {
    lengthMapEditor_.editorExitMouse();
}

void TalesQtLengthMapEditorWidget
    ::editLabelMouseMove(Tales::InputEventData data) {
    lengthMapEditor_.editorMoveMouse(data);

    refreshDisplay();
}

void TalesQtLengthMapEditorWidget
    ::editLabelMousePress(Tales::InputEventData data) {
    lengthMapEditor_.editorPressMouse(data);

    refreshDisplay();
}

void TalesQtLengthMapEditorWidget
    ::editLabelMouseRelease(Tales::InputEventData data) {
    lengthMapEditor_.editorReleaseMouse(data);

    refreshDisplay();
}

void TalesQtLengthMapEditorWidget
    ::editLabelMouseDoubleClick(Tales::InputEventData data) {
    lengthMapEditor_.editorDoubleClickMouse(data);

    refreshDisplay();
}

void TalesQtLengthMapEditorWidget::on_normalizeButton_clicked(bool checked)
{
    lengthMapEditor_.setCurrentMetatileToForward();

    refreshDisplay();
}

void TalesQtLengthMapEditorWidget::on_reverseButton_clicked(bool checked)
{
    lengthMapEditor_.setCurrentMetatileToBackward();

    refreshDisplay();
}

void TalesQtLengthMapEditorWidget::on_widthMapList_clicked(const QModelIndex &index)
{
    ui->heightMapList->setCurrentRow(-1, QItemSelectionModel::Clear);
    lengthMapEditor_.setLengthMap(index.row(),
                                  LengthMapLayeredGraphicScene::mapTypeWidth);

    refreshDisplay();
}

void TalesQtLengthMapEditorWidget::on_heightMapList_clicked(const QModelIndex &index)
{
    ui->widthMapList->setCurrentRow(-1, QItemSelectionModel::Clear);
    lengthMapEditor_.setLengthMap(index.row(),
                                  LengthMapLayeredGraphicScene::mapTypeHeight);

    refreshDisplay();
}

void TalesQtLengthMapEditorWidget::on_gridCheckBox_clicked(bool checked)
{
    lengthMapEditor_.setGridEnabled(checked);

    refreshDisplay();
}

void TalesQtLengthMapEditorWidget::slopeSpeedValueChanged(int number, int value) {
    lengthMapEditor_.setSlopeSpeedValue(number, value);
}
