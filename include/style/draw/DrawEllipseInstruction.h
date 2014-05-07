#pragma once

#include "style/draw/DrawShapeInstruction.h"

namespace wxstyle {

    class DrawEllipseInstruction : public DrawShapeInstruction {
    public:
        class Params : public DrawShapeInstruction::Params {};

    public:
        DrawEllipseInstruction(const Params& params);

        void Draw(wxGraphicsContext* g, const wxSize& windowSize) const override;
    };

} // namespace wxstyle