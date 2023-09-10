/////////////////////////////////////////////////////////////////////////////
// Name:        WaveMakerApp.cpp
// Purpose:     Application entry point for Wave maker
// Author:      Benoit BOUCHEZ
// Modified by:
// Created:     
// Copyright:   (c) BEB Digital Audio
/////////////////////////////////////////////////////////////////////////////

#include "wxICTestApp.h"
#include "wxICTestMainFrame.h"

// 'Main program' equivalent: the program execution "starts" here
bool CwxICTestApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

#if defined(__TARGET_WIN__) && defined (__DEBUG_CONSOLE__)
	if (AllocConsole())
	{
		freopen ("CONOUT$", "wt", stdout);
		SetConsoleTitle (_T("wxIndustrial Controls debug console"));
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	}
#endif

    // create the main application window
    CwxICTestMainFrame* frame = new CwxICTestMainFrame("wxIndustrialControls Test Application");

    frame->Show(true);		// Now triggered in the constructor

    return true;
}  // CwxICTestApp::OnInit()
// -----------------------------------------------------

int CwxICTestApp::OnExit()
{
	wxApp::OnExit();  // Call ancestor
	return 0;
}  // CwxICTestApp::OnExit
// -----------------------------------------------------
