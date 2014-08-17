#include "style/draw/DrawShapeInstruction.h"

#include <wx/brush.h>
#include <wx/colour.h>

#include "style/draw/Anchor.h"
#include "DimRect.h"
#include "Insets.h"

namespace wxstyle {

    typedef DrawShapeInstruction::Params Params;

    struct Params::ParamsImpl {
        DimRect rect;
        wxBrush brush;
        int penSize;
        wxColour penColor;
        wxPenStyle penStyle;
        int cornerRadius;
        HorizontalAlignment horizontalAnchor;
        VerticalAlignment verticalAnchor;
        boost::optional<GradientDefinitionPtr> gradientDefinition;
    };

    Params::Params() {
        impl = std::make_shared<ParamsImpl>();
        impl->rect = DimRect(0, 0, Dimension(0, 1), Dimension(0, 1));
        impl->brush = *wxBLACK_BRUSH;
        impl->penSize = 0;
        impl->penColor = *wxBLACK;
        impl->penStyle = wxPENSTYLE_SOLID;
        impl->cornerRadius = 0;
        impl->horizontalAnchor = HorizontalAlignment::HA_LEFT;
        impl->verticalAnchor = VerticalAlignment::VA_TOP;
    }

    Params& Params::SetRect(const DimRect& rect) {
        impl->rect = rect;
        return *this;
    }

    Params& Params::SetInsets(int left, int top, int right, int bottom) {
        impl->rect = DimRect(left, top, Dimension(-left - right, 1), Dimension(-top - bottom, 1));
        return *this;
    }

    Params& Params::SetInsets(const Insets& insets) {
        SetInsets(insets.Left(), insets.Top(), insets.Right(), insets.Bottom());
        return *this;
    }

    Params& Params::SetColor(const wxColor& color) {
        impl->brush = wxBrush(color);
        return *this;
    }

    Params& Params::SetGradientDefinition(const GradientDefinitionPtr gradientDefinition) {
        impl->gradientDefinition = gradientDefinition;
        return *this;
    }

    Params& Params::SetBrush(const wxBrush& brush) {
        impl->brush = brush;
        return *this;
    }

    Params& Params::SetPenSize(const int penSize) {
        impl->penSize = penSize;
        return *this;
    }

    Params& Params::SetPenColor(const wxColor& penColor) {
        impl->penColor = penColor;
        return *this;
    }

    Params& Params::SetPenStyle(const wxPenStyle penStyle) {
        impl->penStyle = penStyle;
        return *this;
    }

    Params& Params::SetCornerRadius(const int cornerRadius) {
        impl->cornerRadius = cornerRadius;
        return *this;
    }

    Params& Params::SetHorizontalAnchor(HorizontalAlignment horizontalAnchor) {
        impl->horizontalAnchor = horizontalAnchor;
        return *this;
    }

    Params& Params::SetVerticalAnchor(VerticalAlignment verticalAnchor) {
        impl->verticalAnchor = verticalAnchor;
        return *this;
    }

    DimRect Params::GetRect() const {
        return impl->rect;
    }

    wxBrush Params::GetBrush() const {
        return impl->brush;
    }

    bool Params::HasGradientDefinition() const {
        return impl->gradientDefinition;
    }

    GradientDefinitionPtr Params::GetGradientDefinition() const {
        return impl->gradientDefinition.get();
    }

    int Params::GetPenSize() const {
        return impl->penSize;
    }

    wxColour Params::GetPenColor() const {
        return impl->penColor;
    }

    wxPenStyle Params::GetPenStyle() const {
        return impl->penStyle;
    }

    int Params::GetCornerRadius() const {
        return impl->cornerRadius;
    }

    HorizontalAlignment Params::GetHorizontalAnchor() const {
        return impl->horizontalAnchor;
    }

    VerticalAlignment Params::GetVerticalAnchor() const {
        return impl->verticalAnchor;
    }

    DrawShapeInstruction::DrawShapeInstruction(const Params& params) : parameters(params) {}

    Params DrawShapeInstruction::GetParams() const {
        return parameters;
    }

    std::ostream& operator<<(std::ostream& lhs, const DrawShapeInstruction& rhs) {
        return lhs << "DrawRectangleInstruction("
            << "rect:" << rhs.GetParams().GetRect() << " "
            //<< "color:" << std::hex << rhs.GetBrush() << std::dec << " "
            << "penSize:" << rhs.GetParams().GetPenSize() << " "
            << "penColor:" << std::hex << rhs.GetParams().GetPenColor().GetRGB() << std::dec << " "
            << "penStyle:" << rhs.GetParams().GetPenStyle() << " "
            << "cornerRadius:" << rhs.GetParams().GetCornerRadius() << ")";
    }

    bool operator==(const DrawShapeInstruction& lhs, const DrawShapeInstruction& rhs) {
        return lhs.GetParams().GetRect() == rhs.GetParams().GetRect() && lhs.GetParams().GetBrush() == rhs.GetParams().GetBrush() && 
            lhs.GetParams().GetPenColor() == rhs.GetParams().GetPenColor()&& lhs.GetParams().GetPenSize() == rhs.GetParams().GetPenSize() && 
            lhs.GetParams().GetPenStyle() == rhs.GetParams().GetPenStyle() && lhs.GetParams().GetCornerRadius() == rhs.GetParams().GetCornerRadius() && 
            lhs.GetParams().HasGradientDefinition() == rhs.GetParams().HasGradientDefinition() && 
            lhs.GetParams().HasGradientDefinition() ? lhs.GetParams().GetGradientDefinition() == rhs.GetParams().GetGradientDefinition() : true;
    }

} // namespace wxstyle