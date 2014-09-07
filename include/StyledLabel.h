#pragma once

#include <StyledWindow.h>

namespace wxstyle {

    class StyledLabel : public StyledWindow {
    public:
        StyledLabel(wxWindow *parent);
        StyledLabel(wxWindow *parent, wxString label);

        ~StyledLabel() {};

        ClassInfo GetType() const override { return ClassInfo::LABEL; }

    private:
        void Init();
    };

}