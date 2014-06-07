#pragma once

#include <wx\gdicmn.h>

namespace wxstyle {

    /**
     *  Returns the position of an object relative to a reference object based
     *  on their sizes and an alignment.
     *  The alignment is the result of using the OR operation on values of wxAlignment.
     */
    wxPoint Align(wxSize referenceSize, wxSize objectSize, int alignment);

} // namespace wxstyle