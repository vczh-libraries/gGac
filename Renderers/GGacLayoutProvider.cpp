//
// Created by css on 7/3/21.
//

#include "GGacLayoutProvider.h"
#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		using namespace collections;

		namespace elements {

			namespace gtk {

				class GGacParagraph : public Object, public IGuiGraphicsParagraph
				{
				protected:
					IGuiGraphicsLayoutProvider*             provider;
					IGGacRenderTarget*              		renderTarget;
					WString                                 paragraphText;
					bool                                    wrapLine;
					vint                                    maxWidth;
					List<Color>                             usedColors;
					Alignment                               textAlignment;
					bool                                    needFormatData;

					vint                                    caretPos;
					Color                                   caretColor;
					bool                                    caretFrontSide;

					Array<vint>                             charBoundingMetricsMap;
					Dictionary<vint, vint>                  charLineFragmentsMap;

					IGuiGraphicsParagraphCallback*          paraCallback;
					vl::presentation::Point                 paraOffset;
				public:

					GGacParagraph(IGuiGraphicsLayoutProvider* _provider, const WString& _text, IGGacRenderTarget* _renderTarget, IGuiGraphicsParagraphCallback* _callback)
					:provider(_provider),
					renderTarget(_renderTarget),
					paragraphText(_text),
					wrapLine(true),
					maxWidth(-1),
					caretPos(-1),
					caretFrontSide(false),
					textAlignment(Alignment::Left),
					paraCallback(_callback)
					{
					}

					IGuiGraphicsLayoutProvider *GetProvider() override {
						return nullptr;
					}

					IGuiGraphicsRenderTarget *GetRenderTarget() override {
						return nullptr;
					}

					bool GetWrapLine() override {
						return false;
					}

					void SetWrapLine(bool value) override {

					}

					vint GetMaxWidth() override {
						return 0;
					}

					void SetMaxWidth(vint value) override {

					}

					Alignment GetParagraphAlignment() override {
						return Alignment::Top;
					}

					void SetParagraphAlignment(Alignment value) override {

					}

					bool SetFont(vint start, vint length, const WString &value) override {
						return false;
					}

					bool SetSize(vint start, vint length, vint value) override {
						return false;
					}

					bool SetStyle(vint start, vint length, TextStyle value) override {
						return false;
					}

					bool SetColor(vint start, vint length, Color value) override {
						return false;
					}

					bool SetBackgroundColor(vint start, vint length, Color value) override {
						return false;
					}

					bool SetInlineObject(vint start, vint length, const InlineObjectProperties &properties) override {
						return false;
					}

					bool ResetInlineObject(vint start, vint length) override {
						return false;
					}

					vint GetHeight() override {
						return 0;
					}

					bool OpenCaret(vint caret, Color color, bool frontSide) override {
						return false;
					}

					bool CloseCaret() override {
						return false;
					}

					void Render(Rect bounds) override {

					}

					vint GetCaret(vint comparingCaret, CaretRelativePosition position, bool &preferFrontSide) override {
						return 0;
					}

					Rect GetCaretBounds(vint caret, bool frontSide) override {
						return vl::presentation::Rect();
					}

					vint GetCaretFromPoint(Point point) override {
						return 0;
					}

					Nullable<InlineObjectProperties>
					GetInlineObjectFromPoint(Point point, vint &start, vint &length) override {
						return Nullable<InlineObjectProperties>();
					}

					vint GetNearestCaretFromTextPos(vint textPos, bool frontSide) override {
						return 0;
					}

					bool IsValidCaret(vint caret) override {
						return false;
					}

					bool IsValidTextPos(vint textPos) override {
						return false;
					}

					~GGacParagraph() override {

					}

				};

				///

				Ptr <IGuiGraphicsParagraph> GGacLayoutProvider::CreateParagraph(const WString &text, IGuiGraphicsRenderTarget *renderTarget, IGuiGraphicsParagraphCallback *callback)
				{
					return new GGacParagraph(this, text, (IGGacRenderTarget*)renderTarget, callback);
				}

			}

		}

	}

}