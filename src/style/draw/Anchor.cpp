#include "style/draw/Anchor.h"

namespace wxstyle {

    wxPoint ComputeOffset(double w, double h, HorizontalAnchor ha, VerticalAnchor va) {
        return wxPoint(ComputeOffset(w, ha), ComputeOffset(h, va));
    }

    wxPoint ComputeOffset(const wxSize& referenceSize, HorizontalAnchor ha, VerticalAnchor va) {
        return ComputeOffset(referenceSize.GetWidth(), referenceSize.GetHeight(), ha, va);
    }

    wxPoint ComputeOffset(const wxPoint& referencePoint, HorizontalAnchor ha, VerticalAnchor va) {
        return ComputeOffset(referencePoint.x, referencePoint.y, ha, va);
    }

    double ComputeOffset(double w, HorizontalAnchor horizontalAnchor) {
        switch(horizontalAnchor) {
            case HA_LEFT: return 0;
            case HA_CENTER: return - w / 2;
            case HA_RIGHT: return - w;
        }
        return 0;
    }

    double ComputeOffset(double h, VerticalAnchor verticalAnchor) {
        switch(verticalAnchor) {
            case VA_TOP: return 0;
            case VA_CENTER: return - h / 2;
            case VA_BOTTOM: return - h;
        }
        return 0;
    }

} // namespace wxstyle