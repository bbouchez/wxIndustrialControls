/***************************************************************
 * Name:      wxKickBitmapButton.h
 * Purpose:   wxWidgets Kick button
 * Author:    Benoit BOUCHEZ (BEB)
 * Created:   2020-04-11
 * Copyright: (c) Benoit BOUCHEZ
 * License:   wxWindows licence
 **************************************************************/

 /* This wxWidget is an equivalent of the KickButton from VSTGUI framework.
 Button sends an event when clicked. One bitmap is displayed during the click
 A second bitmap is displayed when button is released
 The two bitmaps must have the same size */

#include "wxKickBitmapButton.h"

IMPLEMENT_DYNAMIC_CLASS(wxKickBitmapButton, wxControl)

BEGIN_EVENT_TABLE(wxKickBitmapButton, wxControl)
	EVT_MOUSE_EVENTS(wxKickBitmapButton::OnMouse)
	EVT_PAINT(wxKickBitmapButton::OnPaint)
END_EVENT_TABLE()

wxKickBitmapButton::wxKickBitmapButton (wxWindow *parent,
                   wxWindowID id,
                   wxBitmap& offBitmap,
				   wxBitmap& onBitmap,
                   const wxPoint& pos,
                   const wxSize& size,
                   long style,
                   const wxValidator& WXUNUSED(validator),
                   const wxString& WXUNUSED(name)) : wxControl(parent, id, pos, size, style)
{

	this->Init();

	this->mId=id;
	this->mOffBitmap=&offBitmap;
	this->mOnBitmap=&onBitmap;

	if (parent)
		SetBackgroundColour(parent->GetBackgroundColour());
	else
		SetBackgroundColour(*wxLIGHT_GREY);
}  // wxKickBitmapButton::wxKickBitmapButton
// ----------------------------------------------------------------------------

void wxKickBitmapButton::Init (void)
{
	this->mOffBitmap=0;
	this->mOnBitmap=0;
	this->mId=0;
	this->MouseInControl=false;
	this->mState=false;
}  // wxKickBitmapButton::Init
// ----------------------------------------------------------------------------

void wxKickBitmapButton::OnMouse(wxMouseEvent& event)
{
	wxClientDC dc(this);

	if (event.Entering())
	{
		this->MouseInControl=true;
		return;
	}

	if (event.Leaving())
	{
		this->MouseInControl=false;
		return;
	}

	if (event.LeftUp())
	{
		this->mState=false;
		dc.DrawBitmap(*mOffBitmap, 0, 0, TRUE);
		//Refresh();
		//Click();			// Sending the event here makes the bitmap show properly (released) but it is
							// not what we want (a machine shall activate the output when button is depressed not released)
	}

	if (event.LeftDown() && MouseInControl)
	{
		this->mState=true;
		dc.DrawBitmap(*mOnBitmap, 0, 0, TRUE);
		//Refresh();
		Click();
	}

	event.Skip();
}  // wxKickBitmapButton::OnMouse
// ----------------------------------------------------------------------------

void wxKickBitmapButton::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);

	if (this->mState)
		dc.DrawBitmap(*mOnBitmap, 0, 0, TRUE);
	else
		dc.DrawBitmap(*mOffBitmap, 0, 0, TRUE);
}  // wxKickBitmapButton::OnPaint
// ----------------------------------------------------------------------------

void wxKickBitmapButton::Click (void)
{
	wxCommandEvent event(wxEVT_BUTTON, mId);
	event.SetEventObject(this);
	ProcessEvent (event);
}  // wxKickBitmapButton::Click
// ----------------------------------------------------------------------------
