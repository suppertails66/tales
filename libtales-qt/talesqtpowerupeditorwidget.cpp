#include "talesqtpowerupeditorwidget.h"
#include "ui_talesqtpowerupeditorwidget.h"
#include "talesqtstatevar.h"

TalesQtPowerUpEditorWidget::TalesQtPowerUpEditorWidget(QWidget *parent) :
    QWidget(parent),
    powerUpEditor_(appState_.editor().powerUpEditor()),
    ui(new Ui::TalesQtPowerUpEditorWidget)
{
    ui->setupUi(this);

    initializeEmeraldEditor(ui->emeraldEditorWidget_0, 0);
    initializeEmeraldEditor(ui->emeraldEditorWidget_1, 1);
    initializeEmeraldEditor(ui->emeraldEditorWidget_2, 2);
    initializeEmeraldEditor(ui->emeraldEditorWidget_3, 3);
    initializeEmeraldEditor(ui->emeraldEditorWidget_4, 4);
    initializeEmeraldEditor(ui->emeraldEditorWidget_5, 5);
    initializeEmeraldEditor(ui->emeraldEditorWidget_6, 6);

    refreshDisplay();
}

TalesQtPowerUpEditorWidget::~TalesQtPowerUpEditorWidget()
{
    delete ui;
}

void TalesQtPowerUpEditorWidget::refreshDisplay() {
    ui->emeraldEditorWidget_0->refreshDisplay();
    ui->emeraldEditorWidget_1->refreshDisplay();
    ui->emeraldEditorWidget_2->refreshDisplay();
    ui->emeraldEditorWidget_3->refreshDisplay();
    ui->emeraldEditorWidget_4->refreshDisplay();
    ui->emeraldEditorWidget_5->refreshDisplay();
    ui->emeraldEditorWidget_6->refreshDisplay();
}

void TalesQtPowerUpEditorWidget::initializeEmeraldEditor(
                             EmeraldEditorWidget* widget,
                             int emeraldNum) {
    widget->setEmeraldNum(emeraldNum);
    widget->setPowerUpData(
                powerUpEditor_.powerUpData());
    widget->setEmeraldHealthRefills(
                powerUpEditor_.emeraldHealthRefills());
}
