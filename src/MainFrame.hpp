#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "HistoryFile.hpp"

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
private:
    void Initialize();

    DECLARE_EVENT_TABLE()

    void OnInputText(wxCommandEvent &event);
    void OnHistoryDClick(wxCommandEvent &event);

    void OnChar(wxKeyEvent &event);

    void RefreshList();

    void LaunchSelectedItem();
    void Launch();
    void Launch(const wxString &target);

    void Autocomplete();

    void SelectDelta(int delta);

    void DeleteSelection();

    static int NaturalCompare(const wxString &a, const wxString &b);

    HistoryFile historyFile;

    wxArrayString history;
    wxArrayString matches;
    wxString query;

    wxTextCtrl * txtInput;
    wxListBox * lstHistory;
};

enum {
    ID_Input = 1,
    ID_History
};
