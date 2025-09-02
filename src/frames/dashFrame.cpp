#include "../libs/allFrames.hpp"
#include "../libs/app.hpp"
#include "wx/font.h"
#include "wx/gdicmn.h"
#include "wx/wx.h"

DashFrame::DashFrame(const wxString & user)
      :wxFrame(nullptr, crm_dash, "Dashboard - " + appName)
      
{
      const wxSize btnSize = wxSize(-1,100);
      wxFont btnFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
      wxFont lblFont(16,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_EXTRABOLD);
      
      // Create main sizers for the top-level layout.
      mainSizer = new wxBoxSizer(wxVERTICAL);
      topSizer = new wxBoxSizer(wxHORIZONTAL);
      bottomSizer = new wxBoxSizer(wxHORIZONTAL);

      // Create panels with the frame as their parent.
      searchPanel = new wxPanel(this);
      userPanel = new wxPanel(this);
      searchResults = new wxPanel(this);
      actionsPanel = new wxPanel(this);
      
      // Create controls. Their parent should be the panel they reside on.
      searchBar = new wxTextCtrl(searchPanel, wxID_ANY,"", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
      searchBar->SetHint("Search Customers");
      
      // User Panel Controls
      userMobile = new wxStaticText(userPanel, wxID_ANY, user);
      userMobile->SetFont(lblFont);
      
      // Actions Panel Controls
      AddCust = new wxButton(actionsPanel, AddCustBtn, "Add a Customer", wxDefaultPosition, btnSize);
      AddCust->SetFont(btnFont);
      AddEntry = new wxButton(actionsPanel, AddEntryBtn, "Add an Entry", wxDefaultPosition, btnSize);
      AddEntry->SetFont(btnFont);
      AddSv = new wxButton(actionsPanel, AddSvBtn, "Add a Service", wxDefaultPosition, btnSize);
      AddSv->SetFont(btnFont);
      ChkScrl = new wxButton(actionsPanel, ChkScrlBtn, "Check Scroll", wxDefaultPosition, btnSize);
      ChkScrl->SetFont(btnFont);

      // Set up sizers for nested panels.
      searchSizer = new wxBoxSizer(wxHORIZONTAL);
      searchSizer->Add(searchBar, 1, wxEXPAND | wxALL, 5);
      searchPanel->SetSizer(searchSizer);

      userSizer = new wxBoxSizer(wxHORIZONTAL);
      userSizer->Add(userMobile, 0, wxALIGN_CENTER | wxALL, 5);
      userPanel->SetSizer(userSizer);
      userPanel->SetBackgroundColour(*wxRED);
      
      actionsSizer = new wxBoxSizer(wxVERTICAL);
      actionsSizer->Add(AddCust, 0, wxEXPAND | wxALL, 10);
      actionsSizer->Add(AddEntry, 0, wxEXPAND | wxALL, 10);
      actionsSizer->Add(AddSv, 0, wxEXPAND | wxALL, 10);
      actionsSizer->Add(ChkScrl, 0, wxEXPAND | wxALL, 10);
      actionsPanel->SetSizer(actionsSizer);
      
      // Add panels to the top and bottom sizers.
      topSizer->Add(searchPanel, 2, wxEXPAND | wxALL, 10);
      topSizer->Add(userPanel, 1, wxALL, 10);
      
      bottomSizer->Add(searchResults, 2, wxEXPAND | wxALL, 10);
      bottomSizer->Add(actionsPanel, 1, wxEXPAND | wxALL, 10);
      
      // Add top and bottom sizers to the main sizer.
      mainSizer->Add(topSizer, 0, wxEXPAND);
      mainSizer->Add(bottomSizer, 1, wxEXPAND);

      mainBar = new wxMenuBar();
      UserMenu = new wxMenu();
      LogoutOpt = new wxMenuItem(UserMenu,wxID_ANY,"&LogOut\tCtrl+L","Logs out current user");
      UserMenu->Append(LogoutOpt);
      mainBar->Append(UserMenu,"&User");
      
      // Set the main sizer on the frame to manage its layout.
      this->SetMenuBar(mainBar);
      this->SetSizerAndFit(mainSizer);
      this->SetMinSize(wxSize(800,600));
}
