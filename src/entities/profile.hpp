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
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

struct Profile {
 public:
  static Profile& Instance();

 public:
  std::string display_name;
  std::set<std::string> permissions;
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_ENTITIES_PROFILE_HPP
// -----------------------------------------------------------------------------
