#include "libs/app.hpp"
#include "libs/allFrames.hpp"

wxString appName = "CIAREM";

wxIMPLEMENT_APP(CRM_App);

bool CRM_App::OnInit(){
  // Create a new instance of the LoginFrame
  // LoginFrame * lf = new LoginFrame();

  // DashFrame * df = new DashFrame("user");
  CustFrame * cf = new CustFrame(nullptr);
  // Show the main window. This is the critical step to avoid the segmentation fault.
  // lf->Show(true);

  // df->Show();
  cf->Show();
  // Return true to indicate that the application should start its main event loop
  return true;
}
