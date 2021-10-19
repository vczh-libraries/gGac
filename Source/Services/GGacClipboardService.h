//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACCLIPBOARDSERVICE_H
#define GGAC_GGACCLIPBOARDSERVICE_H

#include "GacUI.h"

namespace vl {

	namespace presentation {

		namespace gtk {

            class GGacClipboardService;

            class GGacClipboardReader : public INativeClipboardReader
            {
                friend class GGacClipboardService;
            public:
                GGacClipboardReader(GGacClipboardService* _service);
                bool ContainsText() override;
                WString GetText() override;
                bool ContainsDocument() override;
                Ptr<DocumentModel> GetDocument() override;
                bool ContainsImage() override;
                Ptr<INativeImage> GetImage() override;
            };

            class GGacClipboardWriter : public INativeClipboardWriter
            {
                friend class GGacClipboardService;
            public:
                GGacClipboardWriter(GGacClipboardService* _service);
                void SetText(const WString& value) override;
                void SetDocument(Ptr<DocumentModel> value) override;
                void SetImage(Ptr<INativeImage> value) override;
                bool Submit() override;
            };

			class GGacClipboardService : public Object, public INativeClipboardService {
			protected:
				Ptr<GGacClipboardReader> reader;
			public:
				Ptr<INativeClipboardReader> ReadClipboard() override;
				Ptr<INativeClipboardWriter> WriteClipboard() override;
			};

		}

	}

}


#endif //GGAC_GGACCLIPBOARDSERVICE_H
