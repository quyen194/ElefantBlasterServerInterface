/********************************************************************
  Copyright 2025, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/12/19 06:32
  filename:  ElefantBlaster/ElefantBlasterServerInterface/ui/main_frame.hpp

  purpose:   Header file for the main window class
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_SERVER_INTERFACE_UI_MAIN_FRAME_HPP
#define ELEFANT_BLASTER_SERVER_INTERFACE_UI_MAIN_FRAME_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <wx/wx.h>

#include <aries_base/definitions/macro.hpp>

#include "ui/tab_user_manage.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class MainFrame : public wxFrame {
 public:
  MainFrame();
  virtual ~MainFrame();

 private:
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);

 private:
  void OnUsersSetGridData(wxThreadEvent& event);

 private:
  TabUserManage* tab_user_manage_;

 private:
  wxMenuBar* menu_bar_;
  wxMenu* menu_files_;
  wxMenu* menu_help_;

  wxStatusBar* status_bar_;

 private:
  DISALLOW_COPY_AND_ASSIGN(MainFrame);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_SERVER_INTERFACE_UI_MAIN_FRAME_HPP
// -----------------------------------------------------------------------------
