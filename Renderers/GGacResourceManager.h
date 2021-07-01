//
// Created by css on 7/1/21.
//

#ifndef GGAC_GGACRESOURCEMANAGER_H
#define GGAC_GGACRESOURCEMANAGER_H

#include <GacUI.h>

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GGacResourceManager : public GuiGraphicsResourceManager, public INativeControllerListener {
				public:
					IGuiGraphicsRenderTarget *GetRenderTarget(INativeWindow *window) override;

					void RecreateRenderTarget(INativeWindow *window) override;

					void ResizeRenderTarget(INativeWindow *window) override;

					IGuiGraphicsLayoutProvider *GetLayoutProvider() override;
				};

			}

		}

	}

}



#endif //GGAC_GGACRESOURCEMANAGER_H
