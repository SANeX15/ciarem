#include <wx/wx.h>

enum ID{
  LoginBtn,
  AddCustBtn,
  AddEntryBtn,
  AddSvBtn,
  ChkScrlBtn
};

class LoginFrame : public wxFrame{
  public:
    LoginFrame();
  private:
    wxBoxSizer * mainSizer,
               * panelSizer;
    wxPanel * panel;
    wxTextCtrl * mob,
               * pwd;
    wxButton * Login,
             * Quit;
    
    void OnLogin(wxCommandEvent & evt);
};

class DashFrame : public wxFrame{
  public:
    DashFrame(const wxString & user);
  private:
    wxMenuBar * mainBar;
    wxMenu * UserMenu;
    wxMenuItem * LogoutOpt;
    wxBoxSizer * mainSizer,
               * topSizer,
               * bottomSizer,
               * userSizer;
    wxPanel * searchPanel,
            * userPanel,
            * searchResults,
            * actionsPanel;
    wxTextCtrl * searchBar;
    wxStaticText * userMobile;
    wxButton * AddCust,
             * AddEntry,
             * AddSv,
             * ChkScrl,
             * LogoutBtn;
};
