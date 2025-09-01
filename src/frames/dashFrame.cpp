#include "../libs/allFrames.hpp"
#include "../libs/app.hpp"
#include "wx/gdicmn.h"
#include "wx/generic/panelg.h"
#include "wx/gtk/button.h"
#include "wx/sizer.h"

DashFrame::DashFrame(const wxString & user)
      :wxFrame(nullptr, crm_dash, "Dashboard - " + appName)
      
{
      // create main container.
      mainSizer = new wxGridSizer(2,2,wxSize(10,10));
      // create 3 main panels.
      userPanel = new wxPanel();
      searchResults = new wxPanel();
      actions = new wxPanel();
      // create 3 sizers for the above.
      actionsSizer = new wxBoxSizer(wxVERTICAL);
      // create controls to fill up.
      searchBar = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER);      AddCust = new wxButton(actions, AddCustBtn, "Add a Customer", wxDefaultPosition, wxDefaultSize);
      AddEntry = new wxButton(actions, AddEntryBtn, "Add an Entry", wxDefaultPosition, wxDefaultSize);
      AddSv = new wxButton(actions, AddSvBtn, "Add a Service", wxDefaultPosition, wxDefaultSize);
      ChkScrl = new wxButton(actions, ChkScrlBtn, "Check Scroll", wxDefaultPosition, wxDefaultSize);

      actionsSizer->Add(AddCust, 0, wxEXPAND | wxALL, 10);
      actionsSizer->Add(AddEntry, 0, wxEXPAND | wxALL, 10);
      actionsSizer->Add(AddSv, 0, wxEXPAND | wxALL, 10);
      actionsSizer->Add(ChkScrl, 0, wxEXPAND | wxALL, 10);
      mainSizer->Add(searchBar, 0, wxEXPAND | wxALL, 10);
      mainSizer->Add(userPanel, 0, wxEXPAND | wxALL, 10);
      mainSizer->Add(searchResults, 0, wxEXPAND | wxALL, 10);
      mainSizer->Add(actions, 0, wxEXPAND | wxALL, 10);

      actions->SetSizer(actionsSizer);
      mainSizer->SetSizeHints(this);
      this->SetSize(500,500);
}
