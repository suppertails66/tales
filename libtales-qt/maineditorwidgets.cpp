#include "maineditorwidgets.h"
#include "ui_maineditorwidgets.h"
#include "talesqtleveleditorwidget.h"
#include "talesqtvrameditorwidget.h"
#include "talesqtmetatilebehavioreditorwidget.h"
#include "talesqtlengthmapeditorwidget.h"
#include "talesqtpaletteeditorwidget.h"
#include "talesqtmetatilestructureeditorwidget.h"
#include "talesqtgraphicseditorwidget.h"
#include "talesqtpowerupeditorwidget.h"
#include "talesqtmusiceditorwidget.h"
#include "talesqtpalettecycleeditorwidget.h"
#include "talesqtenhancementseditor.h"

MainEditorWidgets::MainEditorWidgets(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainEditorWidgets)
{
    ui->setupUi(this);

    // Set up editor widgets
    TalesQtLevelEditorWidget* levelEditor
            = new TalesQtLevelEditorWidget();
    TalesQtVRAMEditorWidget* vramEditor
            = new TalesQtVRAMEditorWidget();
    TalesQtMetatileBehaviorEditorWidget* metatileBehaviorEditor
            = new TalesQtMetatileBehaviorEditorWidget();
    TalesQtLengthMapEditorWidget* lengthMapsEditor
            = new TalesQtLengthMapEditorWidget();
    TalesQtPaletteEditorWidget* paletteEditor
            = new TalesQtPaletteEditorWidget();
    TalesQtMetatileStructureEditorWidget* metatileStructureEditor
            = new TalesQtMetatileStructureEditorWidget();
    TalesQtGraphicsEditorWidget* graphicsEditor
            = new TalesQtGraphicsEditorWidget();
    TalesQtPowerUpEditorWidget* powerUpEditor
            = new TalesQtPowerUpEditorWidget();
    TalesQtMusicEditorWidget* musicEditor
            = new TalesQtMusicEditorWidget();
    TalesQtPaletteCycleEditorWidget* paletteCycleEditor
            = new TalesQtPaletteCycleEditorWidget();
    TalesQtEnhancementsEditor* enhancementsEditor
            = new TalesQtEnhancementsEditor();

    // TODO: whyyyy won't qt let me remove the default pages
    // in the form editor
    while (ui->stackedWidget->count()) {
        ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
    }

    ui->stackedWidget->addWidget(levelEditor);
    ui->stackedWidget->addWidget(vramEditor);
    ui->stackedWidget->addWidget(metatileBehaviorEditor);
    ui->stackedWidget->addWidget(lengthMapsEditor);
    ui->stackedWidget->addWidget(paletteEditor);
    ui->stackedWidget->addWidget(metatileStructureEditor);
    ui->stackedWidget->addWidget(graphicsEditor);
    ui->stackedWidget->addWidget(powerUpEditor);
    ui->stackedWidget->addWidget(musicEditor);
    ui->stackedWidget->addWidget(paletteCycleEditor);
    ui->stackedWidget->addWidget(enhancementsEditor);

    // Load initial data
//    levelEditor->reloadAndRefresh();
    vramEditor->reloadAndRefresh();
}

MainEditorWidgets::~MainEditorWidgets()
{
    delete ui;
}

QStackedWidget& MainEditorWidgets::stackedWidget() {
    return *(ui->stackedWidget);
}
