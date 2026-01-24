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
#include <aries_base/process/thread_pool/thread_pool.hpp>

#include "common/events.hpp"
#include "entities/profile.hpp"
#include "ui/ui_definitions.hpp"
#include "control/process_control.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
using namespace aries_base::common;
using namespace aries_base::process;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

ProcessControl::ProcessControl()
    : wxApp(),
      admin_client_(nullptr),
      login_frame_(nullptr),
      main_frame_(nullptr) {}
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

  settings_->SetCurrentConfig(SettingsManager::kSettingApp);

  // Thread pool settings from app config (section thread_pool)
  uint32_t idle_threads = settings_->GetNested<uint32_t>("/thread_pool/idle_threads", 4);
  uint32_t max_threads = settings_->GetNested<uint32_t>("/thread_pool/max_threads", 16);
  logger_->info("ProcessControl: Initializing ThreadPool... (idle_threads={}, max_threads={})", idle_threads, max_threads);
  ThreadPool::CreateInstance(idle_threads, max_threads);

  Bind(EVT_NET_CONNECTED, &ProcessControl::OnNetConnected, this);
  Bind(EVT_NET_RECONNECT, &ProcessControl::OnNetReconnect, this);
  Bind(EVT_UI_LOGIN_SUBMIT, &ProcessControl::OnLoginSubmit, this);
  Bind(EVT_NET_LOGIN_APPROVED, &ProcessControl::OnLoginApproved, this);
  Bind(EVT_NET_LOGIN_REJECTED, &ProcessControl::OnLoginRejected, this);
  Bind(EVT_UI_MENU_FILE_LOGOUT, &ProcessControl::OnUiMenuFileLogout, this);
  Bind(EVT_UI_MENU_ADMIN_SERVER_SHUTDOWN, &ProcessControl::OnUiMenuAdminServerShutdown, this);
  Bind(EVT_UI_MENU_ADMIN_SERVER_RESTART, &ProcessControl::OnUiMenuAdminServerRestart, this);
  Bind(EVT_UI_MENU_GAME_SERVER_ACTIVE, &ProcessControl::OnUiMenuGameServerActive, this);
  Bind(EVT_UI_MENU_GAME_SERVER_DEACTIVE, &ProcessControl::OnUiMenuGameServerDeactive, this);
  Bind(EVT_UI_MENU_GAME_SERVER_DISCONNECT_ALL_CLIENTS, &ProcessControl::OnUiMenuGameServerDisconnectAllClients, this);
  Bind(EVT_UI_TAB_CHANGED, &ProcessControl::OnUiTabChanged, this);

  login_frame_ = new LoginFrame();
  login_frame_->Bind(wxEVT_DESTROY, [this](wxWindowDestroyEvent&) {
    login_frame_ = nullptr;
  });

  admin_client_ = new AdminClient();
  admin_client_->Start();
  admin_client_->Connect();

  login_frame_->ShowAndCenter();

  return true;
}
// -----------------------------------------------------------------------------

int ProcessControl::OnExit() {
  admin_client_->Stop();

  // Clean up SettingsManager
  SettingsManager::DestroyInstance();

  // Clean up LoggerManager
  LoggerManager::DestroyInstance();

  return wxApp::OnExit();
}
// -----------------------------------------------------------------------------

void ProcessControl::Logout() {
  login_frame_ = new LoginFrame();
  login_frame_->Bind(wxEVT_DESTROY, [this](wxWindowDestroyEvent&) {
    login_frame_ = nullptr;
  });

  if (main_frame_) {
    auto main_frame = main_frame_;
    main_frame_ = nullptr;
    main_frame->Close();
  }

  admin_client_->Disconnect();

  login_frame_->ShowAndCenter();
}
// -----------------------------------------------------------------------------

void ProcessControl::OnNetConnected(wxThreadEvent & event) {
  if (login_frame_ && login_frame_->IsShown()) {
    login_frame_->SetStatusConnected();
  }
  if (main_frame_ && main_frame_->IsShown()) {
    main_frame_->SetStatusConnected();
  }
}
// -----------------------------------------------------------------------------

void ProcessControl::OnNetReconnect(wxThreadEvent& event) {
  if (login_frame_ && login_frame_->IsShown()) {
    login_frame_->SetStatusReconnecting();

    ThreadPool::PostDelayedTask([this](){
      admin_client_->Connect();
    }, 1000);
  }

  if (main_frame_ && main_frame_->IsShown()) {
    wxMessageDialog dlg(main_frame_,
                        "Would you like to reconnect?",
                        "Disconnected from server",
                        wxYES_NO | wxICON_WARNING);
    dlg.SetYesNoLabels("Reconnect", "Logout");
    int result = dlg.ShowModal();
    if (result == wxID_YES) {
      main_frame_->SetStatusReconnecting();
      admin_client_->Connect();
    }
    else {
      Logout();
      admin_client_->Connect();
    }
  }
}
// -----------------------------------------------------------------------------

void ProcessControl::OnLoginSubmit(wxThreadEvent& event) {
  LoginSubmitParams params = event.GetPayload<LoginSubmitParams>();
  admin_client_->LoginRequest(params);
}
// -----------------------------------------------------------------------------

void ProcessControl::OnLoginApproved(wxThreadEvent& event) {
  LoginResponseData login_data = event.GetPayload<LoginResponseData>();

  AuthUser.display_name = login_data.display_name;
  AuthUser.permissions = login_data.permissions;

  if (login_frame_) {
    login_frame_->Close();
  }

  main_frame_ = new MainFrame();
  main_frame_->SetStatusConnected();
  main_frame_->Bind(wxEVT_DESTROY, [this](wxWindowDestroyEvent&) {
    main_frame_ = nullptr;
  });
  main_frame_->ShowAndCenter();
}
// -----------------------------------------------------------------------------

void ProcessControl::OnLoginRejected(wxThreadEvent& event) {
  std::string reason = event.GetString().ToStdString();
  login_frame_->OnLoginRejected(reason);
}
// -----------------------------------------------------------------------------

void ProcessControl::OnUiMenuFileLogout(wxThreadEvent& event) {
  Logout();
}
// -----------------------------------------------------------------------------

void ProcessControl::OnUiMenuAdminServerShutdown(wxThreadEvent& event) {
  admin_client_->ShutDownServer();
}
// -----------------------------------------------------------------------------

void ProcessControl::OnUiMenuAdminServerRestart(wxThreadEvent& event) {
  admin_client_->RestartServer();
}
// -----------------------------------------------------------------------------

void ProcessControl::OnUiMenuGameServerActive(wxThreadEvent& event) {
  admin_client_->ActiveGameServer();
}
// -----------------------------------------------------------------------------

void ProcessControl::OnUiMenuGameServerDeactive(wxThreadEvent& event) {
  admin_client_->DeactiveGameServer();
}
// -----------------------------------------------------------------------------

void ProcessControl::OnUiMenuGameServerDisconnectAllClients(
    wxThreadEvent& event) {
  admin_client_->DisconnectAllGameClients();
}
// -----------------------------------------------------------------------------

void ProcessControl::OnUiTabChanged(wxThreadEvent& event) {
  switch (event.GetInt()) {
    case TabIndex::kUserManage_Users:
      if (AuthUser.users_list.empty()) {
        admin_client_->RequestUsersList({});
      }
      break;
  }
}
// -----------------------------------------------------------------------------
