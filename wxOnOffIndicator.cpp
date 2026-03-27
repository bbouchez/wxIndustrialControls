/***************************************************************
 * Name:      wxOnOffIndicator.cpp
 * Purpose:   Dual bitmap indicator for wxWidgets applications
 * Author:    Benoit BOUCHEZ (benoit@imodular-synth.com)
 * Created:   2020-04-11
 * Copyright: Benoit BOUCHEZ (www.imodular-synth.com)
 * License:
 **************************************************************/

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

#include "wxOnOffIndicator.h"

BEGIN_EVENT_TABLE (wxOnOffIndicator, wxWindow)
	EVT_PAINT (wxOnOffIndicator::OnPaint)
END_EVENT_TABLE()

wxOnOffIndicator::wxOnOffIndicator (wxWindow* Parent, wxPoint IndicatorPosition, wxSize IndicatorSize, wxBitmap& OffBitmap, wxBitmap& OnBitmap) : wxWindow (Parent, -1, IndicatorPosition, IndicatorSize)
{
    myParent=Parent;
    ToggleStatus=false;
    Position=IndicatorPosition;
    Size=IndicatorSize;
    OffImage=&OffBitmap;
    OnImage=&OnBitmap;

	if (Parent) SetBackgroundColour (Parent->GetBackgroundColour());
	else SetBackgroundColour (*wxLIGHT_GREY);
}  // wxOnOffIndicator::wxOnOffIndicator
// --------------------------------------------------------------

void wxOnOffIndicator::SetStatus(bool Status)
{
	if (Status != ToggleStatus)		// Avoid to send refresh() event when indicator state does not change
	{
		ToggleStatus=Status;
		Refresh();
	}
}  // wxOnOffIndicator::SetStatus
// --------------------------------------------------------------

void wxOnOffIndicator::OnPaint (wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);

	printf ("Painting\n");

	// We have to draw the bitmap at 0, 0 since the position is related to the wxWindow object (not the frame)
    if (ToggleStatus) dc.DrawBitmap(*OnImage, wxPoint (0, 0), false);
    else dc.DrawBitmap(*OffImage, wxPoint (0, 0), false);
}  // wxOnOffIndicator::OnPaint
// --------------------------------------------------------------
