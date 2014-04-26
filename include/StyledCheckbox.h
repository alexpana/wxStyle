#pragma once

#include "StyledWindow.h"

namespace wxstyle {

class StyledCheckBox : public StyledWindow {
public:
    StyledCheckBox(wxWindow* parent, wxString text);
    ~StyledCheckBox();

    void SetChecked(bool checked);
    bool IsChecked();
    void ToggleChecked();

protected:
    void OnMouseDown(wxMouseEvent& mouseEvent) override;
    void OnMouseDoubleClick(wxMouseEvent& mouseEvent) override;
    void OnPaint(wxPaintEvent& paintEvent) override;

private:
    wxString m_text;
    bool m_checked;
};

} // namespace wxstyle