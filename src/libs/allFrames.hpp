#include "allForms.hpp"
#include <vector>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/artprov.h>

enum frame_ID{
  crm_login_loginBtn,
  crm_dash_custBtn,
  crm_dash_addBtn,
  crm_dash_svBtn,
  crm_dash_scrlBtn,
  crm_cust_addBtn,
  // custWnd,
  // addWnd,
  // svWnd,
  // scrlWnd,
  // mainWnd,
};

struct Customer {
  std::string uid, name, dob;
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
  private:
    wxSizer * mainSizer;
    wxPanel * searchPanel,
          * cListPanel;
    wxTextCtrl * searchBar;
    wxListView * cListView;
    wxToolBar * mainToolBar;
    void custCols(),
         pop(),
         onClose(wxCloseEvent & evt),
         onTool(wxCommandEvent & evt);
    std::vector<Customer> customers;
};
