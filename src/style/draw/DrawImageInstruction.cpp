#include "style/draw/DrawImageInstruction.h"

#include <boost/optional.hpp>

#include <wx/bitmap.h>
#include <wx/graphics.h>
#include <wx/string.h>

#include "DimPoint.h"
#include "DiMRect.h"
#include "style/draw/ImageRepository.h"

namespace wxstyle {

    typedef DrawImageInstruction::Params Params;

    struct Params::ParamsImpl {
        wxString imagePath;
        DimPoint position;
        DimPoint imageSize;
        HorizontalAnchor horizontalAnchor;
        VerticalAnchor verticalAnchor;
        boost::optional<std::shared_ptr<wxImage>> image;
    };

    Params::Params() {
        impl = std::make_shared<ParamsImpl>();
        impl->horizontalAnchor = HA_CENTER;
        impl->verticalAnchor = VA_CENTER;
    }

    Params& Params::SetImagePath(const wxString& imagePath) {
        impl->imagePath = imagePath;
        return *this;
    }

    Params& Params::SetPosition(const DimPoint& position) {
        impl->position = position;
        return *this;
    }

    Params& Params::SetHorizontalAnchor(HorizontalAnchor horizontalAnchor) {
        impl->horizontalAnchor = horizontalAnchor;
        return *this;
    }

    Params& Params::SetVerticalAnchor(VerticalAnchor verticalAnchor) {
        impl->verticalAnchor = verticalAnchor;
        return *this;
    }

    Params& Params::SetImageSize(const DimPoint& size) {
        impl->imageSize = size;
        return *this;
    }

    Params& Params::SetImage(const std::shared_ptr<wxImage>& image) {
        impl->image = image;
        return *this;
    }

    wxString Params::GetImagePath() const {
        return impl->imagePath;
    }

    DimPoint Params::GetPosition() const {
        return impl->position;
    }

    HorizontalAnchor Params::GetHorizontalAnchor() const {
        return impl->horizontalAnchor;
    }

    VerticalAnchor Params::GetVerticalAnchor() const {
        return impl->verticalAnchor;
    }

    DimPoint Params::GetImageSize() const {
        return impl->imageSize;
    }

    bool Params::HasImage() const {
        return impl->image;
    }

    std::shared_ptr<wxImage> Params::GetImage() const {
        return impl->image.get();
    }

    DrawImageInstruction::DrawImageInstruction(const Params& params) : parameters(params) {}

    Params DrawImageInstruction::GetParams() const {
        return parameters;
    }

    void DrawImageInstruction::Draw(wxGraphicsContext* g, const wxSize& windowSize) const {

        wxImage *image;

        if (GetParams().HasImage()) {
            image = GetParams().GetImage().get();
        } else {
            image = ImageRepository::GetInstance()->GetImage(GetParams().GetImagePath()).get();
        }

        if (image == nullptr) {
            return;
        }

        wxBitmap bitmap = wxBitmap(*image);

        DimPoint position = GetParams().GetPosition();
        DimPoint imageSize = GetParams().GetImageSize();

        wxPoint imagePosition(position.GetValue(windowSize).GetWidth(), position.GetValue(windowSize).GetHeight());
        wxSize finalImageSize(imageSize.GetValue(image->GetSize()));

        wxPoint offset = ComputeOffset(finalImageSize, GetParams().GetHorizontalAnchor(), GetParams().GetVerticalAnchor());

        g->DrawBitmap(bitmap, imagePosition.x + offset.x, imagePosition.y + offset.y, finalImageSize.GetWidth(), finalImageSize.GetHeight());
    }

} // namespace wxstyle