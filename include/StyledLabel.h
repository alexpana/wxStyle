#pragma once

#include <StyledWindow.h>

namespace wxstyle {

    class StyledLabel : public StyledWindow {
    public:
        StyledLabel(wxWindow *parent);
        StyledLabel(wxWindow *parent, wxString label);

        ~StyledLabel() {};

        void SetTextAlignment(wxAlignment alignment) {
            m_textAlignment = alignment;
        }

        wxAlignment GetTextAlignment() const {
            return m_textAlignment;
        }

    private:
        void Init();

    private:
        wxAlignment m_textAlignment;
    };

}