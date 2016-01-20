#include "vrameditorpreviewlabel.h"
#include "talesqtvrameditorwidget.h"
#include "talesqtformatconversion.h"
#include "talesqtstatevar.h"
#include <QMouseEvent>
#include <iostream>

using namespace Tales;

VRAMEditorPreviewLabel::VRAMEditorPreviewLabel(QWidget *parent) :
    QLabel(parent),
    parentEditor_(*(dynamic_cast<TalesQtVRAMEditorWidget*>(parent)))
{
    previewBuffer_ = Graphic(appState_.editor().vramEditor().previewWidth(),
                             appState_.editor().vramEditor().previewHeight());
}

void VRAMEditorPreviewLabel::refreshDisplay() {
    // Resize cache if needed
    if ((previewBuffer_.w() != appState_.editor().vramEditor().previewWidth())
        || (previewBuffer_.h() != appState_.editor().vramEditor().previewHeight())) {
        previewBuffer_ = Graphic(appState_.editor().vramEditor().previewWidth(),
                                 appState_.editor().vramEditor().previewHeight());
    }

    // Generate VRAM preview Graphic
//    Graphic vram = appState_.editor().vramEditor().previewGraphic();
    appState_.editor().vramEditor().drawPreviewGraphic(previewBuffer_);

    // Convert to pixmap
    QPixmap pixmap = TalesQtFormatConversion::graphicToPixmap(previewBuffer_);

    // Change displayed pixmap
    setPixmap(pixmap);

    // Resize as needed
    resize(pixmap.width(), pixmap.height());
}

void VRAMEditorPreviewLabel::mousePressEvent(QMouseEvent* event) {
    // Send left click to editor if left button down
    if (event->buttons() & Qt::LeftButton) {

        // Convert coordinates from absolute to scene using scale
        appState_.editor().vramEditor().mouseLeftClick(
                event->x() / parentEditor_.scale(),
                event->y() / parentEditor_.scale());

        // Update selection if click was successful
//        if (appState_.editor().vramEditor().objectIsSelected()) {
//            parentEditor_.refreshSelectedObject();
//        }
    }

//    std::cerr << "here" << std::endl;
    parentEditor_.refreshSelectedObject();
//    std::cerr << "here2" << std::endl;
    parentEditor_.refreshVRAMIndices();

    // Redraw
    refreshDisplay();
}

void VRAMEditorPreviewLabel::mouseReleaseEvent(QMouseEvent* event) {
    // Send left click to editor if left button down
    if (!(event->buttons() & Qt::LeftButton)) {
        // Convert coordinates from absolute to scene using scale
        appState_.editor().vramEditor().mouseLeftRelease(
                event->x() / parentEditor_.scale(),
                event->y() / parentEditor_.scale());

        parentEditor_.refreshSelectedObject();
    }

    parentEditor_.refreshSelectedObject();
    parentEditor_.refreshVRAMIndices();

    // Redraw
    refreshDisplay();
}

void VRAMEditorPreviewLabel::mouseMoveEvent(QMouseEvent* event) {
    // Send mouse move to editor.
    // Convert coordinates from absolute to scene using scale
    appState_.editor().vramEditor().mouseMove(
                event->x() / parentEditor_.scale(),
                event->y() / parentEditor_.scale(),
                event->buttons()
                  & Qt::LeftButton);

    // Redraw
    refreshDisplay();
}

void VRAMEditorPreviewLabel::enterEvent(QEvent* event) {

}

void VRAMEditorPreviewLabel::leaveEvent(QEvent* event) {
    appState_.editor().vramEditor().mouseLeave();

    // Redraw
    refreshDisplay();
}
