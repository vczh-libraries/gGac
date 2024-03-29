//
// Created by roodkcab on 6/27/21.
//

#include "GGacImageService.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			GGacImageFrame::GGacImageFrame(INativeImage* _image, Glib::RefPtr<Gdk::Pixbuf> _pixbuf)
			:image(_image),
			pixbuf(_pixbuf)
			{

			}

			GGacImageFrame::~GGacImageFrame()
			{
			}

			INativeImage* GGacImageFrame::GetImage()
			{
				return image;
			}

			Size GGacImageFrame::GetSize()
			{
				return pixbuf ? Size(pixbuf->get_width(), pixbuf->get_height())  : Size(0, 0);
			}

			void GGacImageFrame::SetSize(vint width, vint height, bool alwaysScaleUp)
			{
				if (width > 0 && height > 0)
				{ 
					Size size = GetSize();
					width = alwaysScaleUp ? MAX(width, size.x) : MIN(width, size.x);
					height = alwaysScaleUp ? MAX(height, size.y) : MIN(height, size.y);
					pixbuf = pixbuf->scale_simple(width, height, Gdk::InterpType::INTERP_BILINEAR);
				}
			}

			bool GGacImageFrame::SetCache(void* key, Ptr<INativeImageFrameCache> cache)
			{
				vint index = caches.Keys().IndexOf(key);
				if(index != -1)
				{
					return false;
				}
				caches.Add(key, cache);
				cache->OnAttach(this);
				return true;
			}

			Ptr<INativeImageFrameCache>	GGacImageFrame::GetCache(void* key)
			{
				vint index = caches.Keys().IndexOf(key);
				return (index == -1) ? nullptr : caches.Values().Get(index);
			}

			Ptr<INativeImageFrameCache>	GGacImageFrame::RemoveCache(void* key)
			{
				vint index = caches.Keys().IndexOf(key);
				if(index == -1)
					return nullptr;

				Ptr<INativeImageFrameCache> cache = caches.Values().Get(index);
				cache->OnDetach(this);
				caches.Remove(key);
				return cache;
			}

			Glib::RefPtr<Gdk::Pixbuf> GGacImageFrame::GetPixbuf()
			{
                if (!enabled)
                {
                    int w = pixbuf->get_width();
                    int h = pixbuf->get_height();
                    auto greyPixbuf = pixbuf->copy();
                    guint8* pixels = greyPixbuf->get_pixels();
                    if (pixbuf->get_n_channels() == 4) {
                        for (int y = 0; y < h; y++) {
                            for (int x = 0; x < w; x++) {
                                int i = y*pixbuf->get_rowstride() + x*4;
                                guint8 grey = (pixels[i]+pixels[i+1]+pixels[i+2])/6+pixels[i+3]/3;
                                pixels[i] = grey;
                                pixels[i+1] = grey;
                                pixels[i+2] = grey;
                            }
                        }
                    }
                    return greyPixbuf;
                }
				return pixbuf;
			}

            void GGacImageFrame::SetEnabled(bool _enabled)
            {
                enabled = _enabled;
            }

			///

			GGacImage::GGacImage(INativeImageService* _service, Ptr<Gtk::Image> _image)
			:imageService(_service),
			gImage(_image)
			{
				frames.Resize(1);
			}

			GGacImage::~GGacImage()
			{
			}

			INativeImage::FormatType GGacImage::GetFormat()
			{
				//TODO gif
				return INativeImage::Bmp;
			}

			vint GGacImage::GetFrameCount()
			{
				return frames.Count();
			}

			INativeImageFrame* GGacImage::GetFrame(vint index)
			{
				if (index >= 0 && index < frames.Count())
				{
					Ptr<GGacImageFrame>& frame = frames[index];
					if (!frame)
					{
						frame = Ptr(new GGacImageFrame(this, gImage->get_pixbuf()));
					}
					return frame.Obj();
				}
				return 0;
			}

			void GGacImage::SaveToStream(stream::IStream &imageStream, INativeImage::FormatType formatType)
			{
                gchar *buffer;
                gsize len;
                gImage->get_pixbuf()->save_to_buffer(buffer, len);
                imageStream.Write(buffer, len);
			}

			INativeImageService* GGacImage::GetImageService()
			{
				return imageService;
			}

			///

			Ptr<INativeImage> GGacImageService::CreateImageFromFile(const WString &path)
			{
				auto image = Ptr(new Gtk::Image(Glib::ustring::format(path.Buffer())));
				return Ptr(new GGacImage(this, image));
			}

			Ptr<INativeImage> GGacImageService::CreateImageFromMemory(void *buffer, vint length)
			{
                if (length > 0)
                {
                    auto loader = Gdk::PixbufLoader::create();
                    //loader->set_data()
                    loader->write((guint8*)buffer, length/sizeof(guint8));
                    loader->close();
                    auto image = Ptr(new Gtk::Image(loader->get_pixbuf()));
                    return Ptr(new GGacImage(this, image));
                }
                else
                {
                    auto image = Ptr(new Gtk::Image(Glib::RefPtr<Gdk::Pixbuf>((Gdk::Pixbuf*)buffer)));
                    return Ptr(new GGacImage(this, image));
                }
			}

			Ptr<INativeImage> GGacImageService::CreateImageFromStream(stream::IStream &imageStream)
			{
				stream::MemoryStream memoryStream;
				char buffer[65536];
				while (true)
				{
					vint length = imageStream.Read(buffer, sizeof(buffer));
					memoryStream.Write(buffer, length);
					if (length != sizeof(buffer))
					{
						break;
					}
				}
				return CreateImageFromMemory(memoryStream.GetInternalBuffer(), (vint)memoryStream.Size());
			}

		}

	}

}




