/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/20 05:39
  filename:  ElefantBlasterServerInterface/src/entities/profile.cpp

  purpose:   Implementation file for profile entity
*********************************************************************/


// -----------------------------------------------------------------------------
#include "entities/profile.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

Profile& Profile::Instance() {
  static Profile instance;
  return instance;
}
// -----------------------------------------------------------------------------

void Profile::Clear() {
  authorized = false;
  username.clear();
  password.clear();
  display_name.clear();
  permissions.clear();
  users_list.clear();
  groups_list.clear();
  roles_list.clear();
  permissions_list.clear();
}
// -----------------------------------------------------------------------------
