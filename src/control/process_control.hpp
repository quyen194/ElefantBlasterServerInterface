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

#include <spdlog/spdlog.h>

#include <aries_base/definitions/macro.hpp>

#include "common/settings_manager.hpp"
#include "network/admin_client.hpp"
#include "ui/login_frame.hpp"
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
  void OnNetConnected(wxThreadEvent& event);
  void OnNetReconnect(wxThreadEvent& event);

  void OnLoginSubmit(wxThreadEvent& event);
  void OnLoginApproved(wxThreadEvent& event);
  void OnLoginRejected(wxThreadEvent& event);

  void OnUiTabChanged(wxThreadEvent& event);

 private:
  AdminClient* admin_client_;
  LoginFrame* login_frame_;
  MainFrame* main_frame_;

 private:
  SettingsManager* settings_;
  std::shared_ptr<spdlog::logger> logger_;

 private:
  DISALLOW_COPY_AND_ASSIGN(ProcessControl);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_INTERFACE_CONTROL_PROCESS_CONTROL_HPP
// -----------------------------------------------------------------------------
