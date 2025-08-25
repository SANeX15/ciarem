#include "wx/sizer.h"
#include <wx/wx.h>

enum ID{
  crm_Login_ID,
  crm_Quit_ID
};

class MainMenuFrame : public wxFrame{
  public:
    MainMenuFrame(const wxString & title);
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
