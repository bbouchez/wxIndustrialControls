/***************************************************************
 * Name:      wxAnimKnob.cpp
 * Purpose:   Animated bitmap knob widget for wxWidgets
 * Author:    Benoit BOUCHEZ (BEB)
 * Created:   2024-02-01
 * Copyright: (c) Benoit BOUCHEZ
 * License:	  wxWidgets license
 **************************************************************/

 /*
 This widget is equivalent to the CAnimKnob class defined in
 VSTGUI framework from Steinberg.
 The widget provides a value ranging from 0.0 to 1.0 which
 represents the position of the knob

 It requires a unique bitmap which contains different views (subbitmaps) 
 of the knob. According to the value, a specific subbitmap is displayed. 
 The different subbitmaps are stacked in the bitmap object.
 */

#include "wxAnimKnob.h"

IMPLEMENT_DYNAMIC_CLASS(wxAnimKnob, wxControl)

BEGIN_EVENT_TABLE(wxAnimKnob, wxControl)
EVT_MOUSE_EVENTS(wxAnimKnob::OnMouse)
EVT_PAINT(wxAnimKnob::OnPaint)
END_EVENT_TABLE()

wxAnimKnob::wxAnimKnob(wxWindow *parent,
	wxWindowID id,
	wxBitmap* knobBitmap,
	const unsigned int SubBmpHeight,
	const unsigned int NumSubBitmaps,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxValidator& validator,
	const wxString& name) : wxControl(parent, id, pos, size, style)
{
	this->Init();
	mId = id;
	mSize = size;
	this->mKnobBitmap = knobBitmap;
	this->mSubBmpHeight = SubBmpHeight;
	this->mNumBitmaps = NumSubBitmaps;

	if (parent)
		SetBackgroundColour(parent->GetBackgroundColour());
	else
		SetBackgroundColour(*wxLIGHT_GREY);
}  // wxAnimKnob::wxAnimKnob
// ----------------------------------------------------------------------------

void wxAnimKnob::Init(void)
{
	this->mId = 0;
	this->KnobActive = false;
	this->mNumBitmaps = 0;
	this->mKnobBitmap = 0;
	this->MouseInControl = false;
	this->fValue = 0.0f;
	this->mSize = wxSize(0, 0);
	this->mSubBmpHeight = 0;
	this->LastTouchY = 0;
}  // wxAnimKnob::Init
// ----------------------------------------------------------------------------

void wxAnimKnob::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);

	this->Draw(dc);
}  // wxAnimKnob::OnPaint
// ----------------------------------------------------------------------------

void wxAnimKnob::OnMouse(wxMouseEvent& event)
{
	wxPoint mousePos = event.GetPosition();
	int DeltaY;
	float OldValue, TestValue;
	wxClientDC dc(this);
	float ScaleFactor;

	if (event.Entering())
	{
		this->MouseInControl = true;
	}

	if (event.Leaving())
	{
		this->MouseInControl = false;
	}

	if (event.LeftUp())
	{
		ReleaseMouse();
		KnobActive = false;
	}

	if (event.LeftDown() && this->MouseInControl)
	{
		CaptureMouse();
		KnobActive = true;
		//PulseDivider = 0;
		this->LastTouchY = mousePos.y;
	}

	if (!KnobActive) return;		// Touch was started outside of knob area

	if (wxGetKeyState(WXK_ALT))
	{
		ScaleFactor = 0.001f;
	}
	else
	{
		ScaleFactor = 0.005f;
	}

	DeltaY = mousePos.y - LastTouchY;
	LastTouchY = mousePos.y;

	OldValue = fValue;
	TestValue = fValue;

	TestValue = this->fValue - ((float)DeltaY * ScaleFactor);

	if (TestValue > 1.0f) TestValue = 1.0f;
	if (TestValue < 0.0f) TestValue = 0.0f;
	fValue = TestValue;

	// Send event to parent if value has changed
	if (fValue != OldValue)
	{
		this->Moved();
		this->Draw(dc);
	}

	event.Skip();
}  // wxAnimKnob::OnMouse
// ----------------------------------------------------------------------------

void wxAnimKnob::SetValue(float value)
{
	wxClientDC dc(this);

	if (value < 0.0f) return;
	if (value > 1.0f) return;

	fValue = value;
	this->Draw(dc);
}  // wxAnimKnob::SetValue
// ----------------------------------------------------------------------------

void wxAnimKnob::Draw(wxDC& dc)
{
	wxMemoryDC temp_dc;
	temp_dc.SelectObject(*mKnobBitmap);
	unsigned int SourceOffsetY;
	unsigned int ImageIndex;

	ImageIndex = floor(this->fValue*this->mNumBitmaps);

	SourceOffsetY = this->mSubBmpHeight*ImageIndex;

	dc.Blit(wxPoint(0, 0), wxSize(this->mSize.GetWidth(), this->mSubBmpHeight), &temp_dc, wxPoint(0, SourceOffsetY));
}  // wxAnimKnob::Draw
// ----------------------------------------------------------------------------

void wxAnimKnob::Moved(void)
{
	wxCommandEvent event(wxEVT_KNOB_CHANGE, mId);
	event.SetEventObject(this);
	ProcessEvent(event);
}  // wxAnimKnob::Moved
// ----------------------------------------------------------------------------


