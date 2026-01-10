/********************************************************************
  Copyright 2025, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/12/19 08:25
  filename:  ElefantBlaster/ElefantBlasterServerInterface/network/net_client.cpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#include "network/admin_client.hpp"
#include "admin_client.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

AdminClient::AdminClient() : settings_(SettingsManager::Instance()) {
  logger_ = settings_->GetLogger("network", "AdminClient", true);
}
// -----------------------------------------------------------------------------

AdminClient::~AdminClient() {
}
// -----------------------------------------------------------------------------

void AdminClient::LoadSettings() {
  settings_->SetCurrentConfig(SettingsManager::kSettingClient);
  host_ = settings_->GetNested<std::string>("/admin_server/host", "localhost");
  port_ = settings_->GetNested<int>("/admin_server/port", 9003);
}
// -----------------------------------------------------------------------------

bool AdminClient::Connect() {
  // Implementation for connecting to the admin server
  client_.init_asio();
  client_.start_perpetual();
  client_.run();
  return false;
}
// -----------------------------------------------------------------------------

void AdminClient::Disconnect() {
  //
}
// -----------------------------------------------------------------------------
