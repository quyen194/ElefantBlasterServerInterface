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
#include "ui/user_manage/tab_users.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

TabUsers::TabUsers(wxWindow* parent)
    : wxPanel(
          parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL) {
  grid_ = new wxGrid(this, wxID_ANY);
  // set rows and columns
  grid_->CreateGrid(10, 7);

  int i = 0;
  grid_->SetColLabelValue(i++, "Role");
  grid_->SetColLabelValue(i++, "Username");
  grid_->SetColLabelValue(i++, "Display Name");
  grid_->SetColLabelValue(i++, "API Token");
  grid_->SetColLabelValue(i++, "Status");
  grid_->SetColLabelValue(i++, "Ban Reason");
  grid_->SetColLabelValue(i++, "Banned Until");

  auto sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(grid_, 1, wxEXPAND | wxALL);
  SetSizer(sizer);
}
// -----------------------------------------------------------------------------

TabUsers::~TabUsers() {}
// -----------------------------------------------------------------------------
