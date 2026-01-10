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

#include "common/events.hpp"
#include "ui/ui_definitions.hpp"
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

  Bind(EVT_NET_CONNECTED, &ProcessControl::OnNetConnected, this);
  Bind(EVT_NET_RECONNECT, &ProcessControl::OnNetReconnect, this);
  Bind(EVT_UI_LOGIN_SUBMIT, &ProcessControl::OnLoginSubmit, this);
  Bind(EVT_UI_TAB_CHANGED, &ProcessControl::OnUiTabChanged, this);

  login_frame_ = new LoginFrame();

  admin_client_ = new AdminClient(main_frame_);
  admin_client_->Start();
  admin_client_->Connect();

  login_frame_->Show(true);

  return true;
}
// -----------------------------------------------------------------------------

int ProcessControl::OnExit() {
  if (login_frame_) {
    login_frame_ = nullptr;
  }

  if (main_frame_) {
    main_frame_ = nullptr;
  }

  admin_client_->Stop();

  // Clean up SettingsManager
  SettingsManager::DestroyInstance();

  // Clean up LoggerManager
  LoggerManager::DestroyInstance();

  return wxApp::OnExit();
}
// -----------------------------------------------------------------------------

void ProcessControl::OnNetConnected(wxThreadEvent & event) {
  if (login_frame_->IsShown()) {
    login_frame_->SetStatusConnected();
  }
}
// -----------------------------------------------------------------------------

void ProcessControl::OnNetReconnect(wxThreadEvent& event) {
  if (login_frame_->IsShown()) {
    login_frame_->SetStatusReconnecting();
  }
}
// -----------------------------------------------------------------------------

void ProcessControl::OnLoginSubmit(wxThreadEvent& event) {
  LoginSubmitParams params = event.GetPayload<LoginSubmitParams>();
  while (!admin_client_->IsConnected()) {

  }
}
// -----------------------------------------------------------------------------

void ProcessControl::OnUiTabChanged(wxThreadEvent& event) {
  switch (event.GetInt()) {
    case TabIndex::kUserManage_Users:
      break;
  }
}
// -----------------------------------------------------------------------------
