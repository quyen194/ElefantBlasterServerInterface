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
#include <aries_base/process/event/event.hpp>

#include "common/settings_manager.hpp"
#include "ui/main_frame.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
using namespace aries_base::process;
// -----------------------------------------------------------------------------
typedef websocketpp::client<websocketpp::config::asio_tls_client>::message_ptr message_ptr;
typedef websocketpp::connection_hdl connection_hdl;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;
typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

class AdminClient {
 public:
  AdminClient(MainFrame *main_frame);
  virtual ~AdminClient();

  bool LoadConfig();

  bool Start();
  void Stop();

  bool Connect();
  void Disconnect();
  bool IsConnected();

 private:
  context_ptr OnTlsInit(connection_hdl hdl);
  void OnConnected(connection_hdl hdl);
  void OnDisconnected(connection_hdl hdl);
  void OnError(connection_hdl hdl);
  void OnMessage(connection_hdl hdl, message_ptr msg);

 private:
  void Worker();

 private:
  client client_;
  std::string uri_;

  connection_hdl hdl_;
  bool connected_;

  Event worker_end_event_;

 private:
  SettingsManager* settings_;
  MainFrame *main_frame_;
  std::shared_ptr<spdlog::logger> logger_;

 private:
  DISALLOW_COPY_AND_ASSIGN(AdminClient);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_INTERFACE_NETWORK_NET_CLIENT_HPP
// -----------------------------------------------------------------------------
