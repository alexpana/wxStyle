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
                .SetFontDefinition(window->GetStyle().GetFont())
                .SetShadowDefinition(window->GetStyle().GetTextShadow())
                .SetText(window->GetText())
                .SetTextColor(window->GetStyle().GetForegroundColor())
                .SetHorizontalAnchor(HA_LEFT)
                .SetTextPosition(DimPoint(0, Dimension(0, 0.5f))))
            .Draw(g.get(), window->GetSize());
		}
	};

    Style StyledLabel::GetDefaultStyle() {
        return StyledWindow::GetDefaultStyle()
            .SetTextAlignment(wxALIGN_CENTER_VERTICAL)
            .SetFont(FontDefinition().SetSize(9).SetFace("Tahoma").SetWeight(wxFONTWEIGHT_NORMAL))
            .SetForegroundColor("#929395");
    }

	StyledLabel::StyledLabel(wxWindow *parent) : StyledWindow(parent) {
		Init();
	}

	void StyledLabel::Init() {
		SetOpaque(false);

		SetRenderer(std::shared_ptr<DefaultLabelRenderer>(new DefaultLabelRenderer()));
        SetStyle(StyledLabel::GetDefaultStyle());
	}

} // namespace wxstyle