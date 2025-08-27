#include "libs/app.h"
#include "libs/mmframe.h"

wxIMPLEMENT_APP(CRM_App);

bool CRM_App::OnInit(){
  // Create a new instance of the MainMenuFrame
  MainMenuFrame * mmf = new MainMenuFrame("CIAREM");

  // Show the main window. This is the critical step to avoid the segmentation fault.
  mmf->Show(true);

  // Return true to indicate that the application should start its main event loop
  return true;
}
