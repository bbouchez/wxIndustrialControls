/***************************************************************
 * Name:      wxBargraph.cpp
 * Purpose:   Simple Horizontal / Vertical bargraph for wxWidgets applications
 * Author:    Benoit BOUCHEZ (BEB)
 * Created:   2020-04-11
 * Copyright: (c) Benoit BOUCHEZ
 * License:   wxWindows licence
 **************************************************************/

#include "wxBargraph.h"

wxBargraph::wxBargraph(wxWindow* Parent, bool Vertical, float InitialValue, wxPoint LLPosition, wxSize GraphSize, wxColor BarColor, wxColor BackColor, wxBrushStyle Style)
{
    this->myParent=Parent;
    this->LowerLeft=LLPosition;
    this->Size=GraphSize;
    this->CurrentValue=InitialValue;
    this->BrushStyle=Style;
    this->FColor=BarColor;
    this->BColor=BackColor;
}  // wxBargraph::wxBargraph
// --------------------------------------------------------------

wxBargraph::~wxBargraph()
{
}  // wxBargraph::~wxBargraph
// --------------------------------------------------------------

void wxBargraph::OnPaint (wxDC& dc)
{
    wxBrush ActiveBrush;
    wxBrush BackBrush;
    unsigned int ActiveHeight;      // Height in pixels of active area

    // TODO : implement horizontal bargraph

    // *** Vertical bargraph ***
    // Compute lower area limit (active value)
    ActiveHeight=CurrentValue*(float)Size.GetHeight();

	wxPen ActivePen (FColor, 1);
	dc.SetPen(ActivePen);
	ActiveBrush = wxBrush (FColor, BrushStyle);
	dc.SetBrush(ActiveBrush);
	// Rectangles are drawn downward, so we start from the middle
	dc.DrawRectangle(LowerLeft.x, LowerLeft.y-ActiveHeight, Size.GetWidth(), ActiveHeight);

	// Draw inactive aera in background color and using solid fill
	wxPen BackPen (BColor, 1);
	dc.SetPen (BackPen);
	BackBrush = wxBrush (BColor, wxBRUSHSTYLE_SOLID);
	dc.SetBrush(BackBrush);
	dc.DrawRectangle(LowerLeft.x, LowerLeft.y-Size.GetHeight(), Size.GetWidth(), Size.GetHeight()-ActiveHeight);

	dc.SetBrush (wxNullBrush);
	dc.SetPen (wxNullPen);
}  // wxBarpgraph::OnPaint
// --------------------------------------------------------------

void wxBargraph::SetValue (float NewValue)
{
    if (NewValue==this->CurrentValue) return;     // Avoid refreshing graphics for nothing

    if (NewValue<0.0f) NewValue=0.0f;
    if (NewValue>1.0f) NewValue=1.0f;
    this->CurrentValue=NewValue;
    wxClientDC dc(myParent);
    this->OnPaint(dc);
}  // wxBargraph::SetValue
// --------------------------------------------------------------
