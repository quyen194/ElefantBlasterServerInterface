/********************************************************************
  Copyright 2025, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/12/18 18:47
  filename:  ElefantBlaster/ElefantBlasterServerInterface/control/process_control.cpp

  purpose:   Implementation file for the main application class
*********************************************************************/


// -----------------------------------------------------------------------------
#include <aries_base/logger/logger_manager.hpp>

#include "control/process_control.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
using namespace aries_base::common;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

ProcessControl::ProcessControl() : wxApp(), main_frame_(nullptr) {
}
// -----------------------------------------------------------------------------

ProcessControl::~ProcessControl() {
}
// -----------------------------------------------------------------------------

bool ProcessControl::OnInit() {
  // Initialize global logger manager
  LoggerManager::CreateInstance();

  // Initialize settings manager
  SettingsManager::CreateInstance();

  settings_ = SettingsManager::Instance();
  logger_ = settings_->GetLogger("app", "ProcessControl", true);

  main_frame_ = new MainFrame();
  main_frame_->Show(true);

  return true;
}
// -----------------------------------------------------------------------------

int ProcessControl::OnExit() {
  if (main_frame_) {
    main_frame_ = nullptr;
  }

  // Clean up SettingsManager
  SettingsManager::DestroyInstance();

  // Clean up LoggerManager
  LoggerManager::DestroyInstance();

  return wxApp::OnExit();
}
// -----------------------------------------------------------------------------
