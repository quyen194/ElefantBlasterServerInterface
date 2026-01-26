/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/03 11:51
  filename:  ElefantBlaster/ElefantBlasterServerInterface/ui/user_manage/tab_users.cpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#include <aries_base/utils/times.hpp>

#include "common/events.hpp"
#include "entities/profile.hpp"
#include "ui/ui_definitions.hpp"
#include "ui/user_manage/tab_users.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
static std::vector<std::pair<int, std::string>> kColumns = {
  { 100, "Role" },
  { 200, "Username" },
  { 200, "Display Name" },
  { 100, "Status" },
  { 300, "Last Online" },
  { 300, "API Token" },
  { 200, "Ban Reason" },
  { 200, "Banned Until "},
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
TabUsers* TabUsers::instance_ = nullptr;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

TabUsers::TabUsers(wxWindow* parent)
    : wxPanel(
          parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL) {
  instance_ = this;

  auto panel_filter = new wxPanel(this, wxID_ANY);
  auto panel_filter_sizer = new wxBoxSizer(wxHORIZONTAL);

  auto lbl_filter_name = new wxStaticText(panel_filter, wxID_ANY, "Name");
  txt_filter_name_ = new wxTextCtrl(panel_filter, wxID_ANY, wxEmptyString);
  txt_filter_name_->SetMinSize(wxSize(200, -1));
  txt_filter_name_->SetMaxSize(wxSize(500, -1));
  chk_filter_online_ = new wxCheckBox(panel_filter, wxID_ANY, "Online");
  chk_filter_banned_ = new wxCheckBox(panel_filter, wxID_ANY, "Banned");
  btn_filter_apply_ = new wxButton(panel_filter, wxID_ANY, "Apply");

  panel_filter_sizer->Add(lbl_filter_name, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxLEFT | wxRIGHT, 10);
  panel_filter_sizer->Add(txt_filter_name_, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxLEFT | wxRIGHT, 10);
  panel_filter_sizer->Add(chk_filter_online_, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxLEFT | wxRIGHT, 10);
  panel_filter_sizer->Add(chk_filter_banned_, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxLEFT | wxRIGHT, 10);
  panel_filter_sizer->Add(btn_filter_apply_, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxLEFT | wxRIGHT, 10);

  panel_filter->SetSizer(panel_filter_sizer);

  grid_ = new wxGrid(this, wxID_ANY);
  // set rows and columns
  grid_->CreateGrid(0, kColumns.size());

  for (int i = 0; i < kColumns.size(); ++i) {
    grid_->SetColSize(i, kColumns[i].first);
    grid_->SetColLabelValue(i, kColumns[i].second);
  }

  grid_->EnableEditing(false);

  Bind(EVT_NET_USERS_LIST_SUCCESS, &TabUsers::OnUsersListSuccessRespond, this);
  Bind(EVT_NET_USERS_LIST_FAILURE, &TabUsers::OnUsersListFailureRespond, this);

  auto sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(panel_filter, 0, wxEXPAND | wxALL, 10);
  sizer->Add(grid_, 1, wxEXPAND, 10);
  SetSizer(sizer);
}
// -----------------------------------------------------------------------------

TabUsers::~TabUsers() {
  instance_ = nullptr;
}
// -----------------------------------------------------------------------------

TabUsers* TabUsers::Instance() {
  return instance_;
}
// -----------------------------------------------------------------------------

void TabUsers::SelectTab() {
  wxThreadEvent evt(EVT_UI_TAB_CHANGED);
  evt.SetInt(TabIndex::kUserManage_Users);
  wxQueueEvent(wxTheApp->GetTopWindow(), evt.Clone());
}
// -----------------------------------------------------------------------------

void TabUsers::OnUsersListSuccessRespond(wxThreadEvent& event) {
  auto fnGetStatus = [](User &user) -> std::string {
    if (!user.is_actived) {
      return "Inactive";
    }
    if (user.is_banned) {
      return "Banned";
    }
    if (user.last_online_at && user.last_online_at > utils::EpocTime() - 60) {
      return "Online";
    }
    return "Offline";
  };

  grid_->BeginBatch();

  int number_rows = grid_->GetNumberRows();
  if (number_rows > 0) {
    if (number_rows != AuthUser.users_list.size()) {
      grid_->DeleteRows(0, number_rows);
      grid_->AppendRows(AuthUser.users_list.size());
    }
    else {
      grid_->ClearGrid();
    }
  }
  else {
    grid_->AppendRows(AuthUser.users_list.size());
  }

  for (int row = 0; row < AuthUser.users_list.size(); row++) {
    auto &user = AuthUser.users_list[row];
    int col = 0;
    grid_->SetCellValue(row, col++, ToString(user.type));
    grid_->SetCellValue(row, col++, user.username);
    grid_->SetCellValue(row, col++, user.display_name);
    grid_->SetCellValue(row, col++, fnGetStatus(user));
    grid_->SetCellValue(
        row,
        col++,
        user.last_online_at ? utils::time::ToString(user.last_online_at) : "");
    grid_->SetCellValue(row, col++, user.api_token);
    grid_->SetCellValue(row, col++, user.ban_reason);
    grid_->SetCellValue(
        row,
        col++,
        user.banned_until ? utils::time::ToString(user.banned_until) : "");
  }

  grid_->EndBatch();
}
// -----------------------------------------------------------------------------

void TabUsers::OnUsersListFailureRespond(wxThreadEvent& event) {
  std::string reason = event.GetString().ToStdString();
  wxMessageBox(reason, "Get users list failed", wxOK | wxICON_ERROR, this);
}
// -----------------------------------------------------------------------------
