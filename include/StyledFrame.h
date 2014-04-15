#pragma once

#include <vector>

#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/sizer.h>

namespace wxstyle {

class DragHandler;
class ResizeHandler;
class FrameHeader;

class StyledFrame : public wxFrame {

public:
    StyledFrame();
    ~StyledFrame();

    /* Returns a wxPanel that represents the content area of
     * the frame. Clients must use this panel as a parent to
     * all child windows of this frame */
    wxPanel* GetContentPanel();

    /* Resizes this frame to fit its contents */
    void Fit() {
        m_frameSizer->Fit(this);
        wxSize minSize = m_frameInnerSizer->GetMinSize() + wxSize(m_borderSize * 2, m_borderSize * 2);
        SetSize(minSize);
        SetMinSize(minSize);
    }

    /* Sets the size of the border around this frame.
     * The border represents the area where the frame can be
     * stretched. */
    void SetBorderSize(int borderSize) {
        m_borderSize = borderSize;
        for (auto borderSegment : m_borderVector) {
            borderSegment->SetMinSize(wxSize(borderSize, borderSize));
        }
    }

    void SetBorderColor(wxColor borderColor) {
        m_borderColor = borderColor;
        for (auto borderSegment : m_borderVector) {
            borderSegment->SetBackgroundColour(borderColor);
        }
    }

    bool SetBackgroundColour(const wxColour &colour) override;

private:
    void Init();
    void InitBorders();

    void HighlightTopBorder() {}
    void HighlightLeftBorder() {}
    void HighlightRightBorder() {}
    void HighlightBottomBorder() {}
    void RemoveBorderHighlight() {}

private:
    wxPanel *m_framePanel;
    wxFlexGridSizer *m_frameSizer;

    wxPanel *m_frameInnerPanel;
    wxBoxSizer *m_frameInnerSizer;

    wxPanel *m_contentPanel;

    ResizeHandler *m_resizeHandler;

    /* Header panel */
    FrameHeader *m_headerPanel;

    /* Border panels */
    wxPanel *m_borderTop;
    wxPanel *m_borderRight;
    wxPanel *m_borderBottom;
    wxPanel *m_borderLeft;
    wxPanel *m_borderTopLeft;
    wxPanel *m_borderTopRight;
    wxPanel *m_borderBottomLeft;
    wxPanel *m_borderBottomRight;
    std::vector<wxPanel*> m_borderVector;

    /* Properties */
    int m_borderSize;
    wxColor m_borderColor;
};

} // namespace wxstyle