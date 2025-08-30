#include <wx/wx.h>

extern wxString appName;

enum wndID{
  crm_login,
  crm_dash
};

class CRM_App : public wxApp{
  public:
    virtual bool OnInit();
};

DECLARE_APP(CRM_App)
