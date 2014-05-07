#pragma once

class wxSize;
class wxGraphicsContext;

namespace wxstyle {    

    class DrawInstruction {
	public:
		virtual void Draw(wxGraphicsContext* g, const wxSize& windowSize) const = 0;
    };

} // namespace wxstyle