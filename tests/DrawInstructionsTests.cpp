#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/optional/optional.hpp>

#include <wx/pen.h>

#include "DimPoint.h"
#include "DimRect.h"

#include "style/draw/DrawRectangleInstruction.h"
#include "style/draw/DrawImageInstruction.h"

BOOST_AUTO_TEST_SUITE(draw_instructions_suite)

using namespace wxstyle;
using namespace std;

BOOST_AUTO_TEST_CASE(draw_rectangle) {

BOOST_AUTO_TEST_CASE(draw_image) {
    DrawImageInstruction drawImageInstruction1 = DrawImageInstruction::NewBuilder().SetImagePath("test_image").SetPosition(DimPoint(1, 2)).Build();
    
    BOOST_CHECK_EQUAL(drawImageInstruction1.GetImagePath(), "test_image");
    BOOST_CHECK_EQUAL(drawImageInstruction1.GetPosition(), DimPoint(1, 2));

    DrawImageInstruction drawImageInstruction2 = drawImageInstruction1.ToBuilder().SetImagePath("another_image").Build();

    BOOST_CHECK_EQUAL(drawImageInstruction2.GetImagePath(), "another_image");
    BOOST_CHECK_EQUAL(drawImageInstruction2.GetPosition(), DimPoint(1, 2));
}

BOOST_AUTO_TEST_SUITE_END()