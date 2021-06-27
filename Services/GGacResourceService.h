//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACRESOURCESERVICE_H
#define GGAC_GGACRESOURCESERVICE_H

#include "GacUI.h"
#include <gdk/gdk.h>

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacCursor : public INativeCursor
			{
			protected:
				GdkCursor*          cursor;
				bool                isSystemCursor;
				SystemCursorType    systemCursorType;
			public:
				bool IsSystemCursor() override;
				SystemCursorType GetSystemCursorType() override;
			};

			class GGacResourceService : public Object, public INativeResourceService
			{
			protected:
				collections::Array<Ptr<GGacCursor>>    	systemCursors;
				FontProperties                          defaultFont;
			public:
				INativeCursor *GetSystemCursor(INativeCursor::SystemCursorType type) override;
				INativeCursor *GetDefaultSystemCursor() override;
				FontProperties GetDefaultFont() override;
				void SetDefaultFont(const FontProperties &value) override;
			};
		}

	}

}


#endif //GGAC_GGACRESOURCESERVICE_H
