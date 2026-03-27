/***************************************************************
 * Name:      wxKickToggleButton.cpp
 * Purpose:   wxWidgets Kick (monostable) / Toggle (bistable) button
 * Author:    Benoit BOUCHEZ (BEB)
 * Created:   2020-04-11
 * Copyright: (c) Benoit BOUCHEZ
 * License:   wxWindows licence
 **************************************************************/

#include "wxKickToggleButton.h"

wxKickToggleButton::wxKickToggleButton (wxWindow* Parent, unsigned int ButtonType, wxPoint ButtonPosition, wxSize ButtonSize, wxBitmap* OffBitmap, wxBitmap* OnBitmap)
{
    this->myParent=Parent;
    this->ToggleStatus=false;
    this->Type=ButtonType;
    this->Position=ButtonPosition;
    this->Size=ButtonSize;
    this->OffImage=OffBitmap;
    this->OnImage=OnBitmap;
}  // wxKickToggleButton::wxKickToggleButton
// --------------------------------------------------------------

void wxKickToggleButton::OnPaint (wxDC& dc)
{
    if (ToggleStatus) dc.DrawBitmap(*OnImage, Position, false);
    else dc.DrawBitmap(*OffImage, Position, false);
}  // wxKickToggleButton::OnPaint
// --------------------------------------------------------------

bool wxKickToggleButton::OnMouseDown (wxMouseEvent& event)
{
    wxPoint MousePoint(event.GetPosition());

        // Check that mouse is located within the encoder area
    if ((MousePoint.x>=this->Position.x)&&(MousePoint.x<this->Position.x+this->Size.GetWidth()))
    {
        if ((MousePoint.y>=this->Position.y)&&(MousePoint.y<this->Position.y+this->Size.GetHeight()))
        {
            // if we have a Kick button :
            // - show it active until button is released
			if (this->Type == BUTTON_TYPE_KICK)
			{
                ToggleStatus=true;
                wxClientDC dc(myParent);
                this->OnPaint(dc);
                return true;
			}
            // if we have a PUSH button
            // - set status to true
            // - change bitmap to active
            else if (this->Type==BUTTON_TYPE_PUSH)
            {
                ToggleStatus=true;
                wxClientDC dc(myParent);
                this->OnPaint(dc);
                return true;
            }

            // if we have a Toggle button
            // - switch status
            // - change bitmap accordingly
            else if (this->Type==BUTTON_TYPE_TOGGLE)
            {
                ToggleStatus=!ToggleStatus;
                wxClientDC dc(myParent);
                this->OnPaint(dc);
                return true;
            }
        }
    }

    return false;
}  // wxKickToggleButton::OnMouseDown
// --------------------------------------------------------------

void wxKickToggleButton::OnMouseUp (wxMouseEvent& WXUNUSED(event))
{
    // In all cases, button are released when button is up
    // Nothing special to do for toggle buttons
    if (Type==BUTTON_TYPE_KICK)
    {
        ToggleStatus=false;
        wxClientDC dc(myParent);
        this->OnPaint(dc);
    }
}  // wxKickToggleButton::OnMouseUp
// --------------------------------------------------------------

bool wxKickToggleButton::IsActive (void)
{
    return this->ToggleStatus;
}  // wxKickToggleButton::IsActive
// --------------------------------------------------------------

void wxKickToggleButton::SetStatus (bool NewStatus)
{
    ToggleStatus=NewStatus;
    wxClientDC dc(myParent);
    this->OnPaint(dc);
}  // wxKickToggleButton::SetStatus
// --------------------------------------------------------------
