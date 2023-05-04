#include "GUIMyFrame1.h"

void GUIMyFrame1::Repaint() {
    
    m_image.Rescale(m_panel1->GetSize().x, m_panel1->GetSize().y);
    wxBitmap m_bitmap(m_image);
    wxClientDC dc(m_panel1);
    wxBufferedDC dc_buff(&dc);
    dc_buff.Clear();
    dc_buff.DrawBitmap(m_bitmap, 0, 0, true);

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
        file.close();
        std::stringstream ss;
        ss << "Rozmiar obrazka: " << m_image.GetWidth() << " * " << m_image.GetHeight() << std::endl;
        exif = ss.str();
    }
    Repaint();
}
    

void GUIMyFrame1::On_click2(wxCommandEvent& event) {
    event.Skip();
}

void GUIMyFrame1::On_click3(wxCommandEvent& event) {
    event.Skip();
}

void GUIMyFrame1::On_check(wxCommandEvent& event) {
    event.Skip();
}