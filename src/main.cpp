#include <wx/wx.h>
#include <wx/gbsizer.h>

#include <vector>
#include "bufferedbitmap.h"

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

    auto nameLabel = new wxStaticText(panel, wxID_ANY, "File Name:");
    auto kindLabel = new wxStaticText(panel, wxID_ANY, "Kind:");
    auto sizeLabel = new wxStaticText(panel, wxID_ANY, "Size:");
    auto dimensionsLabel = new wxStaticText(panel, wxID_ANY, "Dimensions:");

    auto kindValue = new wxStaticText(panel, wxID_ANY, "PNG");
    auto sizeValue = new wxStaticText(panel, wxID_ANY, "1.2 MB");
    auto dimensionsValue = new wxStaticText(panel, wxID_ANY, "1024x768");

    auto nameText = new wxTextCtrl(panel, wxID_ANY);
    nameText->SetEditable(false);

    auto loadButton = new wxButton(panel, wxID_ANY, "Load...");

    auto bitmap = new BufferedBitmap(panel, wxID_ANY, wxBitmap(wxSize(1, 1)), wxDefaultPosition, FromDIP(wxSize(400, 200)));
    bitmap->SetBackgroundColour(wxColour(0, 0, 0));

    sizer->Add(nameLabel, {0, 0}, {1, 1}, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    sizer->Add(kindLabel, {1, 0}, {1, 1}, wxALIGN_RIGHT);
    sizer->Add(sizeLabel, {2, 0}, {1, 1}, wxALIGN_RIGHT);
    sizer->Add(dimensionsLabel, {3, 0}, {1, 1}, wxALIGN_RIGHT);

    sizer->Add(kindValue, {1, 1}, {1, 1}, wxEXPAND);
    sizer->Add(sizeValue, {2, 1}, {1, 1}, wxEXPAND);
    sizer->Add(dimensionsValue, {3, 1}, {1, 1}, wxEXPAND);

    sizer->Add(nameText, {0, 1}, {1, 2}, wxEXPAND);
    sizer->Add(loadButton, {0, 3}, {1, 1}, wxEXPAND);
    sizer->Add(bitmap, {1, 2}, {3, 2}, wxEXPAND);

    sizer->AddGrowableRow(3);
    sizer->AddGrowableCol(2);

    panel->SetSizer(sizer);

    mainSizer->Add(panel, 1, wxEXPAND | wxALL, margin);
    this->SetSizerAndFit(mainSizer);
}