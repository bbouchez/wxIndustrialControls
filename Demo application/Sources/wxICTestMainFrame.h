/*
*	WaveMakerMainFrame.h
*	WaveMaker project
*	Main frame class definition
*
*	Created by Benoit BOUCHEZ on 10/10/2020
*	Copyright 2020 BEBDigitalAudio. All rights reserved
*
*/

#ifndef __WXICTESTMAINFRAME_H__
#define __WXICTESTMAINFRAME_H__

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wxBargraph.h"
#include "wxKickBitmapButton.h"
#include "wxOnOffBitmapButton.h"
#include "wxOnOffIndicator.h"
#include "wxSimpleLinearController.h"
#include "wxStaticRotaryEncoder.h"
//#include "AngularRegulator.h"
//#include "LinearRegulator.h"
//#include "AngularMeter.h"

// Define a new frame type: this is going to be our main frame
class CwxICTestMainFrame : public wxFrame
{
public:
    // ctor(s)
    CwxICTestMainFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	void OnClose(wxCloseEvent &event);
	void OnTimer(wxTimerEvent& event);
	void OnPaint (wxPaintEvent& event);

private:
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();

	// Menu items
	wxMenu* FileMenu;
	wxMenu* FileNewMenu;
	wxMenu* FileOpenMenu;

	// Create a timer as we will need one almost for all applications
	wxTimer m_timer;

	//kwxAngularRegulator* TestKnob;
	//kwxLinearRegulator* TestSlider;
	//kwxAngularMeter* TestMeter;

	// Static encoder test
	wxBitmap* StaticEncoderBGnd;
	wxStaticText* EncoderValueDisplay;
	wxStaticRotaryEncoder* StaticRotaryEncoder;

	// On/Off bitmap button test
    wxBitmap* ToggleOffBitmap;
	wxBitmap* ToggleOnBitmap;
	wxOnOffBitmapButton* OnOffToggleButton;
	wxStaticText* ToggleValueDisplay;

	// Kick bitmap button test
	wxBitmap* KickOffBitmap;
	wxBitmap* KickOnBitmap;
	wxKickBitmapButton* KickButton;

	// Methods to handle events from wxIndustrialControls
	void OnStaticRotary (wxCommandEvent& event);
	void OnToggleBitmapButton (wxCommandEvent& event);
	void OnKickBitmapButton (wxCommandEvent& event);
};

#endif
