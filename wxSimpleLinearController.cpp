/////////////////////////////////////////////////////////////////////////////
// Name:        LinearRegulator.cpp
// Purpose:     wxIndustrialControls Library
// Author:      Marco Cavallini <m.cavallini AT koansoftware.com>
// Modified by: Benoit BOUCHEZ (BEB)
// Copyright:   (C)2004-2006 Copyright by Koan s.a.s. - www.koansoftware.com
// Licence:     KWIC License http://www.koansoftware.com/kwic/kwic-license.htm
/////////////////////////////////////////////////////////////////////////////

/*
 Release notes

 Nov, 14, 2020
 - port under wxWidgets 3.0
 - comments translated to english
 - code refactorization
 - m_Font default initialization to wxSMALL_FONT. When m_Font is not initialized, the class
   crashes under Linux (it works under Windows because it is set the 0 by default)
 - changed ProcessCommand() to ProcessEvents()
*/

#ifndef WX_PRECOMP
	#include "wx/wx.h"
#endif

#include "wxSimpleLinearController.h"
#include <wx/event.h>
#include <math.h>

IMPLEMENT_DYNAMIC_CLASS(wxSimpleLinearController, wxControl)

BEGIN_EVENT_TABLE(wxSimpleLinearController,wxControl)
	EVT_MOUSE_EVENTS(wxSimpleLinearController::OnMouse)
	EVT_PAINT(wxSimpleLinearController::OnPaint)
END_EVENT_TABLE()

wxSimpleLinearController::wxSimpleLinearController(wxWindow* parent,
		                   const wxWindowID id,
                           const wxPoint& pos,
                           const wxSize& size,
		                   const long int style)
	: wxControl(parent, id, pos, size, style)
{

	m_id = id;

	m_ControlSize = size ;

	m_nScaledVal = 0;
	m_nRealVal = 0;
	m_nTagsNum = 0;

	m_nStato = 0;
	m_nMin = 0;
	m_nMax = 100;

	m_bDirHorizFlag = true;
	m_bShowCurrent = true;
	m_bShowLimits= true;

	m_cActiveBar = *wxGREEN;
	m_cPassiveBar = *wxWHITE;
	m_cBorderColour = *wxRED;
	m_cTagsColour = *wxBLACK;
	m_cValueColour = *wxRED;
	m_cLimitColour = *wxBLACK ;

	m_bShowLimits = true ;
	m_bShowCurrent = true ;

	membitmap = new wxBitmap(size.GetWidth(), size.GetHeight()) ;
	m_Font = *wxSMALL_FONT;
}  // wxSimpleLinearController::wxSimpleLinearController
// -----------------------------------------------------

wxSimpleLinearController::~wxSimpleLinearController()
{
	if (membitmap)
		delete membitmap ;
}  // wxSimpleLinearController::~wxSimpleLinearController
// -----------------------------------------------------

void wxSimpleLinearController::OnPaint(wxPaintEvent &WXUNUSED(event))
{
	wxPaintDC old_dc(this);

	int w,h;
	int yPoint, rectHeight ;

	GetClientSize(&w,&h);

	wxMemoryDC dc;
	dc.SelectObject(*membitmap);

	dc.SetBackground(*wxTheBrushList->FindOrCreateBrush(m_cPassiveBar,wxBRUSHSTYLE_SOLID));
	dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(m_cPassiveBar,wxBRUSHSTYLE_SOLID));
	dc.Clear();

	dc.SetPen(*wxThePenList->FindOrCreatePen(m_cBorderColour, 1, wxPENSTYLE_SOLID));
	dc.DrawRectangle(0, 0, w, h);

	dc.SetPen(*wxThePenList->FindOrCreatePen(m_cActiveBar, 1, wxPENSTYLE_SOLID));
	dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(m_cActiveBar,wxBRUSHSTYLE_SOLID));


	if(m_bDirHorizFlag)
		dc.DrawRectangle(1, 1, m_nScaledVal, h - 2);
	else
	{
		yPoint = h - m_nScaledVal ;

		if (m_nScaledVal == 0 )
			rectHeight = m_nScaledVal ;
		else
		{
			if (m_nRealVal == m_nMax)
			{
				rectHeight = m_nScaledVal;
				yPoint -= 1 ;
			}
			else
				rectHeight = m_nScaledVal - 1 ;
		}

		dc.DrawRectangle(1, yPoint, w - 2, rectHeight);
	}

	if (m_bShowCurrent)
		DrawCurrentValue(dc);

	if (m_bShowLimits)
		DrawLimits(dc);

	if (m_nTagsNum > 0 )
		DrawTags(dc);

	old_dc.Blit(0, 0, w, h, &dc, 0, 0);
}  // wxSimpleLinearController::OnPaint
// -----------------------------------------------------

void wxSimpleLinearController::OnMouse(wxMouseEvent& event)
{
	if (m_nStato == 0 && event.Entering())	//dentro nel controllo
		m_nStato = 1 ;
	else if (m_nStato >= 1 && event.Leaving())	//fuori dal controllo
		m_nStato = 0 ;
	else if (m_nStato == 1 && event.LeftDown())	//click o inizio trascinamento
	{
//		wxLogTrace("Mouse Premuto") ;
		m_nStato = 2 ;
		m_mousePosition = event.GetPosition();
		DrawPosition() ;
	}
	else if (m_nStato == 2 && event.LeftIsDown())	//trascinamento
	{
		m_mousePosition = event.GetPosition();
		DrawPosition() ;
	}
	else if (m_nStato == 2 && event.LeftUp())	//fine trascinamento o rilascio click
	{
		m_nStato = 1 ;
	}
}  // wxSimpleLinearController::OnMouse
// -----------------------------------------------------

void wxSimpleLinearController::DrawPosition()
{
	double coeff = 0 ;
	bool draw = true ;

	if (m_bDirHorizFlag)
	{
		m_nScaledVal = m_mousePosition.x ;
		if ( m_nScaledVal < 0 || m_nScaledVal >= m_ControlSize.GetWidth() - 1)
			draw = false ;
		else
			coeff = (m_ControlSize.GetWidth() - 2) / (double)(m_nMax - m_nMin);
	}
	else
	{
		m_nScaledVal = m_ControlSize.GetHeight() - m_mousePosition.y;
		if ( m_nScaledVal < 0 || m_nScaledVal >= m_ControlSize.GetHeight() - 1)
			draw = false ;
		else
			coeff = (m_ControlSize.GetHeight() - 2) / (double)(m_nMax - m_nMin);
	}


	if (m_nRealVal <= m_nMax && draw)
	{
		m_nRealVal = floor(m_nScaledVal / coeff) ;
		Refresh() ;
		Change() ;
	}
}  // wxSimpleLinearController::DrawPosition
// -----------------------------------------------------

void wxSimpleLinearController::AddTag(int val)
{
	m_aTagsVal[m_nTagsNum++] = val ;
}  // wxSimpleLinearController::AddTag
// -----------------------------------------------------

void wxSimpleLinearController::Change()
{
	wxCommandEvent event(wxEVT_LINEARCONTROLLER, GetId());
	event.SetEventObject(this);
	ProcessEvent (event);
}  // wxSimpleLinearController::Change
// -----------------------------------------------------

void wxSimpleLinearController::SetValue(int val)
{
	int w,h;
	double coeff;

	GetClientSize(&w,&h);

	if(m_bDirHorizFlag)
		coeff = (w - 2) / (double)(m_nMax - m_nMin);
	else
		coeff = (h - 2) / (double)(m_nMax - m_nMin);

	m_nScaledVal = ceil((val - m_nMin) * coeff);
	m_nRealVal = val;

	Refresh();
}  // wxSimpleLinearController::SetValue
// -----------------------------------------------------

void wxSimpleLinearController::DrawCurrentValue(wxDC &dc)
{
	int w,h;
	int tw,th;
	wxString s;

	GetClientSize(&w, &h);

	dc.SetFont (m_Font);
	s.Printf(wxT("%d"), m_nRealVal);
	dc.GetTextExtent(s, &tw, &th);
	dc.SetTextForeground(m_cValueColour);
	dc.DrawText(s, w / 2 - tw / 2 , h / 2 - th / 2);
}  // kwxLinearRegulator::DrawCurrentValue
// -----------------------------------------------------

void wxSimpleLinearController::DrawLimits(wxDC &dc)
{
	int w,h;
	int tw,th;
	wxString s;

	GetClientSize(&w, &h);

	dc.SetFont(m_Font);
	dc.SetTextForeground(m_cLimitColour);

	if(m_bDirHorizFlag)
	{
		// Minimal value
		s.Printf(wxT("%d"), m_nMin);
		dc.GetTextExtent(s, &tw, &th);
		dc.DrawText(s, 5, h / 2 - th / 2);

		// Maximal value
		s.Printf(wxT("%d"), m_nMax);
		dc.GetTextExtent(s, &tw, &th);
		dc.DrawText(s,w - tw - 5, h / 2 - th / 2);
	}
	else
	{
		// Minimal value
		s.Printf(wxT("%d"), m_nMin);
		dc.GetTextExtent(s, &tw, &th);
		dc.DrawText(s, w / 2 - tw / 2, h - th - 5);

		// Maximal value
		s.Printf(wxT("%d"), m_nMax);
		dc.GetTextExtent(s, &tw, &th);
		dc.DrawText(s, w / 2 - tw / 2, 5);
	}

}  // kwxLinearRegulator::DrawLimits
// -----------------------------------------------------

void wxSimpleLinearController::DrawTags(wxDC &dc)
{
	int ntag = 0 ;
	int w, h ;
	int tw,th;
	int scalval = 0 ;
	double tcoeff ;

	wxString text ;

	GetClientSize(&w,&h);
	if(m_bDirHorizFlag)
		tcoeff = (w - 2) / (double)(m_nMax - m_nMin);
	else
		tcoeff = (h - 2) / (double)(m_nMax - m_nMin);

	dc.SetPen(*wxThePenList->FindOrCreatePen(m_cTagsColour, 1, wxPENSTYLE_SOLID));
	dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(m_cTagsColour,wxBRUSHSTYLE_SOLID));
	dc.SetTextForeground(m_cTagsColour);

	while (ntag < m_nTagsNum)
	{
		scalval = floor((m_aTagsVal[ ntag] - m_nMin) * tcoeff);
		text.Printf(wxT("%d"), m_aTagsVal[ ntag]) ;

		if(m_bDirHorizFlag)
		{
			dc.DrawLine(scalval + 1, h - 2 , scalval + 1, h - 10);
			dc.GetTextExtent(text, &tw, &th);
			dc.DrawText(text, scalval + 1 - (tw / 2 ), h - 10 - th);
		}
		else
		{
			dc.DrawLine(w - 2, h - scalval , w - 10 , h - scalval);
			dc.GetTextExtent(text, &tw, &th);
			dc.DrawText(text, w - 10 - tw, h - scalval - (th / 2) );
		}

		ntag++ ;
	}
}  // kwxLinearRegulator::DrawTags
// -----------------------------------------------------


