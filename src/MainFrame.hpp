#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    ~MainFrame() override;
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

    void SelectNext();
    void SelectPrevious();

    wxVector<wxString> history;

    wxTextCtrl * txtInput;
    wxListBox * lstHistory;
};


enum {
    ID_Input = 1,
    ID_History
};
