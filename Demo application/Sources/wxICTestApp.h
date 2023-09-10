/////////////////////////////////////////////////////////////////////////////
// Name:        wxICTestApp.h
// Purpose:     Application entry point for wxIndustrialControl test app
// Author:      Benoit BOUCHEZ
// Modified by:
// Created:     
// Copyright:   (c) BEB Digital Audio
/////////////////////////////////////////////////////////////////////////////

#ifndef __WXICTESTAPP_H__
#define __WXICTESTAPP_H__

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

// Define a new application type, each program should derive a class from wxApp
class CwxICTestApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------
	// wxOVERRIDE can be added as an option on Windows and Mac OS.
	// wxOVERRIDE is not recognized on Linux 

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();		
	virtual int OnExit();
};

#endif