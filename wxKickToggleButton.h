 /***************************************************************
  * Name:      wxKickToggleButton.h
  * Purpose:   wxWidgets Kick (monostable) / Toggle (bistable) button
  * Author:    Benoit BOUCHEZ (BEB)
  * Created:   2020-04-11
  * Copyright: (c) Benoit BOUCHEZ
  * License:   wxWindows license
  **************************************************************/

#ifndef __WXKICKTOGGLEBUTTON_H__
#define __WXKICKTOGGLEBUTTON_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#define BUTTON_TYPE_TOGGLE      0       // State hanges each time button is clicked
#define BUTTON_TYPE_KICK        1       // Button is set only when clicked then released
#define BUTTON_TYPE_PUSH        2       // Button latches when clicked (released by software not by touch)

class wxKickToggleButton
{
public:
    wxKickToggleButton (wxWindow* Parent, unsigned int ButtonType, wxPoint ButtonPosition, wxSize ButtonSize, wxBitmap* OffBitmap, wxBitmap* OnBitmap);

    //! Trigger action on the button when clicked
    //! \return true if button has been activated (mouse in control area)
    bool OnMouseDown (wxMouseEvent& event);

    //! Release action on button if needed
    void OnMouseUp (wxMouseEvent& event);

    //! To call when when parent sends a OnPaint event
    void OnPaint (wxDC& dc);

    //! Return the status of the button
    bool IsActive (void);

    //! Force the status of the button
    void SetStatus (bool NewStatus);

private:
    wxWindow* myParent;
    unsigned int Type;
    bool ToggleStatus;      // Toggle button is active / inactive
    wxPoint Position;
    wxSize Size;
    wxBitmap* OffImage;
    wxBitmap* OnImage;
};

#endif // __WXKICKTOGGLEBUTTON_H__
