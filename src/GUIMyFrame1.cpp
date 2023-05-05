#include "GUIMyFrame1.h"

void GUIMyFrame1::Repaint() {

    m_image.Rescale(m_panel1->GetSize().x, m_panel1->GetSize().y);
    wxBitmap m_bitmap(m_image);
    wxClientDC dc(m_panel1);
    wxBufferedDC dc_buff(&dc);
    dc_buff.Clear();
    dc_buff.DrawBitmap(m_bitmap, 0, 0, true);

    /*static unsigned frame_index = 0;
	static unsigned tick_delay = 0;

	wxClientDC dc1(m_panel1);
	wxBufferedDC dc(&dc1);
	dc.Clear();
    wxBitmap m_bitmap;

	if (m_image.IsOk())
	{
		if (animated)
		{
			dc.DrawBitmap(_animationFrames[frame_index], 0, 0);
			tick_delay = (tick_delay + 1) % 8;
			if (tick_delay >= 7) frame_index = (frame_index + 1) % 60;
			RefreshRect(wxRect(1, 1, 1, 1), false);

			return;
		}
		wxBitmap bitmap(m_image);
		dc.DrawBitmap(m_bitmap, 0, 0);
	}*/

    wxBitmap m_bitmap2;
    m_bitmap2.Create(m_panel2->GetSize().x, m_panel2->GetSize().y);
    wxMemoryDC memDC;
    memDC.SelectObject(m_bitmap2);
    memDC.SetBackground(*wxWHITE_BRUSH);
    memDC.Clear();
    memDC.SetPen(*wxBLACK_PEN);
    memDC.SetBrush(*wxTRANSPARENT_BRUSH);
    memDC.DrawText(exif, 0, 0);
    memDC.SelectObject(wxNullBitmap);
    wxClientDC dc2(m_panel2);   
    wxBufferedDC dc_buff2(&dc2);
    dc_buff2.Clear();
    dc_buff2.DrawBitmap(m_bitmap2, 0, 0, true);
}

void GUIMyFrame1::On_click1(wxCommandEvent& event) {
    wxFileDialog WxOpenFileDialog(this, _("Choose a file"), _(""), _(""), _("jpg files (*.jpg)|*.jpg"), wxFD_OPEN);
    if(WxOpenFileDialog.ShowModal() == wxID_OK)
    {
        std::ifstream file(WxOpenFileDialog.GetPath().mb_str(), std::ios::binary);
        m_image.LoadFile(WxOpenFileDialog.GetPath(), wxBITMAP_TYPE_JPEG);
        m_images.clear();
        m_images.push_back(m_image);
        file.close();
        std::stringstream ss;
        ss << "Rozmiar obrazka: " << m_image.GetWidth() << " * " << m_image.GetHeight() << std::endl
        << "EXIF Info:" << std::endl
        << "Artist: " << std::endl
        << "Copyright:" << std::endl
        << "ResolutionUnit:" << std::endl
        << "XResolution:" << std::endl
        << "YCbCrPositioning:" << std::endl
        << "YResolution:" << std::endl;
        exif = ss.str();
    }
    Repaint();
}

cimg_library::CImg<unsigned char> GUIMyFrame1::WxToCImg(wxImage& image) {
    cimg_library::CImg<unsigned char> img(image.GetWidth(), image.GetHeight(), 1, 3);
    for (int i = 0; i < image.GetWidth(); i++) {
        for (int j = 0; j < image.GetHeight(); j++) {
            img(i, j, 0) = image.GetRed(i, j);
            img(i, j, 1) = image.GetGreen(i, j);
            img(i, j, 2) = image.GetBlue(i, j);
        }
    }
    return img;
}

wxImage GUIMyFrame1::CImgToWx(cimg_library::CImg<unsigned char>& image) {
    wxImage img(image.width(), image.height());
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            img.SetRGB(i, j, image(i, j, 0), image(i, j, 1), image(i, j, 2));
        }
    }
    return img;
}
    
//cenzura
void GUIMyFrame1::On_click2(wxCommandEvent& event) {
    censored == true ? censored = false : censored = true;
    if (censored == true) {
        m_images.push_back(m_image);
        cimg_library::CImg<unsigned char> img= WxToCImg(m_image);
        int startx = img.width() * 0.57;
        int starty = img.height() * 0.02;
        int endx = startx + img.width() * 0.16;
        int endy = starty + img.height() * 0.15;
        cimg_library::CImg<unsigned char> cropped = img.get_crop(startx, starty, endx, endy);
        cropped.blur(7.5);
        img.draw_image(startx, starty, cropped);
        m_image = CImgToWx(img);
    }
    else {
        m_image = m_images.back();
        m_images.pop_back();
    }
}
//erode
void GUIMyFrame1::On_click3(wxCommandEvent& event) {
    eroded == true ? eroded = false : eroded = true;
    if (eroded == true) {
        m_images.push_back(m_image);
        cimg_library::CImg<unsigned char> img = WxToCImg(m_image);
        img.erode(10);
        m_image = CImgToWx(img);
    }
    else {
        m_image = m_images.back();
        m_images.pop_back();
    }
}
//animacja
void GUIMyFrame1::On_check(wxCommandEvent& event) {
    animated == true ? animated = false : animated = true;
    if (animated == true) {
        cimg_library::CImg<unsigned char> img = WxToCImg(m_image);
        float color[3] = { 1, 1, 1 };
        for (int i = 0; i < 240; i++) {
            cimg_library::CImg<unsigned char> mask1(img.width(), img.height(), 1, 3);
            cimg_library::CImg<unsigned char> mask2(img.width(), img.height(), 1, 3);
            mask1.draw_gaussian(
				(img.width() / 2.) + (img.width() * 0.3) * cos(i * M_PI / 60.f),
				(img.height() / 2.) + (img.height() * 0.3) * sin(i * M_PI / 60.f),
				120.0f,
				color,
				1.0f);

			mask2.draw_gaussian(
				(img.width() / 2.) + (img.width() * 0.3) * cos((i + 60.f) * M_PI / 60.f),
				(img.height() / 2.) + (img.height() * 0.3) * sin((i + 60.f) * M_PI / 60.f),
				120.0f,
				color,
				1.0f);
            mask1+=mask2;
            cimg_library::CImg<unsigned char> img2 = img;
            img2.mul(mask1);
            wxImage image = CImgToWx(img2);
            _animationFrames[240-i] = wxBitmap(image);
        }
    }
    else {
        m_image = m_images.back();
        //m_images.pop_back();
    }
}