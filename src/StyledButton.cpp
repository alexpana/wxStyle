#include "StyledButton.h"

#include <algorithm>
#include <memory>

#include <wx/dcbuffer.h>
#include <wx/font.h>
#include <wx/graphics.h>
#include <wx/icon.h>
#include <wx/dcclient.h>

#include "Dimension.h"
#include "DimPoint.h"
#include "DimRect.h"
#include "FontMetrics.h"
#include "Insets.h"
#include "StylesheetRenderer.h"
#include "style/draw/DrawImageInstruction.h"
#include "style/draw/DrawEllipseInstruction.h"
#include "style/draw/DrawRectangleInstruction.h"
#include "style/draw/DrawTextInstruction.h"

namespace wxstyle {

    struct StyledButton::StyledButtonImpl {
    public:
        bool isArmed;
        std::shared_ptr<wxImage> icon;
        StyledButtonImpl() : isArmed(false) {}
    };

    class DefaultButtonRenderer : public StylesheetRenderer {
    public:
        virtual void Render(StyledWindow* window) const {
            StyledButton* button = (StyledButton*) window;

            wxAutoBufferedPaintDC deviceContext(button);
            auto g = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(deviceContext));

            DrawBackground(g.get(), button);

            // Should go together into "content" maybe ?

            RenderIcon(g.get(), button);

            RenderText(g.get(), button);
        }

    private:

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

            DefinitionBundle bundle = button->GetDefinitionBundle();

            DrawTextInstruction(DrawTextInstruction::Params()
                .SetText(button->GetText())
                .SetFontDefinition(bundle.GetFont())
                .SetTextColor(bundle.GetForegroundColor())
                .SetShadowDefinition(bundle.GetTextShadow())
                .SetTextPosition(DimPoint(Dimension( iconWidth / 2 + 3, 0.5), Dimension(-2, 0.5))))
                .Draw(g, button->GetSize());
        }
    };

    Style StyledButton::GetDefaultStyle() {
        static const int radius = 0;
        static const wxColour borderColor = "#2c2c2c";
        static const wxColour bottomHighlight = "#46474B";
        static const wxColour topHighlight = "#606268";
        static const wxColour pressedColor = "#35363A";

        DefinitionBundle defaultBundle = StyledWindow::GetDefaultStyle().GetBundle(Style::CAT_DEFAULT);
        DefinitionBundle pressedBundle = StyledWindow::GetDefaultStyle().GetBundle(Style::CAT_PRESSED);

        defaultBundle
            .SetOpacity(false)
            .SetForegroundColor("#BABCC0")
            .SetFont(
                FontDefinition()
                    .SetFace("Tahoma")
                    .SetSize(10)
                    .SetWeight(wxFONTWEIGHT_BOLD))
            .SetShadow(
                ShadowDefinition()
                    .SetColor("#323232")
                    .SetOffset(wxPoint(0, 1)));

        // Draw Instructions
        auto bottomHighlightInstruction = new DrawRectangleInstruction(
            DrawShapeInstruction::Params()
                .SetColor(bottomHighlight)
                .SetCornerRadius(radius)
                .SetRect(DimRect(0, 0, Dimension(0, 1.0), Dimension(0, 1.0))));

        auto borderInstruction = new DrawRectangleInstruction(
            DrawShapeInstruction::Params()
                .SetColor(borderColor)
                .SetCornerRadius(radius)
                .SetRect(DimRect(0, 0, Dimension(0, 1.0), Dimension(-1, 1.0))));

        auto topHighlightInstruction = new DrawRectangleInstruction(
            DrawShapeInstruction::Params()
                .SetColor(topHighlight)
                .SetCornerRadius(radius)
                .SetRect(DimRect(1, 1, Dimension(-2, 1.0), Dimension(-3, 1.0))));

        GradientDefinitionPtr gradient = std::make_shared<LinearGradientDefinition>(LinearGradientDefinition::Direction::VERTICAL);
        gradient->AddColorStop(0, "#505156");
        gradient->AddColorStop(1, "#404146");

        auto backgroundColorInstruction = new DrawRectangleInstruction(
            DrawShapeInstruction::Params()
                .SetGradientDefinition(gradient)
                .SetCornerRadius(radius)
                .SetRect(DimRect(1, 2, Dimension(-2, 1.0), Dimension(-4, 1.0))));

        auto pressedBackgroundInstruction = new DrawRectangleInstruction(
            DrawShapeInstruction::Params()
                .SetColor(pressedColor)
                .SetCornerRadius(radius)
                .SetRect(DimRect(1, 1, Dimension(-2, 1.0), Dimension(-3, 1.0))));


        std::vector<DrawInstruction*> defaultDrawInstructions;
        defaultDrawInstructions.push_back(bottomHighlightInstruction);
        defaultDrawInstructions.push_back(borderInstruction);
        defaultDrawInstructions.push_back(topHighlightInstruction);
        defaultDrawInstructions.push_back(backgroundColorInstruction);

        std::vector<DrawInstruction*> pressedDrawInstructions;
        pressedDrawInstructions.push_back(bottomHighlightInstruction);
        pressedDrawInstructions.push_back(borderInstruction);
        pressedDrawInstructions.push_back(pressedBackgroundInstruction);

        defaultBundle.SetDrawInstructions(defaultDrawInstructions);
        pressedBundle.SetDrawInstructions(pressedDrawInstructions);

        return Style()
            .AddBundle(Style::CAT_DEFAULT, defaultBundle)
            .AddBundle(Style::CAT_PRESSED, pressedBundle);
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