#include "FrameHeader.h"

#include <wx/sizer.h>
#include <wx/graphics.h>

#include "DimPoint.h"
#include "DimRect.h"
#include "DragHandler.h"
#include "Renderer.h"
#include "StyledFrame.h"
#include "StyledLabel.h"
#include "style/draw/DrawImageInstruction.h"
#include "style/draw/DrawRectangleInstruction.h"
#include "style/draw/DrawTextInstruction.h"
#include "style/draw/ImageRepository.h"

namespace wxstyle {

    wxByte FrameHeader::ACTION_CLOSE = 0x01;
    wxByte FrameHeader::ACTION_MINIMIZE = 0x02;
    wxByte FrameHeader::ACTION_MAXIMIZE = 0x04;

    class TextLabelRenderer : public IRenderer {
    public:
        void Render(StyledWindow* window) const override {
            wxAutoBufferedPaintDC deviceContext(window);
            auto g = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(deviceContext));

            DrawRectangleInstruction(DrawRectangleInstruction::Params()
                .SetColor(window->GetInheritedBackgroundColor()))
            .Draw(g.get(), window->GetSize());

            DrawTextInstruction(DrawTextInstruction::Params()
                .SetFontDefinition(FontDefinition().SetSize(9).SetFace("Tahoma").SetWeight(wxFONTWEIGHT_BOLD))
                .SetText(window->GetText())
                .SetTextColor("#ACACAC")
                .SetHorizontalAnchor(HA_LEFT)
                .SetTextPosition(DimPoint(4, Dimension(0, 0.5f))))
            .Draw(g.get(), window->GetSize());
        }
    };

    class IconRenderer : public IRenderer {
    public:
        void Render(StyledWindow* window) const override {
			StyledButton *button = (StyledButton*) window;

            wxAutoBufferedPaintDC deviceContext(button);
            auto g = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(deviceContext));

            DrawRectangleInstruction(DrawRectangleInstruction::Params().SetColor(button->GetInheritedBackgroundColor()))
            .Draw(g.get(), button->GetSize());

            if (button->IsHovered() || button->IsPressed()) {
                DrawRectangleInstruction(DrawRectangleInstruction::Params()
                    .SetColor("#353538")
                    .SetRect(DimRect(1, 1, Dimension(-2, 1), Dimension(-2, 1))))
                .Draw(g.get(), button->GetSize());
            }

            if (button->IsArmed() && button->IsHovered()) {
                DrawRectangleInstruction(DrawRectangleInstruction::Params()
                    .SetColor("#007acc")
                    .SetRect(DimRect(1, 1, Dimension(-2, 1), Dimension(-2, 1))))
                .Draw(g.get(), button->GetSize());
            }

            DrawImageInstruction(DrawImageInstruction::Params()
                .SetImage(button->GetIcon())
                .SetImageSize(DimPoint(Dimension(0, 1), Dimension(0, 1)))
                .SetPosition(DimPoint(Dimension(0, 0.5), Dimension(0, 0.5)))
                .SetVerticalAnchor(VA_CENTER)
                .SetHorizontalAnchor(HA_CENTER))
                .Draw(g.get(), button->GetSize());

        }
    };

    void FrameHeader::Init(wxWindow *parent, StyledFrame *topLevelWindow) {
        wxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

        m_titleLabel = new StyledLabel(this);
        m_titleLabel->SetFont(m_titleLabel->GetFont().Bold());
        m_titleLabel->SetForegroundColour("#DADADA");
        m_titleLabel->SetRenderer(std::make_shared<TextLabelRenderer>(TextLabelRenderer()));

        m_minimizeButton = std::make_shared<StyledButton>(this, "");
        m_minimizeButton->SetMinSize(wxSize(26, 0));
        m_minimizeButton->SetRenderer(std::make_shared<IconRenderer>());
        m_minimizeButton->SetIcon(ImageRepository::GetInstance()->GetImage("icons/minimize.png"));
        m_minimizeButton->SetOpaque(false);
        m_minimizeButton->Bind(wxEVT_BUTTON, [topLevelWindow](const wxEvent& evt){ 
            topLevelWindow->Iconize(true);
        });

        m_maximizeButton = std::make_shared<StyledButton>(this, "");
        m_maximizeButton->SetMinSize(wxSize(26, 0));
        m_maximizeButton->SetRenderer(std::make_shared<IconRenderer>());
        m_maximizeButton->SetIcon(ImageRepository::GetInstance()->GetImage("icons/maximize.png"));
        m_maximizeButton->SetOpaque(false);
        m_maximizeButton->Bind(wxEVT_BUTTON, [topLevelWindow](const wxEvent& evt){ 
            topLevelWindow->Maximize(!topLevelWindow->IsMaximized());
        });

        m_closeButton = std::make_shared<StyledButton>(this, "");
        m_closeButton->SetMinSize(wxSize(26, 0));
        m_closeButton->SetRenderer(std::make_shared<IconRenderer>());
        m_closeButton->SetIcon(ImageRepository::GetInstance()->GetImage("icons/close.png"));
        m_closeButton->SetOpaque(false);
        m_closeButton->Bind(wxEVT_BUTTON, [topLevelWindow](const wxEvent& evt){ 
            topLevelWindow->Close(true);
        });

        sizer->Add(m_titleLabel, wxSizerFlags(1).Expand());

        sizer->Add(m_minimizeButton.get(), wxSizerFlags().Expand());
        sizer->Add(m_maximizeButton.get(), wxSizerFlags().Expand());
        sizer->Add(m_closeButton.get(), wxSizerFlags().Expand());

        /* Install the drag handler on the header panel */
        m_dragHandler = new DragHandler(topLevelWindow);
        m_dragHandler->Install(this);
        m_dragHandler->Install(m_titleLabel);

        SetOpaque(true);
        SetBackgroundColour("#202020");

        SetSizer(sizer);
    }

    void FrameHeader::OnPaint(wxPaintEvent& paintEvent) {
        wxAutoBufferedPaintDC dc(this);
        auto g = wxGraphicsContext::Create(dc);

        g->SetBrush(wxBrush("#202050"));
        g->DrawRectangle(0, 0, GetSize().GetWidth(), GetSize().GetHeight());
    }

    void FrameHeader::SetTitle(const wxString& title) {
        m_title = title;
        m_titleLabel->SetText(m_title);
    }

    void FrameHeader::OnResize(wxSizeEvent& resizeEvent) {
        Layout();
    }

} // namespace wxstyle