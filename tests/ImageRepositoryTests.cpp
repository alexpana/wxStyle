#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/optional/optional.hpp>

#include <wx/filefn.h>
#include <wx/filename.h>

#include "style/draw/ImageRepository.h"

BOOST_AUTO_TEST_SUITE(image_repository_suite)

using namespace wxstyle;
using namespace std;

class TestFixture {
public:
    TestFixture() {
        wxImage::AddHandler(new wxJPEGHandler());

        ImageRepository *repository = ImageRepository::GetInstance();

        repository->SetRepositoryPath(wxGetCwd() + wxFileName::GetPathSeparator() + "data");
    }

    ~TestFixture() {
        ImageRepository::ReleaseInstance();
        wxImage::CleanUpHandlers();
    }
};

BOOST_AUTO_TEST_CASE(load_image) {

    TestFixture fixture;

    ImageRepository *repository = ImageRepository::GetInstance();

    wxImage *testImage = repository->GetImage("test_image.jpg");

    BOOST_REQUIRE(testImage != nullptr);
    BOOST_CHECK_EQUAL(testImage->GetWidth(), 8);
    BOOST_CHECK_EQUAL(testImage->GetHeight(), 8);
}

BOOST_AUTO_TEST_SUITE_END()