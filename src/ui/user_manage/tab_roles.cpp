/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/27 05:43
  filename:  ElefantBlaster/ElefantBlasterServerInterface/ui/user_manage/tab_roles.hpp

  purpose:   Implementation file for the user roles management tab
*********************************************************************/


// -----------------------------------------------------------------------------
#include "common/events.hpp"
#include "entities/profile.hpp"
#include "ui/ui_definitions.hpp"
#include "ui/user_manage/tab_roles.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
static std::vector<std::pair<int, std::string>> kColumns = {
  { 200, "Role Name" },
  { 200, "Display Name" },
  { 400, "Description" },
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
TabRoles* TabRoles::instance_ = nullptr;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

TabRoles::TabRoles(wxWindow* parent)
    : wxPanel(
          parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL) {
  instance_ = this;

  grid_ = new wxGrid(this, wxID_ANY);
  // set rows and columns
  grid_->CreateGrid(0, kColumns.size());

  for (int i = 0; i < kColumns.size(); ++i) {
    grid_->SetColSize(i, kColumns[i].first);
    grid_->SetColLabelValue(i, kColumns[i].second);
  }

  grid_->EnableEditing(false);

  Bind(EVT_NET_ROLES_LIST_SUCCESS, &TabRoles::OnRolesListSuccessRespond, this);
  Bind(EVT_NET_ROLES_LIST_FAILURE, &TabRoles::OnRolesListFailureRespond, this);

  auto sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(grid_, 1, wxEXPAND, 10);
  SetSizer(sizer);
}
// -----------------------------------------------------------------------------

TabRoles::~TabRoles() {
  instance_ = nullptr;
}
// -----------------------------------------------------------------------------

TabRoles* TabRoles::Instance() {
  return instance_;
}
// -----------------------------------------------------------------------------

void TabRoles::SelectTab() {
  wxThreadEvent evt(EVT_UI_TAB_CHANGED);
  evt.SetInt(TabIndex::kUserManage_Roles);
  wxQueueEvent(wxTheApp->GetTopWindow(), evt.Clone());
}
// -----------------------------------------------------------------------------

void TabRoles::OnRolesListSuccessRespond(wxThreadEvent& event) {
  grid_->BeginBatch();

  int number_rows = grid_->GetNumberRows();
  if (number_rows > 0) {
    if (number_rows != AuthUser.roles_list.size()) {
      grid_->DeleteRows(0, number_rows);
      grid_->AppendRows(AuthUser.roles_list.size());
    }
    else {
      grid_->ClearGrid();
    }
  }
  else {
    grid_->AppendRows(AuthUser.roles_list.size());
  }

  for (int row = 0; row < AuthUser.roles_list.size(); row++) {
    auto &role = AuthUser.roles_list[row];
    int col = 0;
    grid_->SetCellValue(row, col++, std::string(role.name));
    grid_->SetCellValue(row, col++, std::string(role.display_name));
    grid_->SetCellValue(row, col++, std::string(role.desc));

    if (!role.is_actived) {
      auto rowAttr = new wxGridCellAttr();
      rowAttr->SetBackgroundColour(wxColour(245, 245, 245));
      rowAttr->SetTextColour(wxColour(158, 158, 158));
      grid_->SetRowAttr(row, rowAttr);
    }
    else if (role.is_system) {
      auto rowAttr = new wxGridCellAttr();
      rowAttr->SetBackgroundColour(wxColour(227, 242, 253));
      rowAttr->SetTextColour(wxColour(13, 71, 161));
      grid_->SetRowAttr(row, rowAttr);
    }
  }

  grid_->EndBatch();
}
// -----------------------------------------------------------------------------

void TabRoles::OnRolesListFailureRespond(wxThreadEvent& event) {
  std::string reason = event.GetString().ToStdString();
  wxMessageBox(reason, "Get roles list failed", wxOK | wxICON_ERROR, this);
}
// -----------------------------------------------------------------------------
