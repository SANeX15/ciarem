#include <wx/wx.h>

enum ID{
  crm_Login_ID,
  crm_Quit_ID
};

class LoginFrame : public wxFrame{
  public:
    LoginFrame(const wxString & title);
  private:
    wxBoxSizer * mainSizer;
    wxBoxSizer * panelSizer;
    wxPanel * panel;
    wxTextCtrl * mob;
    wxTextCtrl * pwd;
    wxButton * Login;
    wxButton * Quit;
    
    void OnLogin(wxCommandEvent & evt);
    void OnQuit(wxCommandEvent & evt);
};
