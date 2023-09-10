/***************************************************************
 * Name:      wxOnOffBitmapButton.cpp
 * Purpose:   wxWidgets Toggle On/Off button
 * Author:    Benoit BOUCHEZ (BEB)
 * Created:   2020-04-11
 * Copyright: (c) Benoit BOUCHEZ
 * License:   wxWindows licence
 **************************************************************/

/* This wxWidget is an equivalent of the OnOffButton from VSTGUI framework.
Button is activated by a first click (value = true) and deactivated by a
second click (value = false). Each state is represented by a different
bitmap.
The two bitmaps must have the same size */

#include "wxOnOffBitmapButton.h"

IMPLEMENT_DYNAMIC_CLASS(wxOnOffBitmapButton, wxControl)

BEGIN_EVENT_TABLE(wxOnOffBitmapButton, wxControl)
	EVT_MOUSE_EVENTS(wxOnOffBitmapButton::OnMouse)
	EVT_PAINT(wxOnOffBitmapButton::OnPaint)
END_EVENT_TABLE()

wxOnOffBitmapButton::wxOnOffBitmapButton (wxWindow *parent,
                   wxWindowID id,
                   wxBitmap& offBitmap,
				   wxBitmap& onBitmap,
                   const wxPoint& pos,
                   const wxSize& size,
                   long style,
                   const wxValidator& WXUNUSED(validator),
                   const wxString& WXUNUSED(name)) : wxControl(parent, id, pos, size, style)
{

	Init();

	mId=id;
	mOffBitmap=&offBitmap;
	mOnBitmap=&onBitmap;

	if (parent)
		SetBackgroundColour(parent->GetBackgroundColour());
	else
		SetBackgroundColour(*wxLIGHT_GREY);
}  // wxOnOffBitmapButton::wxOnOffBitmapButton
// ----------------------------------------------------------------------------

/*
wxOnOffBitmapButton::~wxOnOffBitmapButton()
{
	printf ("wxOnOffBitmapButton destructor called\n");
}  // wxOnOffBitmapButton::~wxOnOffBitmapButton
// ----------------------------------------------------------------------------
*/

void wxOnOffBitmapButton::Init (void)
{
	mOffBitmap=0;
	mOnBitmap=0;
	mId=0;
	MouseInControl=false;
	UserToggleAllowed=true;
	mState=false;
}  // wxOnOffBitmapButton::Init
// ----------------------------------------------------------------------------

void wxOnOffBitmapButton::SetValue(bool state)
{
	if (state==mState) return;		// Value does not change : no need to update

	mState=state;
	Refresh();
}  // wxOnOffBitmapButton::SetValue
// ----------------------------------------------------------------------------

void wxOnOffBitmapButton::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);

	if (mState)
		dc.DrawBitmap(*mOnBitmap, 0, 0, TRUE);
	else
		dc.DrawBitmap(*mOffBitmap, 0, 0, TRUE);
}  // wxOnOffBitmapButton::OnPaint
// ----------------------------------------------------------------------------

void wxOnOffBitmapButton::OnMouse(wxMouseEvent& event)
{
	if (event.Entering())
	{
		MouseInControl=true;
		return;
	}

	if (event.Leaving())
	{
		MouseInControl=false;
		return;
	}

	// Toggle state when clicked
	if (event.LeftDown() && MouseInControl)
	{
        if (UserToggleAllowed)
        {
            if (mState) mState=false;
            else mState=true;
            Refresh();
        }
		Click();
	}

	event.Skip();
}  // wxOnOffBitmapButton::OnMouse
// ----------------------------------------------------------------------------

void wxOnOffBitmapButton::Click (void)
{
	wxCommandEvent event(wxEVT_BUTTON, mId);
	event.SetEventObject(this);
	ProcessEvent (event);
}  // wxOnOffBitmapButton::Click
// ----------------------------------------------------------------------------

void wxOnOffBitmapButton::AllowUserChange (bool Allow)
{
	UserToggleAllowed=Allow;
}  // wxOnOffBitmapButton::AllowChange
// ----------------------------------------------------------------------------

