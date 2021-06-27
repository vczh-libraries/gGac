//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACIMAGESERVICE_H
#define GGAC_GGACIMAGESERVICE_H

#include "GacUI.h"

namespace vl {

	namespace presentation {

		namespace gtk {
			class GGacImage : public Object, public INativeImage
			{
			public:
				INativeImageService *GetImageService() override;
				FormatType GetFormat() override;
				vint GetFrameCount() override;
				INativeImageFrame *GetFrame(vint index) override;
				void SaveToStream(stream::IStream &imageStream, FormatType formatType) override;
			};

			class GGacImageService : public Object, public INativeImageService
			{
			public:
				Ptr<INativeImage> CreateImageFromFile(const WString &path) override;
				Ptr<INativeImage> CreateImageFromMemory(void *buffer, vint length) override;
				Ptr<INativeImage> CreateImageFromStream(stream::IStream &imageStream) override;
			};

		}

	}

}

#endif //GGAC_GGACIMAGESERVICE_H
