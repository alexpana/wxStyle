#include "style/draw/ImageRepository.h"

#include <wx/filename.h>

namespace wxstyle {

    ImageRepository* ImageRepository::INSTANCE = nullptr;

    ImageRepository* ImageRepository::GetInstance() {
        if (INSTANCE == nullptr) {
            INSTANCE = new ImageRepository();
            INSTANCE->SetRepositoryPath(wxGetCwd());
        }

        return INSTANCE;
    }

    void ImageRepository::ReleaseInstance() {
        if (INSTANCE != nullptr) {
            delete INSTANCE;
            INSTANCE = nullptr;
        }
    }

    ImageRepository::ImageRepository() {
    }

    std::shared_ptr<wxImage> ImageRepository::GetImage(const wxString& imageName) {
        auto it = m_imageMap.find(imageName);
        if (it != m_imageMap.end()) {
            return it->second;
        }

        bool imageFound = LoadImage(imageName);
        if (imageFound) {
            return GetImage(imageName);
        } else {
            // Report missing image
            return nullptr;
        }
    }

    bool ImageRepository::LoadImage(const wxString& imageName) {
        wxString filePath = m_repositoryPath + wxFileName::GetPathSeparator() + imageName;

        if (wxFileName::FileExists(filePath)) {

            wxImage* image = new wxImage(filePath);
            if (image != nullptr && image->IsOk()) {
                m_imageMap[imageName] = std::shared_ptr<wxImage>(image);
            } else {
                return false;
            }

        } else {
            return false;
        }

        return true;
    }

    wxString ImageRepository::GetRepositoryPath() {
        return m_repositoryPath;
    }

    void ImageRepository::SetRepositoryPath(const wxString& path) {
        m_repositoryPath = path;
    }

} // namespace wxstyle