#include <QApplication>
#include "talesqtmainwindow.h"
#include "startupromdialog.h"
#include "talesqtstatevar.h"
#include "genericerrordialog.h"
#include "exception/TalesException.h"
#include "exception/OutOfRangeIndexException.h"
#include "util/StringConversion.h"
#include "util/FileManip.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace Luncheon;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Check config file for data
    if ((!(appState_.configFile().hasKey("Global", "SourceRomPath")))
            || (!(FileManip::fileExists(
              (appState_.configFile().valueOfKey("Global", "SourceRomPath")))))) {
        // If config file does not have source ROM path or that ROM does not
        // exist, do ROM select dialog
        StartupROMDialog romDialog;
        int result = romDialog.exec();

        // on cancel: can't continue without ROM, exit editor
        if (result == QDialog::Rejected) {
            return 0;
        }

        appState_.configFile().setValue(
                    "Global", "SourceRomPath", romDialog.selectedFileName());
    }

//    appState_.writeConfigFile();

    std::string sourceRomPath = appState_.configFile()
                        .valueOfKey("Global", "SourceRomPath");

//    std::cerr << sourceRomPath << std::endl;

    try {

    appState_.startEditor(sourceRomPath);

    TalesQtMainWindow w;
    w.show();
    int result = a.exec();

    // Save config file on exit
    appState_.writeConfigFile();

    return result;

    }
//    catch (Tales::OutOfRangeIndexException& e) {
//        std::cerr << "out of range index: " << e.nameOfSourceFile()
//                  << " line " << e.lineNum() << std::endl;
//    }
    catch (Tales::TalesException& e) {
        GenericErrorDialog(std::string("Fatal error: ")
                           + "TalesException: "
                           + e.what()
                           + "\n\n"
                           + "Source: " + e.nameOfSourceFile()
                           + ",\n" + e.source()
                           + ", line " + StringConversion::toString(e.lineNum()))
                .exec();
    }
    catch (std::exception& e) {
        GenericErrorDialog(std::string("Fatal error: ")
                           + "std::exception: "
                           + e.what())
                .exec();
    }
    catch (...) {
        GenericErrorDialog(std::string("Fatal error: ")
                           + "unknown problem, aborting")
                .exec();
    }
}
