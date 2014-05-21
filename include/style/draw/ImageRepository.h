#pragma once

#include <memory>
#include <unordered_map>

#include <wx/image.h>

namespace wxstyle {

    class ImageRepository {
    public:
        static ImageRepository* GetInstance();

        static void ReleaseInstance();

        std::shared_ptr<wxImage> GetImage(const wxString& imageName);

        wxString GetRepositoryPath();

        void SetRepositoryPath(const wxString& path);

    private:
        static ImageRepository* INSTANCE;

    private:
        ImageRepository();

        bool LoadImage(const wxString& image);

    private:
        /** Hash function for wxString objects. **/
        struct wxStringHash {
        public:
            std::size_t operator()(const wxString& s) {
                return std::hash<std::string>()(std::string(s.data()));
            }
        };

    private:
        wxString m_repositoryPath;
        std::unordered_map<wxString, std::shared_ptr<wxImage>, wxStringHash> m_imageMap;
    };

} // namespace wxstyle