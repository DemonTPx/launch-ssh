#include "App.hpp"

#include "icon.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    if ( ! wxApp::OnInit()) {
        return false;
    }

    wxIcon icon(icon_xpm);

    auto mainFrame = new MainFrame(_("SSH launch"), wxDefaultPosition, wxDefaultSize);
    mainFrame->Show(true);
    mainFrame->SetIcon(icon);

    return true;
}
