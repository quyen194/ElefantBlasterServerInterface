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
  notebook_ = new wxNotebook(this, wxID_ANY);
  notebook_->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED,
                 &TabUserManage::OnNotebookPageChanged,
                 this);

  if (HasPermission(AuthUser.permissions, permission::user::view)) {
    tab_users_ = new TabUsers(notebook_);
    notebook_->AddPage(tab_users_, "Users");
    tab_ids_[tab_users_] = TabIndex::kUserManage_Users;
  }

  if (HasPermission(AuthUser.permissions, permission::role::all) ||
      HasPermission(AuthUser.permissions, permission::role::view)) {
    tab_roles_ = new TabRoles(notebook_);
    notebook_->AddPage(tab_roles_, "Roles");
    tab_ids_[tab_roles_] = TabIndex::kUserManage_Roles;
  }

  if (HasPermission(AuthUser.permissions, permission::self::all) ||
      HasPermission(AuthUser.permissions, permission::self::view_high_risk) ||
      HasPermission(AuthUser.permissions, permission::self::view_medium_risk) ||
      HasPermission(AuthUser.permissions, permission::self::view_low_risk)) {
    tab_permissions_ = new TabPermissions(notebook_);
    notebook_->AddPage(tab_permissions_, "Permissions");
    tab_ids_[tab_permissions_] = TabIndex::kUserManage_Permissions;
  }

  auto sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(notebook_, 1, wxEXPAND);
  SetSizer(sizer);

  wxNotebookEvent evt(wxEVT_NOTEBOOK_PAGE_CHANGED,
                      notebook_->GetId(),
                      0,           // new page = first tab
                      wxNOT_FOUND  // old page
  );
  evt.SetEventObject(notebook_);

  // Send async (simulate user click)
  wxPostEvent(notebook_->GetEventHandler(), evt);
}
// -----------------------------------------------------------------------------

TabUserManage::~TabUserManage() {}
// -----------------------------------------------------------------------------

void TabUserManage::OnNotebookPageChanged(wxBookCtrlEvent& event) {
  int newPage = event.GetSelection();

  if (newPage != wxNOT_FOUND) {
    auto panel = dynamic_cast<wxPanel*>(notebook_->GetPage(newPage));
    switch (tab_ids_[panel]) {
      case TabIndex::kUserManage_Users:
        tab_users_->SelectTab();
        break;

      case TabIndex::kUserManage_Roles:
        tab_roles_->SelectTab();
        break;

      case TabIndex::kUserManage_Permissions:
        tab_permissions_->SelectTab();
        break;

      default:
        return;
    }
  }

  // Handle page change if needed
  event.Skip();
}
// -----------------------------------------------------------------------------

