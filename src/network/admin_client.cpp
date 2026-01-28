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
#include "entities/profile.hpp"
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

AdminClient::AdminClient()
    : hdl_(connection_hdl()),
      connected_(false),
      worker_end_event_(true, false),
      is_stopping_(false),
      settings_(SettingsManager::Instance()) {
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
  if (!connected_) {
    return;
  }

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

  if (AuthUser.authorized) {
    Login();
  }
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
    case protocol::ServerMessage::kLoginSuccessResponse: {
      OnLoginRespond(hdl, msg.login_success_response());
    } break;
    case protocol::ServerMessage::kLoginFailureResponse: {
      OnLoginRespond(hdl, msg.login_failure_response());
    } break;
    case protocol::ServerMessage::kUsersListSuccessResponse: {
      OnUsersListRespond(hdl, msg.users_list_success_response());
    } break;
    case protocol::ServerMessage::kUsersListFailureResponse: {
      OnUsersListRespond(hdl, msg.users_list_failure_response());
    } break;
    case protocol::ServerMessage::kGroupsListSuccessResponse: {
      OnGroupsListRespond(hdl, msg.groups_list_success_response());
    } break;
    case protocol::ServerMessage::kGroupsListFailureResponse: {
      OnGroupsListRespond(hdl, msg.groups_list_failure_response());
    } break;
    case protocol::ServerMessage::kRolesListSuccessResponse: {
      OnRolesListRespond(hdl, msg.roles_list_success_response());
    } break;
    case protocol::ServerMessage::kRolesListFailureResponse: {
      OnRolesListRespond(hdl, msg.roles_list_failure_response());
    } break;
    case protocol::ServerMessage::kPermissionsListSuccessResponse: {
      OnPermissionsListRespond(hdl, msg.permissions_list_success_response());
    } break;
    case protocol::ServerMessage::kPermissionsListFailureResponse: {
      OnPermissionsListRespond(hdl, msg.permissions_list_failure_response());
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

  AuthUser.authorized = false;
  AuthUser.username = params.username;
  AuthUser.password = params.password;

  return Login();
}
// -----------------------------------------------------------------------------

bool AdminClient::Login() {
  if (AuthUser.username.empty() || AuthUser.password.empty()) {
    return false;
  }

  protocol::ClientMessage msg;
  auto req = msg.mutable_login_request();
  req->set_username(AuthUser.username);
  req->set_password(AuthUser.password);

  return Send(msg);
}
// -----------------------------------------------------------------------------

bool AdminClient::Logout() {
  AuthUser.Clear();

  Disconnect();

  return true;
}
// -----------------------------------------------------------------------------

void AdminClient::OnLoginRespond(connection_hdl hdl,
                                 const admin_auth::LoginSuccessResponse& res) {
  LoginResponseData data;
  data.display_name = res.display_name();
  for (int i = 0; i < res.permissions_size(); i++) {
    data.permissions.insert(res.permissions(i));
  }

  AuthUser.authorized = true;

  auto evt = new wxThreadEvent(EVT_NET_LOGIN_APPROVED);
  evt->SetPayload(data);
  wxQueueEvent(wxTheApp, evt);
}
// -----------------------------------------------------------------------------

void AdminClient::OnLoginRespond(connection_hdl hdl,
                                 const admin_auth::LoginFailureResponse& res) {
  AuthUser.username.clear();
  AuthUser.password.clear();

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

bool AdminClient::RequestUsersList(const FilterUsersParams& params) {
  logger_->info("AdminClient: Send Users List Request");

  protocol::ClientMessage msg;
  auto req = msg.mutable_users_list_request();
  req->set_filter_name(params.filter_name);
  req->set_sort_type(params.sort_type);
  req->set_last_id(params.last_id);
  req->set_max_count(params.max_count);

  return Send(msg);
}
// -----------------------------------------------------------------------------

void AdminClient::OnUsersListRespond(
    connection_hdl hdl, const users_management::UsersListSuccessResponse& res) {
  for (int i = 0; i < res.users_size(); i++) {
    auto user_data = res.users(i);

    User user;
    user.id = user_data.id();
    user.type = static_cast<UserType>(user_data.type());
    user.username = user_data.username();
    user.display_name = user_data.display_name();
    user.api_token = user_data.api_token();
    user.last_online_at = user_data.last_online_at();
    user.is_banned = user_data.is_banned();
    user.ban_reason = user_data.ban_reason();
    user.banned_until = user_data.banned_until();
    user.is_actived = user_data.is_actived();

    AuthUser.users_list.push_back(user);
  }

  auto evt = new wxThreadEvent(EVT_NET_USERS_LIST_SUCCESS);
  wxQueueEvent(TabUsers::Instance(), evt);
}
// -----------------------------------------------------------------------------

void AdminClient::OnUsersListRespond(
    connection_hdl hdl, const users_management::UsersListFailureResponse& res) {
  auto evt = new wxThreadEvent(EVT_NET_USERS_LIST_FAILURE);
  evt->SetString(res.reason());
  wxQueueEvent(TabUsers::Instance(), evt);
}
// -----------------------------------------------------------------------------

bool AdminClient::RequestGroupsList() {
  logger_->info("AdminClient: Send Groups List Request");

  protocol::ClientMessage msg;
  msg.mutable_groups_list_request();

  return Send(msg);
}
// -----------------------------------------------------------------------------

void AdminClient::OnGroupsListRespond(
    connection_hdl hdl, const users_management::GroupsListSuccessResponse& res) {
  for (int i = 0; i < res.groups_size(); i++) {
    auto group_data = res.groups(i);

    Group group;
    group.id = group_data.id();
    group.is_system = group_data.is_system();
    group.name = group_data.name();
    group.display_name = group_data.display_name();
    group.desc = group_data.desc();
    group.is_actived = group_data.is_actived();

    AuthUser.groups_list.push_back(group);
  }

  auto evt = new wxThreadEvent(EVT_NET_GROUPS_LIST_SUCCESS);
  wxQueueEvent(TabGroups::Instance(), evt);
}
// -----------------------------------------------------------------------------

void AdminClient::OnGroupsListRespond(
    connection_hdl hdl, const users_management::GroupsListFailureResponse& res) {
  auto evt = new wxThreadEvent(EVT_NET_GROUPS_LIST_FAILURE);
  evt->SetString(res.reason());
  wxQueueEvent(TabGroups::Instance(), evt);
}
// -----------------------------------------------------------------------------

bool AdminClient::RequestRolesList() {
  logger_->info("AdminClient: Send Roles List Request");

  protocol::ClientMessage msg;
  msg.mutable_roles_list_request();

  return Send(msg);
}
// -----------------------------------------------------------------------------

void AdminClient::OnRolesListRespond(
    connection_hdl hdl, const users_management::RolesListSuccessResponse& res) {
  for (int i = 0; i < res.roles_size(); i++) {
    auto role_data = res.roles(i);

    Role role;
    role.id = role_data.id();
    role.is_system = role_data.is_system();
    role.name = role_data.name();
    role.display_name = role_data.display_name();
    role.desc = role_data.desc();
    role.is_actived = role_data.is_actived();

    AuthUser.roles_list.push_back(role);
  }

  auto evt = new wxThreadEvent(EVT_NET_ROLES_LIST_SUCCESS);
  wxQueueEvent(TabRoles::Instance(), evt);
}
// -----------------------------------------------------------------------------

void AdminClient::OnRolesListRespond(
    connection_hdl hdl, const users_management::RolesListFailureResponse& res) {
  auto evt = new wxThreadEvent(EVT_NET_ROLES_LIST_FAILURE);
  evt->SetString(res.reason());
  wxQueueEvent(TabRoles::Instance(), evt);
}
// -----------------------------------------------------------------------------

bool AdminClient::RequestPermissionsList() {
  logger_->info("AdminClient: Send Permissions List Request");

  protocol::ClientMessage msg;
  msg.mutable_permissions_list_request();

  return Send(msg);
}
// -----------------------------------------------------------------------------

void AdminClient::OnPermissionsListRespond(
    connection_hdl hdl,
    const users_management::PermissionsListSuccessResponse& res) {
  for (int i = 0; i < res.permissions_size(); i++) {
    auto permission_data = res.permissions(i);

    Permission permission;
    permission.risk = static_cast<RiskLevel>(permission_data.risk_level());
    permission.name = permission_data.name();
    permission.desc = permission_data.desc();

    AuthUser.permissions_list.push_back(permission);
  }

  auto evt = new wxThreadEvent(EVT_NET_PERMISSIONS_LIST_SUCCESS);
  wxQueueEvent(TabPermissions::Instance(), evt);
}
// -----------------------------------------------------------------------------

void AdminClient::OnPermissionsListRespond(
    connection_hdl hdl,
    const users_management::PermissionsListFailureResponse& res) {
  auto evt = new wxThreadEvent(EVT_NET_PERMISSIONS_LIST_FAILURE);
  evt->SetString(res.reason());
  wxQueueEvent(TabPermissions::Instance(), evt);
}
// -----------------------------------------------------------------------------
