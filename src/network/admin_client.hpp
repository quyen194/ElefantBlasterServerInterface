/********************************************************************
  Copyright 2025, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/12/19 08:24
  filename:  ElefantBlaster/ElefantBlasterServerInterface/network/net_client.hpp

  purpose:   Network interface for admin client
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_SERVER_INTERFACE_NETWORK_NET_CLIENT_HPP
#define ELEFANT_BLASTER_SERVER_INTERFACE_NETWORK_NET_CLIENT_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <cstdint>
#include <string>

#include <spdlog/spdlog.h>

#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

#include <aries_base/definitions/macro.hpp>

#include "common/settings_manager.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
typedef websocketpp::connection_hdl connection_hdl;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;
typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

class AdminClient {
 public:
  AdminClient();
  virtual ~AdminClient();

  void LoadSettings();

  bool Connect();
  void Disconnect();

 private:
  client client_;

  std::string host_;
  int port_;

 private:
  SettingsManager* settings_;
  std::shared_ptr<spdlog::logger> logger_;

 private:
  DISALLOW_COPY_AND_ASSIGN(AdminClient);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_INTERFACE_NETWORK_NET_CLIENT_HPP
// -----------------------------------------------------------------------------
