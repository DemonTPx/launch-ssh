#include "MainFrame.hpp"

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size):
        wxFrame(nullptr, -1, title, pos, size, wxDEFAULT_FRAME_STYLE ^ (wxMINIMIZE_BOX | wxMAXIMIZE_BOX))
{
    Initialize();
}

void MainFrame::Initialize() {
    txtInput = new wxTextCtrl(this, ID_Input, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP);
    lstHistory = new wxListBox(this, ID_History);

    auto sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(txtInput, 0, wxEXPAND | wxALL, 5);
    sizer->Add(lstHistory, 1, wxEXPAND | wxALL, 5);
    sizer->SetMinSize(600, 500);

    SetSizerAndFit(sizer);

    // NOTE: history items always lower case? should be when matching!
    history.push_back(_("demontpx.com"));
    history.push_back(_("test1"));
    history.push_back(_("test10"));
    history.push_back(_("test11"));
    history.push_back(_("test12"));
    history.push_back(_("test20"));
    history.push_back(_("test-acc2"));
    history.push_back(_("test-acc1"));

    for (auto &target : history) {
        lstHistory->Append(target);
    }
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_TEXT(ID_Input, MainFrame::OnInputText)
    EVT_LISTBOX_DCLICK(ID_History, MainFrame::OnHistoryDClick)
    EVT_CHAR_HOOK(MainFrame::OnChar)
END_EVENT_TABLE()

void MainFrame::OnInputText(wxCommandEvent &event) {
    query = txtInput->GetValue().Lower();
    lstHistory->SetSelection(wxNOT_FOUND);
    RefreshList();
}

void MainFrame::OnHistoryDClick(wxCommandEvent &event) {
    LaunchSelectedItem();
}

void MainFrame::OnChar(wxKeyEvent &event) {
    auto keyCode = event.GetKeyCode();

    if (keyCode == WXK_BACK || keyCode >= WXK_SPACE && keyCode < WXK_START) {
        if ( ! txtInput->HasFocus()) {
            long start, end;
            txtInput->GetSelection(&start, &end);
            txtInput->SetFocus();
            txtInput->SetSelection(start, end);
        }
        event.Skip();
    }

    switch (keyCode) {
        case WXK_ESCAPE:
            Close();
            break;
        case WXK_TAB:
            Autocomplete();
            break;
        case WXK_UP:
        case WXK_NUMPAD_UP:
            SelectPrevious();
            break;
        case WXK_DOWN:
        case WXK_NUMPAD_DOWN:
            SelectNext();
            break;
        case WXK_RETURN:
        case WXK_NUMPAD_ENTER:
            Launch();
            break;
        default:
            event.Skip();
    }
}

void MainFrame::RefreshList() {
    unsigned int index = 0;
    matches.clear();

    for (auto &target : history) {
        auto noMoreItems = index >= lstHistory->GetCount();

        if (target.StartsWith(query)) {
            matches.push_back(target);
            if (noMoreItems || lstHistory->GetString(index) != target) {
                lstHistory->Insert(target, index);
            }
            if (target == query) {
                lstHistory->SetSelection(index);
            }
            index++;
        } else {
            if ( ! noMoreItems && lstHistory->GetString(index) == target) {
                lstHistory->Delete(index);
            }
        }
    }
}

void MainFrame::LaunchSelectedItem() {
    if (lstHistory->GetSelection() == wxNOT_FOUND) {
        return;
    }

    auto item = lstHistory->GetStringSelection();

    Launch(item);
}

void MainFrame::Launch() {
    auto target = txtInput->GetValue();

    Launch(target);
}

void MainFrame::Launch(const wxString &target) {
    auto command = _("x-terminal-emulator -e ssh ");
    command.Append(target);

    wxExecute(command);
    Close();
}

void MainFrame::Autocomplete() {
    if (matches.empty()) {
        wxBell();

        return;
    }

    wxString longestMatch = matches.at(0);

    for (auto &target : matches) {
        while ( ! target.StartsWith(longestMatch)) {
            longestMatch = longestMatch.SubString(0, longestMatch.Length() - 2);
        }

        if (longestMatch.Length() == query.Length()) {
            wxBell();

            return;
        }
    }

    txtInput->SetValue(longestMatch);
    txtInput->SetSelection(longestMatch.Length(), longestMatch.Length());
}

void MainFrame::SelectNext() {
    if (lstHistory->GetSelection() == wxNOT_FOUND && lstHistory->GetCount() != 0) {
        lstHistory->SetSelection(0);
    } else if (lstHistory->GetSelection() < lstHistory->GetCount() - 1) {
        lstHistory->SetSelection(lstHistory->GetSelection() + 1);
    }
}

void MainFrame::SelectPrevious() {
    if (lstHistory->GetSelection() > 0) {
        lstHistory->SetSelection(lstHistory->GetSelection() - 1);
    }
}
