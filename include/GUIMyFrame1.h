#pragma once
#include "GUI.h"
#include "CImg.h"
#include "TinyEXIF.h"
#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include <string>
#include <sstream>
#include <wx/filedlg.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/colourdata.h>
#include <wx/colordlg.h>
#include <wx/dir.h>
#include <wx/msgdlg.h>
#include <wx/numdlg.h>
#include <wx/pen.h>
#include <wx/brush.h>
#include <wx/font.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/dc.h>
#include <wx/dcgraph.h>
#include <wx/dcmirror.h>
#include <wx/dcscreen.h>
#include <wx/dcsvg.h>
#include <wx/dcprint.h>


class GUIMyFrame1 : public MyFrame1 {
    protected:
		wxButton* m_button1;
		wxButton* m_button2;
		wxButton* m_button3;
		wxCheckBox* m_checkBox1;

		virtual void MainFormClose( wxCloseEvent& event ){ Destroy(); }
        virtual void WxPanel_Repaint( wxUpdateUIEvent& event ){ Repaint();}
		virtual void On_click1( wxCommandEvent& event );
		virtual void On_click2( wxCommandEvent& event );
		virtual void On_click3( wxCommandEvent& event );
		virtual void On_check( wxCommandEvent& event );
        void Repaint();
		cimg_library::CImg<unsigned char> WxToCImg(wxImage& image);
		wxImage CImgToWx(cimg_library::CImg<unsigned char> image);

	public:

		GUIMyFrame1( wxWindow* parent): MyFrame1(parent){wxInitAllImageHandlers(); m_panel1->SetBackgroundColour(wxColor(*wxBLACK));};
		~GUIMyFrame1(){};
        wxImage m_image;
		std::vector<wxImage> m_images;
        wxString exif;
		bool censored = false, eroded = false, animated = false;
		wxBitmap RenderedFrames[240];
		int frame_index = 0;
		int tick_delay = 0;
};
