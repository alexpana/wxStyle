#include "StyledLabel.h"

#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/window.h>
#include <wx/fontenum.h>

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
			wxString text = window->GetLabel();
			std::shared_ptr<Style> style = window->GetStyle();

			int fontFlags = wxFONTFLAG_DEFAULT;
			if (window->GetFont().GetWeight() == wxFONTWEIGHT_BOLD) {
				fontFlags = fontFlags | wxFONTFLAG_BOLD;
			}

			g->SetFont(g->CreateFont(12, "Tahoma", fontFlags, window->GetForegroundColour()));
			g->SetBrush(wxBrush(window->GetForegroundColour()));

			wxSize textSize = deviceContext.GetTextExtent(text);
			wxSize labelSize = window->GetSize();
			wxAlignment textAlignment = dynamic_cast<StyledLabel*>(window)->GetTextAlignment();
			wxPoint textPosition = GetTextPositionFromAlignment(textAlignment, labelSize, textSize);

			RenderBackground(g.get(), window);

			DrawTextInstruction instr = DrawTextInstruction::NewBuilder()
				.SetFontDefinition(FontDefinition().SetSize(9).SetWeight(wxFONTWEIGHT_BOLD))
				.SetShadowDefinition(ShadowDefinition().SetColor("#505050").SetOffset(wxPoint(0, 1)))
				.SetText("Hello World!")
				.SetTextColor("#DADADA")
				.SetHorizontalAnchor(HTA_LEFT)
				.SetTextPosition(DimPoint(4, Dimension(0, 0.5f)))
				.Build();

			DrawRectangleInstruction instr1 = DrawRectangleInstruction::NewBuilder()
				.SetRect(DimRect(1, 1, Dimension(-2, 1), Dimension(-2, 1)))
				.SetPenSize(2)
				.SetPenColor("#8d85dd")
				.SetPenStyle(wxPENSTYLE_SOLID)
				.SetCornerRadius(4)
				.SetBrush(wxBrush("#565186"))
				.Build();

			if (window->IsHovered() && window->IsPressed()) {
				instr1.Draw(g.get(), window->GetSize());
			}

			instr.Draw(g.get(), window->GetSize());
		}

		void RenderBackground( wxGraphicsContext * g, StyledWindow* window ) const
		{
			g->SetBrush(wxBrush(window->GetInheritedBackgroundColor()));
			g->DrawRectangle(0, 0, window->GetSize().GetWidth(), window->GetSize().GetHeight());
		}

		wxPoint GetTextPositionFromAlignment(wxAlignment textAlignment, wxSize &labelSize, wxSize &textSize) const
		{
			wxPoint textPosition(0, 0);

			if (textAlignment & wxAlignment::wxALIGN_CENTER_HORIZONTAL) {
				textPosition.x = (labelSize.GetWidth() - textSize.GetWidth()) / 2;
			}

			if (textAlignment & wxAlignment::wxALIGN_RIGHT) {
				textPosition.x = labelSize.GetWidth() - textSize.GetWidth();
			}

			if (textAlignment & wxAlignment::wxALIGN_CENTER_VERTICAL) {
				textPosition.y = (labelSize.GetHeight() - textSize.GetHeight()) / 2;
			}

			if (textAlignment & wxAlignment::wxALIGN_BOTTOM) {
				textPosition.y = labelSize.GetHeight() - textSize.GetHeight();
			}

			return textPosition;
		}

		void RenderText(wxGraphicsContext *g, wxString text, wxPoint &textPosition, int fontFlags, StyledWindow *window) const
		{
	//         g->SetFont(g->CreateFont(12, "Tahoma", fontFlags, 0x161616));
	//         g->DrawText(text, textPosition.x + 1, textPosition.y + 1);

			g->SetFont(g->CreateFont(11, "Tahoma", fontFlags, window->GetForegroundColour()));
			g->DrawText(text, textPosition.x, textPosition.y);
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