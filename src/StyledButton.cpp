#include "StyledButton.h"

#include <memory>

#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/font.h>

#include "Dimension.h"
#include "DimPoint.h"
#include "DimRect.h"
#include "style/draw/DrawImageInstruction.h"
#include "style/draw/DrawEllipseInstruction.h"
#include "style/draw/DrawRectangleInstruction.h"
#include "style/draw/DrawTextInstruction.h"

namespace wxstyle {

	struct StyledButton::StyledButtonImpl {
	public:
		bool isArmed;

		StyledButtonImpl() : isArmed(false) {}
	};

	class DefaultButtonRenderer : public IRenderer {

    public:
		virtual void Render(StyledWindow* window) const {
            RenderPhotoshopImpl(window);
        }

    private:
        void RenderPhotoshopImpl(StyledWindow* window) const {
            static const int radius = 0;
            static const wxColour borderColor = "#2c2c2c";
            static const wxColour bottomHighlight = "#46474B";
            static const wxColour topHighlight = "#606268";
            static const wxColour pressedColor = "#35363A";

            const int w = window->GetSize().GetWidth();
            const int h = window->GetSize().GetHeight();

            wxAutoBufferedPaintDC deviceContext(window);
            auto g = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(deviceContext));

            ClearBackground(g.get(), window);

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

            DrawTextInstruction drawTextInstruction(DrawTextInstruction::Params()
                .SetText(window->GetText())
                .SetFontDefinition((FontDefinition().SetSize(10).SetFace("Tahoma")))
                .SetTextColor("#BABCC0")
                .SetShadowDefinition(ShadowDefinition().SetColor("#434343").SetOffset(wxPoint(0, -1)))
                .SetTextPosition(DimPoint(Dimension(0, 0.5), Dimension(-2, 0.5))));

            bottomHighlightInstruction.Draw(g.get(), window->GetSize());
            borderInstruction.Draw(g.get(), window->GetSize());

            if (window->IsPressed() && window->IsHovered()) {
                pressedBackgroundInstruction.Draw(g.get(), window->GetSize());
            } else {
                topHighlightInstruction.Draw(g.get(), window->GetSize());
                backgroundColorInstruction.Draw(g.get(), window->GetSize());
            }

            drawTextInstruction.Draw(g.get(), window->GetSize());
        }

        void RenderGradientImpl(StyledWindow* window) const {
			StyledButton* button = (StyledButton*) window;

			if (button->GetStyle()->drawInstructions) {
				// draw using the instructions
			} else {
				// draw using the default style
			}
            static const int radius = 0;
            static const wxColor bottomHighlight = "#454545";
            static const wxColor borderColor = "#1c1617";
            static const wxColor startColor = "#302D2D";
            static const wxColor endColor = "#404040";
            static const wxColor highlight = "#a5D5B5B";

            const int w = window->GetSize().GetWidth();
            const int h = window->GetSize().GetHeight();

            wxAutoBufferedPaintDC deviceContext(window);
			auto g = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(deviceContext));

			ClearBackground(g.get(), window);

			// bottom highlight
            DrawRectangleInstruction(DrawShapeInstruction::Params()
                .SetColor(bottomHighlight)
                .SetRect(DimRect(0, 0, Dimension(0, 1.0), Dimension(0, 1.0))))
                .Draw(g.get(), window->GetSize());

			// border
            DrawRectangleInstruction(DrawShapeInstruction::Params()
                .SetColor(borderColor)
                .SetRect(DimRect(0, 0, Dimension(0, 1.0), Dimension(-1, 1.0))))
            .Draw(g.get(), window->GetSize());

			// top highlight
            DrawRectangleInstruction(DrawShapeInstruction::Params()
                .SetColor(highlight)
                .SetRect(DimRect(1, 1, Dimension(-2, 1.0), Dimension(-2, 1.0))))
                .Draw(g.get(), window->GetSize());

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
            .Draw(g.get(), window->GetSize());

            DrawTextInstruction(DrawTextInstruction::Params()
                .SetText(window->GetText())
                .SetFontDefinition((FontDefinition().SetSize(10).SetFace("Tahoma").SetWeight(wxFONTWEIGHT_BOLD)))
                .SetTextColor("#AAAAAA")
                .SetShadowDefinition(ShadowDefinition().SetColor("#161616").SetOffset(wxPoint(0, 1 )))
                .SetTextPosition(DimPoint(Dimension(0, 0.5), Dimension(-2, 0.5))))
            .Draw(g.get(), window->GetSize());
		}

		void ClearBackground(wxGraphicsContext *g, StyledWindow *window) const {
            DrawRectangleInstruction(DrawShapeInstruction::Params()
                .SetColor(window->GetBackgroundColour())
                .SetRect(DimRect(0, 0, Dimension(0, 1.0), Dimension(0, 1.0))))
            .Draw(g, window->GetSize());
		}
	};

	StyledButton::StyledButton() : StyledWindow(nullptr, ""),
		pimpl(new StyledButtonImpl)
	{
	}

	StyledButton::StyledButton(wxWindow* parent, wxString text) : StyledWindow(parent, text),
		pimpl(new StyledButtonImpl)
	{
		SetBackgroundColour(parent->GetBackgroundColour());
		SetMinSize(wxSize(10, 26));

		SetRenderer(std::make_shared<DefaultButtonRenderer>());
	}
	
	StyledButton::~StyledButton() {
	}
	
	bool StyledButton::IsArmed() {
		return pimpl->isArmed;
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

	void StyledButton::ClearBackground(wxGraphicsContext *g) {
		wxRect clientRect = GetClientRect();

		g->SetBrush(g->CreateBrush(GetBackgroundColour()));
		g->DrawRectangle(clientRect.GetX(), clientRect.GetY(), clientRect.GetWidth(), clientRect.GetHeight());
	}

	void StyledButton::OnMouseMoved(wxMouseEvent& mouseEvent) {
		if (mouseEvent.ButtonDown(wxMOUSE_BTN_LEFT)) {
			pimpl->isArmed = true;
		}
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

	void StyledButton::OnMouseDoubleClick(wxMouseEvent& mouseEvent) {
		OnMouseDown(mouseEvent);
	}

} // namespace wxstyle