#include "wx/sizer.h"
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
    wxGridSizer * mainSizer;
    wxBoxSizer * actionsSizer;
    wxPanel * userPanel,
            * searchResults,
            * actions;
    wxTextCtrl * searchBar;
    wxButton * AddCust,
             * AddEntry,
             * AddSv,
             * ChkScrl;
    wxStaticText * username;
};
