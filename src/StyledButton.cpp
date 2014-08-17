#include "StyledButton.h"

#include <algorithm>
#include <memory>

#include <wx/dcbuffer.h>
#include <wx/font.h>
#include <wx/graphics.h>
#include <wx/icon.h>

#include "Dimension.h"
#include "DimPoint.h"
#include "DimRect.h"
#include "FontMetrics.h"
#include "Insets.h"
#include "style/draw/DrawImageInstruction.h"
#include "style/draw/DrawEllipseInstruction.h"
#include "style/draw/DrawRectangleInstruction.h"
#include "style/draw/DrawTextInstruction.h"
#include "wx/dcclient.h"

namespace wxstyle {

	struct StyledButton::StyledButtonImpl {
	public:
		bool isArmed;
		std::shared_ptr<wxImage> icon;
		StyledButtonImpl() : isArmed(false) {}
	};

	class DefaultButtonRenderer : public IRenderer {
	public:
		virtual void Render(StyledWindow* window) const {
			StyledButton* button = (StyledButton*) window;

			wxAutoBufferedPaintDC deviceContext(button);
			auto g = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(deviceContext));

			ClearBackground(g.get(), button);

			RenderBackground(g.get(), button);

			RenderIcon(g.get(), button);

			RenderText(g.get(), button);
		}

	private:
		void RenderBackground(wxGraphicsContext *g, StyledButton *button) const {
			RenderPhotoshopImpl(g, button);
		}

		void RenderIcon(wxGraphicsContext* g, StyledButton *button) const {
			auto icon = button->GetIcon();

			if (icon) {
				wxRect textSize = button->GetTextMetrics();

				DrawImageInstruction(DrawImageInstruction::Params()
					.SetImage(icon)
					.SetImageSize(DimPoint(Dimension(0, 1), Dimension(0, 1)))
					.SetPosition(DimPoint(Dimension(- textSize.GetWidth() / 2 - 3, 0.5), Dimension(0, 0.5)))
					.SetVerticalAnchor(VA_CENTER)
					.SetHorizontalAnchor(HA_CENTER))
				.Draw(g, button->GetSize());
			}
		}

		void RenderText(wxGraphicsContext* g, StyledButton *button) const {
			int iconWidth = button->GetIcon() ? button->GetIcon()->GetWidth() : 0;

			DrawTextInstruction(DrawTextInstruction::Params()
				.SetText(button->GetText())
				.SetFontDefinition(FontDefinition().SetSize(10).SetFace("Tahoma").SetWeight(wxFONTWEIGHT_BOLD))
				.SetTextColor("#BABCC0")
				.SetShadowDefinition(ShadowDefinition().SetColor("#323232").SetOffset(wxPoint(0, 1)))
				.SetTextPosition(DimPoint(Dimension( iconWidth / 2 + 3, 0.5), Dimension(-2, 0.5))))
				.Draw(g, button->GetSize());
		}

		void RenderPhotoshopImpl(wxGraphicsContext *g, StyledButton *button) const {
			static const int radius = 0;
			static const wxColour borderColor = "#2c2c2c";
			static const wxColour bottomHighlight = "#46474B";
			static const wxColour topHighlight = "#606268";
			static const wxColour pressedColor = "#35363A";

			const int w = button->GetSize().GetWidth();
			const int h = button->GetSize().GetHeight();

			DrawRectangleInstruction bottomHighlightInstruction(DrawShapeInstruction::Params()
				.SetColor(bottomHighlight)
				.SetCornerRadius(radius)
				.SetRect(DimRect(0, 0, Dimension(0, 1.0), Dimension(0, 1.0))));

			DrawRectangleInstruction borderInstruction = DrawRectangleInstruction(DrawShapeInstruction::Params()
				.SetColor(borderColor)
				.SetCornerRadius(radius)
				.SetRect(DimRect(0, 0, Dimension(0, 1.0), Dimension(-1, 1.0))));

			DrawRectangleInstruction topHighlightInstruction = DrawRectangleInstruction(DrawShapeInstruction::Params()
				.SetColor(topHighlight)
				.SetCornerRadius(radius)
				.SetRect(DimRect(1, 1, Dimension(-2, 1.0), Dimension(-3, 1.0))));

			GradientDefinitionPtr gradient = std::make_shared<LinearGradientDefinition>(LinearGradientDefinition::Direction::VERTICAL);
			gradient->AddColorStop(0, "#505156");
			gradient->AddColorStop(1, "#404146");

			DrawRectangleInstruction backgroundColorInstruction(DrawShapeInstruction::Params()
				.SetGradientDefinition(gradient)
				.SetCornerRadius(radius)
				.SetRect(DimRect(1, 2, Dimension(-2, 1.0), Dimension(-4, 1.0))));

			DrawRectangleInstruction pressedBackgroundInstruction(DrawShapeInstruction::Params()
				.SetColor(pressedColor)
				.SetCornerRadius(radius)
				.SetRect(DimRect(1, 1, Dimension(-2, 1.0), Dimension(-3, 1.0))));

			bottomHighlightInstruction.Draw(g, button->GetSize());
			borderInstruction.Draw(g, button->GetSize());

			if (button->IsArmed() && button->IsHovered()) {
				pressedBackgroundInstruction.Draw(g, button->GetSize());
			} else {
				topHighlightInstruction.Draw(g, button->GetSize());
				backgroundColorInstruction.Draw(g, button->GetSize());
			}
		}

		void RenderGradientImpl(StyledButton *button) const {
			static const int radius = 0;
			static const wxColor bottomHighlight = "#454545";
			static const wxColor borderColor = "#1c1617";
			static const wxColor startColor = "#302D2D";
			static const wxColor endColor = "#404040";
			static const wxColor highlight = "#a5D5B5B";

			const int w = button->GetSize().GetWidth();
			const int h = button->GetSize().GetHeight();

			wxAutoBufferedPaintDC deviceContext(button);
			auto g = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(deviceContext));

			ClearBackground(g.get(), button);

			// bottom highlight
			DrawRectangleInstruction(DrawShapeInstruction::Params()
				.SetColor(bottomHighlight)
				.SetRect(DimRect(0, 0, Dimension(0, 1.0), Dimension(0, 1.0))))
				.Draw(g.get(), button->GetSize());

			// border
			DrawRectangleInstruction(DrawShapeInstruction::Params()
				.SetColor(borderColor)
				.SetRect(DimRect(0, 0, Dimension(0, 1.0), Dimension(-1, 1.0))))
			.Draw(g.get(), button->GetSize());

			// top highlight
			DrawRectangleInstruction(DrawShapeInstruction::Params()
				.SetColor(highlight)
				.SetRect(DimRect(1, 1, Dimension(-2, 1.0), Dimension(-2, 1.0))))
				.Draw(g.get(), button->GetSize());

			GradientDefinitionPtr gradient = std::make_shared<LinearGradientDefinition>(LinearGradientDefinition::Direction::VERTICAL);
			if (button->IsArmed()) {
				gradient->AddColorStop(1, startColor);
				gradient->AddColorStop(0.9f, endColor);
				gradient->AddColorStop(0, endColor);
			} else {
				gradient->AddColorStop(0, startColor);
				gradient->AddColorStop(0.1f, endColor);
				gradient->AddColorStop(1, endColor);
			}

			DrawRectangleInstruction(DrawShapeInstruction::Params()
				.SetGradientDefinition(gradient)
				.SetRect(DimRect(1, 1, Dimension(-2, 1.0), Dimension(-3, 1.0))))
			.Draw(g.get(), button->GetSize());
		}

		void ClearBackground(wxGraphicsContext *g, StyledWindow *window) const {
			DrawRectangleInstruction(DrawShapeInstruction::Params()
				.SetColor(window->GetBackgroundColour())
				.SetRect(DimRect(0, 0, Dimension(0, 1.0), Dimension(0, 1.0))))
			.Draw(g, window->GetSize());
		}
	};

	Style StyledButton::GetDefaultStyle() {
		DefinitionBundle defaultBundle = StyledWindow::GetDefaultStyle().GetBundle(Style::CAT_DEFAULT);
		defaultBundle.SetOpacity(false);
		return Style().AddBundle(Style::CAT_DEFAULT, defaultBundle);
	}

	StyledButton::StyledButton(wxWindow* parent, wxString text) : StyledWindow(parent, text),
		pimpl(new StyledButtonImpl)
	{
		SetRenderer(std::make_shared<DefaultButtonRenderer>());
		SetStyle(StyledButton::GetDefaultStyle());
	}
	
	StyledButton::~StyledButton() {
	}
	
	const std::shared_ptr<wxImage> StyledButton::GetIcon() const {
		return pimpl->icon;
	}

	void StyledButton::SetIcon(const std::shared_ptr<wxImage> icon) {
		pimpl->icon = icon;
	}

	bool StyledButton::IsArmed() {
		return pimpl->isArmed;
	}

	wxSize StyledButton::GetMinSize() const {
		int width = 0;
		int height = 0;

		int iconWidth = 0;
		int iconHeight = 0;
		if (GetIcon()) {
			iconWidth = GetIcon()->GetWidth();
			iconHeight = GetIcon()->GetHeight();
		}

		TextMetrics textMetrics(const_cast<StyledButton*>(this));
		wxSize textSize;

		textSize = textMetrics.GetTextSize(GetText(), GetDefinitionBundle().GetFont());

		width += GetInsets().Width();
		width += iconWidth;
		width += GetTextMetrics().GetWidth();

		height += GetInsets().Height();
		height += std::max(iconHeight, GetTextMetrics().GetHeight());

		wxSize userMinSize = StyledWindow::GetMinSize();
		return wxSize(std::max(width, userMinSize.GetWidth()), std::max(height, userMinSize.GetHeight()));
	}

	wxSize StyledButton::GetTextMetrics() const {
		wxWindowDC dc(const_cast<StyledButton*>(this));

		wxFont font(FontDefinition().SetSize(10).SetFace("Tahoma").SetWeight(wxFONTWEIGHT_BOLD).CreateFontInfo());
		
		int width, height;
		wxString text = GetText();
		dc.GetTextExtent(text, &width, &height, 0, 0, &font);

		return wxSize(width, height);
	}

	void StyledButton::OnMouseDown(wxMouseEvent& mouseEvent) {
		pimpl->isArmed = true;
		Refresh();
	}

	void StyledButton::OnMouseReleased(wxMouseEvent& mouseEvent) {
		if (IsArmed()) {
			SendClickEvent();
		}

		pimpl->isArmed = false;
		Refresh();
	}

	void StyledButton::OnMouseDoubleClick(wxMouseEvent& mouseEvent) {
		OnMouseDown(mouseEvent);
	}

	void StyledButton::OnMouseLeaveWindow(wxMouseEvent& mouseEvent) {
		pimpl->isArmed = false;
		Refresh();
	}

	void StyledButton::OnMouseEnterWindow(wxMouseEvent& mouseEvent) {
		if (mouseEvent.ButtonIsDown(wxMOUSE_BTN_LEFT)) {
			pimpl->isArmed = true;
		}
		Refresh();
	}

	void StyledButton::SendClickEvent() {
		wxCommandEvent event(wxEVT_BUTTON, GetId());
		event.SetEventObject(this);
		ProcessWindowEvent(event);
	}

} // namespace wxstyle