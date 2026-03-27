/***************************************************************
 * Name:      wxBargraph.h
 * Purpose:   Simple Horizontal / Vertical bargraph for wxWidgets applications
 * Author:    Benoit BOUCHEZ (BEB)
 * Created:   2020-04-11
 * Copyright: (c) Benoit BOUCHEZ
 * License:   wxWindows licence
 **************************************************************/

#ifndef __WXBARGRAPH_H__
#define __WXBARGRAPH_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class WXDLLIMPEXP_CORE wxBargraph
{
public:
    wxBargraph(wxWindow* Parent,
                bool Vertical,
                float InitialValue,
                wxPoint LLPosition,
                wxSize GraphSize,
                wxColor BarColor,
                wxColor BackColor,
                wxBrushStyle Style);
    ~wxBargraph();

    //! To call when when parent sends a OnPaint event
    void OnPaint (wxDC& dc);

    //! Bargraph value is 0.0 to 1.0
    void SetValue (float NewValue);
private:
    wxWindow* myParent;
    float CurrentValue;
    wxPoint LowerLeft;
    wxSize Size;
    wxBrushStyle BrushStyle;
    wxColor FColor;
    wxColor BColor;             // Background color
};

#endif // __WXBARGRAPH_H__
