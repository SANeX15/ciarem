#include "wx/listctrl.h"
#include <wx/wx.h>

enum ID{
  crm_login_loginBtn,
  crm_dash_custBtn,
  crm_dash_addBtn,
  crm_dash_svBtn,
  crm_dash_scrlBtn,
  custWnd,
  // addWnd,
  // svWnd,
  // scrlWnd,
  // mainWnd,
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
    void onBtnClick(wxCommandEvent & evt);
  private:
    wxMenuBar * mainBar;
    wxMenu * UserMenu;
    wxMenuItem * LogoutOpt;
    wxGridSizer * mainSizer;
    wxButton * custBtn,
             * addBtn,
             * svBtn,
             * scrlBtn;
};

class CustFrame : public wxFrame {
  public:
    CustFrame(wxWindow * parent);
    void custCols();
    void pop();
  private:
    wxSizer * mainSizer;
    wxPanel * searchPanel,
          * cListPanel;
    wxTextCtrl * searchBar;
    wxListView * cListView;
};
