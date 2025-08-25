#include <wx/wx.h>

enum ID{
  crm_Login_ID,
  crm_Quit_ID
};

class MainMenuFrame : public wxFrame{
  public:
    MainMenuFrame(wxString & title);
  private:
    wxTextCtrl * mob;
    wxTextCtrl * pwd;
    wxButton * Login;
    wxButton * Quit;
    
    void OnLogin(wxCommandEvent & evt);
    void OnQuit(wxCommandEvent & evt);
};
