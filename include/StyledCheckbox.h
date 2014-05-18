#pragma once

#include <memory>

#include "StyledWindow.h"

namespace wxstyle {

    class StyledCheckBox : public StyledWindow {
    public:
        StyledCheckBox(wxWindow* parent, wxString text);

        void SetChecked(bool checked);
        bool IsChecked();
        void ToggleChecked();

    protected:
        void OnMouseDown(wxMouseEvent& mouseEvent) override;
        void OnMouseDoubleClick(wxMouseEvent& mouseEvent) override;

    private:
        void Init();

    private:
		class Implementation;
        std::unique_ptr<Implementation> pimpl;
    };

} // namespace wxstyle