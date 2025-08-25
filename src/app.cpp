#include "libs/app.h"
#include "libs/mmframe.h"

wxIMPLEMENT_APP(CRM_App);

bool CRM_App::OnInit(){
  MainMenuFrame * mmf = new MainMenuFrame("CIAREM");
  return true;
}
