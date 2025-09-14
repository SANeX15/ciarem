#include "../libs/allFrames.hpp"
#include "../libs/db.hpp"
#include "wx/listbase.h"

CustFrame::CustFrame(wxWindow * parent)
          :wxFrame(parent, wxID_ANY, "Manage Customers")
{

  mainSizer = new wxBoxSizer(wxVERTICAL);

  searchBar = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
  cListView = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
  mainToolBar = CreateToolBar();

  mainToolBar->AddTool(crm_cust_addBtn, "New Customer", wxArtProvider::GetBitmap(wxART_NEW,wxART_TOOLBAR), "Creates a Customer Entry");
  mainToolBar->AddTool(crm_cust_relBtn, "Reload Entries", wxArtProvider::GetBitmap(wxART_REFRESH,wxART_TOOLBAR), "Refresh the list for new entries");
  mainToolBar->AddTool(crm_cust_delBtn, "Delete Customer", wxArtProvider::GetBitmap(wxART_DELETE, wxART_TOOLBAR), "Deletes a Customer Entry");
  mainToolBar->Realize();

  searchBar->SetHint("Search Customer by Name or UID");
  mainSizer->Add(searchBar, 0, wxALL | wxEXPAND,10);
  mainSizer->Add(cListView, 1, wxALL | wxEXPAND, 10);
  this->SetSizerAndFit(mainSizer);

  cListView->Bind(wxEVT_LIST_ITEM_SELECTED, &CustFrame::onListItemSel,this);

  // Bind toolbar to it's event
  mainToolBar->Bind(wxEVT_TOOL, &CustFrame::onTool, this);

  // Bind the close event to the onClose handler
  this->Bind(wxEVT_CLOSE_WINDOW, &CustFrame::onClose, this);

  custCols();
  populate();
  cListView->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
}

void CustFrame::onTool(wxCommandEvent & evt){
  int id = evt.GetId();
  switch(id){
    case crm_cust_addBtn:
      cf = new CustForm(this, true);
      cf->Show();
      break;
    case crm_cust_relBtn:
      populate();
      break;
    case crm_cust_delBtn:
      delCust();
    default:
      evt.Skip();
      break;
  }
}

void CustFrame::custCols(){
  cListView->AppendColumn("uid", wxLIST_FORMAT_LEFT, 110);
  cListView->AppendColumn("name", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE_USEHEADER);
  cListView->AppendColumn("dob", wxLIST_FORMAT_LEFT, 90);
}

void CustFrame::onListItemSel(wxListEvent & evt){
  long itemIndex = evt.GetItem().GetId();

  if(itemIndex > 0 && itemIndex < static_cast<long>(customers.size())){
    Customer selCust = customers[itemIndex];
    selID = std::stol(selCust.uid);
  }
}

void CustFrame::delCust(){
  db::crmDB dbObj;
  std::shared_ptr<sql::Connection> conn = dbObj.retconn();
  if(conn){
    if (selID != 0) {
      dbObj.remEntry(conn, db::cust_tbl,selID);
    }
  }
}

void CustFrame::populate(){
  customers.clear();
  cListView->DeleteAllItems();

  db::crmDB dbObj;
  std::shared_ptr<sql::Connection> conn = dbObj.retconn();
  if(conn){
    customers = dbObj.getEntries<Customer>(conn, db::cust_tbl);
    dbObj.disconnect(conn);

    if (customers.empty()) {
      wxMessageBox("No entries found in the customer table.", "Info");
      return;
    }

    long index;
    for(size_t i = 0; i < customers.size(); ++i){
      index = cListView->InsertItem(i, customers[i].uid);
      cListView->SetItem(index, 1, customers[i].name);
      cListView->SetItem(index, 2, customers[i].dob);
    }
  } else {
    wxMessageBox("Failed to retrieve data from database : Table Empty");
    return;
  }
}

void CustFrame::onClose(wxCloseEvent & evt){
  // if(GetParent()){
    GetParent()->Show();
  // }
  evt.Skip();
  Destroy();
}
