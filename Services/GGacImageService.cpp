//
// Created by css on 6/27/21.
//

#include "GGacImageService.h"

vl::Ptr<vl::presentation::INativeImage>
vl::presentation::gtk::GGacImageService::CreateImageFromFile(const vl::WString &path) {
	return Ptr<INativeImage>();
}

vl::Ptr<vl::presentation::INativeImage>
vl::presentation::gtk::GGacImageService::CreateImageFromMemory(void *buffer, vl::vint length) {
	return Ptr<INativeImage>();
}

vl::Ptr<vl::presentation::INativeImage>
vl::presentation::gtk::GGacImageService::CreateImageFromStream(vl::stream::IStream &imageStream) {
	return Ptr<INativeImage>();
}

vl::presentation::INativeImageService *vl::presentation::gtk::GGacImage::GetImageService() {
	return nullptr;
}

vl::presentation::INativeImage::FormatType vl::presentation::gtk::GGacImage::GetFormat() {
	return Jpeg;
}

vl::vint vl::presentation::gtk::GGacImage::GetFrameCount() {
	return 0;
}

vl::presentation::INativeImageFrame *vl::presentation::gtk::GGacImage::GetFrame(vl::vint index) {
	return nullptr;
}

void vl::presentation::gtk::GGacImage::SaveToStream(vl::stream::IStream &imageStream,
													vl::presentation::INativeImage::FormatType formatType) {

}
