#include "wx/sizer.h"
#include <wx/wx.h>

enum ID{
  LoginBtn
};

class LoginFrame : public wxFrame{
  public:
    LoginFrame();
  private:
    wxBoxSizer * mainSizer;
    wxBoxSizer * panelSizer;
    wxPanel * panel;
    wxTextCtrl * mob;
    wxTextCtrl * pwd;
    wxButton * Login;
    wxButton * Quit;
    
    void OnLogin(wxCommandEvent & evt);
};

class DashFrame : public wxFrame{
  public:
    DashFrame(const wxString & user);
  private:
    wxBoxSizer * mainSizer;
};
