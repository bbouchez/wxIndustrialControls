/***************************************************************
 * Name:      wxOnOffIndicator.h
 * Purpose:   Dual bitmap indicator for wxWidgets applications
 * Author:    Benoit BOUCHEZ (benoit@imodular-synth.com)
 * Created:   2020-04-11
 * Copyright: Benoit BOUCHEZ (www.imodular-synth.com)
 * License:	  wxWidgets
 **************************************************************/

#ifndef __WXONOFFINDICATOR_H__
#define __WXONOFFINDICATOR_H__

class wxOnOffIndicator : public wxWindow
{
public:
    wxOnOffIndicator (wxWindow* Parent, wxPoint IndicatorPosition, wxSize IndicatorSize, wxBitmap& OffBitmap, wxBitmap& OnBitmap);

    //! To call when when parent sends a OnPaint event
    void OnPaint (wxPaintEvent& event);

    //! Return the status of the button
    void SetStatus (bool Status);

private:
	DECLARE_EVENT_TABLE()
    wxWindow* myParent;
    bool ToggleStatus;      // Toggle button is active / inactive
    wxPoint Position;
    wxSize Size;
    wxBitmap* OffImage;
    wxBitmap* OnImage;
};


#endif // __WXONOFFINDICATOR_H__
