#include <wx/wx.h>
#include <vector>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

enum class InputType
{
    SingleLine,
    MultiLine
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello World", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    std::vector<std::pair<wxString, InputType>> form = {
        {"Name", InputType::SingleLine},
        {"Address", InputType::MultiLine},
        {"Phone", InputType::SingleLine},
        {"Email", InputType::SingleLine},
        {"Notes", InputType::MultiLine}};

    const auto margin = FromDIP(10);

    auto mainSizer = new wxBoxSizer(wxVERTICAL);
    wxPanel *panel = new wxPanel(this, wxID_ANY);

    auto sizer = new wxGridSizer(form.size(), 2, margin, margin);

    for (const auto &[label, type] : form)
    {
        auto labelCtrl = new wxStaticText(panel, wxID_ANY, label);
        sizer->Add(labelCtrl, 0, wxALIGN_CENTER_VERTICAL);

        auto style = type == InputType::SingleLine ? 0 : wxTE_MULTILINE;
        auto inputCtrl = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style);

        sizer->Add(inputCtrl, 1, wxEXPAND);
    }

    panel->SetSizer(sizer);

    mainSizer->Add(panel, 1, wxEXPAND | wxALL, margin);
    this->SetSizer(mainSizer);
}