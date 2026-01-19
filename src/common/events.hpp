/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/04 15:41
  filename:  ElefantBlaster/ElefantBlasterServerInterface/common/events.hpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_SERVER_INTERFACE_COMMON_EVENTS_HPP
#define ELEFANT_BLASTER_SERVER_INTERFACE_COMMON_EVENTS_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <set>
#include <string>

#include <wx/wx.h>
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
wxDECLARE_EVENT(EVT_NET_CONNECTED, wxThreadEvent);
wxDECLARE_EVENT(EVT_NET_RECONNECT, wxThreadEvent);
// -----------------------------------------------------------------------------
struct LoginSubmitParams {
  std::string username;
  std::string password;
};
wxDECLARE_EVENT(EVT_UI_LOGIN_SUBMIT, wxThreadEvent);
// -----------------------------------------------------------------------------
struct LoginResponseData {
  std::string display_name;
  std::set<std::string> permissions;
};
wxDECLARE_EVENT(EVT_NET_LOGIN_APPROVED, wxThreadEvent);
wxDECLARE_EVENT(EVT_NET_LOGIN_REJECTED, wxThreadEvent);
// -----------------------------------------------------------------------------
wxDECLARE_EVENT(EVT_UI_MENU_ADMIN_SERVER_SHUTDOWN, wxThreadEvent);
wxDECLARE_EVENT(EVT_UI_MENU_ADMIN_SERVER_RESTART, wxThreadEvent);
wxDECLARE_EVENT(EVT_UI_MENU_GAME_SERVER_ACTIVE, wxThreadEvent);
wxDECLARE_EVENT(EVT_UI_MENU_GAME_SERVER_DEACTIVE, wxThreadEvent);
wxDECLARE_EVENT(EVT_UI_MENU_GAME_SERVER_DISCONNECT_ALL_CLIENTS, wxThreadEvent);
wxDECLARE_EVENT(EVT_UI_TAB_CHANGED, wxThreadEvent);
wxDECLARE_EVENT(EVT_SERVER_UPDATE, wxThreadEvent);
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_INTERFACE_COMMON_EVENTS_HPP
// -----------------------------------------------------------------------------
