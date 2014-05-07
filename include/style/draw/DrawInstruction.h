#pragma once

#include <wx/brush.h>
#include <wx/colour.h>
#include <wx/gdicmn.h>
#include <wx/graphics.h>
#include <wx/pen.h>

#include "DimRect.h"

namespace wxstyle {    

    class DrawInstruction {
	public:
		virtual void Draw(wxGraphicsContext* g, const wxSize& windowSize) const = 0;
    };

} // namespace wxstyle