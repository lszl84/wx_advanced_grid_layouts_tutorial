#include <wx/wx.h>
#include <wx/gbsizer.h>

#include <vector>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

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
    const auto margin = FromDIP(10);

    auto mainSizer = new wxBoxSizer(wxVERTICAL);
    wxPanel *panel = new wxPanel(this, wxID_ANY);
    this->SetBackgroundColour(panel->GetBackgroundColour());

    auto sizer = new wxGridBagSizer(margin, margin);

    std::vector<std::pair<wxGBPosition, wxGBSpan>> items = {
        {{0, 0}, {1, 2}},
        {{1, 0}, {1, 1}},
        {{2, 0}, {1, 1}},
        {{3, 0}, {1, 2}},
        {{4, 0}, {1, 3}},
        {{1, 1}, {1, 1}},
        {{2, 1}, {1, 1}},
        {{0, 2}, {4, 1}}};

    for (auto &item : items)
    {
        auto initialSize = sizer->GetEmptyCellSize() * 2;

        if (item.first == wxGBPosition(1, 0))
        {
            initialSize.SetWidth(FromDIP(100));
        }

        auto p = new wxPanel(panel, wxID_ANY, wxDefaultPosition, initialSize);
        p->SetBackgroundColour(wxColour(100, 100, 200));

        sizer->Add(p, item.first, item.second, wxEXPAND);
    }

    sizer->AddGrowableRow(0, 2);
    sizer->AddGrowableRow(4, 1);

    sizer->AddGrowableCol(1);
    sizer->AddGrowableCol(2);

    sizer->SetMinSize(FromDIP(wxSize(600, 400)));

    panel->SetSizer(sizer);

    mainSizer->Add(panel, 1, wxEXPAND | wxALL, margin);
    this->SetSizerAndFit(mainSizer);
}