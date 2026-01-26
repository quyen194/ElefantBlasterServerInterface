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
  PermissionsListData permissions_data = event.GetPayload<PermissionsListData>();

  grid_->BeginBatch();

  int number_rows = grid_->GetNumberRows();
  if (number_rows > 0) {
    if (number_rows != permissions_data.list.size()) {
      grid_->DeleteRows(0, number_rows);
      grid_->AppendRows(permissions_data.list.size());
    }
    else {
      grid_->ClearGrid();
    }
  }
  else {
    grid_->AppendRows(permissions_data.list.size());
  }

  for (int row = 0; row < permissions_data.list.size(); row++) {
    auto &permission = permissions_data.list[row];
    int col = 0;
    grid_->SetCellValue(row, col++, ToString(permission.risk));
    grid_->SetCellValue(row, col++, std::string(permission.name));
    grid_->SetCellValue(row, col++, std::string(permission.desc));

    switch (permission.risk) {
      case RiskLevel::kHigh: {
        auto highRiskAttr = new wxGridCellAttr();
        highRiskAttr->SetBackgroundColour(wxColour(253, 236, 234));
        highRiskAttr->SetTextColour(wxColour(127, 29, 29));
        grid_->SetRowAttr(row, highRiskAttr);
      } break;

      case RiskLevel::kMedium: {
        auto mediumRiskAttr = new wxGridCellAttr();
        mediumRiskAttr->SetBackgroundColour(wxColour(255, 244, 229));
        mediumRiskAttr->SetTextColour(wxColour(146, 64, 14));
        grid_->SetRowAttr(row, mediumRiskAttr);
      } break;

      case RiskLevel::kLow: {
        auto lowRiskAttr = new wxGridCellAttr();
        lowRiskAttr->SetBackgroundColour(wxColour(237, 247, 237));
        lowRiskAttr->SetTextColour(wxColour(27, 94, 32));
        grid_->SetRowAttr(row, lowRiskAttr);
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
