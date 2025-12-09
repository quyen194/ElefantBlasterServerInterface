/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/15 05:13
  filename:  ElefantBlaster/ElefantBlasterServerInterface/entrypoint/entrypoint.cpp

  purpose:   Entry point for the Elefant Blaster Server Interface application
*********************************************************************/


// -----------------------------------------------------------------------------
#include "control/process_control.hpp"
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#if defined(_WIN32)
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif  // _WIN32
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
wxIMPLEMENT_APP(ProcessControl);
// -----------------------------------------------------------------------------
