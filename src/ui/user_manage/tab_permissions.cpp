/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/25 07:22
  filename:  ElefantBlaster/ElefantBlasterServerInterface/ui/user_manage/tab_permissions.hpp

  purpose:   Implementation file for the user permissions management tab
*********************************************************************/


// -----------------------------------------------------------------------------
#include "common/events.hpp"
#include "entities/profile.hpp"
#include "ui/ui_definitions.hpp"
#include "ui/user_manage/tab_permissions.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
static std::vector<std::pair<int, std::string>> kColumns = {
  { 100, "Risk Level" },
  { 300, "Name" },
  { 400, "Description" },
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
TabPermissions* TabPermissions::instance_ = nullptr;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

TabPermissions::TabPermissions(wxWindow* parent)
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

  Bind(EVT_NET_PERMISSIONS_LIST_SUCCESS, &TabPermissions::OnPermissionsListSuccessRespond, this);
  Bind(EVT_NET_PERMISSIONS_LIST_FAILURE, &TabPermissions::OnPermissionsListFailureRespond, this);

  auto sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(grid_, 1, wxEXPAND, 10);
  SetSizer(sizer);
}
// -----------------------------------------------------------------------------

TabPermissions::~TabPermissions() {
  instance_ = nullptr;
}
// -----------------------------------------------------------------------------

TabPermissions* TabPermissions::Instance() {
  return instance_;
}
// -----------------------------------------------------------------------------

void TabPermissions::SelectTab() {
  wxThreadEvent evt(EVT_UI_TAB_CHANGED);
  evt.SetInt(TabIndex::kUserManage_Permissions);
  wxQueueEvent(wxTheApp->GetTopWindow(), evt.Clone());
}
// -----------------------------------------------------------------------------

void TabPermissions::OnPermissionsListSuccessRespond(wxThreadEvent& event) {
  grid_->BeginBatch();

  int number_rows = grid_->GetNumberRows();
  if (number_rows > 0) {
    if (number_rows != AuthUser.permissions_list.size()) {
      grid_->DeleteRows(0, number_rows);
      grid_->AppendRows(AuthUser.permissions_list.size());
    }
    else {
      grid_->ClearGrid();
    }
  }
  else {
    grid_->AppendRows(AuthUser.permissions_list.size());
  }

  for (int row = 0; row < AuthUser.permissions_list.size(); row++) {
    auto &permission = AuthUser.permissions_list[row];
    int col = 0;
    grid_->SetCellValue(row, col++, ToString(permission.risk));
    grid_->SetCellValue(row, col++, std::string(permission.name));
    grid_->SetCellValue(row, col++, std::string(permission.desc));

    switch (permission.risk) {
      case RiskLevel::kHigh: {
        auto rowAttr = new wxGridCellAttr();
        rowAttr->SetBackgroundColour(wxColour(253, 236, 234));
        rowAttr->SetTextColour(wxColour(127, 29, 29));
        grid_->SetRowAttr(row, rowAttr);
      } break;

      case RiskLevel::kMedium: {
        auto rowAttr = new wxGridCellAttr();
        rowAttr->SetBackgroundColour(wxColour(255, 244, 229));
        rowAttr->SetTextColour(wxColour(146, 64, 14));
        grid_->SetRowAttr(row, rowAttr);
      } break;

      case RiskLevel::kLow: {
        auto rowAttr = new wxGridCellAttr();
        rowAttr->SetBackgroundColour(wxColour(237, 247, 237));
        rowAttr->SetTextColour(wxColour(27, 94, 32));
        grid_->SetRowAttr(row, rowAttr);
      } break;
    }
  }

  grid_->EndBatch();
}
// -----------------------------------------------------------------------------

void TabPermissions::OnPermissionsListFailureRespond(wxThreadEvent& event) {
  std::string reason = event.GetString().ToStdString();
  wxMessageBox(reason, "Get permissions list failed", wxOK | wxICON_ERROR, this);
}
// -----------------------------------------------------------------------------
