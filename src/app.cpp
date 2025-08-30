#include "libs/app.hpp"
#include "libs/allFrames.hpp"

wxString appName = "CIAREM";

wxIMPLEMENT_APP(CRM_App);

bool CRM_App::OnInit(){
  // Create a new instance of the MainMenuFrame
  LoginFrame * lf = new LoginFrame();

  // Show the main window. This is the critical step to avoid the segmentation fault.
  lf->Show(true);

  // Return true to indicate that the application should start its main event loop
  return true;
}
