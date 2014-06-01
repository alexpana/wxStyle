#pragma once

#include <wx/pen.h>

#include "style/draw/Anchor.h"
#include "style/draw/DrawInstruction.h"
#include "style/draw/Gradient.h"

class wxColor;
class wxBrush;

namespace wxstyle { 

    class DimRect;

    class DrawShapeInstruction : public DrawInstruction {
    public:
        class Params {

        public:
            Params();

            Params& SetRect(const DimRect& rect);

            Params& SetInsets(int left, int top, int right, int bottom);

            DimRect GetRect() const;

            Params& SetColor(const wxColor& color);

            Params& SetBrush(const wxBrush& brush);

            wxBrush GetBrush() const;

            Params& SetGradientDefinition(const GradientDefinitionPtr gradientDefinition);

            bool HasGradientDefinition() const;

            GradientDefinitionPtr GetGradientDefinition() const;

            Params& SetPenSize(const int penSize);

            int GetPenSize() const;

            Params& SetPenColor(const wxColor& penColor);

            wxColour GetPenColor() const;

            Params& SetPenStyle(const wxPenStyle penStyle);

            wxPenStyle GetPenStyle() const;

            Params& SetCornerRadius(const int cornerRadius);

            int GetCornerRadius() const;

            Params& SetHorizontalAnchor(HorizontalAnchor horizontalAnchor);

            HorizontalAnchor GetHorizontalAnchor() const;

            Params& SetVerticalAnchor(VerticalAnchor verticalAnchor);

            VerticalAnchor GetVerticalAnchor() const;

        private:
            struct ParamsImpl;
            std::shared_ptr<ParamsImpl> impl;
        };

    public:
        DrawShapeInstruction(const Params& params);

        virtual void Draw(wxGraphicsContext* g, const wxSize& windowSize) const = 0;

        Params GetParams() const;

    private:
        Params parameters;
    };

    std::ostream& operator<<(std::ostream& lhs, const DrawShapeInstruction& rhs);
    bool operator==(const DrawShapeInstruction& lhs, const DrawShapeInstruction& rhs);

} // namespace wxstyle