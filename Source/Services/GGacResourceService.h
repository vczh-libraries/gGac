//
// Created by roodkcab on 6/27/21.
//

#ifndef GGAC_GGACRESOURCESERVICE_H
#define GGAC_GGACRESOURCESERVICE_H

#include "GacUI.h"
#include "GGacCursor.h"
#include <gdk/gdk.h>

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacResourceService : public Object, public INativeResourceService
			{
			protected:
				collections::Array<Ptr<GGacCursor>>    	systemCursors;
				FontProperties                          defaultFont;
			public:
				GGacResourceService();
				virtual ~GGacResourceService();
				INativeCursor *GetSystemCursor(INativeCursor::SystemCursorType type) override;
				INativeCursor *GetDefaultSystemCursor() override;
				FontProperties GetDefaultFont() override;
				void SetDefaultFont(const FontProperties &value) override;
				void EnumerateFonts(collections::List<WString>& fonts) override;
			};
		}

	}

}


#endif //GGAC_GGACRESOURCESERVICE_H
