//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACIMAGESERVICE_H
#define GGAC_GGACIMAGESERVICE_H

#include "GacUI.h"
#include <gtkmm.h>

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacImageFrame: public Object, public INativeImageFrame
			{
			protected:
				INativeImage*                                                   image;
				Glib::RefPtr<Gdk::Pixbuf> 										pixbuf;
				collections::Dictionary<void*, Ptr<INativeImageFrameCache>>     caches;

			public:
				GGacImageFrame(INativeImage* _image, Glib::RefPtr<Gdk::Pixbuf> _pixbuf);
				~GGacImageFrame();

				INativeImage*				GetImage() override;
				Size						GetSize() override;

				bool						SetCache(void* key, Ptr<INativeImageFrameCache> cache) override;
				Ptr<INativeImageFrameCache>	GetCache(void* key) override;
				Ptr<INativeImageFrameCache>	RemoveCache(void* key) override;

				///
				Glib::RefPtr<Gdk::Pixbuf>	GetPixbuf();
			};

			class GGacImage : public Object, public INativeImage
			{
			protected:
				INativeImageService* 						imageService;
				Ptr<Gtk::Image> 							gImage;
				collections::Array<Ptr<GGacImageFrame>>    	frames;
			public:
				GGacImage(INativeImageService* _service, Ptr<Gtk::Image> _image);
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
