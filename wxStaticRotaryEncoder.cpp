/***************************************************************
 * Name:      wxStaticRotaryEncoder.cpp
 * Purpose:   Rotary encoder widgets for wxWidgets applications
 * Author:    Benoit BOUCHEZ (BEB)
 * Created:   2020-04-11
 * Copyright: (c) Benoit BOUCHEZ
 * License:	  wxWidgets license
 **************************************************************/

/*
This widget is mainly designed for touch screen applications. It
emulates a endless rotary encoder (sometimes known as ALPHA DIAL)

This version of encoder is called "static" as its graphical
representation does not change when the encoder is moved (hence
its value is changed)

Graphical representation of the encoder is a square bitmap
provided by the host application.
*/

#include "wxStaticRotaryEncoder.h"

IMPLEMENT_DYNAMIC_CLASS(wxStaticRotaryEncoder, wxControl)

BEGIN_EVENT_TABLE(wxStaticRotaryEncoder, wxControl)
	EVT_MOUSE_EVENTS(wxStaticRotaryEncoder::OnMouse)
	EVT_PAINT(wxStaticRotaryEncoder::OnPaint)
END_EVENT_TABLE()

wxStaticRotaryEncoder::wxStaticRotaryEncoder(wxWindow *parent,
                   wxWindowID id,
                   wxBitmap& backgroundBitmap,
				   int MinimumValue,
				   int MaximumValue,
                   const wxPoint& pos,
                   const wxSize& size,
                   long style,
                   const wxValidator& validator,
                   const wxString& name) : wxControl(parent, id, pos, size, style)
{
	Init();

	mId=id;
	mBackBitmap=&backgroundBitmap;
	mSize=size;
	mMin = MinimumValue;
	mMax = MaximumValue;

	// Compute positions of the nine quadrants limits
	OneThirdX=size.GetWidth()*0.33f;
	TwoThirdX=OneThirdX*2;

	OneThirdY = size.GetHeight()*0.33f;
	TwoThirdY = OneThirdY*2;

	if (parent)
		SetBackgroundColour(parent->GetBackgroundColour());
	else
		SetBackgroundColour(*wxLIGHT_GREY);
}  // wxStaticRotaryEncoder::wxStaticRotaryEncoder
// ----------------------------------------------------------------------------

/*
wxStaticRotaryEncoder::~wxStaticRotaryEncoder ()
{
	printf ("wxStaticRotaryEncoder destroyed\n");
}  // wxStaticRotaryEncoder::~wxStaticRotaryEncoder
// ----------------------------------------------------------------------------
*/

void wxStaticRotaryEncoder::Init (void)
{
	mBackBitmap=0;
	mId=0;
	MouseInControl=false;
	mValue=0;
	mSize=wxSize(0, 0);
	LastTouchX = 0;
	LastTouchY = 0;
	PulseDivider = 0;
	EncoderActive = false;
}  // wxStaticRotaryEncoder::Init
// ----------------------------------------------------------------------------

void wxStaticRotaryEncoder::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);

	dc.DrawBitmap(*mBackBitmap, 0, 0, TRUE);
}  // wxStaticRotaryEncoder::OnPaint
// ----------------------------------------------------------------------------

void wxStaticRotaryEncoder::OnMouse(wxMouseEvent& event)
{
	wxPoint mousePos = event.GetPosition();
	int Quadrant;
	int DeltaX, DeltaY;
	bool Plus, Minus;		// Sign of the "rotation"
	int StepSize, AbsDeltaX, AbsDeltaY;
	int TestValue, OldValue;

	//printf ("%d %d\n", mousePos.x, mousePos.y);

	// Check that we are inside the encoder area
	if (mousePos.x < 0) return;
	if (mousePos.x > mSize.GetWidth()) return;
	if (mousePos.y < 0) return;
	if (mousePos.y > mSize.GetHeight()) return;

	if (event.Entering())
	{
		MouseInControl=true;
	}

	if (event.Leaving())
	{
		MouseInControl=false;
	}

	if (event.LeftUp())
	{
		EncoderActive = false;
	}

	if (event.LeftDown() && MouseInControl)
	{
		EncoderActive = true;
		PulseDivider = 0;
		LastTouchX = mousePos.x;
		LastTouchY = mousePos.y;
	}

	// User has moved fingers on the encoder surface
	if (!EncoderActive) return;		// Touch was started outside of encoder area

	// Detect in which quadrant finger is now located
	// Quadrant organization
	// 0 1 2
	// 7   3
	// 6 5 4
	Quadrant = -1;
	if (mousePos.y <= OneThirdY)	// Top line
	{
		if (mousePos.x <= OneThirdX) Quadrant = 0;
		else if (mousePos.x <= TwoThirdX) Quadrant = 1;
		else Quadrant = 2;
	}
	else if (mousePos.y <= TwoThirdY)	// Middle line
	{
		if (mousePos.x <= OneThirdX) Quadrant = 7;
		else if (mousePos.x > TwoThirdX) Quadrant = 3;
	}
	else  // Bottom line
	{
		if (mousePos.x <= OneThirdX) Quadrant = 6;
		else if (mousePos.x <= TwoThirdX) Quadrant = 5;
		else Quadrant = 4;
	}
	//printf ("Quadrant : %d\n", Quadrant);
	if (Quadrant == -1) return;

	// Compute direction (+ or -) depending on quadrant
	DeltaX = mousePos.x-LastTouchX;
	DeltaY = mousePos.y-LastTouchY;

	LastTouchX = mousePos.x;
	LastTouchY = mousePos.y;
	//printf ("Delta X Y : %d %d\n", DeltaX, DeltaY);

	Plus = false;
	Minus = false;
	StepSize = 0;
	AbsDeltaX = abs (DeltaX);
	AbsDeltaY = abs (DeltaY);

	switch (Quadrant)
    {
        case 0 :
            if ((DeltaX>0)&&(DeltaY<=0)) Plus=true;
            else if ((DeltaX<=0)&&(DeltaY>0)) Minus=true;
            if (AbsDeltaX>AbsDeltaY) StepSize=AbsDeltaX;
            else StepSize=AbsDeltaY;
            break;
        case 1 :        // Only X motion is taken into account
            if (DeltaX>0) Plus=true;
            if (DeltaX<0) Minus=true;
            StepSize=AbsDeltaX;
            break;
        case 2 :
            if ((DeltaX>0)&&(DeltaY>=0)) Plus=true;
            else if ((DeltaX<=0)&&(DeltaY<0)) Minus=true;
            if (AbsDeltaX>AbsDeltaY) StepSize=AbsDeltaX;
            else StepSize=AbsDeltaY;
            break;
        case 3 :        // Only Y motion is taken into account
            if (DeltaY>0) Plus=true;
            if (DeltaY<0) Minus=true;
            StepSize=AbsDeltaY;
            break;
        case 4 :
            if ((DeltaX<0)&&(DeltaY>=0)) Plus=true;
            else if ((DeltaX>=0)&&(DeltaY<0)) Minus=true;
            if (AbsDeltaX>AbsDeltaY) StepSize=AbsDeltaX;
            else StepSize=AbsDeltaY;
            break;
        case 5 :        // Only X motion is taken into account
            if (DeltaX>0) Minus=true;
            if (DeltaX<0) Plus=true;
            StepSize=AbsDeltaX;
            break;
        case 6 :
            if ((DeltaX<0)&&(DeltaY<=0)) Plus=true;
            if ((DeltaX>=0)&&(DeltaY>0)) Minus=true;
            if (AbsDeltaX>AbsDeltaY) StepSize=AbsDeltaX;
            else StepSize=AbsDeltaY;
            break;
        case 7 :        // Only Y motion is taken into account
            if (DeltaY>0) Minus=true;
            if (DeltaY<0) Plus=true;
            StepSize=AbsDeltaY;
            break;
    }
    //printf ("Plus Minus : %d %d\n", Plus, Minus);
    //printf ("Step size : %d\n", StepSize);

	// Scale step size to avoid huge jumps in value
    if (StepSize>4)
    {
        StepSize=StepSize>>2;
    }
    else
    {
        PulseDivider+=1;
        if (PulseDivider<5)
        {
            // Cancel the tops until there is enough pulses
            Plus=false;
            Minus=false;
        }
        else (PulseDivider=0);
    }

	if ((Plus == false) && (Minus == false)) return;

	// Update value (step * direction) and check that value stays in range
	OldValue = mValue;
	TestValue = mValue;
	if (Plus) TestValue += StepSize;
	else if (Minus) TestValue -= StepSize;
	if (TestValue<mMin) TestValue = mMin;
	if (TestValue>mMax) TestValue = mMax;
	mValue = TestValue;
	//printf ("%d\n", mValue);

	// Send event to parent if value has changed
	if (mValue != OldValue) this->Moved();

	event.Skip();
}  // wxStaticRotaryEncoder::OnMouse
// ----------------------------------------------------------------------------

void wxStaticRotaryEncoder::Moved (void)
{
	wxCommandEvent event(wxEVT_ENCODER_CHANGE, mId);
	event.SetEventObject(this);
	ProcessEvent (event);
}  // wxStaticRotaryEncoder::Moved
// ----------------------------------------------------------------------------

void wxStaticRotaryEncoder::SetValue(int Value)
{
    if ((Value>=mMin)&&(Value<=mMax)) mValue = Value;
}  // wxStaticRotaryEncoder::SetValue
// ----------------------------------------------------------------------------

void wxStaticRotaryEncoder::SetMinValue (int Value)
{
    mMin = Value;
    if (mValue < mMin) mValue = mMin;
}  // wxStaticRotaryEncoder::SetMinValue
// ----------------------------------------------------------------------------

void wxStaticRotaryEncoder::SetMaxValue (int Value)
{
    mMax = Value;
    if (mValue > mMax) mValue = mMax;
}  // wxStaticRotaryEncoder::SetMaxValue
// ----------------------------------------------------------------------------



