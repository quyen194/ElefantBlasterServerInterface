/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/27 05:43
  filename:  ElefantBlaster/ElefantBlasterServerInterface/ui/user_manage/tab_roles.hpp

  purpose:   Header file for the user roles management tab
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_SERVER_INTERFACE_UI_USER_MANAGE_TAB_ROLES_HPP
#define ELEFANT_BLASTER_SERVER_INTERFACE_UI_USER_MANAGE_TAB_ROLES_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <wx/grid.h>
#include <wx/wx.h>

#include <aries_base/definitions/macro.hpp>
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class TabRoles : public wxPanel {
 public:
  TabRoles(wxWindow* parent);
  virtual ~TabRoles();

  static TabRoles* Instance();

  void SelectTab();

  void OnRolesListSuccessRespond(wxThreadEvent& event);
  void OnRolesListFailureRespond(wxThreadEvent& event);

 private:
  wxGrid *grid_;

 private:
  static TabRoles* instance_;

 private:
  DISALLOW_COPY_AND_ASSIGN(TabRoles);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_INTERFACE_UI_USER_MANAGE_TAB_ROLES_HPP
// -----------------------------------------------------------------------------
