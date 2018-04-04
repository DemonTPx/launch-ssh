#include "HistoryFile.hpp"

#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/textfile.h>

void HistoryFile::Load(const wxString &filename, wxArrayString &history) {
    wxTextFile file(filename);

    if ( ! file.Exists()) {
        file.Create();
    }
    file.Open();

    for (auto line = file.GetFirstLine(); ! file.Eof(); line = file.GetNextLine()) {
        auto target = line.Trim();

        if ( ! target.empty()) {
            history.push_back(target);
        }
    }

    file.Close();
}

void HistoryFile::Save(const wxString &filename, wxArrayString &history) {
    wxTextFile file(filename);

    if ( ! file.Exists()) {
        file.Create();
    }

    file.Open();
    file.Clear();

    for (auto &target : history) {
        file.AddLine(target);
    }

    file.Write();
    file.Close();
}
