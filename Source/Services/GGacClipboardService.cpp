//
// Created by css on 6/27/21.
//

#include "GGacClipboardService.h"
#include <gtkmm/clipboard.h>

namespace vl {

	namespace presentation {

		namespace gtk {

            GGacClipboardWriter::GGacClipboardWriter(GGacClipboardService* _service) 
            {
            }

            void GGacClipboardWriter::SetText(const WString& value) 
            {
            }

            void GGacClipboardWriter::SetDocument(Ptr<DocumentModel> value) 
            {
            }

            void GGacClipboardWriter::SetImage(Ptr<INativeImage> value) 
            {
            }

            bool GGacClipboardWriter::Submit() 
            {
                return false;
            }

            ////
            GGacClipboardReader::GGacClipboardReader(GGacClipboardService* _service) 
            {
            }

            bool GGacClipboardReader::ContainsText() 
            {
                return true;
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
                return false;
            }

            Ptr<INativeImage> GGacClipboardReader::GetImage() 
            {
                return Ptr<INativeImage>();
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

