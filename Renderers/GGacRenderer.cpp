//
// Created by css on 6/27/21.
//

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class CoreGraphicsRenderTarget: public GGacRenderTarget
				{
				protected:
					//CoreGraphicsView*       nativeView;
					//List<Rect>              clippers;
					vint                    clipperCoverWholeTargetCounter;
					INativeWindow*          window;
				public:
					void StartRendering() override {

					}

					RenderTargetFailure StopRendering() override {
						return None;
					}

					void PushClipper(Rect clipper) override {

					}

					void PopClipper() override {

					}

					Rect GetClipper() override {
						return vl::presentation::Rect();
					}

					bool IsClipperCoverWholeTarget() override {
						return false;
					}

					Cairo::RefPtr<Cairo::Context> GetGGacContext() override {
						return Cairo::RefPtr<Cairo::Context>();
					}
				};

				namespace {
					GGacRenderTarget*      g_currentRenderTarget;
				}

				void SetCurrentRenderTarget(GGacRenderTarget* renderTarget)
				{
					g_currentRenderTarget = renderTarget;
				}

				GGacRenderTarget* GetCurrentRenderTarget()
				{
					return g_currentRenderTarget;
				}
			}

		}

	}

}