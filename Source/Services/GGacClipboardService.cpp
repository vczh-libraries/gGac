//
// Created by css on 6/27/21.
//

#include "GGacClipboardService.h"

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
                return false;
            }

            WString GGacClipboardReader::GetText() 
            {
                return vl::WString();
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
                    reader = new GGacClipboardReader(this);
                }
                return reader;
			}

			Ptr<INativeClipboardWriter> GGacClipboardService::WriteClipboard() 
            {
                return new GGacClipboardWriter(this);
			}

		}

	}

}

