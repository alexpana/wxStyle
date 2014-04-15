#include "wx/app.h"
#include "wx/button.h"
#include "wx/combobox.h"
#include "wx/checkbox.h"
#include "wx/dcclient.h"
#include "wx/event.h"
#include "wx/frame.h"
#include "wx/graphics.h"
#include "wx/panel.h"
#include "wx/sizer.h"
#include "wx/stattext.h"
#include "wx/sysopt.h"
#include "wx/textctrl.h"

#include "StyledButton.h"
#include "StyledFrame.h"
#include "StyledLabel.h"
#include "Dimension.h"

#include <functional>
#include <debugapi.h>
#include <string>

using namespace wxstyle;

class DemoApp : public wxApp {
public:

    bool OnInit() override {
        // call base class method to ensure the program arguments are processed
        wxApp::OnInit();

        InitComponents();
        InitLayout();

        return true;
    }

    void InitComponents() 
    {
        mainFrame = new StyledFrame();

        mainFrame->Show(true);
        mainFrame->SetMinSize(wxSize(200, 200));

        contentPanel = mainFrame->GetContentPanel();

        label = new StyledLabel(contentPanel);
        label->SetLabel("Hello World!");
        label->SetForegroundColour("#AFAFAF");

        staticText = new wxStaticText(contentPanel, wxID_ANY, "");
        staticText->SetLabelText("Hello World!");
        staticText->SetForegroundColour("#AFAFAF");

        button = new wxButton(contentPanel, wxID_ANY, "Click me!");

        styledButton = new wxstyle::StyledButton(contentPanel, "Styled");

        checkBox = new wxCheckBox(contentPanel, wxID_ANY, "Check me!");

        textArea = new wxTextCtrl(contentPanel, wxID_ANY);

        comboBox = new wxComboBox(contentPanel, wxID_ANY);
        wxString items[4] = {"luffy", "sanji", "zoro", "nami"};
        comboBox->Set(wxArrayString(4, items));

        sizer = new wxBoxSizer(wxVERTICAL);

// 		boost::optional<Dimension> dim1 = Dimension::ValueOf("10");
// 		boost::optional<Dimension> dim2 = Dimension::ValueOf("10%+32");
// 		boost::optional<Dimension> dim3 = Dimension::ValueOf("1%-45");
// 		boost::optional<Dimension> dim4 = Dimension::ValueOf("-10");
// 		boost::optional<Dimension> dim5 = Dimension::ValueOf("-10%");
// 		boost::optional<Dimension> dim6 = Dimension::ValueOf("23%+");
		boost::optional<Dimension> dim7 = Dimension::ValueOf("+");
		boost::optional<Dimension> dim8 = Dimension::ValueOf("-");
		if (dim8) {
			int relative = dim8->GetRelative();
		}
    }

    void InitLayout() 
    {
        wxSizerFlags flags = wxSizerFlags().Expand().Border(wxALL, 4);
        contentPanel->SetSizer(sizer, true);

        sizer->Add(label, flags);
        sizer->Add(staticText, flags);
        sizer->Add(button, flags);
        sizer->Add(styledButton, flags);
        sizer->Add(checkBox, flags);
        sizer->Add(textArea, flags);
        sizer->Add(comboBox, flags);

        mainFrame->Fit();
    }

private:
    StyledFrame* mainFrame;

    wxBoxSizer *sizer;

    wxPanel *contentPanel;

    StyledLabel *label;
    wxStaticText *staticText;

    wxButton *button;
    StyledButton *styledButton;
    wxCheckBox *checkBox;
    wxTextCtrl *textArea;
    wxComboBox *comboBox;
};

IMPLEMENT_APP(DemoApp);