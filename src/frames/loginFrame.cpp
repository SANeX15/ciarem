#include "../libs/allFrames.hpp"
#include "../libs/app.hpp"
#include "../libs/db.hpp"

LoginFrame::LoginFrame()
              :wxFrame(nullptr, crm_login, "Login - " + appName)
{
  // create the parent container organiser
  mainSizer = new wxBoxSizer(wxVERTICAL);

  // child container that'll hold controls
  panel = new wxPanel(this, wxID_ANY);

  // helps organise controls in child container
  panelSizer = new wxBoxSizer(wxVERTICAL);

  // create field-based controls
  mob = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
  pwd = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_PASSWORD);

  // place field controls in panel
  panelSizer->Add(mob, 0, wxEXPAND | wxALL, 10);
  panelSizer->Add(pwd, 0, wxEXPAND | wxALL, 10);

  // create button control
  Login = new wxButton(panel, crm_login_loginBtn, "Login", wxDefaultPosition, wxDefaultSize);

  // place button control in panel
  panelSizer->Add(Login, 0, wxEXPAND | wxALL, 10);

  // set panelSizer as panel's organiser
  panel->SetSizer(panelSizer);

  // put panel in parent
  mainSizer->Add(panel, 1, wxEXPAND | wxALL, 10);

  // make mainSizer as the organiser of parent window (this)
  this->SetSizerAndFit(mainSizer);
  this->SetSize(350,400);
  // Tell Login to call a func when clicked
  Login->Bind(wxEVT_BUTTON, &LoginFrame::OnLogin, this);
}

void LoginFrame::OnLogin(wxCommandEvent & evt){
  db::crmDB dbObj;
  std::string uname = mob->GetValue().ToStdString();
  std::string passwd = pwd->GetValue().ToStdString();
  std::shared_ptr<sql::Connection> conn = dbObj.retconn();
  wxString msg;

  if (conn == NULL){
    msg = "db uninit";
  }
  else {
    msg = (dbObj.userAuth(conn,uname,passwd)== true)?"login success":"login failed";
  }
  
  wxMessageDialog d(this,msg);
  d.ShowModal();
  dbObj.disconnect(conn);
}
