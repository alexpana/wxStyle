#include "style/draw/DrawImageInstruction.h"

#include <wx/bitmap.h>

namespace wxstyle {

    typedef DrawImageInstruction::Builder Builder;

    Builder::Builder() {}
    Builder::Builder(const wxString& imagePath, const DimPoint& position) :
        m_imagePath(imagePath), m_position(position)
    {}

    Builder& Builder::SetImagePath(const wxString& imagePath) {
        m_imagePath = imagePath;
        return *this;
    }

    Builder& Builder::SetPosition(const DimPoint& position) {
        m_position = position;
        return *this;
    }

    DrawImageInstruction Builder::Build() {
        return DrawImageInstruction(m_imagePath, m_position);
    }


    DrawImageInstruction::DrawImageInstruction(const wxString& imagePath, const DimPoint& position) :
        m_imagePath(imagePath), m_position(position)
    {}

    void DrawImageInstruction::Draw(wxGraphicsContext* g, const wxSize& windowSize) const {
    }

} // namespace wxstyle