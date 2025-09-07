#include "../libs/allFrames.hpp"
#include "wx/listctrl.h"
#include "wx/string.h"
#include <string>

CustFrame::CustFrame(){

  mainSizer = new wxBoxSizer(wxVERTICAL);

  // searchBar = new wxTextCtrl(this, wxID_ANY,"", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
  // cListView = new wxListView();

  // mainSizer->Add(searchBar, 0, wxALL | wxEXPAND,10);
  // mainSizer->Add(cListView, 0, wxALL | wxEXPAND, 10);
  this->SetSizerAndFit(mainSizer);

  // custCols();
  // pop();
}

void CustFrame::custCols(){
  cListView->AppendColumn("uid",wxLIST_FORMAT_LEFT,15);
  cListView->AppendColumn("name",wxLIST_FORMAT_LEFT,60);
  cListView->AppendColumn("dob",wxLIST_FORMAT_LEFT,12);
}

void CustFrame::pop(){
  long index; wxString name;
  for(int i=0; i<10; i++){
    index = cListView->InsertItem(i , "12345678912");
    name = "person " + std::to_string(i);
    cListView->SetItem(index, 1, name);
    cListView->SetItem(index, 2, "1990-20-20");
  }
}
