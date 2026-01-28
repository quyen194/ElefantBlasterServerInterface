/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/08 15:00
  filename:  ElefantBlaster/ElefantBlasterServerInterface/common/events.cpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#include "common/events.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
wxDEFINE_EVENT(EVT_NET_CONNECTED, wxThreadEvent);
wxDEFINE_EVENT(EVT_NET_RECONNECT, wxThreadEvent);
// -----------------------------------------------------------------------------
wxDEFINE_EVENT(EVT_UI_LOGIN_SUBMIT, wxThreadEvent);
wxDEFINE_EVENT(EVT_NET_LOGIN_APPROVED, wxThreadEvent);
wxDEFINE_EVENT(EVT_NET_LOGIN_REJECTED, wxThreadEvent);
// -----------------------------------------------------------------------------
wxDEFINE_EVENT(EVT_UI_MENU_FILE_LOGOUT, wxThreadEvent);
wxDEFINE_EVENT(EVT_UI_MENU_ADMIN_SERVER_SHUTDOWN, wxThreadEvent);
wxDEFINE_EVENT(EVT_UI_MENU_ADMIN_SERVER_RESTART, wxThreadEvent);
wxDEFINE_EVENT(EVT_UI_MENU_GAME_SERVER_ACTIVE, wxThreadEvent);
wxDEFINE_EVENT(EVT_UI_MENU_GAME_SERVER_DEACTIVE, wxThreadEvent);
wxDEFINE_EVENT(EVT_UI_MENU_GAME_SERVER_DISCONNECT_ALL_CLIENTS, wxThreadEvent);
wxDEFINE_EVENT(EVT_UI_TAB_CHANGED, wxThreadEvent);
// -----------------------------------------------------------------------------
wxDEFINE_EVENT(EVT_UI_REQUEST_USERS_LIST, wxThreadEvent);
wxDEFINE_EVENT(EVT_NET_USERS_LIST_SUCCESS, wxThreadEvent);
wxDEFINE_EVENT(EVT_NET_USERS_LIST_FAILURE, wxThreadEvent);
// -----------------------------------------------------------------------------
wxDEFINE_EVENT(EVT_UI_REQUEST_GROUPS_LIST, wxThreadEvent);
wxDEFINE_EVENT(EVT_NET_GROUPS_LIST_SUCCESS, wxThreadEvent);
wxDEFINE_EVENT(EVT_NET_GROUPS_LIST_FAILURE, wxThreadEvent);
// -----------------------------------------------------------------------------
wxDEFINE_EVENT(EVT_UI_REQUEST_ROLES_LIST, wxThreadEvent);
wxDEFINE_EVENT(EVT_NET_ROLES_LIST_SUCCESS, wxThreadEvent);
wxDEFINE_EVENT(EVT_NET_ROLES_LIST_FAILURE, wxThreadEvent);
// -----------------------------------------------------------------------------
wxDEFINE_EVENT(EVT_UI_REQUEST_PERMISSIONS_LIST, wxThreadEvent);
wxDEFINE_EVENT(EVT_NET_PERMISSIONS_LIST_SUCCESS, wxThreadEvent);
wxDEFINE_EVENT(EVT_NET_PERMISSIONS_LIST_FAILURE, wxThreadEvent);
// -----------------------------------------------------------------------------
