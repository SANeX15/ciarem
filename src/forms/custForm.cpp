#include "../libs/allForms.hpp"

CustForm::CustForm(const int & mode, wxWindow * parent)
         :wxFrame(parent, wxID_ANY, (mode)?"Add a Customer's Details":"Modify a Customer's Details")
{
  
}
