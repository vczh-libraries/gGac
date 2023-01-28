//
// Created by roodkcab on 6/27/21.
//

#include "GGacClipboardService.h"
#include "GGacImageService.h"
#include <gtkmm/clipboard.h>

namespace vl {

	namespace presentation {

		namespace gtk {

            GGacClipboardWriter::GGacClipboardWriter(GGacClipboardService* _service) 
            {
            }

            void GGacClipboardWriter::SetText(const WString& value) 
            {
                auto clipboard = Gtk::Clipboard::get();
                clipboard->set_text(Glib::ustring::format(value.Buffer()));
            }

            void GGacClipboardWriter::SetDocument(Ptr<DocumentModel> value) 
            {
                auto clipboard = Gtk::Clipboard::get();
                clipboard->set_text(Glib::ustring::format(value->GetText(true).Buffer()));
                //TODO: set image
            }

            void GGacClipboardWriter::SetImage(Ptr<INativeImage> value) 
            {
                /*
                auto clipboard = Gtk::Clipboard::get();
                clipboard->set_image(static_cast<GGacImageFrame *>(static_cast<GGacImage *>(value.Obj())->GetFrame(0))->GetPixbuf());
                 */
            }

            bool GGacClipboardWriter::Submit() 
            {
                return true;
            }

            ////
            GGacClipboardReader::GGacClipboardReader(GGacClipboardService* _service)
            {
            }

            bool GGacClipboardReader::ContainsText() 
            {
                auto clipboard = Gtk::Clipboard::get();
                return clipboard->wait_is_text_available();
            }

            WString GGacClipboardReader::GetText() 
            {
                auto clipboard = Gtk::Clipboard::get();
                auto text = clipboard->wait_for_text();
                return WString((wchar_t *) g_convert(text.c_str(), -1, "wchar_t", "utf-8", NULL, NULL, NULL));
            }

            bool GGacClipboardReader::ContainsDocument() 
            {
                return false;
            }

            Ptr<DocumentModel> GGacClipboardReader::GetDocument() 
            {
                return Ptr<DocumentModel>();
            }

            bool GGacClipboardReader::ContainsImage() 
            {
                auto clipboard = Gtk::Clipboard::get();
                return clipboard->wait_is_image_available();
            }

            Ptr<INativeImage> GGacClipboardReader::GetImage() 
            {
                auto clipboard = Gtk::Clipboard::get();
                auto image = clipboard->wait_for_image();
                return Ptr(new GGacImage(GetCurrentController()->ImageService(), Ptr(new Gtk::Image(image))));
            }

			Ptr<INativeClipboardReader> GGacClipboardService::ReadClipboard() 
            {
                if (!reader)
                {
                    reader = Ptr(new GGacClipboardReader(this));
                }
                return reader;
			}

			Ptr<INativeClipboardWriter> GGacClipboardService::WriteClipboard() 
            {
                return Ptr(new GGacClipboardWriter(this));
			}

		}

	}

}

