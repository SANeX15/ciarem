#include <wx/wx.h>
#include <wx/datectrl.h>

enum form_ID {
  crm_cust_saveBtn,
  crm_cust_cancelBtn,
};

class CustForm : public wxFrame {
  public:
    CustForm(wxWindow * parent, const bool mode);
    void onBtnClick(wxCommandEvent & evt);
    void saveProc();
  private:
    wxBoxSizer * mainSizer,
               * btnSizer;
    wxPanel * btnPanel;
    wxButton * saveBtn,
             * cancelBtn;
    wxTextCtrl * nameField,
               * uidField;
    wxDatePickerCtrl * dobField;
    wxStaticText * Title;
};
