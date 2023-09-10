/*
*	WaveMakerMainFrame.cpp
*	WaveMaker project
*	Main frame class implementation
*
*	Created by Benoit BOUCHEZ on 10/10/2020
*	Copyright 2020 BEBDigitalAudio. All rights reserved
*
*/

#include "wxICTestMainFrame.h"
#include "wxICTestApp.h"
#include <stdlib.h>

// the application icon (under Windows it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "../sample.xpm"
#endif

#define TIMER_ID			1000
#define ID_STATIC_ENCODER	1001
#define ID_TOGGLE_BITMAP_BUTTON 1002
#define ID_KICK_BITMAP_BUTTON   1003

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(CwxICTestMainFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  CwxICTestMainFrame::OnQuit)
    EVT_MENU(Minimal_About, CwxICTestMainFrame::OnAbout)
	EVT_CLOSE(CwxICTestMainFrame::OnClose)
	EVT_TIMER(TIMER_ID, CwxICTestMainFrame::OnTimer)
	EVT_PAINT(CwxICTestMainFrame::OnPaint)
	//EVT_ANGULARREG_CHANGE (ID_KNOB_TEST, CwxICTestMainFrame::OnKnob)
	EVT_ROTARYENCODER_CHANGE (ID_STATIC_ENCODER, CwxICTestMainFrame::OnStaticRotary)
	EVT_BUTTON (ID_TOGGLE_BITMAP_BUTTON, CwxICTestMainFrame::OnToggleBitmapButton)
	EVT_BUTTON (ID_KICK_BITMAP_BUTTON, CwxICTestMainFrame::OnKickBitmapButton)
wxEND_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
wxIMPLEMENT_APP(CwxICTestApp);

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
CwxICTestMainFrame::CwxICTestMainFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title), m_timer (this, TIMER_ID)
{
    // set the frame icon
    SetIcon(wxICON(sample));
	SetClientSize (1040, 600);

    // create a menu bar
    FileMenu = new wxMenu();
    wxMenu *helpMenu = new wxMenu;

	// Populate the menus
    FileMenu->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(Minimal_About, "&About\tF1", "Show about dialog");

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(FileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);

	wxInitAllImageHandlers();		// Accept all image formats for bitmaps

	// Test wxIndustrialControls

	// wxStaticRotaryEncoder (test bitmap size is 200 x 200)
    StaticEncoderBGnd = new wxBitmap (wxT("images/encoder.png"), wxBITMAP_TYPE_PNG);
	StaticRotaryEncoder = new wxStaticRotaryEncoder (this, ID_STATIC_ENCODER, *StaticEncoderBGnd, -100, 100, wxPoint(10, 10), wxSize (200, 200), wxBORDER_NONE);
	// Note : wxALIGN_CENTRE does not always work on wxGTK
	EncoderValueDisplay = new wxStaticText (this, wxID_ANY, wxT("0"), wxPoint (10, 220), wxSize(200, -1), wxALIGN_CENTRE+wxST_NO_AUTORESIZE);

	// wxOnOffBitmapButton
	ToggleOffBitmap = new wxBitmap (wxT("images/manual_off.png"), wxBITMAP_TYPE_PNG);
	ToggleOnBitmap = new wxBitmap (wxT("images/manual_on.png"), wxBITMAP_TYPE_PNG);
	OnOffToggleButton = new wxOnOffBitmapButton (this, ID_TOGGLE_BITMAP_BUTTON, *ToggleOffBitmap, *ToggleOnBitmap, wxPoint (250, 100), wxSize (70, 70));
    ToggleValueDisplay = new wxStaticText (this, wxID_ANY, wxT("OFF"), wxPoint(250, 190), wxSize (70, -1), wxALIGN_CENTRE+wxST_NO_AUTORESIZE);

    // wxKickBitmapButton
    KickOffBitmap = new wxBitmap (wxT("images/kick_off.png"), wxBITMAP_TYPE_PNG);
    KickOnBitmap = new wxBitmap (wxT("images/kick_on.png"), wxBITMAP_TYPE_PNG);
    KickButton = new wxKickBitmapButton (this, ID_KICK_BITMAP_BUTTON, *KickOffBitmap, *KickOnBitmap, wxPoint(350, 100), wxSize (81, 76));

	/*
	TestKnob=new kwxAngularRegulator (this, ID_KNOB_TEST, wxPoint (300, 300), wxSize (101, 101), wxBORDER_NONE);
	TestKnob->SetAngle (-45, 225);
	TestKnob->SetRange (0, 100);
	TestKnob->SetValue (0);

	TestSlider=new kwxLinearRegulator (this, -1, wxPoint(100, 300), wxSize (50, 200), wxBORDER_NONE);
	TestSlider->SetHorizontalDirection (false);
	TestSlider->SetRangeVal (0, 260);

	TestMeter=new kwxAngularMeter (this, -1, wxPoint(100, 100), wxSize (100, 100));
	TestMeter->SetRange (0, 100);
	TestMeter->SetNumSectors (3);
	TestMeter->SetSectorColor (0, *wxBLUE);
	TestMeter->SetSectorColor (1, *wxWHITE);
	TestMeter->SetSectorColor (2, *wxYELLOW);
	*/

	// Run the timer every millisecond as it will be used for the RTP-MIDI thread for now
	//m_timer.Start(1);
}  // CwxICTestMainFrame::CWaveMakerMainFrame
// -----------------------------------------------------

// Quit command by menu (not button on top bar)
void CwxICTestMainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}  // CwxICTestMainFrame::OnQuit
// -----------------------------------------------------

// Click on close icon on top bar or request to close the window sent by OnQuit
void CwxICTestMainFrame::OnClose(wxCloseEvent& WXUNUSED(event))
{
	// Delete dynamically allocated wxIndustrialControls BEFORE we delete the bitmaps used by them
    if (StaticRotaryEncoder) delete StaticRotaryEncoder;
    if (OnOffToggleButton) delete OnOffToggleButton;
    if (KickButton) delete KickButton;

    // TODO : move bitmap deletion after wxIndustrialControls deletion
	// Delete all bitmaps used by the various controls
	if (KickOffBitmap) delete KickOffBitmap;
	if (KickOffBitmap) delete KickOnBitmap;
	if (StaticEncoderBGnd) delete StaticEncoderBGnd;
	if (ToggleOffBitmap) delete ToggleOffBitmap;
	if (ToggleOnBitmap) delete ToggleOnBitmap;

	m_timer.Stop();

	Destroy();
}  // CwxICTestMainFrame::OnClose
// -----------------------------------------------------

void CwxICTestMainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format
                 (
                    "wxIndustrialControl Test Application!\n"
                    "\n"
                    "Written using %s\n"
                    "Running under %s.",
                    wxVERSION_STRING,
                    wxGetOsDescription()
                 ),
                 "About wxICTest",
                 wxOK | wxICON_INFORMATION,
                 this);
}  // CwxICTestMainFrame::OnAbout
// -----------------------------------------------------

void CwxICTestMainFrame::OnTimer(wxTimerEvent& WXUNUSED(event))
{
}  // CwxICTestMainFrame::OnTimer
// -----------------------------------------------------

void CwxICTestMainFrame::OnPaint (wxPaintEvent& WXUNUSED(event))
{
}  // CwxICTestMainFrame::OnPaint
// -----------------------------------------------------

void CwxICTestMainFrame::OnStaticRotary (wxCommandEvent& WXUNUSED(event))
{
	//printf ("Static rotary encoder position : %d\n", TestStaticEncoder->GetValue());
	EncoderValueDisplay->SetLabel (wxString::Format(wxT("%d"), StaticRotaryEncoder->GetValue()));
}  // CwxICTestMainFrame::OnStaticRotary
// -----------------------------------------------------

void CwxICTestMainFrame::OnToggleBitmapButton (wxCommandEvent& WXUNUSED(event))
{
    if (OnOffToggleButton->GetValue()==0) ToggleValueDisplay->SetLabel (wxT("OFF"));
    else ToggleValueDisplay->SetLabel (wxT("ON"));
}  // CwxICTestMainFrame::OnToggleBitmapButton
// -----------------------------------------------------

void CwxICTestMainFrame::OnKickBitmapButton (wxCommandEvent& WXUNUSED(event))
{
    //wxMessageBox ("Kick bitmap button has been pressed", "wxKickBitmapButton test", wxOK+wxICON_INFORMATION);
}  // CwxICTestMainFrame::OnKickBitmapButton
// -----------------------------------------------------
