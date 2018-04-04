#include "App.hpp"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    if ( ! wxApp::OnInit()) {
        return false;
    }

    auto mainFrame = new MainFrame(APP_NAME, wxDefaultPosition, wxDefaultSize);
    mainFrame->Show(true);

    return true;
}
