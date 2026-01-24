/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/08 11:07
  filename:  ElefantBlaster/ElefantBlasterServerInterface/ui/login_frame.cpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#include <wx/display.h>

#include "common/events.hpp"
#include "ui/login_frame.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

LoginFrame::LoginFrame()
    : wxFrame(nullptr,
              wxID_ANY,
              "Elefant Blaster Server Interface",
              wxDefaultPosition,
              wxDefaultSize,
              wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX),
      is_closing_(false) {
  auto username_sizer = new wxBoxSizer(wxHORIZONTAL);
  auto lbl_username = new wxStaticText(this, wxID_ANY, "Username");
  lbl_username->SetMinSize(wxSize(90, -1));
  txt_username_ = new wxTextCtrl(this, wxID_ANY, "admin");
  username_sizer->Add(lbl_username, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
  username_sizer->Add(txt_username_, 1);

  auto password_sizer = new wxBoxSizer(wxHORIZONTAL);
  auto lbl_password = new wxStaticText(this, wxID_ANY, "Password");
  lbl_password->SetMinSize(wxSize(90, -1));
  txt_password_ = new wxTextCtrl(this,
                                 wxID_ANY,
                                 "quyen194",
                                 wxDefaultPosition,
                                 wxDefaultSize,
                                 wxTE_PASSWORD);
  password_sizer->Add(lbl_password, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
  password_sizer->Add(txt_password_, 1);

  auto button_sizer = new wxBoxSizer(wxHORIZONTAL);
  btn_submit_ = new wxButton(this, wxID_OK, "Submit");
  btn_submit_->Bind(wxEVT_BUTTON, &LoginFrame::OnSubmit, this);
  btn_submit_->SetDefault();
  btn_submit_->Disable();
  btn_exit_ = new wxButton(this, wxID_CANCEL, "Exit");
  btn_exit_->Bind(wxEVT_BUTTON, &LoginFrame::OnExit, this);
  button_sizer->AddStretchSpacer();
  button_sizer->Add(btn_submit_, 0, wxRIGHT, 10);
  button_sizer->Add(btn_exit_, 0);
  button_sizer->AddStretchSpacer();

  status_bar_ = CreateStatusBar();
  status_bar_->SetStatusText("Connecting ...");

  Bind(wxEVT_CLOSE_WINDOW, &LoginFrame::OnClose, this);

  auto sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(username_sizer, 0, wxEXPAND | wxALL, 10);
  sizer->Add(password_sizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
  sizer->Add(button_sizer, 0, wxEXPAND | wxTOP | wxBOTTOM, 15);
  SetSizer(sizer);
  SetClientSize(400, 160);
  Layout();
}
// -----------------------------------------------------------------------------

LoginFrame::~LoginFrame() {}
// -----------------------------------------------------------------------------

void LoginFrame::ShowAndCenter() {
  Show();
  Center();
}
// -----------------------------------------------------------------------------

void LoginFrame::SetStatusConnected() {
  status_bar_->SetStatusText("Connected");
  btn_submit_->Enable();
}
// -----------------------------------------------------------------------------

void LoginFrame::SetStatusReconnecting() {
  status_bar_->SetStatusText("Reconnecting ...");
  btn_submit_->Disable();
}
// -----------------------------------------------------------------------------

void LoginFrame::OnSubmit(wxCommandEvent& event) {
  LoginSubmitParams params;
  params.username = txt_username_->GetValue();
  params.password = txt_password_->GetValue();

  if (params.username.empty() || params.password.empty()) {
    wxMessageBox("Please input username and password!",
                 "Login failed",
                 wxOK | wxICON_ERROR,
                 this);
    return;
  }

  btn_submit_->Disable();

  auto evt = new wxThreadEvent(EVT_UI_LOGIN_SUBMIT);
  evt->SetPayload(params);
  wxQueueEvent(wxTheApp, evt);
}
// -----------------------------------------------------------------------------

void LoginFrame::OnLoginRejected(const std::string reason) {
  wxMessageBox(reason, "Login failed", wxOK | wxICON_ERROR, this);

  btn_submit_->Enable();
}
// -----------------------------------------------------------------------------

void LoginFrame::OnExit(wxCommandEvent& event) {
  Close();
}
// -----------------------------------------------------------------------------

void LoginFrame::OnClose(wxCloseEvent& event) {
  if (is_closing_) {
    event.Skip();
    return;
  }

  is_closing_ = true;

  Destroy();
}
// -----------------------------------------------------------------------------
