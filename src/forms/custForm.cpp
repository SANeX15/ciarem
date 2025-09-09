#include "../libs/allForms.hpp"
#include "../libs/db.hpp"

CustForm::CustForm(wxWindow * parent, const bool mode)
         :wxFrame(parent, wxID_ANY, (mode)?"Add a Customer's Details":"Modify a Customer's Details")
{
  mainSizer = new wxBoxSizer(wxVERTICAL);
  btnSizer = new wxBoxSizer(wxHORIZONTAL);
  btnPanel = new wxPanel(this);
  saveBtn = new wxButton(btnPanel, crm_cust_saveBtn, "Save");
  cancelBtn = new wxButton(btnPanel, crm_cust_cancelBtn, "Cancel");

  Title = new wxStaticText(this, wxID_ANY,(mode)?"New Customer's Details":"Existing Customer's Details");
  
  wxTextValidator uidVal(wxFILTER_NUMERIC);
  nameField = new wxTextCtrl(this, wxID_ANY, "");
  uidField = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, uidVal);
  dobField = new wxDatePickerCtrl(this, wxID_ANY);

  btnSizer->Add(saveBtn,0,wxALL | wxEXPAND, 10);
  btnSizer->Add(cancelBtn, 0, wxALL | wxEXPAND, 10);
  btnPanel->SetSizer(btnSizer);

  uidField->SetHint("UID no.");
  nameField->SetHint("Name");
  
  mainSizer->Add(Title, 0, wxALL | wxEXPAND, 10);
  mainSizer->Add(uidField, 0 , wxALL | wxEXPAND, 10);
  mainSizer->Add(nameField, 0 , wxALL | wxEXPAND, 10);
  mainSizer->Add(dobField, 0 , wxALL | wxEXPAND, 10);
  mainSizer->Add(btnPanel, 0 , wxALL | wxEXPAND, 10);

  this->SetSizerAndFit(mainSizer);

  saveBtn->Bind(wxEVT_BUTTON, &CustForm::onBtnClick, this);
  cancelBtn->Bind(wxEVT_BUTTON, &CustForm::onBtnClick, this);
}

void CustForm::onBtnClick(wxCommandEvent & evt) {
  int id = evt.GetId();
  switch (id){
    case crm_cust_saveBtn:
      if(uidField->GetValue().IsEmpty() || nameField->GetValue().IsEmpty() || dobField->GetValue() == wxDateTime::Today()){
        wxMessageBox("You left some values unchanged");
      } else {
        saveProc();
      }
      Destroy();
      break;
    case crm_cust_cancelBtn:
      Destroy();
      break;
    default:
      break;
  }
}

void CustForm::saveProc(){
  std::shared_ptr<sql::Connection> conn = db::retconn();
  std::vector<std::string> values;
  
  values.push_back(uidField->GetValue().ToStdString());
  values.push_back(nameField->GetValue().ToStdString());
  values.push_back(dobField->GetValue().FormatISODate().ToStdString());
  
  db::newEntry(conn, db::cust_tbl, values);
}
