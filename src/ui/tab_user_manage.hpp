/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/02 15:40
  filename:  ElefantBlaster/ElefantBlasterServerInterface/ui/tab_user_manage.hpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_SERVER_INTERFACE_UI_TAB_USER_MANAGE_HPP
#define ELEFANT_BLASTER_SERVER_INTERFACE_UI_TAB_USER_MANAGE_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <wx/notebook.h>
#include <wx/wx.h>

#include <aries_base/definitions/macro.hpp>

#include "ui/user_manage/tab_users.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class TabUserManage : public wxPanel {
 public:
  TabUserManage(wxWindow* parent)
      : wxPanel(parent,
                wxID_ANY,
                wxDefaultPosition,
                wxDefaultSize,
                wxTAB_TRAVERSAL) {
    auto notebook = new wxNotebook(this, wxID_ANY);

    notebook->AddPage(new TabUsers(notebook), "Users");

    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(notebook, 1, wxEXPAND | wxALL);
    SetSizer(sizer);
  }
  virtual ~TabUserManage() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(TabUserManage);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_INTERFACE_UI_TAB_USER_MANAGE_HPP
// -----------------------------------------------------------------------------
