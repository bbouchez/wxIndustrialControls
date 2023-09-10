/***************************************************************
 * Name:      wxOnOffBitmapButton.h
 * Purpose:   wxWidgets Toggle On/Off button
 * Author:    Benoit BOUCHEZ (BEB)
 * Created:   2020-04-11
 * Copyright: (c) Benoit BOUCHEZ
 * License:   wxWindows licence
 **************************************************************/

#ifndef __ONOFFBITMAPBUTTON_H__
#define __ONOFFBITMAPBUTTON_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class WXDLLIMPEXP_CORE wxOnOffBitmapButton : public wxControl
{
public:
	wxOnOffBitmapButton () { Init(); }

	wxOnOffBitmapButton(wxWindow *parent,
                   wxWindowID id,
                   wxBitmap& offBitmap,
				   wxBitmap& onBitmap,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = wxBORDER_NONE,
                   const wxValidator& validator = wxDefaultValidator,
                   const wxString& name = wxButtonNameStr);

	// Nothing allocated dynamically by the class : keep the default destructor
	//virtual ~wxOnOffBitmapButton();

	bool GetValue() { return mState ; };
	void SetValue(bool state);

	// Allow the button to change state when clicked
	// If not set, the button sends a click event but does not change by itself
	void AllowUserChange (bool Allow);

protected:
	void Init(void);

private:
	DECLARE_DYNAMIC_CLASS(wxOnOffBitmapButton)
	DECLARE_EVENT_TABLE()

	void OnPaint(wxPaintEvent& event);
	void OnMouse(wxMouseEvent& event);
	void Click(void);

	bool mState;
	wxBitmap* mOffBitmap;
	wxBitmap* mOnBitmap;
	wxWindowID mId;
	bool MouseInControl;			// Mouse cursor is on the control surface
	bool UserToggleAllowed;
};

#endif  // __ONOFFBITMAPBUTTON_H__
