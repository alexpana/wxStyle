#pragma once

#include <wx/gdicmn.h>

namespace wxstyle {

    enum HorizontalAnchor {
        HA_LEFT,
        HA_CENTER,
        HA_RIGHT
    };

    enum VerticalAnchor {
        VA_TOP,
        VA_CENTER,
        VA_BOTTOM
    };

    wxPoint ComputeOffset(double w, double h, HorizontalAnchor ha, VerticalAnchor va);

    wxPoint ComputeOffset(const wxSize& referenceSize, HorizontalAnchor ha, VerticalAnchor va);

    wxPoint ComputeOffset(const wxPoint& referencePoint, HorizontalAnchor ha, VerticalAnchor va);

    double ComputeOffset(double w, HorizontalAnchor ha);

    double ComputeOffset(double h, VerticalAnchor va);

} // namespace wxstyle