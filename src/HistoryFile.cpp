#include "HistoryFile.hpp"

#include <wx/textfile.h>
#include <wx/stdpaths.h>

HistoryFile::HistoryFile() {
    auto standardPaths = wxStandardPaths::Get();

    // TODO: Windows/mac compatibility
    filename = standardPaths.GetUserConfigDir().Append("/.config/launch-ssh-history");
}

void HistoryFile::Load(wxArrayString &history) {
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

void HistoryFile::Save(wxArrayString &history) {
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
