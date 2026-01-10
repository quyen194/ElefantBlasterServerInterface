/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/03 08:34
  filename:  ElefantBlaster/ElefantBlasterServerInterface/ui/user_manage/tab_users.hpp

  purpose:   Header file for the user management tab
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_SERVER_INTERFACE_UI_USER_MANAGE_TAB_USERS_HPP
#define ELEFANT_BLASTER_SERVER_INTERFACE_UI_USER_MANAGE_TAB_USERS_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <wx/grid.h>
#include <wx/notebook.h>
#include <wx/wx.h>

#include <aries_base/definitions/macro.hpp>
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class TabUsers : public wxPanel {
 public:
  TabUsers(wxWindow* parent);
  virtual ~TabUsers();

 private:
  wxGrid *grid_;

 private:
  DISALLOW_COPY_AND_ASSIGN(TabUsers);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_INTERFACE_UI_USER_MANAGE_TAB_USERS_HPP
// -----------------------------------------------------------------------------
