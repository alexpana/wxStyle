#include <wx/graphics.h>

#include "DimRect.h"
#include "StyledCheckBox.h"
#include "style/draw/DrawRectangleInstruction.h"

namespace wxstyle {

	class StyledCheckBox::Implementation {
	public:
		bool checked;
	};

	class DefaultCheckBoxRenderer : public IRenderer {
	public:
		virtual void Render(StyledWindow *window) const {
			wxAutoBufferedPaintDC deviceContext(window);
			auto g = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(deviceContext));

			ClearBackground(window, g.get());

			DrawCheckbox(window, g.get());

			DrawText(window, g.get());
		}

		void ClearBackground(StyledWindow *window, wxGraphicsContext *g) const {
			wxRect clientRect = window->GetClientRect();
			g->SetBrush(g->CreateBrush(window->GetInheritedBackgroundColor()));
			g->DrawRectangle(clientRect.GetX(), clientRect.GetY(), clientRect.GetWidth(), clientRect.GetHeight());
		}

		void DrawCheckbox(StyledWindow *window, wxGraphicsContext *g) const {
			static const int radius = 0;
			static const wxColour borderColor = "#1c1617";
			static const wxColour bottomHighlight = "#46474B";
			static const wxColour topHighlight = "#606268";
			static const wxColour backgroundColor = "#2b2a2a";
			static const wxColour checkedBorder = "#2f4b20";

			const int h = window->GetSize().GetHeight();
			const int w = h - 1;

			DrawRectangleInstruction bottomHighlightInstruction(DrawShapeInstruction::Params()
				.SetColor(bottomHighlight)
				.SetCornerRadius(radius)
				.SetRect(DimRect(0, 0, Dimension(w, 0), Dimension(h, 0.0))));

			DrawRectangleInstruction borderInstruction = DrawRectangleInstruction(DrawShapeInstruction::Params()
				.SetColor(borderColor)
				.SetCornerRadius(radius)
				.SetRect(DimRect(0, 0, Dimension(w, 0), Dimension(h-1, 0))));

			DrawRectangleInstruction backgroundColorInstruction(DrawShapeInstruction::Params()
				.SetColor(backgroundColor)
				.SetCornerRadius(radius)
				.SetRect(DimRect(1, 1, Dimension(w-2, 0), Dimension(h-3, 0))));

			GradientDefinitionPtr gradient = std::make_shared<LinearGradientDefinition>(LinearGradientDefinition::Direction::VERTICAL);
			gradient->AddColorStop(0, "#61ae36");
			gradient->AddColorStop(1, "#3b6b21");

			DrawRectangleInstruction checkedBackgroundInstruction(DrawShapeInstruction::Params()
				.SetGradientDefinition(gradient)
				.SetCornerRadius(radius)
				.SetRect(DimRect(2, 2, Dimension(w-4, 0), Dimension(h-5, 0))));

			DrawRectangleInstruction checkedBorderInstruction(DrawShapeInstruction::Params()
				.SetColor(checkedBorder)
				.SetCornerRadius(radius)
				.SetRect(DimRect(1, 1, Dimension(w-2, 0), Dimension(h-3, 0))));

			bottomHighlightInstruction.Draw(g, window->GetSize());
			borderInstruction.Draw(g, window->GetSize());

			backgroundColorInstruction.Draw(g, window->GetSize());

			if (static_cast<StyledCheckBox*>(window)->IsChecked()) {
				checkedBackgroundInstruction.Draw(g, window->GetSize());
			}
		}

		void DrawText(StyledWindow *window, wxGraphicsContext *g) const {
			int fontFlags = wxFONTFLAG_DEFAULT;

			if (window->GetFont().GetWeight() == wxFONTWEIGHT_BOLD) {
				fontFlags = fontFlags | wxFONTFLAG_BOLD;
			}

			g->SetFont(g->CreateFont(11, "Tahoma", fontFlags, window->GetForegroundColour()));
			g->DrawText(window->GetText(), 16, 0);
		}

	};

	Style StyledCheckBox::GetDefaultStyle() {
		return StyledWindow::GetDefaultStyle();
	}

	StyledCheckBox::StyledCheckBox(wxWindow *parent, wxString text) : 
		StyledWindow(parent, text), pimpl(new Implementation)
	{ 
		Init(); 
	}

	void StyledCheckBox::Init() {
		SetRenderer(std::shared_ptr<DefaultCheckBoxRenderer>(new DefaultCheckBoxRenderer()));
		SetStyle(StyledCheckBox::GetDefaultStyle());

		SetMinSize(wxSize(DEFAULT_MIN_WIDTH, 14));
		SetOpaque(false);
		pimpl->checked = false;
	}

	void StyledCheckBox::SetChecked(bool checked) {
		pimpl->checked = checked;
	}

	bool StyledCheckBox::IsChecked() {
		return pimpl->checked;
	}

	void StyledCheckBox::ToggleChecked() {
		pimpl->checked = ! pimpl->checked;
	}

	void StyledCheckBox::OnMouseDown(wxMouseEvent& mouseEvent) {
		ToggleChecked();
	}

	void StyledCheckBox::OnMouseDoubleClick(wxMouseEvent& mouseEvent) {
		OnMouseDown(mouseEvent);
	}
} // namespace wxstyle