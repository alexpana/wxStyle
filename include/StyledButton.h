#pragma once

#include <memory>
#include <wx/window.h>

#include "StyledWindow.h"

namespace wxstyle {

    class StyledButton : public StyledWindow {
    public:
        StyledButton(wxWindow* parent, wxString text);
        virtual ~StyledButton();

        bool IsArmed();

		// buttons have support for icons
		const std::shared_ptr<wxImage> GetIcon() const;
		void SetIcon(const std::shared_ptr<wxImage> icon);

		wxSize GetMinSize() const override;

		wxSize GetTextMetrics() const;

        ClassInfo GetType() const override { return ClassInfo::BUTTON; }

    protected:
        void OnMouseDown(wxMouseEvent& mouseEvent) override;
        void OnMouseDoubleClick(wxMouseEvent& mouseEvent) override;
        void OnMouseReleased(wxMouseEvent& mouseEvent) override;

        void OnMouseLeaveWindow(wxMouseEvent& mouseEvent) override;
        void OnMouseEnterWindow(wxMouseEvent& mouseEvent) override;

    private:
        void SendClickEvent();

    private:
		struct StyledButtonImpl;
		std::unique_ptr<StyledButtonImpl> pimpl;
    };

} // namespace wxstyle