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

#include "ui/main_frame.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "Elefant Blaster Server Interface",
              wxDefaultPosition, wxSize(800, 600)) {
  menu_files_ = new wxMenu;
  menu_files_->Append(wxID_EXIT, "&Exit\tAlt-X", "Exit the application");

  menu_help_ = new wxMenu;
  menu_help_->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

  menu_bar_ = new wxMenuBar;
  menu_bar_->Append(menu_files_, "&File");
  menu_bar_->Append(menu_help_, "&Help");

  SetMenuBar(menu_bar_);

  Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
  Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);

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
  Layout();
}
// -----------------------------------------------------------------------------

MainFrame::~MainFrame() {
}
// -----------------------------------------------------------------------------

void MainFrame::OnExit(wxCommandEvent& event) {
  Close(true);
}
// -----------------------------------------------------------------------------

void MainFrame::OnAbout(wxCommandEvent& event) {
  wxMessageBox(L"Elefant Blaster Server Interface\n"
               L"Version 1.0\n"
               L"Copyright © 2025, Cong Quyen Knight.\n"
               L"All rights reserved.",
               L"About",
               wxOK | wxICON_INFORMATION, this);
}
// -----------------------------------------------------------------------------

void MainFrame::OnUsersSetGridData(wxThreadEvent& event) {}
// -----------------------------------------------------------------------------
