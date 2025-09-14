#include "../libs/allFrames.hpp"
#include "../libs/db.hpp"
#include "wx/event.h"
#include "wx/string.h"
#include <cstddef>
#include <vector>

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

  searchBar->Bind(wxEVT_TEXT, &CustFrame::onSearch, this);
  
  cListView->Bind(wxEVT_LIST_ITEM_SELECTED, &CustFrame::onListItemSel,this);

  // Bind toolbar to it's event
  mainToolBar->Bind(wxEVT_TOOL, &CustFrame::onTool, this);

  // Bind the close event to the onClose handler
  this->Bind(wxEVT_CLOSE_WINDOW, &CustFrame::onClose, this);

  selID = -1;
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
      break;
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

void CustFrame::onSearch(wxCommandEvent & evt){
  wxString sQuery = searchBar->GetValue().Lower();

  if (sQuery.IsEmpty()) {
    updLV(customers);
    return;
  }

  std::vector<Customer> sResults;
  for(const auto & customer : customers){
    wxString name = wxString(customer.name).Lower();
    wxString uid = wxString::Format("%lld",customer.uid);

    if (name.StartsWith(sQuery) || uid.StartsWith(sQuery)){
      sResults.push_back(customer);
    }
  }
  updLV(sResults);
}


void CustFrame::onListItemSel(wxListEvent & evt){
  long itemIndex = evt.GetItem().GetData();

  if(itemIndex >= 0 && itemIndex < static_cast<long>(customers.size())){
    Customer selCust = customers[itemIndex];
    selID = selCust.uid;
  }
}

void CustFrame::delCust(){
  if(selID == -1){
    wxMessageBox("Select an entry to delete.", "Operational Error");
  }

  wxMessageDialog confirm(this,"Are you sure about deleting this entry ? (no rollbacks !)", "Operational Warning", wxYES_NO | wxICON_QUESTION);
  if (confirm.ShowModal() == wxID_NO) {
    return;
  }
  
  db::crmDB dbObj;
  std::shared_ptr<sql::Connection> conn = dbObj.retconn();
  if(conn){
    std::string err = dbObj.remEntry(conn, db::cust_tbl, selID);
    if (!err.empty()) {
      wxMessageBox("An error occurred while deleting the entry: " + wxString(err), "Error");
    } else {
      populate();
    }
    dbObj.disconnect(conn);
    selID = -1;
  } else {
    wxMessageBox("Database Connection Failed !", "Operational Error");
  }
}

void CustFrame::updLV(const std::vector<Customer> & toShow){
  cListView->DeleteAllItems();

  long listIndex;
  for (size_t originalIndex = 0; originalIndex < toShow.size(); ++originalIndex) {
    for (const auto & cToShow: toShow){
      if (customers[originalIndex].uid == cToShow.uid) {
        wxString uidLV = wxString::Format("%lld", customers[originalIndex].uid);
        cListView->InsertItem(listIndex, uidLV);
        cListView->SetItem(listIndex, 1, customers[originalIndex].name);
        cListView->SetItem(listIndex, 2, customers[originalIndex].dob);
        cListView->SetItemData(listIndex, originalIndex);
        listIndex++;
        break;
      }
    }
  }
}

void CustFrame::populate(){
  customers.clear();

  db::crmDB dbObj;
  std::shared_ptr<sql::Connection> conn = dbObj.retconn();
  
  if(conn){
    customers = dbObj.getEntries<Customer>(conn, db::cust_tbl);
    dbObj.disconnect(conn);
    updLV(customers);
  } else {
    wxMessageBox("Failed to retrieve data from database : Table Empty");
    return;
  }
}

void CustFrame::onClose(wxCloseEvent & evt){
  if(GetParent()){
    GetParent()->Show();
  }
  evt.Skip();
  Destroy();
}
