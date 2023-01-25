//
// Created by css on 7/3/21.
//

#ifndef GGAC_GGACLAYOUTPROVIDER_H
#define GGAC_GGACLAYOUTPROVIDER_H

#include <GacUI.h>
#include <gtkmm.h>

using namespace vl::collections;

typedef unsigned char BYTE;
typedef unsigned short WORD;

typedef struct _ABC {
	double abcA;
	double abcB; //width of glyphs
	double abcC;
} ABC;

typedef struct _GOFFSET {
	long du;
	long dv;
} GOFFSET;

typedef struct _SCRIPT_VISATTR {
	WORD uJustification : 4;
	WORD fClusterStart : 1;
	WORD fDiacritic : 1;
	WORD fZeroWidth : 1;
	WORD fReserved : 1;
	WORD fShapeReserved : 8;
} SCRIPT_VISATTR;

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				struct UniscribeColorRange
				{
					vint							start;
					vint							end;

					UniscribeColorRange(){}
					UniscribeColorRange(vint _start, vint _end):start(_start),end(_end){}

					bool operator==(const UniscribeColorRange& range) const { return start==range.start; }
					bool operator!=(const UniscribeColorRange& range) const { return start!=range.start; }
					bool operator<(const UniscribeColorRange& range) const { return start<range.start; }
					bool operator<=(const UniscribeColorRange& range) const { return start<=range.start; }
					bool operator>(const UniscribeColorRange& range) const { return start>range.start; }
					bool operator>=(const UniscribeColorRange& range) const { return start>=range.start; }
				};

				struct UniscribeColor
				{
					Color							fontColor;
					Color							backgroundColor;

					UniscribeColor(){}
					UniscribeColor(Color _fontColor, Color _backgroundColor):fontColor(_fontColor),backgroundColor(_backgroundColor){}

					bool operator==(const UniscribeColor& color) const { return fontColor==color.fontColor && backgroundColor==color.backgroundColor; }
					bool operator!=(const UniscribeColor& color) const { return fontColor!=color.fontColor || backgroundColor!=color.backgroundColor; }
				};

				typedef Nullable<IGuiGraphicsParagraph::InlineObjectProperties>	InlineObject;

/***********************************************************************
UniscribeFragment
***********************************************************************/

				struct UniscribeFragment
				{
					typedef Dictionary<UniscribeColorRange, UniscribeColor>		ColorRangeMap;

					//***************************** Document Data (Text)
					ColorRangeMap									colors;
					FontProperties									fontStyle;
					const WString									text;
					Ptr<Pango::FontDescription>						fontObject;
					//***************************** Document Data (Element)
					InlineObject									inlineObjectProperties;
					List<Ptr<UniscribeFragment>>					cachedTextFragment;

					UniscribeFragment(const WString& _text);

					WString							GetFingerprint();
					void							CutColors(vint start, vint length);
					void							UpdateOverlappedColors(vint start, vint length, Color UniscribeColor::* colorField, Color color);
					void							DefragmentColors();
					UniscribeColor					GetCharColor(vint charIndex);
					Ptr<UniscribeFragment>			Copy(vint start, vint length);
                    Ptr<Pango::AttrList>            GetAttributes();
				};

/***********************************************************************
UniscribeGlyphData
***********************************************************************/

				struct UniscribeGlyphData
				{
					//***************************** Uniscribe Data
					Array<WORD>						glyphs; //index in font of each glyph
					Array<PangoGlyphVisAttr>		glyphVisattrs; //cluster begin & color of each glyph
					Array<double>					glyphAdvances; //width of each glyph
					Array<WORD>						charCluster; //glyph of each utf8 char: flflflfl => 00112233
					ABC								runAbc;

					UniscribeGlyphData();

					void							ClearUniscribeData(vint glyphCount, vint length);
					bool							BuildUniscribeData(Cairo::RefPtr<Cairo::Context> cr, const Pango::Item& scriptItem, const wchar_t* runText, vint length, List<vint>& breakings, List<bool>& breakingAvailabilities);
					void							BuildUniscribeData(Cairo::RefPtr<Cairo::Context> cr, const Pango::Item& scriptItem, PangoLogAttr* charLogattrs, const wchar_t* runText, vint length);
				};

/***********************************************************************
UniscribeItem
***********************************************************************/

				class UniscribeItem : public Object
				{
				public:
					//***************************** Uniscribe Data
					Pango::Item						scriptItem;
					vint							startFromLine;
					vint							length;
					WString					        itemText;
					Array<PangoLogAttr>				charLogattrs;

					UniscribeItem();
					~UniscribeItem();

					void							ClearUniscribeData();
					bool							BuildUniscribeData();
					bool							IsRightToLeft();
				};

/***********************************************************************
UniscribeRun
***********************************************************************/

				class UniscribeRun : public Object
				{
				public:
					struct RunFragmentBounds
					{
						vint						startFromRun;
						vint						length;
						Rect						bounds;
					};

					class IRendererCallback : public Interface
					{
					public:
						virtual Cairo::RefPtr<Cairo::Context> 			GetGGacContext() = 0;
						virtual Point									GetParagraphOffset() = 0;
						virtual IGuiGraphicsParagraphCallback*			GetParagraphCallback() = 0;
					};

					//***************************** Document Data
					UniscribeFragment*				documentFragment;
					UniscribeItem*					scriptItem;
					//***************************** Uniscribe Data
					vint							startFromLine;
					vint							startFromFragment;
					vint							length;
					const wchar_t*					runText;
					//***************************** Layout Data
					List<RunFragmentBounds>			fragmentBounds;

					UniscribeRun();
					~UniscribeRun();

					virtual bool					BuildUniscribeData(Cairo::RefPtr<Cairo::Context> cr, List<vint>& breakings)=0;
					virtual vint					SumWidth(vint charStart, vint charLength)=0;
					virtual vint					SumHeight()=0;
					virtual vint					SumTextHeight()=0;
					virtual void					SearchForLineBreak(vint tempStart, vint maxWidth, bool firstRun, vint& charLength, vint& charAdvances)=0;
					virtual void					Render(IRendererCallback* callback, vint fragmentBoundsIndex, vint offsetX, vint offsetY, bool renderBackground)=0;
				};

/***********************************************************************
UniscribeTextRun
***********************************************************************/

				class UniscribeTextRun : public UniscribeRun
				{
                private:
                    //***************************** Uniscribe Data
                    PangoGlyphString*               scriptCache;
                    double                          advance;
                    bool							needFontFallback;

				public:
                    UniscribeGlyphData				wholeGlyph;

					UniscribeTextRun();
					~UniscribeTextRun();

					void							ClearUniscribeData();
					void							SearchSingleGlyphCluster(vint charStart, vint& charLength, vint& cluster, vint& nextCluster);
					void							SearchSingleChar(vint charStart, vint& charLength, vint& cluster, vint& nextCluster);
					void							SearchGlyphCluster(vint charStart, vint charLength, vint& cluster, vint& nextCluster);
					bool							BuildUniscribeData(Cairo::RefPtr<Cairo::Context> cr, List<vint>& breakings)override;
					vint							SumWidth(vint charStart, vint charLength)override;
					vint							SumHeight()override;
					vint							SumTextHeight()override;
					void							SearchForLineBreak(vint tempStart, vint maxWidth, bool firstRun, vint& charLength, vint& charAdvances)override;
					void							Render(IRendererCallback* callback, vint fragmentBoundsIndex, vint offsetX, vint offsetY, bool renderBackground)override;
				};

/***********************************************************************
UniscribeElementRun
***********************************************************************/

				class UniscribeEmbeddedObjectRun : public UniscribeRun
				{
				public:
					//***************************** Document Data
					IGuiGraphicsParagraph::InlineObjectProperties	properties;

					UniscribeEmbeddedObjectRun();
					~UniscribeEmbeddedObjectRun();

					bool							BuildUniscribeData(Cairo::RefPtr<Cairo::Context> cr, List<vint>& breakings)override;
					vint							SumWidth(vint charStart, vint charLength)override;
					vint							SumHeight()override;
					vint							SumTextHeight()override;
					void							SearchForLineBreak(vint tempStart, vint maxWidth, bool firstRun, vint& charLength, vint& charAdvances)override;
					void							Render(IRendererCallback* callback, vint fragmentBoundsIndex, vint offsetX, vint offsetY, bool renderBackground)override;
				};

/***********************************************************************
UniscribeVirtualLine
***********************************************************************/

				class UniscribeVirtualLine : Object
				{
				public:
					//***************************** Document Data
					vint							startFromLine;
					vint							length;
					const wchar_t*					runText;
					//***************************** Layout Data
					vint							firstRunIndex;
					vint							firstRunBoundsIndex;
					vint							lastRunIndex;
					vint							lastRunBoundsIndex;
					Rect							bounds;

					UniscribeVirtualLine();
				};

/***********************************************************************
UniscribeLine
***********************************************************************/

				class UniscribeLine : public Object
				{
				public:
					//***************************** Document Data
					List<Ptr<UniscribeFragment>>	documentFragments;
					vint							startFromParagraph;
					WString							lineText;
					//***************************** Uniscribe Data
					List<Ptr<UniscribeItem>>		scriptItems;
					List<Ptr<UniscribeRun>>			scriptRuns;
					//***************************** Layout Data
					List<Ptr<UniscribeVirtualLine>>	virtualLines;
					Rect							bounds;

					UniscribeLine();

					void							ClearUniscribeData();
					bool							BuildUniscribeData();
					void							Layout(vint availableWidth, Alignment alignment, vint top, vint& totalHeight);
					void							Render(UniscribeRun::IRendererCallback* callback, vint offsetX, vint offsetY, bool renderBackground);
				};

/***********************************************************************
UniscribeParagraph
***********************************************************************/

				class UniscribeParagraph : public Object
				{
				public:
					//***************************** Document Data
					List<Ptr<UniscribeFragment>>	documentFragments;
					Alignment						paragraphAlignment;
					WString							paragraphText;
					bool							built;
					//***************************** Uniscribe Data
					List<Ptr<UniscribeLine>>		lines;
					//***************************** Layout Data
					vint							lastAvailableWidth;
					Rect							bounds;

					UniscribeParagraph();
					~UniscribeParagraph();

					void							ClearUniscribeData();
					bool							BuildUniscribeData();
					void							Layout(vint availableWidth, Alignment alignment);
					void							Render(UniscribeRun::IRendererCallback* callback, bool renderBackground);

					void							SearchFragment(vint start, vint length, vint& fs, vint& ss, vint& fe, vint& se);
					bool							CutFragment(vint fs, vint ss, vint fe, vint se, vint& f1, vint& f2);
					void							CutFragmentColors(vint fs, vint ss, vint fe, vint se, Color UniscribeColor::* colorField, Color color);

					bool							SetFont(vint start, vint length, const WString& value);
					bool							SetSize(vint start, vint length, vint value);
					bool							SetStyle(vint start, vint length, bool bold, bool italic, bool underline, bool strikeline);
					bool							SetColor(vint start, vint length, Color value);
					bool							SetBackgroundColor(vint start, vint length, Color value);
					bool							SetInlineObject(vint start, vint length, const IGuiGraphicsParagraph::InlineObjectProperties& properties);
					InlineObject					ResetInlineObject(vint start, vint length);

					void							GetLineIndexFromTextPos(vint textPos, vint& frontLine, vint& backLine);
					void							GetVirtualLineIndexFromTextPos(vint textPos, vint lineIndex, vint& frontLine, vint& backLine);
					void							GetItemIndexFromTextPos(vint textPos, vint lineIndex, vint& frontItem, vint& backItem);
					Rect							GetCaretBoundsWithLine(vint caret, vint lineIndex, vint virtualLineIndex, bool frontSide);
					vint							GetCaretFromXWithTextRunBounds(vint x, vint lineIndex, vint runIndex, vint runBoundsIndex);
					vint							GetCaretFromXWithLine(vint x, vint lineIndex, vint virtualLineIndex);
					InlineObject					GetInlineObjectFromXWithLine(vint x, vint lineIndex, vint virtualLineIndex, vint& start, vint& length);
					vint							GetLineY(vint lineIndex);
					vint							GetVirtualLineY(vint lineIndex, vint virtualLineIndex);
					vint							GetLineIndexFromY(vint y);
					vint							GetVirtualLineIndexFromY(vint y, vint lineIndex);

					vint							GetCaret(vint comparingCaret, IGuiGraphicsParagraph::CaretRelativePosition position, bool& preferFrontSide);
					Rect							GetCaretBounds(vint caret, bool frontSide);
					vint							GetCaretFromPoint(Point point);
					InlineObject					GetInlineObjectFromPoint(Point point, vint& start, vint& length);
					vint							GetNearestCaretFromTextPos(vint textPos, bool frontSide);
					bool							IsValidCaret(vint caret);
					bool							IsValidTextPos(vint textPos);
				};

				class GGacLayoutProvider : public Object, public IGuiGraphicsLayoutProvider
				{
				public:
					Ptr <IGuiGraphicsParagraph> CreateParagraph(const WString &text, IGuiGraphicsRenderTarget *renderTarget, IGuiGraphicsParagraphCallback *callback) override;
				};

			}

		}

	}

}



#endif //GGAC_GGACLAYOUTPROVIDER_H
