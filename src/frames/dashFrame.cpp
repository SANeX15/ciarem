#include "../libs/allFrames.hpp"
#include "../libs/app.hpp"

DashFrame::DashFrame(const wxString & user)
      :wxFrame(nullptr, crm_dash, "Dashboard - " + appName)
{
      // create main container
      mainSizer = new wxBoxSizer(wxVERTICAL);
      SetSizerAndFit(mainSizer);
}
