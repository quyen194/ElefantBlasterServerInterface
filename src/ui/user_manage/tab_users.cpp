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
#include "common/events.hpp"
#include "ui/ui_definitions.hpp"
#include "ui/user_manage/tab_users.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
std::vector<std::pair<int, std::string>> kUserGridColumns = {
  { 100, "Role" },
  { 200, "Username" },
  { 200, "Display Name" },
  { 100, "Status" },
  { 300, "Last Online" },
  { 300, "API Token" },
  { 200, "Ban Reason" },
  { 200, "Banned Until "}
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

TabUsers::TabUsers(wxWindow* parent)
    : wxPanel(
          parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL) {
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
  grid_->CreateGrid(10, kUserGridColumns.size());

  for (int i = 0; i < kUserGridColumns.size(); ++i) {
    grid_->SetColSize(i, kUserGridColumns[i].first);
    grid_->SetColLabelValue(i, kUserGridColumns[i].second);
  }

  grid_->EnableEditing(false);

  auto sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(panel_filter, 0, wxEXPAND | wxALL, 10);
  sizer->Add(grid_, 1, wxEXPAND, 10);
  SetSizer(sizer);
}
// -----------------------------------------------------------------------------

TabUsers::~TabUsers() {}
// -----------------------------------------------------------------------------

void TabUsers::SelectTab() {
  wxThreadEvent evt(EVT_UI_TAB_CHANGED);
  evt.SetInt(TabIndex::kUserManage_Users);
  wxQueueEvent(wxTheApp->GetTopWindow(), evt.Clone());
}
// -----------------------------------------------------------------------------
