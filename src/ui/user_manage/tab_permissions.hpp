/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/25 07:10
  filename:  ElefantBlaster/ElefantBlasterServerInterface/ui/user_manage/tab_permissions.hpp

  purpose:   Header file for the user permissions management tab
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_SERVER_INTERFACE_UI_USER_MANAGE_TAB_PERMISSIONS_HPP
#define ELEFANT_BLASTER_SERVER_INTERFACE_UI_USER_MANAGE_TAB_PERMISSIONS_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <wx/grid.h>
#include <wx/wx.h>

#include <aries_base/definitions/macro.hpp>
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class TabPermissions : public wxPanel {
 public:
  TabPermissions(wxWindow* parent);
  virtual ~TabPermissions();

  static TabPermissions* Instance();

  void SelectTab();

  void OnPermissionsListSuccessRespond(wxThreadEvent& event);
  void OnPermissionsListFailureRespond(wxThreadEvent& event);

 private:
  wxGrid *grid_;

 private:
  static TabPermissions* instance_;

 private:
  DISALLOW_COPY_AND_ASSIGN(TabPermissions);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_INTERFACE_UI_USER_MANAGE_TAB_PERMISSIONS_HPP
// -----------------------------------------------------------------------------
