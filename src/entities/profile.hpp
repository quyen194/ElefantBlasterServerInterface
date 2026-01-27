/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/20 05:35
  filename:  ElefantBlaster/ElefantBlasterServerInterface/entities/profile.hpp

  purpose:   Header file for profile entity
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_SERVER_ENTITIES_PROFILE_HPP
#define ELEFANT_BLASTER_SERVER_ENTITIES_PROFILE_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <set>
#include <string>
#include <vector>

#include <entities/user.hpp>
#include <entities/role.hpp>
#include <entities/permission.hpp>
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

struct Profile {
 public:
  static Profile& Instance();
  void Clear();

 public:
  bool authorized;
  std::string username;
  std::string password;
  std::string display_name;
  std::set<std::string> permissions;

  std::vector<User> users_list;
  std::vector<Role> roles_list;
  std::vector<Permission> permissions_list;
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#define AuthUser Profile::Instance()
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_ENTITIES_PROFILE_HPP
// -----------------------------------------------------------------------------
