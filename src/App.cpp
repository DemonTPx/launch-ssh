#include "App.hpp"

#include "icon.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    if ( ! wxApp::OnInit()) {
        return false;
    }

    auto mainFrame = new MainFrame(_("Launch SSH"), wxDefaultPosition, wxDefaultSize);
    mainFrame->Show(true);
    mainFrame->SetIcon(wxIcon(wxICON(icon)));

    return true;
}
