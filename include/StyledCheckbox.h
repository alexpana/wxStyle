#pragma once

#include <wx/graphics.h>

#include "StyledWindow.h"

namespace wxstyle {

class StyledCheckBox : public StyledWindow {
public:
    StyledCheckBox(wxWindow* parent, wxString text) : StyledWindow(parent, text) { Init(); }
    ~StyledCheckBox() {}

    void SetChecked(bool checked) {
        m_isChecked = checked;
    }

    bool IsChecked() {
        return m_isChecked;
    }

    void ToggleChecked() {
        m_isChecked = !m_isChecked;
    }

protected:
    void OnMouseDown(wxMouseEvent& mouseEvent) override;
    void OnMouseDoubleClick(wxMouseEvent& mouseEvent) override;

private:
    void Init();

private:
    bool m_isChecked;
};

} // namespace wxstyle