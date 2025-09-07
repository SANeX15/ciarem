#include "../libs/allFrames.hpp"
#include "../libs/app.hpp"
#include "wx/event.h"

DashFrame::DashFrame(const wxString & user)
      :wxFrame(nullptr, crm_dash, "Dashboard - " + appName)
      
{
      const wxSize btnSize = wxSize(-1,100);
      wxFont btnFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
      wxFont lblFont(16,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_EXTRABOLD);
      
      // Create main sizers for the top-level layout.
      mainSizer = new wxGridSizer(2,2,10);
      
      // Actions Panel Controls
      custBtn = new wxButton(this, crm_dash_custBtn, "Manage Customers", wxDefaultPosition, btnSize);
      custBtn->SetFont(btnFont);
      addBtn = new wxButton(this, crm_dash_addBtn, "Add an Entry", wxDefaultPosition, btnSize);
      addBtn->SetFont(btnFont);
      svBtn = new wxButton(this, crm_dash_svBtn, "Manage Services", wxDefaultPosition, btnSize);
      svBtn->SetFont(btnFont);
      scrlBtn = new wxButton(this, crm_dash_scrlBtn, "Open Scroll", wxDefaultPosition, btnSize);
      scrlBtn->SetFont(btnFont);
      
      // Add top and bottom sizers to the main sizer.
      mainSizer->Add(custBtn, 0, wxEXPAND | wxALL, 10);
      mainSizer->Add(addBtn, 0, wxEXPAND | wxALL, 10);
      mainSizer->Add(svBtn, 0, wxEXPAND | wxALL, 10);
      mainSizer->Add(scrlBtn, 0, wxEXPAND | wxALL, 10);
      mainBar = new wxMenuBar();
      UserMenu = new wxMenu();
      LogoutOpt = new wxMenuItem(UserMenu,wxID_ANY,"&LogOut\tCtrl+L","Logs out current user");
      UserMenu->Append(LogoutOpt);
      mainBar->Append(UserMenu,"&User");
      
      // Set the main sizer on the frame to manage its layout.
      this->SetMenuBar(mainBar);
      this->SetSizerAndFit(mainSizer);
      this->SetMinSize(wxSize(400,300));

      // bindings
      custBtn->Bind(wxEVT_BUTTON, &DashFrame::onBtnClick, this);
}

void DashFrame::onBtnClick(wxCommandEvent & evt){
      CustFrame * frm;
      int id = evt.GetId();
      switch (id) {
            case crm_dash_addBtn:
                  frm = new CustFrame();
                  break;
            case crm_dash_custBtn:
                  break;
            case crm_dash_svBtn:
                  break;
            case crm_dash_scrlBtn:
                  break;
            default :
                  break;
      }
      this->Hide();
      frm->Show();
}
