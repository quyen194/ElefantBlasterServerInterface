/********************************************************************
  Copyright 2025, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/12/18 18:42
  filename:  ElefantBlaster/ElefantBlasterServerInterface/control/process_control.hpp

  purpose:   Header file for the main application class
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_SERVER_INTERFACE_CONTROL_PROCESS_CONTROL_HPP
#define ELEFANT_BLASTER_SERVER_INTERFACE_CONTROL_PROCESS_CONTROL_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <wx/wx.h>

#include <aries_base/definitions/macro.hpp>

#include "ui/main_frame.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class ProcessControl : public wxApp {
 public:
  ProcessControl();
  virtual ~ProcessControl();

  virtual bool OnInit() override;
  virtual int OnExit() override;

 private:
  MainFrame* main_frame_;

 private:
  DISALLOW_COPY_AND_ASSIGN(ProcessControl);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_INTERFACE_CONTROL_PROCESS_CONTROL_HPP
// -----------------------------------------------------------------------------
