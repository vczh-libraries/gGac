//
// Created by css on 6/27/21.
//

#include "GGacResourceService.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			GGacResourceService::GGacResourceService()
			{
				defaultFont.fontFamily = L"Segoe UI";
				defaultFont.size = 12;
				defaultFont.italic = false;
				defaultFont.bold = false;
				defaultFont.underline = false;
				defaultFont.strikeline = false;
				defaultFont.antialias = true;
				defaultFont.verticalAntialias = true;
			}

			GGacResourceService::~GGacResourceService()
			{
			}

			INativeCursor* GGacResourceService::GetSystemCursor(vl::presentation::INativeCursor::SystemCursorType type)
			{
				return nullptr;
			}

			INativeCursor* GGacResourceService::GetDefaultSystemCursor()
			{
				return nullptr;
			}

			bool GGacCursor::IsSystemCursor()
			{
				return true;
			}

			FontProperties GGacResourceService::GetDefaultFont()
			{
				return defaultFont;
			}

			void GGacResourceService::SetDefaultFont(const vl::presentation::FontProperties &value)
			{
				defaultFont = value;
			}

		}

	}
}



vl::presentation::INativeCursor::SystemCursorType vl::presentation::gtk::GGacCursor::GetSystemCursorType() {
	return Hand;
}
