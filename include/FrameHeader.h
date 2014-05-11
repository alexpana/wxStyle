#pragma once

#include "StyledWindow.h"

namespace wxstyle {

    class DragHandler;
    class StyledLabel;

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

        virtual void SetTitle(const wxString& title);

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