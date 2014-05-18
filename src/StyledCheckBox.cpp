#include <wx/graphics.h>

#include "DimRect.h"
#include "StyledCheckBox.h"
#include "style/draw/DrawRectangleInstruction.h"

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
        
            GradientDefinitionPtr gradientDefinition = std::make_shared<RadialGradientDefinition>(RadialGradientDefinition());
            gradientDefinition->AddColorStop(0, "#000000");
            gradientDefinition->AddColorStop(1, "#FFFFFF");

			if (dynamic_cast<StyledCheckBox*>(window)->IsChecked()) {
				DrawRectangleInstruction(
                    DrawRectangleInstruction::Params()
                        .SetRect(DimRect(1, 1, 12, 12))
                        .SetGradientDefinition(gradientDefinition))
                    .Draw(g.get(), window->GetSize());
			} else {
				g->SetBrush(g->CreateBrush(wxBrush("#595757")));
                g->DrawEllipse(2, 2, 10, 10);
			}

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
		SetMinSize(wxSize(DEFAULT_MIN_WIDTH, 14));
		SetOpaque(false);
		m_isChecked = false;
	}

	void StyledCheckBox::OnMouseDown(wxMouseEvent& mouseEvent) {
		ToggleChecked();
	}

	void StyledCheckBox::OnMouseDoubleClick(wxMouseEvent& mouseEvent) {
		OnMouseDown(mouseEvent);
	}
} // namespace wxstyle