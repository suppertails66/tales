#ifndef TALESQTSTATE_H
#define TALESQTSTATE_H

#include "talesqteditormodes.h"
#include "talesqtmainwindow.h"
#include "editors/TailsAdvEditor.h"
#include "util/IniFile.h"
#include <string>

/**
 * Simple global class representing application state.
 * This includes the currently selected editor and so on.
 */
class TalesQtState
{
public:
    TalesQtState();

    ~TalesQtState();

    void reload();

    void changeEditor(TalesQtEditorModes::TalesQtEditorMode editorMode__);

    void setMainWindow(TalesQtMainWindow* mainWindow__);

    void startEditor(const std::string& filename);

    Tales::TailsAdvEditor& editor();

    std::string lastLoadedFileName();
    void setLastLoadedFileName(const std::string& lastLoadedFileName__);

    Luncheon::IniFile& configFile();
    void writeConfigFile();
protected:
    const static std::string configFileName_;

    TalesQtMainWindow* mainWindow_;

    Tales::TailsAdvEditor* editor_;

    TalesQtEditorModes::TalesQtEditorMode editorMode_;

    std::string lastLoadedFileName_;

    Luncheon::IniFile configFile_;

};

#endif // TALESQTSTATE_H
