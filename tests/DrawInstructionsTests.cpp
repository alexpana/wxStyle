#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/optional/optional.hpp>

#include "style/DrawInstruction.h"

BOOST_AUTO_TEST_SUITE(draw_instructions_suite)

using namespace wxstyle;
using namespace std;

BOOST_AUTO_TEST_CASE(draw_rectangle) {
	DrawRectangleInstruction instr = DrawRectangleInstruction::NewBuilder()
		->SetRect(DimRect(0, 0, 10, 10))
		->SetPenStyle(wxPENSTYLE_SOLID)
		->SetPenSize(1)
		->Build();

	BOOST_CHECK_EQUAL(instr, DrawRectangleInstruction(DimRect(0, 0, 10, 10), "#000000", 1, "#000000", wxPENSTYLE_SOLID));
}

BOOST_AUTO_TEST_SUITE_END()