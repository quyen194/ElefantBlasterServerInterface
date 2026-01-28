/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/28 07:08
  filename:  ElefantBlaster/ElefantBlasterServerInterface/ui/user_manage/tab_groups.hpp

  purpose:   Implementation file for the user groups management tab
*********************************************************************/


// -----------------------------------------------------------------------------
#include "common/events.hpp"
#include "entities/profile.hpp"
#include "ui/ui_definitions.hpp"
#include "ui/user_manage/tab_groups.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
static std::vector<std::pair<int, std::string>> kColumns = {
  { 200, "Group Name" },
  { 200, "Display Name" },
  { 400, "Description" },
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
TabGroups* TabGroups::instance_ = nullptr;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

TabGroups::TabGroups(wxWindow* parent)
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

  Bind(EVT_NET_GROUPS_LIST_SUCCESS, &TabGroups::OnGroupsListSuccessRespond, this);
  Bind(EVT_NET_GROUPS_LIST_FAILURE, &TabGroups::OnGroupsListFailureRespond, this);

  auto sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(grid_, 1, wxEXPAND, 10);
  SetSizer(sizer);
}
// -----------------------------------------------------------------------------

TabGroups::~TabGroups() {
  instance_ = nullptr;
}
// -----------------------------------------------------------------------------

TabGroups* TabGroups::Instance() {
  return instance_;
}
// -----------------------------------------------------------------------------

void TabGroups::SelectTab() {
  wxThreadEvent evt(EVT_UI_TAB_CHANGED);
  evt.SetInt(TabIndex::kUserManage_Groups);
  wxQueueEvent(wxTheApp->GetTopWindow(), evt.Clone());
}
// -----------------------------------------------------------------------------

void TabGroups::OnGroupsListSuccessRespond(wxThreadEvent& event) {
  grid_->BeginBatch();

  int number_rows = grid_->GetNumberRows();
  if (number_rows > 0) {
    if (number_rows != AuthUser.groups_list.size()) {
      grid_->DeleteRows(0, number_rows);
      grid_->AppendRows(AuthUser.groups_list.size());
    }
    else {
      grid_->ClearGrid();
    }
  }
  else {
    grid_->AppendRows(AuthUser.groups_list.size());
  }

  for (int row = 0; row < AuthUser.groups_list.size(); row++) {
    auto &group = AuthUser.groups_list[row];
    int col = 0;
    grid_->SetCellValue(row, col++, std::string(group.name));
    grid_->SetCellValue(row, col++, std::string(group.display_name));
    grid_->SetCellValue(row, col++, std::string(group.desc));

    if (!group.is_actived) {
      auto rowAttr = new wxGridCellAttr();
      rowAttr->SetBackgroundColour(wxColour(245, 245, 245));
      rowAttr->SetTextColour(wxColour(158, 158, 158));
      grid_->SetRowAttr(row, rowAttr);
    }
    else if (group.is_system) {
      auto rowAttr = new wxGridCellAttr();
      rowAttr->SetBackgroundColour(wxColour(227, 242, 253));
      rowAttr->SetTextColour(wxColour(13, 71, 161));
      grid_->SetRowAttr(row, rowAttr);
    }
  }

  grid_->EndBatch();
}
// -----------------------------------------------------------------------------

void TabGroups::OnGroupsListFailureRespond(wxThreadEvent& event) {
  std::string reason = event.GetString().ToStdString();
  wxMessageBox(reason, "Get groups list failed", wxOK | wxICON_ERROR, this);
}
// -----------------------------------------------------------------------------
