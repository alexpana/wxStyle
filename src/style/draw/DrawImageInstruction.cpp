#include "style/draw/DrawImageInstruction.h"

#include <wx/bitmap.h>
#include <wx/graphics.h>

#include "style/draw/ImageRepository.h"

namespace wxstyle {

    typedef DrawImageInstruction::Builder Builder;

    Builder::Builder() : 
        m_imagePath(""), m_position(DimPoint(0, 0)), m_horizontalAnchor(HA_CENTER), m_verticalAnchor(VA_CENTER), m_imageSize(DimPoint(Dimension(0, 1), Dimension(0, 1)))
    {}

    Builder::Builder(const wxString& imagePath, const DimPoint& position, HorizontalAnchor horizontalAnchor, VerticalAnchor verticalAnchor, const DimPoint& size) :
        m_imagePath(imagePath), m_position(position), m_horizontalAnchor(horizontalAnchor), m_verticalAnchor(verticalAnchor), m_imageSize(size)
    {}

    Builder& Builder::SetImagePath(const wxString& imagePath) {
        m_imagePath = imagePath;
        return *this;
    }

    Builder& Builder::SetPosition(const DimPoint& position) {
        m_position = position;
        return *this;
    }

    Builder& Builder::SetHorizontalAnchor(HorizontalAnchor horizontalAnchor) {
        m_horizontalAnchor = horizontalAnchor;
        return *this;
    }

    Builder& Builder::SetVerticalAnchor(VerticalAnchor verticalAnchor) {
        m_verticalAnchor = verticalAnchor;
        return *this;
    }

    Builder& Builder::SetImageSize(const DimPoint& size) {
        m_imageSize = size;
        return *this;
    }

    DrawImageInstruction Builder::Build() {
        return DrawImageInstruction(m_imagePath, m_position, m_horizontalAnchor, m_verticalAnchor, m_imageSize);
    }


    DrawImageInstruction::DrawImageInstruction(const wxString& imagePath, const DimPoint& position, HorizontalAnchor horizontalAnchor, VerticalAnchor verticalAnchor, const DimPoint& size) :
        m_imagePath(imagePath), m_position(position), m_horizontalAnchor(horizontalAnchor), m_verticalAnchor(verticalAnchor), m_imageSize(size)
    {}

    void DrawImageInstruction::Draw(wxGraphicsContext* g, const wxSize& windowSize) const {

        wxImage *image = ImageRepository::GetInstance()->GetImage(m_imagePath);

        if (image == nullptr) {
            return;
        }

        wxBitmap bitmap = wxBitmap(*image);


        wxPoint imagePosition(m_position.GetValue(windowSize).GetWidth(), m_position.GetValue(windowSize).GetHeight());
        wxSize imageSize(m_imageSize.GetValue(image->GetSize()));

        wxPoint offset = ComputeOffset(imageSize, m_horizontalAnchor, m_verticalAnchor);

        g->DrawBitmap(bitmap, imagePosition.x + offset.x, imagePosition.y + offset.y, imageSize.GetWidth(), imageSize.GetHeight());
    }

} // namespace wxstyle