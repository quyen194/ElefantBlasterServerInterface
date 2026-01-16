/********************************************************************
  Copyright 2025, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/12/19 08:25
  filename:  ElefantBlaster/ElefantBlasterServerInterface/network/net_client.cpp

  purpose:   Network interface for admin client
*********************************************************************/


// -----------------------------------------------------------------------------
#include <aries_base/process/thread_pool/thread_pool.hpp>

#include "common/events.hpp"
#include "network/admin_client.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
// -----------------------------------------------------------------------------
typedef asio::ssl::context context;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

AdminClient::AdminClient(MainFrame* main_frame)
    : hdl_(connection_hdl()),
      connected_(false),
      worker_end_event_(true, false),
      is_stopping_(false),
      settings_(SettingsManager::Instance()),
      main_frame_(main_frame) {
  logger_ = settings_->GetLogger("network", "AdminClient", true);

  client_.init_asio();

  client_.set_tls_init_handler(bind(&AdminClient::OnTlsInit, this, _1));
  client_.set_open_handler(bind(&AdminClient::OnConnected, this, _1));
  client_.set_close_handler(bind(&AdminClient::OnDisconnected, this, _1));
  client_.set_fail_handler(bind(&AdminClient::OnError, this, _1));
  client_.set_message_handler(bind(&AdminClient::OnMessage, this, _1, _2));
}
// -----------------------------------------------------------------------------

AdminClient::~AdminClient() {
}
// -----------------------------------------------------------------------------

bool AdminClient::LoadConfig() {
  settings_->SetCurrentConfig(SettingsManager::kSettingClient);

  std::string hostname = settings_->GetNested<std::string>("/admin_server/host", "localhost");
  int port = settings_->GetNested<int>("/admin_server/port", 9003);
  uri_ = "wss://" + hostname + ":" + std::to_string(port);

  return true;
}
// -----------------------------------------------------------------------------

bool AdminClient::Start() {
  is_stopping_ = false;

  // Set perpetual mode to keep the client running
  client_.start_perpetual();

  ThreadPool::Instance()->PostTask(bind(&AdminClient::Worker, this),
                                   &worker_end_event_);

  return true;
}
// -----------------------------------------------------------------------------

void AdminClient::Stop() {
  is_stopping_ = true;
  // Unset perpetual mode so server stop when no connection actived
  client_.stop_perpetual();
  Disconnect();
  client_.get_io_service().stop();
  worker_end_event_.Wait();
}
// -----------------------------------------------------------------------------

bool AdminClient::Connect() {
  if (!LoadConfig()) {
      logger_->error("AdminClient: Failed to load configs, cannot connect to server");
      return false;
  }

  websocketpp::lib::error_code ec;
  client::connection_ptr conn = client_.get_connection(uri_, ec);

  if (ec) {
    logger_->error("AdminClient: Connect error: {}", ec.message());
    return false;
  }

  client_.connect(conn);

  return true;
}
// -----------------------------------------------------------------------------

void AdminClient::Disconnect() {
  websocketpp::lib::error_code ec;
  client_.close(client_.get_con_from_hdl(hdl_), websocketpp::close::status::going_away, "", ec);
  if (ec) {
    logger_->error("AdminClient: Error initiating close: {}", ec.message());
  }
}
// -----------------------------------------------------------------------------

bool AdminClient::IsConnected() {
  return connected_;
}
// -----------------------------------------------------------------------------

void AdminClient::Worker() {
  // Start the ASIO io_service run loop
  logger_->info("AdminClient: Client run loop started");
  try {
    client_.run();
  } catch (const std::exception& e) {
    logger_->error("AdminServer: Exception in server run loop: {}", e.what());
  }
  logger_->info("AdminClient: Client run loop stopped");
}
// -----------------------------------------------------------------------------

context_ptr AdminClient::OnTlsInit(connection_hdl hdl) {
  context_ptr ctx = websocketpp::lib::make_shared<context>(context::sslv23);

  try {
    ctx->set_verify_mode(asio::ssl::verify_none);
  }
  catch(const std::exception& e) {
    logger_->error("AdminClient: Exception in OnTlsInit: {}", e.what());
  }

  return ctx;
}
// -----------------------------------------------------------------------------

void AdminClient::OnConnected(connection_hdl hdl) {
  hdl_ = hdl;
  connected_ = true;
  logger_->info("AdminClient: Connected to server");

  auto evt = new wxThreadEvent(EVT_NET_CONNECTED);
  wxQueueEvent(wxTheApp, evt);
}
// -----------------------------------------------------------------------------

void AdminClient::OnDisconnected(connection_hdl hdl) {
  hdl_ = connection_hdl();
  connected_ = false;

  if (!is_stopping_) {
    logger_->info("AdminClient: Disconnected from server. Reconnecting ...");

    auto evt = new wxThreadEvent(EVT_NET_RECONNECT);
    wxQueueEvent(wxTheApp, evt);
  }
  else {
    logger_->info("AdminClient: Disconnected from server");
  }
}
// -----------------------------------------------------------------------------

void AdminClient::OnError(connection_hdl hdl) {
  logger_->error("AdminClient: Connection error occurred");

  auto evt = new wxThreadEvent(EVT_NET_RECONNECT);
  wxQueueEvent(wxTheApp, evt);
}
// -----------------------------------------------------------------------------

void AdminClient::OnMessage(connection_hdl hdl, message_ptr message) {
  if (message->get_opcode() != websocketpp::frame::opcode::binary)
    return;

  protocol::ServerMessage msg;
  if (!msg.ParseFromArray(message->get_payload().data(),
                          message->get_payload().size())) {
    // corrupted or incompatible
    return;
  }

  switch (msg.body_case()) {
    case protocol::ServerMessage::kLoginResponse: {
      OnLoginRespond(hdl, msg.login_response());
    } break;
  }
}
// -----------------------------------------------------------------------------

bool AdminClient::Send(const protocol::ClientMessage &message) {
  if (!IsConnected()) {
    return false;
  }

  utils::bytes buffer(message.ByteSizeLong());
  message.SerializeToArray(buffer.data(), buffer.size());

  return Send(buffer);
}
// -----------------------------------------------------------------------------

bool AdminClient::Send(const utils::bytes &data) {
  if (!IsConnected()) {
    return false;
  }

  websocketpp::lib::error_code ec;
  client_.send(hdl_,  //
               data.data(),
               data.size(),
               websocketpp::frame::opcode::binary,
               ec);

  if (ec) {
    logger_->error("AdminClient: Send message failed: {}", ec.message());
    return false;
  }

  return true;
}
// -----------------------------------------------------------------------------

bool AdminClient::LoginRequest(LoginSubmitParams& params) {
  logger_->info("AdminClient: Send Login Request for {}", params.username);

  protocol::ClientMessage msg;
  auto req = msg.mutable_login_request();
  req->set_username(params.username);
  req->set_password(params.password);

  return Send(msg);
}
// -----------------------------------------------------------------------------

void AdminClient::OnLoginRespond(connection_hdl hdl,
                                 const admin_auth::LoginResponse& res) {
  if (res.result()) {
    auto evt = new wxThreadEvent(EVT_NET_LOGIN_APPROVED);
    wxQueueEvent(wxTheApp, evt);
    return;
  }

  auto evt = new wxThreadEvent(EVT_NET_LOGIN_REJECTED);
  evt->SetString(res.reason());
  wxQueueEvent(wxTheApp, evt);
}
// -----------------------------------------------------------------------------

bool AdminClient::ShutDownServer() {
  logger_->info("AdminClient: Send ShutDown Server Request");

  protocol::ClientMessage msg;
  msg.mutable_shutdown_server_request();

  return Send(msg);
}
// -----------------------------------------------------------------------------

bool AdminClient::RestartServer() {
  logger_->info("AdminClient: Send Restart Server Request");

  protocol::ClientMessage msg;
  msg.mutable_restart_server_request();

  return Send(msg);
}
// -----------------------------------------------------------------------------

bool AdminClient::ActiveGameServer() {
  logger_->info("AdminClient: Send Active GameServer Request");

  protocol::ClientMessage msg;
  msg.mutable_active_game_server_request();

  return Send(msg);
}
// -----------------------------------------------------------------------------

bool AdminClient::DeactiveGameServer() {
  logger_->info("AdminClient: Send Deactive GameServer Request");

  protocol::ClientMessage msg;
  msg.mutable_deactive_game_server_request();

  return Send(msg);
}
// -----------------------------------------------------------------------------

bool AdminClient::DisconnectAllGameClients() {
  logger_->info("AdminClient: Send Disconnect All Game Clients Request");

  protocol::ClientMessage msg;
  msg.mutable_disconnect_all_game_clients_request();

  return Send(msg);
}
// -----------------------------------------------------------------------------
