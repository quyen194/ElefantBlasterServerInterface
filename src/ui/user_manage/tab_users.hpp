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

  static TabUsers* Instance();

  inline wxGrid* GetGrid() { return grid_; }

  void SelectTab();

  void OnUsersListSuccessRespond(wxThreadEvent& event);
  void OnUsersListFailureRespond(wxThreadEvent& event);

 private:
  wxTextCtrl *txt_filter_name_;
  wxCheckBox *chk_filter_online_;
  wxCheckBox *chk_filter_banned_;
  wxButton *btn_filter_apply_;
  wxGrid *grid_;

 private:
  static TabUsers* instance_;

 private:
  DISALLOW_COPY_AND_ASSIGN(TabUsers);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_INTERFACE_UI_USER_MANAGE_TAB_USERS_HPP
// -----------------------------------------------------------------------------
