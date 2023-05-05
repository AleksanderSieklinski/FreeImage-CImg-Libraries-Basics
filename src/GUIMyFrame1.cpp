#include "GUIMyFrame1.h"

void GUIMyFrame1::Repaint() {
    m_image.Rescale(m_panel1->GetSize().x, m_panel1->GetSize().y);
	wxClientDC dc1(m_panel1);
	wxBufferedDC dc(&dc1);
	dc.Clear();
	if (animated) {
		dc.DrawBitmap(RenderedFrames[frame_index], 0, 0);
		tick_delay = (tick_delay + 1) % 8;
		if (tick_delay >= 7) frame_index = (frame_index + 1) % 240;
		RefreshRect(wxRect(0,0,1,1),false);
		return;
	}
    wxBitmap m_bitmap(m_image);
	dc.DrawBitmap(m_bitmap, 0, 0);
}

void GUIMyFrame1::On_click1(wxCommandEvent& event) {
    wxFileDialog WxOpenFileDialog(this, _("Choose a file"), _(""), _(""), _("jpg files (*.jpg)|*.jpg"), wxFD_OPEN);
    if(WxOpenFileDialog.ShowModal() == wxID_OK)
    {
        std::ifstream file(WxOpenFileDialog.GetPath().mb_str(), std::ios::binary);
        TinyEXIF::EXIFInfo imageEXIF(file);
        m_image.LoadFile(WxOpenFileDialog.GetPath(), wxBITMAP_TYPE_JPEG);
        m_images.clear();
        m_images.push_back(m_image);
        file.close();
        std::stringstream ss;
        ss << "Rozmiar obrazka: " << m_image.GetWidth() << " * " << m_image.GetHeight() << std::endl;
        if(imageEXIF.Make!="") {
            ss << "EXIF Info: " << imageEXIF.Make << std::endl;
        }
        if(imageEXIF.Copyright!=""){
            ss << "Artist: " << imageEXIF.Copyright << std::endl
            << "Copyright: " << imageEXIF.Copyright << std::endl;
        }
        if(imageEXIF.ResolutionUnit) {
            if (imageEXIF.ResolutionUnit==2) {
                ss << "ResolutionUnit: inches" << std::endl;
            }
            else {
                ss << "ResolutionUnit: centimeters" << std::endl;
            }
        }
        if(imageEXIF.XResolution) {
            ss << "XResolution: " << imageEXIF.XResolution << std::endl;
        }
        //if(imageEXIF.YCbCrPositioning) {
        //    ss << "YCbCrPositioning: " << "Center of pixel array" << std::endl;
        //}
        if(imageEXIF.YResolution) {
            ss << "YResolution: " << imageEXIF.YResolution << std::endl;
        }
        if(imageEXIF.ExposureTime) {
            ss << "ExposureTime: " << imageEXIF.ExposureTime << std::endl;
        }
        if(imageEXIF.Flash) {
            ss << "Flash: " << imageEXIF.Flash << std::endl;
        }
        if(imageEXIF.ISOSpeedRatings) {
            ss << "ISOSpeedRatings: " << imageEXIF.ISOSpeedRatings << std::endl;
        }
        if(imageEXIF.DateTimeOriginal!="") {
            ss << "DateTimeOriginal: " << imageEXIF.DateTimeOriginal << std::endl;
        }
        if(imageEXIF.GeoLocation.Latitude) {
            ss << "GeoLocation.Latitude: " << imageEXIF.GeoLocation.Latitude << std::endl;
        }
        if(imageEXIF.GeoLocation.Longitude) {
            ss << "GeoLocation.Longitude: " << imageEXIF.GeoLocation.Longitude << std::endl;
        }
        if(imageEXIF.GeoLocation.Altitude) {
            ss << "GeoLocation.Altitude: " << imageEXIF.GeoLocation.Altitude << std::endl;
        }
        if(imageEXIF.BitsPerSample) {
            ss << "BitsPerSample: " << imageEXIF.BitsPerSample << std::endl;
        }

        exif = ss.str();
    }
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
    dc2.Clear();
    dc2.DrawBitmap(m_bitmap2, 0, 0, true);
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

wxImage GUIMyFrame1::CImgToWx(cimg_library::CImg<unsigned char> image) {
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
    if(animated == true) {
        m_images.push_back(m_image);
		cimg_library::CImg<unsigned char> img = WxToCImg(m_image);
		float color_spec[3] = { 1.0f, 1.0f, 1.0f };

		for (int i = 0; i < 240; i++) {
            cimg_library::CImg<float> mask1(m_image.GetSize().x, m_image.GetSize().y, 1,3);
            cimg_library::CImg<float> mask2(m_image.GetSize().x, m_image.GetSize().y, 1,3);
			mask1.draw_gaussian((m_image.GetSize().x / 2) + (m_image.GetSize().x * 0.25) * cos(i * M_PI / 240.0f),(m_image.GetSize().y / 2) + (m_image.GetSize().y * 0.25) * sin(i * M_PI / 240.0f),140.0f,color_spec,0.7f);
			mask2.draw_gaussian((m_image.GetSize().x / 2) + (m_image.GetSize().x * 0.25) * cos((i + 240.0f) * M_PI / 240.0f),(m_image.GetSize().y / 2) + (m_image.GetSize().y * 0.25) * sin((i + 240.0f) * M_PI / 240.0f),140.0f,color_spec,0.7f);
			mask1 += mask2;

			cimg_library::CImg<float> img2 = img;
			img2.mul(mask1);
			RenderedFrames[239 - i] = wxBitmap(CImgToWx(img2));
		}
    }
    else {
        m_image = m_images.back();
        m_images.pop_back();
    }
}