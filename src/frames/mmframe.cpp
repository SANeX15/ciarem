#include "../libs/mmframe.h"
#include "../libs/app.h"
#include "../libs/db.h"
#include "wx/string.h"

wxString mmtitle = "Login";

MainMenuFrame::MainMenuFrame(const wxString & title)
              :wxFrame(nullptr, crm_mm, title + " - " + mmtitle)
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
  Login = new wxButton(panel, wxID_ANY, "Login", wxDefaultPosition, wxDefaultSize);

  // place button control in panel
  panelSizer->Add(Login, 0, wxEXPAND | wxALL, 10);

  // set panelSizer as panel's organiser
  panel->SetSizer(panelSizer);

  // put panel in parent
  mainSizer->Add(panel, 1, wxEXPAND | wxALL, 10);

  // make mainSizer as the organiser of parent window (this)
  this->SetSizerAndFit(mainSizer);

  // Tell Login to call a func when clicked
  Login->Bind(wxEVT_BUTTON, &MainMenuFrame::OnLogin, this);
}

void MainMenuFrame::OnLogin(wxCommandEvent & evt){
  std::string uname = mob->GetValue().ToStdString();
  std::string passwd = pwd->GetValue().ToStdString();
  std::shared_ptr<sql::Connection> conn = db::connect();
  wxString msg;
  if (conn == NULL){
    msg = "db uninit";
  }
  else {
    msg = (db::userAuth(conn,uname,passwd)== true)?"login success":"login failed";
  }
  wxMessageDialog d(this,msg);
  d.ShowModal();
}
