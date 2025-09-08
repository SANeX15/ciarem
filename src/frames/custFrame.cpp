#include "../libs/allFrames.hpp"

CustFrame::CustFrame(wxWindow * parent)
          :wxFrame(parent, wxID_ANY, "Manage Customers")
{

  mainSizer = new wxBoxSizer(wxVERTICAL);

  searchBar = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
  cListView = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
  mainToolBar = CreateToolBar();

  mainToolBar->AddTool(crm_cust_addBtn, "New Customer", wxArtProvider::GetBitmap(wxART_NEW,wxART_TOOLBAR), "Creates a Customer Entry");
  mainToolBar->Realize();

  searchBar->SetHint("Search Customer by Name or UID");
  mainSizer->Add(searchBar, 0, wxALL | wxEXPAND,10);
  mainSizer->Add(cListView, 1, wxALL | wxEXPAND, 10);
  this->SetSizerAndFit(mainSizer);

  // Bind toolbar to it's event
  mainToolBar->Bind(wxEVT_TOOL, &CustFrame::onTool, this);

  // Bind the close event to the onClose handler
  this->Bind(wxEVT_CLOSE_WINDOW, &CustFrame::onClose, this);

  custCols();
  pop();
  cListView->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
}

void CustFrame::onTool(wxCommandEvent & evt){
  int id = evt.GetId();
  switch(id){
    case crm_cust_addBtn:
      break;
    default:
      break;
  }
}

void CustFrame::custCols(){
  cListView->AppendColumn("uid", wxLIST_FORMAT_LEFT, 110);
  cListView->AppendColumn("name", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE_USEHEADER);
  cListView->AppendColumn("dob", wxLIST_FORMAT_LEFT, 90);
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
