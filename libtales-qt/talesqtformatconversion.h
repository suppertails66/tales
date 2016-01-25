#ifndef TALESQTFORMATCONVERSION_H
#define TALESQTFORMATCONVERSION_H

#include "structs/Graphic.h"
#include <QPixmap>
#include <QImage>

class TalesQtFormatConversion
{
public:
    static QPixmap graphicToPixmap(Tales::Graphic& graphic);

    static QImage graphicToImage(Tales::Graphic& graphic);

    static void drawGraphicToImage(QImage& image,
                                   Tales::Graphic& graphic);
protected:

};

#endif // TALESQTFORMATCONVERSION_H
