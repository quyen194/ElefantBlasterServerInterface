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
#include <map>

#include <wx/wx.h>
#include <wx/notebook.h>

#include <aries_base/definitions/macro.hpp>

#include "ui/ui_definitions.hpp"
#include "ui/user_manage/tab_users.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class TabUserManage : public wxPanel {
 public:
  TabUserManage(wxWindow* parent);
  virtual ~TabUserManage();

 private:
  void OnNotebookPageChanged(wxBookCtrlEvent& event);

 private:
  TabUsers *tab_users_;

  std::map<int, TabIndex> tab_ids_;

 private:
  DISALLOW_COPY_AND_ASSIGN(TabUserManage);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_INTERFACE_UI_TAB_USER_MANAGE_HPP
// -----------------------------------------------------------------------------
