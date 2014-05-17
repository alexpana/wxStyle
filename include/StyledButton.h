#pragma once

#include <memory>
#include <wx/window.h>

#include "StyledWindow.h"

namespace wxstyle {

    class StyledButton : public StyledWindow {
    public:
        StyledButton();
        StyledButton(wxWindow* parent, wxString text);
        virtual ~StyledButton();

        bool IsArmed();

    protected:
        void OnMouseDown(wxMouseEvent& mouseEvent) override;
        void OnMouseDoubleClick(wxMouseEvent& mouseEvent) override;
        void OnMouseReleased(wxMouseEvent& mouseEvent) override;

        void OnMouseMoved(wxMouseEvent& mouseEvent) override;
        void OnMouseLeaveWindow(wxMouseEvent& mouseEvent) override;
        void OnMouseEnterWindow(wxMouseEvent& mouseEvent) override;

    private:
        void ClearBackground(wxGraphicsContext *g);
        void SendClickEvent();

    private:
		struct StyledButtonImpl;
		std::unique_ptr<StyledButtonImpl> pimpl;
    };

} // namespace wxstyle