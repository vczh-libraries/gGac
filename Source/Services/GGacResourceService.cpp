//
// Created by css on 6/27/21.
//

#include "GGacResourceService.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			GGacResourceService::GGacResourceService()
			{
                systemCursors.Resize(INativeCursor::SystemCursorCount);
                for(vint i=0;i<systemCursors.Count();i++)
                {
                    systemCursors[i]=Ptr(new GGacCursor((INativeCursor::SystemCursorType)i));
                }
				defaultFont.fontFamily = L"Segoe UI";
				defaultFont.size = 11;
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
                vint index=(vint)type;
                if(0<=index && index<systemCursors.Count())
                {
                    return systemCursors[index].Obj();
                }
                else
                {
                    return 0;
                }
			}

			INativeCursor* GGacResourceService::GetDefaultSystemCursor()
			{
                return GetSystemCursor(INativeCursor::Arrow);
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