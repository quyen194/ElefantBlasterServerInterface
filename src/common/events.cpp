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
wxDEFINE_EVENT(EVT_UI_TAB_CHANGED, wxThreadEvent);
wxDEFINE_EVENT(EVT_SERVER_UPDATE, wxThreadEvent);
// -----------------------------------------------------------------------------
