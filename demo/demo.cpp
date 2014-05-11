#include "demo.h"

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
        mainFrame = new StyledFrame("Demo Board");
        mainFrame->Show(true);
        mainFrame->SetMinSize(wxSize(200, 200));

        wxPanel *contentPanel = mainFrame->GetContentPanel();

        styledLabel = new StyledLabel(contentPanel);
        styledLabel->SetText("Styled Label");
        styledLabel->SetForegroundColour("#AFAFAF");

        styledButton = new wxstyle::StyledButton(contentPanel, "Styled Button");

        nativeLabel = new wxStaticText(contentPanel, wxID_ANY, "");
        nativeLabel->SetLabelText("Native Label");
        nativeLabel->SetForegroundColour("#AFAFAF");

        styledCheckBox = new StyledCheckBox(contentPanel, "Styled CheckBox");
        styledCheckBox->SetForegroundColour("#AFAFAF");

        nativeButton = new wxButton(contentPanel, wxID_ANY, "Native Button");

        nativeCheckBox = new wxCheckBox(contentPanel, wxID_ANY, "Native CheckBox");

        nativeTextField = new wxTextCtrl(contentPanel, wxID_ANY);

        nativeComboBox = new wxComboBox(contentPanel, wxID_ANY);
        wxString options[] = {"luffy", "sanji", "zoro", "nami"};
        nativeComboBox->Set(wxArrayString(4, options));
    }

    void InitLayout() 
    {
        wxSizerFlags flags = wxSizerFlags().Expand().Border(wxALL, 4);

        wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        mainFrame->GetContentPanel()->SetSizer(sizer, true);

        sizer->Add(nativeLabel, flags);
        sizer->Add(styledLabel, flags);
        sizer->Add(nativeButton, flags);
        sizer->Add(styledButton, flags);
        sizer->Add(nativeCheckBox, flags);
        sizer->Add(styledCheckBox, flags);

        /* Not yet implemented */
        sizer->Add(nativeTextField, flags);
        sizer->Add(nativeComboBox, flags);

        mainFrame->Fit();
    }

    int OnExit() override {
        DoStop();
        return 0;
    }

private:
    StyledFrame *mainFrame;

    StyledButton *styledButton;
    StyledLabel *styledLabel;
    StyledCheckBox *styledCheckBox;

    wxButton *nativeButton;
    wxStaticText *nativeLabel;
    wxCheckBox *nativeCheckBox;

    wxTextCtrl *nativeTextField;
    wxComboBox *nativeComboBox;
};

IMPLEMENT_APP(DemoApp);