#include "talesqtformatconversion.h"
#include <QImage>
#include <QPixmap>

using namespace Tales;

QPixmap TalesQtFormatConversion::graphicToPixmap(Graphic& graphic) {
    QImage temp(graphic.w(), graphic.h(), QImage::Format_RGB32);

    for (int j = 0; j < graphic.h(); j++) {
        QRgb* rgb = (QRgb*)(temp.scanLine(j));

        for (int i = 0; i < graphic.w(); i++) {
            Color color = graphic.getPixel(i, j);
            (*rgb) = qRgba(color.r(),
                           color.g(),
                           color.b(),
                           // Convert from our alpha to Qt's
                           0xFF - color.a());
            ++rgb;
        }
    }

    return QPixmap().fromImage(temp);
}

void TalesQtFormatConversion::drawGraphicToImage(QImage& image,
                               Tales::Graphic& graphic) {
    if ((image.width() != graphic.w())
        || (image.height() != graphic.h())) {
        image = QImage(graphic.w(), graphic.h(), QImage::Format_RGB32);
    }

    for (int j = 0; j < graphic.h(); j++) {
        QRgb* rgb = (QRgb*)(image.scanLine(j));

        for (int i = 0; i < graphic.w(); i++) {
            Color color = graphic.getPixel(i, j);
            (*rgb) = qRgba(color.r(),
                           color.g(),
                           color.b(),
                           color.a());
            ++rgb;
        }
    }
}
