#include <wx/graphics.h>

#include "StyledCheckBox.h"

namespace wxstyle {

	class DefaultCheckBoxRenderer : public IRenderer {
	public:
		virtual void Render(StyledWindow *window) const {
			wxAutoBufferedPaintDC deviceContext(window);
			auto g = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(deviceContext));

			ClearBackground(window, g.get());

			// Draw glow / highlight
			wxColor highlightColor;
	//         if (window->isHovered()) {
				highlightColor = wxColor(111, 119, 98, 60);
	//         } else {
	//             highlightColor = wxColor(111, 119, 98, 0);
	//         }

			g->SetBrush(g->CreateBrush(wxBrush(highlightColor)));
			g->DrawEllipse(0, 0, 14, 14);

			g->SetBrush(g->CreateBrush(wxBrush("#1e1919")));
			g->DrawEllipse(1, 1, 12, 12);
        
			if (dynamic_cast<StyledCheckBox*>(window)->IsChecked()) {
				wxGraphicsGradientStops gradientStops;
				gradientStops.Add(wxColor("#4b6224"), 0.0f);
				gradientStops.Add(wxColor("#719d34"), 0.3f);
				gradientStops.Add(wxColor("#719d34"), 1.0f);
				wxGraphicsBrush brush = g->CreateRadialGradientBrush(7, 7, 7, 7, 5, gradientStops);
        
				g->SetBrush(brush);
			} else {
				g->SetBrush(g->CreateBrush(wxBrush("#595757")));
			}

			g->DrawEllipse(2, 2, 10, 10);

			int fontFlags = wxFONTFLAG_DEFAULT;
			if (window->GetFont().GetWeight() == wxFONTWEIGHT_BOLD) {
				fontFlags = fontFlags | wxFONTFLAG_BOLD;
			}
			g->SetFont(g->CreateFont(11, "Tahoma", fontFlags, window->GetForegroundColour()));
			//g->DrawText(text, textPosition.x, textPosition.y);
			g->DrawText(window->GetText(), 16, 0);
		}

		void ClearBackground(StyledWindow *window, wxGraphicsContext *g) const {
			wxRect clientRect = window->GetClientRect();
			g->SetBrush(g->CreateBrush(window->GetInheritedBackgroundColor()));
			g->DrawRectangle(clientRect.GetX(), clientRect.GetY(), clientRect.GetWidth(), clientRect.GetHeight());
		}
	};

	void StyledCheckBox::Init() {
		SetRenderer(std::shared_ptr<DefaultCheckBoxRenderer>(new DefaultCheckBoxRenderer()));
		SetMinSize(wxSize(DEFAULT_WIDTH, 14));
		SetOpaque(false);
		m_isChecked = false;
	}

	void StyledCheckBox::OnMouseDown(wxMouseEvent& mouseEvent) {
		ToggleChecked();
	}

	void StyledCheckBox::OnMouseDoubleClick(wxMouseEvent& mouseEvent) {
		OnMouseDown(mouseEvent);
	}

	boost::optional<wxString> StyledCheckBox::GetComponentProperty(const wxString& propertyName) {
		if (propertyName == "checked") {
			return m_isChecked ? "t" : "f";
		}

		return boost::optional<wxString>();
	}

} // namespace wxstyle