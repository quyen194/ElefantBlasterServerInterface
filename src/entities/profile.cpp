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
