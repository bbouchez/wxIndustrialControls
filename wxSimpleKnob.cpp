/***************************************************************
 * Name:      wxSimpleKnob.cpp
 * Purpose:   Simple knob widget for wxWidgets
 * Author:    Benoit BOUCHEZ (BEB)
 * Created:   2024-02-01
 * Copyright: (c) Benoit BOUCHEZ
 * License:	  wxWidgets license
 **************************************************************/

#include "wxSimpleKnob.h"

IMPLEMENT_DYNAMIC_CLASS(wxSimpleKnob, wxControl)

BEGIN_EVENT_TABLE(wxSimpleKnob, wxControl)
EVT_MOUSE_EVENTS(wxSimpleKnob::OnMouse)
EVT_PAINT(wxSimpleKnob::OnPaint)
END_EVENT_TABLE()

void wxSimpleKnob::Init(void)
{
	this->mId = 0;

}  // wxSimpleKnob::Init
// -----------------------------------------------------

wxSimpleKnob::wxSimpleKnob(wxWindow *parent,
	wxWindowID id,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxValidator& validator,
	const wxString& name) : wxControl(parent, id, pos, size, style)
{
	this->mId = id;
	this->mSize = size;
}  // wxSimpleKnob::wxSimpleKnob
// -----------------------------------------------------

void wxSimpleKnob::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);

	this->Draw(dc);
}  // wxSimpleKnob::OnPaint
// -----------------------------------------------------

void wxSimpleKnob::OnMouse(wxMouseEvent& event)
{
	wxPoint mousePos = event.GetPosition();

	if (event.Entering())
	{
		this->MouseInControl = true;
	}

	if (event.Leaving())
	{
		this->MouseInControl = false;
	}
}  // wxSimpleKnob::OnMouse
// -----------------------------------------------------

void wxSimpleKnob::Draw(wxDC& dc)
{

}  // wxSimpleKnob::Draw
// -----------------------------------------------------
