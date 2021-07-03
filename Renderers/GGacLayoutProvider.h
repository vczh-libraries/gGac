//
// Created by css on 7/3/21.
//

#ifndef GGAC_GGACLAYOUTPROVIDER_H
#define GGAC_GGACLAYOUTPROVIDER_H

#include <GacUI.h>

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GGacLayoutProvider : public Object, public IGuiGraphicsLayoutProvider {
				public:
					Ptr <IGuiGraphicsParagraph> CreateParagraph(const WString &text, IGuiGraphicsRenderTarget *renderTarget, IGuiGraphicsParagraphCallback *callback) override;
				};

			}

		}

	}

}



#endif //GGAC_GGACLAYOUTPROVIDER_H
