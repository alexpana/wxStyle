#include "Algorithms.h"

namespace wxstyle {

    wxPoint Align(wxSize referenceSize, wxSize objectSize, AlignmentDefinition alignment) {
        int x = 0;
        int y = 0;

        if (alignment.GetHorizontal() == HA_LEFT) x = 0;
        if (alignment.GetHorizontal() == HA_CENTER) x = (referenceSize.GetWidth() - objectSize.GetWidth()) / 2;
        if (alignment.GetHorizontal() == HA_RIGHT) x = referenceSize.GetWidth() - objectSize.GetWidth();

        if (alignment.GetVertical() == VA_TOP) y = 0;
        if (alignment.GetVertical() == VA_CENTER) y = (referenceSize.GetHeight() - objectSize.GetHeight()) / 2;
        if (alignment.GetVertical() == VA_BOTTOM) y = referenceSize.GetHeight() - objectSize.GetHeight();

        return wxPoint(x, y);
    }

} // namespace wxstyle