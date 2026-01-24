/********************************************************************
  Copyright 2025, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/12/19 06:33
  filename:  ElefantBlaster/ElefantBlasterServerInterface/ui/main_frame.cpp

  purpose:   Implementation file for the main window class
*********************************************************************/


// -----------------------------------------------------------------------------
#include <wx/notebook.h>

#include "common/events.hpp"
#include "ui/main_frame.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
namespace _MenuId {
enum T {
  kFile_Logout = wxID_HIGHEST + 1,

  kAdminServer_Shutdown,
  kAdminServer_Restart,

  kGameServer_Active,
  kGameServer_Deactive,
  kGameServer_DisconnectAllClients,
};
}  // namespace _MenuId
typedef _MenuId::T MenuId;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
MainFrame* MainFrame::instance_ = nullptr;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

MainFrame::MainFrame()
    : wxFrame(nullptr,
              wxID_ANY,
              "Elefant Blaster Server Interface",
              wxDefaultPosition,
              wxDefaultSize) {
  instance_ = this;

  menu_files_ = new wxMenu;
  menu_files_->Append(MenuId::kFile_Logout, "&Logout");
  menu_files_->Append(wxID_EXIT, "&Exit\tAlt-X", "Exit the application");

  menu_admin_server_ = new wxMenu;
  menu_admin_server_->Append(MenuId::kAdminServer_Shutdown, "&Shutdown");
  menu_admin_server_->Append(MenuId::kAdminServer_Restart, "&Restart");

  menu_game_server_ = new wxMenu;
  menu_game_server_->Append(MenuId::kGameServer_Active, "&Active");
  menu_game_server_->Append(MenuId::kGameServer_Deactive, "&Deactive");
  menu_game_server_->Append(MenuId::kGameServer_DisconnectAllClients, "Di&sconnect All Clients");

  menu_help_ = new wxMenu;
  menu_help_->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

  menu_bar_ = new wxMenuBar;
  menu_bar_->Append(menu_files_, "&File");
  menu_bar_->Append(menu_admin_server_, "&Admin Server");
  menu_bar_->Append(menu_game_server_, "&Game Server");
  menu_bar_->Append(menu_help_, "&Help");

  SetMenuBar(menu_bar_);

  Bind(wxEVT_MENU, &MainFrame::OnFileExit, this, wxID_EXIT);
  Bind(wxEVT_MENU, &MainFrame::OnFileLogout, this, MenuId::kFile_Logout);
  Bind(wxEVT_MENU, &MainFrame::OnAdminServerShutdown, this, MenuId::kAdminServer_Shutdown);
  Bind(wxEVT_MENU, &MainFrame::OnAdminServerRestart, this, MenuId::kAdminServer_Restart);
  Bind(wxEVT_MENU, &MainFrame::OnGameServerActive, this, MenuId::kGameServer_Active);
  Bind(wxEVT_MENU, &MainFrame::OnGameServerDeactive, this, MenuId::kGameServer_Deactive);
  Bind(wxEVT_MENU, &MainFrame::OnGameServerDisconnectAllClients, this, MenuId::kGameServer_DisconnectAllClients);
  Bind(wxEVT_MENU, &MainFrame::OnHelpAbout, this, wxID_ABOUT);

  status_bar_ = CreateStatusBar(2);
  int widths[2] = { -1, 200 };
  status_bar_->SetStatusWidths(2, widths);
  status_bar_->SetStatusText("Not connected", 1);

  auto notebook = new wxNotebook(this, wxID_ANY);

  tab_user_manage_ = new TabUserManage(notebook);

  notebook->AddPage(tab_user_manage_, "User Management");

  auto sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(notebook, 1, wxEXPAND);
  SetSizer(sizer);
  SetClientSize(1000, 600);
  Layout();
}
// -----------------------------------------------------------------------------

MainFrame::~MainFrame() {
  instance_ = nullptr;
}
// -----------------------------------------------------------------------------

MainFrame* MainFrame::Instance() {
  return instance_;
}
// -----------------------------------------------------------------------------

void MainFrame::ShowAndCenter() {
  Show();
  Center();
}
// -----------------------------------------------------------------------------

void MainFrame::SetStatusConnected() {
  status_bar_->SetStatusText("Connected", 1);
}
// -----------------------------------------------------------------------------

void MainFrame::SetStatusReconnecting() {
  status_bar_->SetStatusText("Reconnecting ...", 1);
}
// -----------------------------------------------------------------------------

void MainFrame::OnFileLogout(wxCommandEvent & event) {
  auto evt = new wxThreadEvent(EVT_UI_MENU_FILE_LOGOUT);
  wxQueueEvent(wxTheApp, evt);
}
// -----------------------------------------------------------------------------

void MainFrame::OnFileExit(wxCommandEvent& event) {
  Close(true);
}
// -----------------------------------------------------------------------------

void MainFrame::OnAdminServerShutdown(wxCommandEvent& event) {
  auto evt = new wxThreadEvent(EVT_UI_MENU_ADMIN_SERVER_SHUTDOWN);
  wxQueueEvent(wxTheApp, evt);
}
// -----------------------------------------------------------------------------

void MainFrame::OnAdminServerRestart(wxCommandEvent& event) {
  auto evt = new wxThreadEvent(EVT_UI_MENU_ADMIN_SERVER_RESTART);
  wxQueueEvent(wxTheApp, evt);
}
// -----------------------------------------------------------------------------

void MainFrame::OnGameServerActive(wxCommandEvent& event) {
  auto evt = new wxThreadEvent(EVT_UI_MENU_GAME_SERVER_ACTIVE);
  wxQueueEvent(wxTheApp, evt);
}
// -----------------------------------------------------------------------------

void MainFrame::OnGameServerDeactive(wxCommandEvent& event) {
  auto evt = new wxThreadEvent(EVT_UI_MENU_GAME_SERVER_DEACTIVE);
  wxQueueEvent(wxTheApp, evt);
}
// -----------------------------------------------------------------------------

void MainFrame::OnGameServerDisconnectAllClients(wxCommandEvent& event) {
  auto evt = new wxThreadEvent(EVT_UI_MENU_GAME_SERVER_DISCONNECT_ALL_CLIENTS);
  wxQueueEvent(wxTheApp, evt);
}
// -----------------------------------------------------------------------------

void MainFrame::OnHelpAbout(wxCommandEvent& event) {
  wxMessageBox(L"Elefant Blaster Server Interface\n"
               L"Version 1.0\n"
               L"Copyright © 2025, Cong Quyen Knight.\n"
               L"All rights reserved.",
               L"About",
               wxOK | wxICON_INFORMATION, this);
}
// -----------------------------------------------------------------------------
