#include "../libs/allFrames.hpp"
#include "wx/event.h"
#include "wx/listbase.h"
#include <string>

CustFrame::CustFrame(wxWindow * parent)
          :wxFrame(parent, wxID_ANY, "Manage Customers")
{

  mainSizer = new wxBoxSizer(wxVERTICAL);

  searchBar = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
  cListView = new wxListView(this);

  mainSizer->Add(searchBar, 0, wxALL | wxEXPAND,10);
  mainSizer->Add(cListView, 1, wxALL | wxEXPAND, 10);
  this->SetSizerAndFit(mainSizer);

  custCols();
  //pop();
  cListView->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
}

void CustFrame::custCols(){
  cListView->AppendColumn("uid",wxLIST_FORMAT_LEFT,110);
  cListView->AppendColumn("name",wxLIST_FORMAT_LEFT);
  cListView->AppendColumn("dob",wxLIST_FORMAT_LEFT,90);
}

void CustFrame::pop(){
  customers.clear();
  cListView->DeleteAllItems();
  
  long index; wxString name;
  for(int i=0; i<10; i++){
    Customer c;
    c.uid = std::to_string(12345678901 + i);
    c.name = "person " + std::to_string(i);
    c.dob = "2000-01-" + std::to_string(i);
    customers.push_back(c);
  }
  for(size_t i = 0; i < customers.size(); ++i){
    index = cListView->InsertItem(i , customers[i].uid);
    cListView->SetItem(index, 1, customers[i].name);
    cListView->SetItem(index, 2, customers[i].dob);
  }
}

void CustFrame::onClose(wxCloseEvent & evt){
  // if(GetParent()){
    GetParent()->Show();
  // }
  evt.Skip();
  Destroy();
}
