#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class HistoryFile {
public:
    HistoryFile();

    void Load(wxArrayString &history);
    void Save(wxArrayString &history);

private:
    wxString filename;
};
