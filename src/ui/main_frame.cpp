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
#include "ui/main_frame.hpp"
#include "ui/tab_user_manage.hpp"
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

  auto notebook = new wxNotebook(this, wxID_ANY);

  notebook->AddPage(new TabUserManage(notebook), "User Management");

  auto sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(notebook, 1, wxEXPAND | wxALL);
  SetSizer(sizer);
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
