#include "objectheadercombobox.h"
#include "util/StringConversion.h"
#include <string>

using namespace Tales;
using namespace Luncheon;

ObjectHeaderComboBox::ObjectHeaderComboBox(QWidget *parent) :
    QComboBox(parent)
{
}

void ObjectHeaderComboBox::repopulate(EditableLevelGraphicsData& src) {
    // Clear existing contents
    clear();

    for (int i = 0; i < src.numBaseObjectGraphicsHeaders(); i++) {
        // Add stock headers
        addItem((std::string("Stock object group ")
                + StringConversion::toString(i)).c_str(),
                QVariant(i));
    }
    for (int i = src.numBaseObjectGraphicsHeaders();
         i < src.objectGraphicsHeadersSize();
         i++) {
        // Add user-made headers (if they exist)
        addItem((std::string("Custom object group ")
                + StringConversion::toString(
                    i - src.numBaseObjectGraphicsHeaders())).c_str(),
                QVariant(i));
    }
}
