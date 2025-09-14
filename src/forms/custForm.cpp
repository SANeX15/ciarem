#include "../libs/allFrames.hpp"
#include "../libs/db.hpp"

CustForm::CustForm(wxWindow * parent, const bool mode)
         :wxDialog(parent, wxID_ANY, (mode)?"Add a Customer's Details":"Modify a Customer's Details")
{
  mainSizer = new wxBoxSizer(wxVERTICAL);
  btnSizer = new wxBoxSizer(wxHORIZONTAL);
  btnPanel = new wxPanel(this);
  saveBtn = new wxButton(btnPanel, crm_cust_saveBtn, "Save");
  cancelBtn = new wxButton(btnPanel, crm_cust_cancelBtn, "Cancel");

  Title = new wxStaticText(this, wxID_ANY,(mode)?"New Customer's Details":"Existing Customer's Details");
  
  wxTextValidator uidVal(wxFILTER_NUMERIC);
  nameField = new wxTextCtrl(this, crm_cust_nameField, "");
  uidField = new wxTextCtrl(this, crm_cust_uidField, "", wxDefaultPosition, wxDefaultSize, 0, uidVal);
  dobField = new wxDatePickerCtrl(this, wxID_ANY);

  btnSizer->Add(saveBtn,0,wxALL | wxEXPAND, 10);
  btnSizer->Add(cancelBtn, 0, wxALL | wxEXPAND, 10);
  btnPanel->SetSizer(btnSizer);

  uidField->SetHint("UID no.");
  uidField->SetMaxLength(12);
  nameField->SetHint("Name");
  
  mainSizer->Add(Title, 0, wxALL | wxEXPAND, 10);
  mainSizer->Add(uidField, 0 , wxALL | wxEXPAND, 10);
  mainSizer->Add(nameField, 0 , wxALL | wxEXPAND, 10);
  mainSizer->Add(dobField, 0 , wxALL | wxEXPAND, 10);
  mainSizer->Add(btnPanel, 0 , wxALL | wxEXPAND, 10);

  this->SetSizerAndFit(mainSizer);

  uidField->Bind(wxEVT_TEXT, &CustForm::checkField, this);
  saveBtn->Bind(wxEVT_BUTTON, &CustForm::onBtnClick, this);
  cancelBtn->Bind(wxEVT_BUTTON, &CustForm::onBtnClick, this);
}

void CustForm::onBtnClick(wxCommandEvent & evt) {
  int id = evt.GetId();
  switch (id){
    case crm_cust_saveBtn:
      if(uidField->GetValue().IsEmpty() || nameField->GetValue().IsEmpty() || dobField->GetValue() == wxDateTime::Today()){
        wxMessageBox("You left some values unchanged");
        return;
      } else {
        saveProc();
      }
      break;
    case crm_cust_cancelBtn:
      Destroy();
      break;
    default:
      break;
  }
}

void CustForm::saveProc(){
  db::crmDB dbObj;
  std::shared_ptr<sql::Connection> conn = dbObj.retconn();
  std::vector<std::string> values;
  
  values.push_back(uidField->GetValue().ToStdString());
  values.push_back(nameField->GetValue().ToStdString());
  values.push_back(dobField->GetValue().FormatISODate().ToStdString());

  std::string err = dbObj.newEntry(conn, db::cust_tbl, values);
  
  if(!err.empty()){
    wxMessageBox("An error occured while saving details: " + err, "Save Error");
  }
  else{
    CustFrame *parentFrame = dynamic_cast<CustFrame*>(GetParent());
    if (parentFrame) {
      parentFrame->populate();
    }
    Destroy();
  }
  dbObj.disconnect(conn);
}

void CustForm::checkField(wxCommandEvent & evt){
  int id = evt.GetId();
  wxString tmp = "";
  switch (id) {
    case crm_cust_uidField:
      tmp = uidField->GetValue();
      if (tmp.Length() == 12) {
        uidField->SetForegroundColour(*wxWHITE);
        uidField->Refresh();
        saveBtn->Enable();
      } else {
        uidField->SetForegroundColour(wxColour(255, 200, 200));
        uidField->Refresh();
        saveBtn->Disable();
      }
      break;
    default:
      evt.Skip();
  }
}
