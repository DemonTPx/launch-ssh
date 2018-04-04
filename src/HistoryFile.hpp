#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class HistoryFile {
public:
    void Load(const wxString &filename, wxArrayString &history);
    void Save(const wxString &filename, wxArrayString &history);
};
