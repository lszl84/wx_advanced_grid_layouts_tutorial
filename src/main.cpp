#include <wx/wx.h>
#include <wx/gbsizer.h>
#include <wx/file.h>
#include <wx/filename.h>
#include <wx/filedlg.h>

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

    auto nameFormSizer = new wxBoxSizer(wxHORIZONTAL);
    nameFormSizer->Add(nameText, 1, wxEXPAND | wxRIGHT, margin);
    nameFormSizer->Add(loadButton, 0, wxALIGN_CENTER_VERTICAL);

    auto bitmap = new BufferedBitmap(panel, wxID_ANY, wxBitmap(wxSize(1, 1)), wxDefaultPosition, FromDIP(wxSize(400, 200)));

    sizer->Add(nameLabel, {0, 0}, {1, 1}, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    sizer->Add(kindLabel, {1, 0}, {1, 1}, wxALIGN_RIGHT);
    sizer->Add(sizeLabel, {2, 0}, {1, 1}, wxALIGN_RIGHT);
    sizer->Add(dimensionsLabel, {3, 0}, {1, 1}, wxALIGN_RIGHT);

    sizer->Add(kindValue, {1, 1}, {1, 1}, wxEXPAND);
    sizer->Add(sizeValue, {2, 1}, {1, 1}, wxEXPAND);
    sizer->Add(dimensionsValue, {3, 1}, {1, 1}, wxEXPAND);

    sizer->Add(nameFormSizer, {0, 1}, {1, 3}, wxEXPAND);
    sizer->Add(bitmap, {1, 2}, {3, 2}, wxEXPAND);

    sizer->AddGrowableRow(3);
    sizer->AddGrowableCol(2);

    panel->SetSizer(sizer);

    mainSizer->Add(panel, 1, wxEXPAND | wxALL, margin);
    this->SetSizerAndFit(mainSizer);

    wxInitAllImageHandlers();

    loadButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent &event)
                     {
                         wxFileDialog openFileDialog(this, "Open Image", "", "", "Image files (*.png;*.jpg;*.jpeg;*.bmp)|*.png;*.jpg;*.jpeg;*.bmp", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

                         if (openFileDialog.ShowModal() == wxID_CANCEL)
                         {
                             return;
                         }

                         wxImage image;
                         if (!image.LoadFile(openFileDialog.GetPath()))
                         {
                             wxMessageBox("Failed to load image");
                             return;
                         }

                         // set bitmap
                         bitmap->SetBitmap(wxBitmap(image));
                         nameText->SetValue(openFileDialog.GetPath());

                         wxFile file(openFileDialog.GetPath());

                         kindValue->SetLabel(wxFileName(openFileDialog.GetPath()).GetExt().Upper());
                         sizeValue->SetLabel(wxString::Format("%d KB", static_cast<int>(file.Length() / 1024)));

                         dimensionsValue->SetLabel(wxString::Format("%d x %d", image.GetWidth(), image.GetHeight()));

                         this->Layout();
                         this->Fit(); });
}