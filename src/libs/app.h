#include <wx/wx.h>

enum wndID{
  crm_mm
};

class CRM_App : public wxApp{
  public:
    virtual bool OnInit();
};

DECLARE_APP(CRM_App)
