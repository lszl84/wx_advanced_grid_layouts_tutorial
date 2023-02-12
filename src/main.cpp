#include <wx/wx.h>

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
    const int WIDTH = FromDIP(30);
    const int HEIGHT = FromDIP(30);

    const int COLS = 20;
    const int ROWS = 13;

    auto mainSizer = new wxBoxSizer(wxVERTICAL);
    auto sizer = new wxGridSizer(ROWS, COLS, 0, 0);

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            auto square = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(WIDTH, HEIGHT));
            bool isDark = (i + j) % 2 == 0;
            square->SetBackgroundColour(isDark ? wxColor(80, 80, 80) : *wxWHITE);

            sizer->Add(square, 1, wxEXPAND);
        }
    }

    mainSizer->Add(sizer);
    this->SetSizerAndFit(mainSizer);
}