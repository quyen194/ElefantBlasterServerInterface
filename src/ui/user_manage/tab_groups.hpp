/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/28 07:08
  filename:  ElefantBlaster/ElefantBlasterServerInterface/ui/user_manage/tab_roles.hpp

  purpose:   Header file for the user roles management tab
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_SERVER_INTERFACE_UI_USER_MANAGE_TAB_GROUPS_HPP
#define ELEFANT_BLASTER_SERVER_INTERFACE_UI_USER_MANAGE_TAB_GROUPS_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <wx/grid.h>
#include <wx/wx.h>

#include <aries_base/definitions/macro.hpp>
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class TabGroups : public wxPanel {
 public:
  TabGroups(wxWindow* parent);
  virtual ~TabGroups();

  static TabGroups* Instance();

  void SelectTab();

  void OnGroupsListSuccessRespond(wxThreadEvent& event);
  void OnGroupsListFailureRespond(wxThreadEvent& event);

 private:
  wxGrid *grid_;

 private:
  static TabGroups* instance_;

 private:
  DISALLOW_COPY_AND_ASSIGN(TabGroups);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_INTERFACE_UI_USER_MANAGE_TAB_GROUPS_HPP
// -----------------------------------------------------------------------------
