#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "MainFrame.hpp"

class App : public wxApp {
public:
    bool OnInit() override;
};


