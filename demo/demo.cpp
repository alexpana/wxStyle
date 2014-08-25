#include "demo.h"

#include "time.h"

using namespace wxstyle;

class DemoApp : public wxApp {
public:

    bool OnInit() override {
        wxApp::OnInit();

        DoStart();

        InitComponents();
        InitLayout();

        return true;
    }

    void DoStart() {
        wxImage::AddHandler(new wxJPEGHandler());
        wxImage::AddHandler(new wxPNGHandler());
    }

    void DoStop() {
        wxImage::CleanUpHandlers();
        ImageRepository::ReleaseInstance();
    }

    void InitComponents() 
    {
        XMLStylesheetLoader loader;
        Stylesheet stylesheet = loader.Load("test.xml");

        mainFrame = new StyledFrame("Demo Board");
        mainFrame->Show(true);
        mainFrame->SetMinSize(wxSize(200, 200));

        wxPanel *contentPanel = mainFrame->GetContentPanel();

        styledLabel = new StyledLabel(contentPanel);
        styledLabel->SetText("Styled Label");
        styledLabel->SetForegroundColour("#AFAFAF");
        styledLabel->SetStyle(stylesheet.GetStyle("label.default"));

//      styledButton = new wxstyle::StyledButton(contentPanel, "Styled Button");
// 		styledButton->SetInsets(Insets(12, 12, 12, 12));

		styledButtonWithIcon = new wxstyle::StyledButton(contentPanel, "Styled Button");
		styledButtonWithIcon->SetIcon(ImageRepository::GetInstance()->GetImage("icons/music_babcc0_16.png"));
        styledButtonWithIcon->SetInsets(Insets(12, 12, 12, 12));

        nativeLabel = new wxStaticText(contentPanel, wxID_ANY, "");
        nativeLabel->SetLabelText("Native Label");
        nativeLabel->SetForegroundColour("#AFAFAF");

        styledCheckBox = new StyledCheckBox(contentPanel, "Styled CheckBox");
        styledCheckBox->SetForegroundColour("#AFAFAF");
        styledCheckBox->SetStyle(stylesheet.GetStyle("checkbox.default"));

        styledTextBox = new StyledTextBox(contentPanel, "");

        nativeButton = new wxButton(contentPanel, wxID_ANY, "Native Button");

        nativeCheckBox = new wxCheckBox(contentPanel, wxID_ANY, "Native CheckBox");

        nativeTextField = new wxTextCtrl(contentPanel, wxID_ANY);

//         nativeComboBox = new wxComboBox(contentPanel, wxID_ANY);
//         wxString options[] = {"luffy", "sanji", "zoro", "nami"};
//         nativeComboBox->Set(wxArrayString(4, options));
    }

    void InitLayout() 
    {
        wxSizerFlags flags = wxSizerFlags().Expand().Border(wxALL, 4);

        wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        mainFrame->GetContentPanel()->SetSizer(sizer, true);

        sizer->Add(nativeLabel, flags);
        sizer->Add(styledLabel, flags);

        sizer->Add(nativeButton, flags);
        //sizer->Add(styledButton, flags);
		sizer->Add(styledButtonWithIcon, flags);

        sizer->Add(nativeCheckBox, flags);
        sizer->Add(styledCheckBox, flags);

        sizer->Add(styledTextBox, flags);
        sizer->Add(nativeTextField, flags);

        //sizer->Add(nativeComboBox, flags);

        mainFrame->Fit();
        mainFrame->SetSize(mainFrame->GetSize() + wxSize(60, 0));
    }

    int OnExit() override {
        DoStop();
        return 0;
    }

private:
    StyledFrame *mainFrame;

    StyledButton *styledButton;
    StyledButton *styledButtonWithIcon;
	StyledLabel *styledLabel;
    StyledCheckBox *styledCheckBox;
    StyledTextBox *styledTextBox;

    wxButton *nativeButton;
    wxStaticText *nativeLabel;
    wxCheckBox *nativeCheckBox;

    wxTextCtrl *nativeTextField;
    wxComboBox *nativeComboBox;
};

IMPLEMENT_APP(DemoApp);