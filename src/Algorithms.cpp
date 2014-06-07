#include "Algorithms.h"

namespace wxstyle {

    wxPoint Align(wxSize referenceSize, wxSize objectSize, int alignment) {
        int x = 0;
        int y = 0;

        if (alignment & wxAlignment::wxALIGN_LEFT) x = 0;
        if (alignment & wxAlignment::wxALIGN_CENTER_HORIZONTAL) x = (referenceSize.GetWidth() - objectSize.GetWidth()) / 2;
        if (alignment & wxAlignment::wxALIGN_RIGHT) x = referenceSize.GetWidth() - objectSize.GetWidth();

        if (alignment & wxAlignment::wxALIGN_TOP) y = 0;
        if (alignment & wxAlignment::wxALIGN_CENTER_VERTICAL) y = (referenceSize.GetHeight() - objectSize.GetHeight()) / 2;
        if (alignment & wxAlignment::wxALIGN_BOTTOM) y = referenceSize.GetHeight() - objectSize.GetHeight();

        return wxPoint(x, y);
    }

} // namespace wxstyle