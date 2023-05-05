///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-282-g1fa54006)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,200 ), wxDefaultSize );

	wxBoxSizer* bSizer1main;
	bSizer1main = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer2in;
	bSizer2in = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer3gui;
	bSizer3gui = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer4load;
	bSizer4load = new wxBoxSizer( wxVERTICAL );

	m_button1 = new wxButton( this, wxID_ANY, _("Wczytaj obrazek"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4load->Add( m_button1, 0, wxALL|wxEXPAND, 5 );


	bSizer3gui->Add( bSizer4load, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5cens;
	bSizer5cens = new wxBoxSizer( wxVERTICAL );

	m_button2 = new wxButton( this, wxID_ANY, _("Cenzura"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5cens->Add( m_button2, 0, wxALL|wxEXPAND, 5 );


	bSizer3gui->Add( bSizer5cens, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer6erd;
	bSizer6erd = new wxBoxSizer( wxVERTICAL );

	m_button3 = new wxButton( this, wxID_ANY, _("Erode"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6erd->Add( m_button3, 0, wxALL|wxEXPAND, 5 );


	bSizer3gui->Add( bSizer6erd, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer7chck;
	bSizer7chck = new wxBoxSizer( wxVERTICAL );

	m_checkBox1 = new wxCheckBox( this, wxID_ANY, _("Animacja"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7chck->Add( m_checkBox1, 0, wxALL|wxEXPAND|wxSHAPED, 5 );


	bSizer3gui->Add( bSizer7chck, 1, wxEXPAND, 5 );


	bSizer2in->Add( bSizer3gui, 1, wxEXPAND, 5 );


	wxBoxSizer* bSizer8exif;
	bSizer8exif = new wxBoxSizer( wxVERTICAL );

	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition,wxSize(300,500), wxTAB_TRAVERSAL );
	m_panel2->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	
	bSizer8exif->Add( m_panel2, 1, wxEXPAND | wxALL, 5 );

	bSizer2in->Add( bSizer8exif, 1, wxEXPAND, 5 );

	bSizer1main->Add( bSizer2in, 0, 0, 5 );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );

	bSizer1main->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer1main );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MyFrame1::MainFormClose ) );
	m_panel1->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MyFrame1::WxPanel_Repaint ), NULL, this );
	m_panel2->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MyFrame1::WxPanel_Repaint ), NULL, this );
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::On_click1 ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::On_click2 ), NULL, this );
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::On_click3 ), NULL, this );
	m_checkBox1->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::On_check ), NULL, this );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MyFrame1::MainFormClose ) );
	m_panel1->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MyFrame1::WxPanel_Repaint ), NULL, this );
	m_panel2->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MyFrame1::WxPanel_Repaint ), NULL, this );
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::On_click1 ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::On_click2 ), NULL, this );
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::On_click3 ), NULL, this );
	m_checkBox1->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::On_check ), NULL, this );

}
