#include "talesqtstate.h"
#include "talesqtformatconversion.h"
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
#include <iostream>

using namespace Tales;

const std::string TalesQtState::configFileName_("tales.cfg");

TalesQtState::TalesQtState()
    : mainWindow_(0),
      editor_(0),
      editorMode_(static_cast<TalesQtEditorModes::TalesQtEditorMode>(0)),
      configFile_(configFileName_) { };

TalesQtState::~TalesQtState() {
    delete editor_;
}

void TalesQtState::reload() {
    changeEditor(editorMode_);
}

void TalesQtState::changeEditor(TalesQtEditorModes::TalesQtEditorMode editorMode__) {
    // Change displayed editor widget
    mainWindow_->mainEditorWidgets().stackedWidget().setCurrentIndex(editorMode__);

    // Refresh the switched-to widget
    switch (editorMode__) {
    case TalesQtEditorModes::levelEditor:
    {
        TalesQtLevelEditorWidget* widget
                = (TalesQtLevelEditorWidget*)(mainWindow_->mainEditorWidgets()
                                                .stackedWidget().currentWidget());
        widget->reloadAndRefresh();
        break;
    }
    case TalesQtEditorModes::vramEditor:
    {
//        editor_->vramEditor().changeMap(++areaNum, 1);
//        editor_->vramEditor().refresh();
        TalesQtVRAMEditorWidget* widget
                = (TalesQtVRAMEditorWidget*)(mainWindow_->mainEditorWidgets()
                                                .stackedWidget().currentWidget());
        widget->refreshDisplay();
        break;
    }
    case TalesQtEditorModes::metatileBehaviorEditor:
    {
//        editor_->vramEditor().changeMap(++areaNum, 1);
//        editor_->vramEditor().refresh();
        TalesQtMetatileBehaviorEditorWidget* widget
                = (TalesQtMetatileBehaviorEditorWidget*)
                    (mainWindow_->mainEditorWidgets()
                        .stackedWidget().currentWidget());
        widget->reloadAndRefresh();
        break;
    }
    case TalesQtEditorModes::lengthMapsEditor:
    {
//        editor_->vramEditor().changeMap(++areaNum, 1);
//        editor_->vramEditor().refresh();
        TalesQtLengthMapEditorWidget* widget
                = (TalesQtLengthMapEditorWidget*)
                    (mainWindow_->mainEditorWidgets()
                        .stackedWidget().currentWidget());
        widget->refreshDisplay();
        break;
    }
    case TalesQtEditorModes::paletteEditor:
    {
//        editor_->vramEditor().changeMap(++areaNum, 1);
//        editor_->vramEditor().refresh();
        TalesQtPaletteEditorWidget* widget
                = (TalesQtPaletteEditorWidget*)
                    (mainWindow_->mainEditorWidgets()
                        .stackedWidget().currentWidget());
        widget->refreshDisplay();
        break;
    }
    case TalesQtEditorModes::metatileStructureEditor:
    {
        TalesQtMetatileStructureEditorWidget* widget
                = (TalesQtMetatileStructureEditorWidget*)
                    (mainWindow_->mainEditorWidgets()
                        .stackedWidget().currentWidget());
        widget->refreshDisplay();
        break;
    }
    case TalesQtEditorModes::graphicsEditor:
    {
        TalesQtGraphicsEditorWidget* widget
                = (TalesQtGraphicsEditorWidget*)
                    (mainWindow_->mainEditorWidgets()
                        .stackedWidget().currentWidget());
        widget->refreshDisplay();
        break;
    }
    case TalesQtEditorModes::powerUpEditor:
    {
        TalesQtPowerUpEditorWidget* widget
                = (TalesQtPowerUpEditorWidget*)
                    (mainWindow_->mainEditorWidgets()
                        .stackedWidget().currentWidget());
        widget->refreshDisplay();
        break;
    }
    case TalesQtEditorModes::musicEditor:
    {
        TalesQtMusicEditorWidget* widget
                = (TalesQtMusicEditorWidget*)
                    (mainWindow_->mainEditorWidgets()
                        .stackedWidget().currentWidget());
        widget->refreshDisplay();
        break;
    }
    case TalesQtEditorModes::paletteCycleEditor:
    {
        TalesQtPaletteCycleEditorWidget* widget
                = (TalesQtPaletteCycleEditorWidget*)
                    (mainWindow_->mainEditorWidgets()
                        .stackedWidget().currentWidget());
        widget->refreshDisplay();
        break;
    }
    case TalesQtEditorModes::enhancementsEditor:
    {
        TalesQtEnhancementsEditor* widget
                = (TalesQtEnhancementsEditor*)
                    (mainWindow_->mainEditorWidgets()
                        .stackedWidget().currentWidget());
        widget->refreshDisplay();
        break;
    }
    default:
        break;
    }

    editorMode_ = editorMode__;

    mainWindow_->changeMode(editorMode__);
}

TailsAdvEditor& TalesQtState::editor() {
    return *editor_;
}

void TalesQtState::setMainWindow(TalesQtMainWindow* mainWindow__) {
    mainWindow_ = mainWindow__;
}

void TalesQtState::startEditor(const std::string& filename) {
    editor_ = new TailsAdvEditor(filename);
}

std::string TalesQtState::lastLoadedFileName() {
    return lastLoadedFileName_;
}

void TalesQtState
    ::setLastLoadedFileName(const std::string& lastLoadedFileName__) {
    lastLoadedFileName_ = lastLoadedFileName__;
}

Luncheon::IniFile& TalesQtState::configFile() {
    return configFile_;
}

void TalesQtState::writeConfigFile() {
    configFile_.writeFile(configFileName_);
}
