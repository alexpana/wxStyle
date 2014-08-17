#pragma once

#include <wx/gdicmn.h>
#include <cstdint>

namespace wxstyle {

    enum HorizontalAlignment {
        HA_LEFT,
        HA_CENTER,
        HA_RIGHT
    };

    enum VerticalAlignment {
        VA_TOP,
        VA_CENTER,
        VA_BOTTOM
    };

    wxPoint ComputeOffset(double w, double h, HorizontalAlignment ha, VerticalAlignment va);

    wxPoint ComputeOffset(const wxSize& referenceSize, HorizontalAlignment ha, VerticalAlignment va);

    wxPoint ComputeOffset(const wxPoint& referencePoint, HorizontalAlignment ha, VerticalAlignment va);

    double ComputeOffset(double w, HorizontalAlignment ha);

    double ComputeOffset(double h, VerticalAlignment va);

} // namespace wxstyle