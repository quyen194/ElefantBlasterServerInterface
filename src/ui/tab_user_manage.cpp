/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/04 07:30
  filename:  ElefantBlasterServer/ElefantBlasterServerInterface/ui/tab_user_manage.cpp

  purpose:   Implementation file for the user management tab
*********************************************************************/


// -----------------------------------------------------------------------------
#include <wx/notebook.h>

#include <entities/permission_list.hpp>

#include "entities/profile.hpp"
#include "ui/tab_user_manage.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

TabUserManage::TabUserManage(wxWindow* parent)
    : wxPanel(parent,
              wxID_ANY,
              wxDefaultPosition,
              wxDefaultSize,
              wxTAB_TRAVERSAL) {
  int key;

  auto notebook = new wxNotebook(this, wxID_ANY);
  notebook->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED,
                 &TabUserManage::OnNotebookPageChanged,
                 this);

  bool selected = false;

  if (HasPermission(AuthUser.permissions, permission::user::view)) {
    tab_users_ = new TabUsers(notebook);
    key = notebook->AddPage(tab_users_, "Users");
    tab_ids_[key] = TabIndex::kUserManage_Users;

    if (!selected) {
      selected = true;

      wxNotebookEvent evt(wxEVT_NOTEBOOK_PAGE_CHANGED,
                          notebook->GetId(),
                          key,  // new page
                          0     // old page
      );
      evt.SetEventObject(notebook);

      // Send async (simulate user click)
      wxPostEvent(notebook->GetEventHandler(), evt);
    }
  }

  auto sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(notebook, 1, wxEXPAND);
  SetSizer(sizer);
}
// -----------------------------------------------------------------------------

TabUserManage::~TabUserManage() {}
// -----------------------------------------------------------------------------

void TabUserManage::OnNotebookPageChanged(wxBookCtrlEvent& event) {
  int newPage = event.GetSelection();

  switch (tab_ids_[newPage]) {
    case TabIndex::kUserManage_Users:
      tab_users_->SelectTab();
      break;

    default:
      return;
  }

  // Handle page change if needed
  event.Skip();
}
// -----------------------------------------------------------------------------

