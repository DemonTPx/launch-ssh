#include "MainFrame.hpp"

extern "C" {
#include "strnatcmp.h"
}

#include <algorithm>

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

    historyFile.Load(history);

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
    query = txtInput->GetValue().Trim();
    lstHistory->SetSelection(wxNOT_FOUND);
    RefreshList();
}

void MainFrame::OnHistoryDClick(wxCommandEvent &event) {
    LaunchSelectedItem();
}

void MainFrame::OnChar(wxKeyEvent &event) {
    auto keyCode = event.GetKeyCode();

    if (keyCode == WXK_BACK || (keyCode >= WXK_SPACE && keyCode < WXK_START)) {
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
            SelectDelta(-1);
            break;
        case WXK_DOWN:
        case WXK_NUMPAD_DOWN:
            SelectDelta(1);
            break;
        case WXK_PAGEUP:
        case WXK_NUMPAD_PAGEUP:
            SelectDelta(-10);
            break;
        case WXK_PAGEDOWN:
        case WXK_NUMPAD_PAGEDOWN:
            SelectDelta(10);
            break;
        case WXK_HOME:
        case WXK_NUMPAD_HOME:
            if (lstHistory->GetCount() != 0) {
                lstHistory->Select(0);
            }
            break;
        case WXK_END:
        case WXK_NUMPAD_END:
            if (lstHistory->GetCount() != 0) {
                lstHistory->Select(lstHistory->GetCount() - 1);
            }
            break;
        case WXK_RETURN:
        case WXK_NUMPAD_ENTER:
            Launch();
            break;
        case WXK_DELETE:
        case WXK_NUMPAD_DELETE:
            DeleteSelection();
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
    if (lstHistory->GetSelection() != wxNOT_FOUND) {
        LaunchSelectedItem();

        return;
    }

    if (query.Len() == 0) {
        return;
    }

    Launch(query);
}

void MainFrame::Launch(const wxString &target) {
    auto command = _("x-terminal-emulator -e ssh ");
    command.Append(target);

    wxExecute(command);

    Close();

    if (history.Index(target) == wxNOT_FOUND) {
        history.push_back(target);
        history.Sort(NaturalCompare);
        historyFile.Save(history);
    }
}

void MainFrame::Autocomplete() {
    if (matches.empty()) {
        wxBell();

        return;
    }

    wxString longestMatch = matches[0];

    for (auto &target : matches) {
        while ( ! target.StartsWith(longestMatch)) {
            longestMatch = longestMatch.Left(longestMatch.Len() - 1);
        }

        if (longestMatch.Len() == query.Len()) {
            wxBell();

            return;
        }
    }

    txtInput->SetValue(longestMatch);
    txtInput->SetSelection(longestMatch.Len(), longestMatch.Len());
}

void MainFrame::SelectDelta(int delta) {
    if (lstHistory->GetCount() == 0) {
        return;
    }

    int newSelection = lstHistory->GetSelection() + delta;

    lstHistory->SetSelection(std::max(0, std::min((int) lstHistory->GetCount() - 1, newSelection)));
}

void MainFrame::DeleteSelection() {
    if (lstHistory->GetSelection() == wxNOT_FOUND) {
        return;
    }

    auto selection = (unsigned int) lstHistory->GetSelection();

    history.Remove(lstHistory->GetStringSelection());
    historyFile.Save(history);
    lstHistory->Delete(selection);

    if (selection < lstHistory->GetCount()) {
        lstHistory->Select(selection);
    } else if (selection > 0) {
        lstHistory->Select(selection - 1);
    }

    RefreshList();
}

int MainFrame::NaturalCompare(const wxString &a, const wxString &b) {
    return strnatcmp(a.c_str(), b.c_str());
}
