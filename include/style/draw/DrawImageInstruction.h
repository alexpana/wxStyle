#pragma once

#include <memory>

#include <wx/image.h>

#include "style/draw/Anchor.h"
#include "style/draw/DrawInstruction.h"

class wxBitmap;

namespace wxstyle {
    class DimPoint;

    class DrawImageInstruction : public DrawInstruction {
    public:
        class Params {
        public:
            Params();

            Params& SetImagePath(const wxString& imagePath);

            wxString GetImagePath() const;

            Params& SetPosition(const DimPoint& position);

            DimPoint GetPosition() const;

            Params& SetHorizontalAnchor(HorizontalAlignment horizontalAnchor);

            HorizontalAlignment GetHorizontalAnchor() const;

            Params& SetVerticalAnchor(VerticalAlignment verticalAnchor);

            VerticalAlignment GetVerticalAnchor() const;

            Params& SetImageSize(const DimPoint& size);

            DimPoint GetImageSize() const;

            Params& SetImage(const std::shared_ptr<wxImage>& image);

            bool HasImage() const;

            std::shared_ptr<wxImage> GetImage() const;

        private:
            struct ParamsImpl;
            std::shared_ptr<ParamsImpl> impl;
        };

    public:
        DrawImageInstruction(const Params& params);

        virtual void Draw(wxGraphicsContext* g, const wxSize& windowSize) const override;

        Params GetParams() const;

    private:
        Params parameters;

        // used for caching the bitmap
        //const boost::optional<wxBitmap> m_cachedBitmap;
    };
} // namespace wxstyle