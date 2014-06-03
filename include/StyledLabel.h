#pragma once

#include <StyledWindow.h>

namespace wxstyle {

    class StyledLabel : public StyledWindow {
    public:
        StyledLabel(wxWindow *parent);
        StyledLabel(wxWindow *parent, wxString label);

        ~StyledLabel() {};

        static Style GetDefaultStyle();

    private:
        void Init();
    };

}