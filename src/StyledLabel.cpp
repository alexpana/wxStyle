#include "StyledLabel.h"

#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/window.h>
#include <wx/fontenum.h>

#include "DimPoint.h"
#include "DimRect.h"
#include "style/draw/DrawTextInstruction.h"
#include "style/draw/DrawRectangleInstruction.h"

namespace wxstyle {

	class DefaultLabelRenderer : public IRenderer {
	public:
		DefaultLabelRenderer() {};
		~DefaultLabelRenderer() {};

		virtual void Render(StyledWindow* window) const {
			wxAutoBufferedPaintDC deviceContext(window);
			auto g = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(deviceContext));

			DrawRectangleInstruction(DrawRectangleInstruction::Params()
                .SetColor(window->GetInheritedBackgroundColor()))
            .Draw(g.get(), window->GetSize());

            DrawTextInstruction(DrawTextInstruction::Params()
                .SetFontDefinition(FontDefinition().SetSize(9).SetFace("Tahoma").SetWeight(wxFONTWEIGHT_BOLD))
                .SetShadowDefinition(ShadowDefinition().SetColor("#505050").SetOffset(wxPoint(0, 1)))
                .SetText(window->GetText())
                .SetTextColor("#202020")
                .SetHorizontalAnchor(HA_LEFT)
                .SetTextPosition(DimPoint(0, Dimension(0, 0.5f))))
            .Draw(g.get(), window->GetSize());
		}
	};

	StyledLabel::StyledLabel(wxWindow *parent) : StyledWindow(parent) {
		Init();
	}

	void StyledLabel::Init() {
		SetOpaque(false);
		SetTextAlignment(wxALIGN_CENTER_VERTICAL);
		SetRenderer(std::shared_ptr<DefaultLabelRenderer>(new DefaultLabelRenderer()));
	}

} // namespace wxstyle