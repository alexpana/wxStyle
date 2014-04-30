#pragma once

#include "StyledWindow.h"
#include "StyledLabel.h"

#include <wx/panel.h>
#include <wx/stattext.h>

namespace wxstyle {

    class DragHandler;

    class FrameHeader : public StyledWindow {
    public:
        static wxByte ACTION_CLOSE;
        static wxByte ACTION_MINIMIZE;
        static wxByte ACTION_MAXIMIZE;

        FrameHeader(wxWindow *parent, wxWindow *topLevelWindow) : StyledWindow(parent) {
            Init(parent, topLevelWindow);
        }
        virtual ~FrameHeader() {}

        virtual void SetIcon() {}

        virtual void SetTitle(const wxString& title) {
            m_title = title;
            m_titleLabel->SetLabel(m_title);
        }

        virtual wxString GetTitle() {
            return m_title;
        }

        virtual void SetActions(int actionsMask) {
            m_actionsMask = actionsMask;
        }

        virtual int GetActions() {
            return m_actionsMask;
        }

    protected:
        void OnPaint(wxPaintEvent& paintEvent) override;

    private:
        void Init(wxWindow* parent, wxWindow *topLevelWindow);

    private:
        wxString m_title;
        int m_actionsMask;

        StyledLabel *m_titleLabel;

        DragHandler *m_dragHandler;
    };

} // namespace wxstyle