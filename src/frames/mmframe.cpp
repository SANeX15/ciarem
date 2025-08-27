#include "../libs/mmframe.h"
#include "../libs/app.h"

wxString mmtitle = "Login";

MainMenuFrame::MainMenuFrame(const wxString & title)
              :wxFrame(nullptr, crm_mm, title + " - " + mmtitle)
{
  mob = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
  pwd = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_PASSWORD);
  panelSizer = new wxBoxSizer(wxVERTICAL);
  mainSizer = new wxBoxSizer(wxVERTICAL);
  panel = new wxPanel(this,wxID_ANY);
  Login = new wxButton(panel, crm_Login_ID, "Login", wxDefaultPosition, wxDefaultSize);

  panelSizer->Add(mob, 0, wxEXPAND | wxALL, 10);
  panelSizer->Add(pwd, 0, wxEXPAND | wxALL, 10);
  panelSizer->Add(Login, 0, wxALIGN_CENTER | wxALL, 10);
  panel->SetSizer(panelSizer);
  
  mainSizer->Add(panel, 1, wxEXPAND | wxALL, 10);
  this->SetSizerAndFit(mainSizer);

  Login->Bind(wxEVT_BUTTON, &MainMenuFrame::OnLogin, this);
}

void MainMenuFrame::OnLogin(wxCommandEvent & evt){
  wxMessageDialog(this,"hehe");
}
