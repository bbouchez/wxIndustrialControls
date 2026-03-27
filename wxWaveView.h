/***************************************************************
 * Name:      wxWaveView.h
 * Purpose:   Wave viewer created originally for the DSS1 Editor
 * Created:   2024-02/09
 * Copyright: (c) Benoit BOUCHEZ
 * License:   wxWindows licence
 **************************************************************/

#ifndef __WXWAVEVIEW_H__
#define __WXWAVEVIEW_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class WXDLLIMPEXP_CORE wxWaveView : public wxControl
{
public:
	wxWaveView(wxWindow* Parent,
		wxPoint LLPosition,
		wxSize GraphSize);

	void OnPaint(wxDC& dc);
private:
	wxWindow* myParent;
	wxSize Size;
};

#endif