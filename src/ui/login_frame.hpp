/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/08 10:57
  filename:  ElefantBlaster/ElefantBlasterServerInterface/ui/login_frame.hpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_SERVER_INTERFACE_UI_LOGIN_FRAME_HPP
#define ELEFANT_BLASTER_SERVER_INTERFACE_UI_LOGIN_FRAME_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <wx/wx.h>

#include <aries_base/definitions/macro.hpp>
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class LoginFrame : public wxFrame {
 public:
  LoginFrame();
  virtual ~LoginFrame();

  void ShowAndCenter();

  void SetStatusConnected();
  void SetStatusReconnecting();

  void OnLoginRejected(const std::string reason);

 private:
  void OnSubmit(wxCommandEvent& event);
  void OnExit(wxCommandEvent& event);
  void OnClose(wxCloseEvent& event);

 private:
  wxTextCtrl *txt_username_;
  wxTextCtrl *txt_password_;
  wxButton *btn_submit_;
  wxButton *btn_exit_;

  wxStatusBar* status_bar_;

  bool is_closing_;

 private:
  DISALLOW_COPY_AND_ASSIGN(LoginFrame);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_INTERFACE_UI_LOGIN_FRAME_HPP
// -----------------------------------------------------------------------------
