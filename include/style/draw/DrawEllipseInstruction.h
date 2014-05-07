#pragma once

#include "style/draw/DrawShapeInstruction.h"

namespace wxstyle {

    class DrawEllipseInstruction : public DrawShapeInstruction {
    public:
        DrawEllipseInstruction(const DrawShapeInstruction::Params& params);

        void Draw(wxGraphicsContext* g, const wxSize& windowSize) const override;
    };

} // namespace wxstyle