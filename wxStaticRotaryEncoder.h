/***************************************************************
 * Name:      wxStaticRotaryEncoder.h
 * Purpose:   Rotary encoder widgets for wxWidgets applications
 * Author:    Benoit BOUCHEZ (BEB)
 * Created:   2020-04-11
 * Copyright: (c) Benoit BOUCHEZ
 * License:	  wxWidgets license
 **************************************************************/

#ifndef __STATICROTARYENCODER_H__
#define __STATICROTARYENCODER_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

// Event generated by this control
const int wxEVT_ENCODER_FIRST = wxEVT_FIRST + 5402;

const wxEventType wxEVT_ENCODER_CHANGE	= wxEVT_ENCODER_FIRST + 1;

#define EVT_ROTARYENCODER_CHANGE(id, fn)	\
		DECLARE_EVENT_TABLE_ENTRY(wxEVT_ENCODER_CHANGE, id, -1, \
		(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
		(wxObject*)NULL ),

class WXDLLIMPEXP_CORE wxStaticRotaryEncoder : public wxControl
{
public:
	wxStaticRotaryEncoder () { Init(); }

	wxStaticRotaryEncoder(wxWindow *parent,
                   wxWindowID id,
                   wxBitmap& backgroundBitmap,
				   int MinimumValue,
				   int MaximumValue,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = wxBORDER_NONE,
                   const wxValidator& validator = wxDefaultValidator,
                   const wxString& name = wxButtonNameStr);

	// Nothing allocated dynamically by the class : keep the default destructor
	// virtual ~wxStaticRotaryEncoder();

	int GetValue() { return mValue ; };
	void SetValue(int value);

	void SetMinValue (int Value);
	void SetMaxValue (int Value);

protected:
	void Init(void);

private:
	DECLARE_DYNAMIC_CLASS(wxStaticRotaryEncoder)
	DECLARE_EVENT_TABLE()

	void OnPaint(wxPaintEvent& event);
	void OnMouse(wxMouseEvent& event);
	void Moved(void);		// Called when encoder is moved

	wxWindowID mId;
	int mValue;
	wxBitmap* mBackBitmap;			// Background bitmap
	bool MouseInControl;			// Mouse cursor is on the control surface
	wxSize mSize;
	unsigned int PulseDivider;		// Mouse ticks / value change ticks
	int LastTouchX;
	int LastTouchY;
	bool EncoderActive;			// Touch started in encoder area
	int OneThirdX, TwoThirdX;		// Control is splitted in 9 zones (quadrants)
	int OneThirdY, TwoThirdY;
	int mMin, mMax;				// Minimum and maximum value
};

#endif		// __STATICROTARYENCODER_H__