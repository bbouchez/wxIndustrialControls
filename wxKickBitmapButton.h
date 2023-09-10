/***************************************************************
 * Name:      wxKickBitmapButton.h
 * Purpose:   wxWidgets Kick button
 * Author:    Benoit BOUCHEZ (BEB)
 * Created:   2020-04-11
 * Copyright: (c) Benoit BOUCHEZ
 * License:   wxWindows licence
 **************************************************************/

#ifndef __KICKBITMAPBUTTON_H__
#define __KICKBITMAPBUTTON_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class WXDLLIMPEXP_CORE wxKickBitmapButton : public wxControl
{
public:
	wxKickBitmapButton () { Init(); }	
	
	wxKickBitmapButton(wxWindow *parent,
                   wxWindowID id,
                   wxBitmap& offBitmap,
				   wxBitmap& onBitmap,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = wxBORDER_NONE,
                   const wxValidator& validator = wxDefaultValidator,
                   const wxString& name = wxButtonNameStr);

	// Nothing allocated dynamically by the class : keep the default destructor
	//virtual ~wxKickBitmapButton();

protected:
	void Init(void);

private:
	DECLARE_DYNAMIC_CLASS(wxKickBitmapButton)
	DECLARE_EVENT_TABLE()

	void OnPaint(wxPaintEvent& event);
	void OnMouse(wxMouseEvent& event);
	void Click(void);

	wxBitmap* mOffBitmap;
	wxBitmap* mOnBitmap;
	wxWindowID mId;
	bool MouseInControl;			// Mouse cursor is on the control surface
	bool mState;
};

#endif  // __KICKBITMAPBUTTON_H__