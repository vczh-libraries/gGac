//
// Created by css on 7/3/21.
//

#include "GGacLayoutProvider.h"
#include "GGacRenderer.h"
#include <pangomm/glyphstring.h>
#include <iostream>

namespace vl {

	namespace presentation {

		using namespace collections;

		namespace elements {

			namespace gtk {

				using namespace regex;

/***********************************************************************
UniscribeFragment
***********************************************************************/

				UniscribeFragment::UniscribeFragment(const WString& _text)
						:text(_text)
				{
					colors.Add(UniscribeColorRange(0, text.Length()), UniscribeColor(Color(0, 0, 0), Color(0, 0, 0, 0)));
				}

				WString UniscribeFragment::GetFingerprint()
				{
					return fontStyle.fontFamily+L"#"
						   +itow(fontStyle.size)+L"#"
						   +(fontStyle.bold?L"B":L"N")+L"#"
						   +(fontStyle.italic?L"I":L"N")+L"#"
						   +(fontStyle.underline?L"U":L"N")+L"#"
						   +(fontStyle.strikeline?L"S":L"N")+L"#"
							;
				}

				void UniscribeFragment::CutColors(vint start, vint length)
				{
					vint end=start+length;
					for(vint i=colors.Count()-1;i>=0;i--)
					{
						UniscribeColorRange key=colors.Keys()[i];
						if(key.start<end && start<key.end)
						{
							UniscribeColor value=colors.Values()[i];

							vint s1=key.start;
							vint s2=key.start>start?key.start:start;
							vint s3=key.end<end?key.end:end;
							vint s4=key.end;

							colors.Remove(key);
							if(s1<s2)
							{
								colors.Add(UniscribeColorRange(s1, s2), value);
							}
							if(s2<s3)
							{
								colors.Add(UniscribeColorRange(s2, s3), value);
							}
							if(s3<s4)
							{
								colors.Add(UniscribeColorRange(s3, s4), value);
							}
						}
					}
				}

				void UniscribeFragment::UpdateOverlappedColors(vint start, vint length, Color UniscribeColor::* colorField, Color color)
				{
					vint end=start+length;
					for(vint i=colors.Count()-1;i>=0;i--)
					{
						UniscribeColorRange key=colors.Keys()[i];
						if(key.start<end && start<key.end)
						{
							UniscribeColor value=colors.Values()[i];
							value.*colorField=color;
							colors.Set(key, value);
						}
					}
				}

				void UniscribeFragment::DefragmentColors()
				{
					vint lastIndex=-1;
					UniscribeColor lastColor;
					for(vint i=colors.Count()-1;i>=-1;i--)
					{
						if(lastIndex==-1)
						{
							lastIndex=i;
							if(i!=-1)
							{
								lastColor=colors.Values()[i];
							}
						}
						else if(i==-1 || colors.Values()[i]!=lastColor)
						{
							if(lastIndex-i>0)
							{
								vint start=colors.Keys()[i+1].start;
								vint end=colors.Keys()[lastIndex].end;
								UniscribeColorRange key(start, end);

								for(vint j=lastIndex;j>i;j--)
								{
									colors.Remove(colors.Keys()[j]);
								}
								colors.Add(key, lastColor);
							}
							lastIndex=i;
							if(i!=-1)
							{
								lastColor=colors.Values()[i];
							}
						}
					}
				}

				UniscribeColor UniscribeFragment::GetCharColor(vint charIndex)
				{
					vint start=0;
					vint end=colors.Count()-1;
					while(start<=end)
					{
						vint middle=(start+end)/2;
						UniscribeColorRange key=colors.Keys()[middle];
						if(charIndex<key.start)
						{
							end=middle-1;
						}
						else if(charIndex>=key.end)
						{
							start=middle+1;
						}
						else
						{
							return colors.Values()[middle];
						}
					}
					return UniscribeColor();
				}

				Ptr<UniscribeFragment> UniscribeFragment::Copy(vint start, vint length)
				{
					vint end=start+length;
					Ptr<UniscribeFragment> fragment=Ptr(new UniscribeFragment(length==0?L"":text.Sub(start, length)));
					fragment->fontStyle=fontStyle;
					fragment->fontObject=fontObject;

					if(length!=0)
					{
						fragment->colors.Clear();
						CutColors(start, length);
						for(vint i=0;i<colors.Count();i++)
						{
							UniscribeColorRange key=colors.Keys()[i];
							if(key.start<end && start<key.end)
							{
								UniscribeColor value=colors.Values()[i];
								fragment->colors.Add(UniscribeColorRange(key.start-start, key.end-start), value);
							}
						}
					}
					return fragment;
				}

/***********************************************************************
UniscribeGlyphData
***********************************************************************/

				UniscribeGlyphData::UniscribeGlyphData()
                :sa(0)
				{
					ClearUniscribeData(0, 0);
				}

				void UniscribeGlyphData::ClearUniscribeData(vint glyphCount, vint length)
				{
					glyphs.Resize(glyphCount);
					glyphVisattrs.Resize(glyphCount);
					glyphAdvances.Resize(glyphCount);
					glyphOffsets.Resize(glyphCount);
					charCluster.Resize(length);
					memset(&runAbc, 0, sizeof(runAbc));
					memset(&sa, 0, sizeof(sa));
				}


				bool UniscribeGlyphData::BuildUniscribeData(Cairo::RefPtr<Cairo::Context> cr, const Pango::Item& scriptItem, PangoGlyphString* cache, const wchar_t* runText, vint length, List<vint>& breakings, List<bool>& breakingAvailabilities, double scale)
				{
					vint glyphCount=glyphs.Count();
					bool resizeGlyphData=false;
					if(glyphCount==0)
					{
						glyphCount=(vint)(1.5*length+16);
						resizeGlyphData=true;
					}
					sa = *scriptItem.get_analysis().gobj();
					{
						// generate shape information
						if(resizeGlyphData)
						{
							glyphs.Resize(glyphCount);
							glyphVisattrs.Resize(glyphCount);
							charCluster.Resize(length);
						}

						while(true)
						{
                            auto str = Glib::ustring::format(runText).substr(0, length);
                            pango_shape(str.c_str(), str.bytes(), &sa, cache);
                            glyphCount = cache->num_glyphs;
                            for (vint i = 0; i < cache->num_glyphs; i++)
							{
								glyphVisattrs[i] = cache->glyphs[i].attr;
                                charCluster[i] = str.length() - Glib::ustring::format(str.c_str() + cache->log_clusters[i]).length();//cache->log_clusters[i];//$i th character coresponding glyph at n th byte of string
							}
							break;
						}
						if(resizeGlyphData)
						{
							glyphs.Resize(glyphCount);
							glyphVisattrs.Resize(glyphCount);
						}
					}

					{
						// generate breaking information
						breakings.Add(0);
						vint charIndex=0;
						bool lastGlyphAvailable=false;
						while(charIndex<length)
						{
							vint glyphIndex=charCluster[charIndex];
							vint nextCharIndex=charIndex;
							while(nextCharIndex<length && charCluster[nextCharIndex]==glyphIndex)
							{
								nextCharIndex++;
							}

							vint glyphCount=0;
							if(nextCharIndex==length)
							{
								glyphCount=glyphs.Count()-glyphIndex;
							}
							else
							{
								glyphCount=charCluster[nextCharIndex]-glyphIndex;
							}

							if(scriptItem.get_analysis().get_level() % 2 == 1)
							{
								glyphCount=-glyphCount;
								glyphIndex-=glyphCount-1;
							}

							bool available=true;
							/*for(vint i=0;i<glyphCount;i++)
							{
                                //TODO: check glyphs is invalid
								if(glyphs[i+glyphIndex]==0)
								{
									available=false;
								}
							}*/

							if(charIndex==0)
							{
								lastGlyphAvailable=available;
								breakingAvailabilities.Add(available);
							}
							else if(lastGlyphAvailable!=available)
							{
								breakings.Add(charIndex);
								lastGlyphAvailable=available;
								breakingAvailabilities.Add(available);
							}

							charIndex=nextCharIndex;
						}
					}

					if(breakings.Count()==1)
					{
						// generate place information
						if(resizeGlyphData)
						{
							glyphAdvances.Resize(glyphCount);
							glyphOffsets.Resize(glyphCount);
						}

						int totalWidth = 0, advanceIndex = 0;
						for (vint i = 0; i < glyphCount; i++)
						{
                            auto geometry = cache->glyphs[i].geometry;
							glyphAdvances[advanceIndex] = geometry.width / PANGO_SCALE * scale;
							totalWidth += glyphAdvances[advanceIndex];
							advanceIndex++;
						}
						runAbc.abcA = 0;
						runAbc.abcB = totalWidth;
						runAbc.abcC = 0;
					}

					return true;
					BUILD_UNISCRIBE_DATA_FAILED:
					return false;
				}

				void UniscribeGlyphData::BuildUniscribeData(Cairo::RefPtr<Cairo::Context> cr, const Pango::Item& scriptItem, PangoLogAttr* charLogattrs, const wchar_t* runText, vint length)
				{
					vint glyphCount=0;
					for(vint i=0;i<length;i++)
					{
						if(i==0 || charLogattrs[i].is_cursor_position)
						{
							glyphCount++;
						}
					}

					ClearUniscribeData(glyphCount, length);
					sa=*scriptItem.get_analysis().gobj();
					memset(&glyphs[0], 0, sizeof(glyphs[0])*glyphs.Count());
					memset(&glyphVisattrs[0], 0, sizeof(glyphVisattrs[0])*glyphVisattrs.Count());
					memset(&glyphAdvances[0], 0, sizeof(glyphAdvances[0])*glyphAdvances.Count());
					memset(&glyphOffsets[0], 0, sizeof(glyphOffsets[0])*glyphOffsets.Count());
					memset(&charCluster[0], 0, sizeof(charCluster[0])*charCluster.Count());

					for(vint i=0;i<glyphCount;i++)
					{
						glyphs[i]=(WORD)i;
					}

					if(sa.level % 2 == 1)
					{
						vint currentGlyphCount=0;
						for(vint i=0;i<length;i++)
						{
							if(i==0 || charLogattrs[i].is_cursor_position)
							{
								currentGlyphCount++;
							}
							charCluster[i]=(WORD)(glyphCount-currentGlyphCount);
						}
					}
					else
					{
						vint currentGlyphCount=0;
						for(vint i=0;i<length;i++)
						{
							if(i==0 || charLogattrs[i].is_cursor_position)
							{
								currentGlyphCount++;
							}
							charCluster[i]=(WORD)(currentGlyphCount-1);
						}
					}

					{
						vint lastCharIndex=0;
						vint lastGlyphIndex=0;
						for(vint i=0;i<=length;i++)
						{
							if(i==0 || charLogattrs[i].is_cursor_position)
							{
								vint glyphLength=i-lastCharIndex;
								const wchar_t* glyphText = sa.level % 2 == 1 ? runText + length - lastCharIndex - glyphLength : runText + lastCharIndex;
                                PangoRectangle size;
                                Cairo::TextExtents extent;
                                cr->get_text_extents(Glib::ustring::format(glyphText).substr(0, length).c_str(), extent);
								glyphAdvances[lastGlyphIndex] = extent.width;
								lastCharIndex=i;
								lastGlyphIndex++;
							}
						}
					}

					for(vint i=0;i<glyphCount;i++)
					{
						runAbc.abcB+=glyphAdvances[i];
					}
				}

/***********************************************************************
UniscribeItem
***********************************************************************/

				UniscribeItem::UniscribeItem()
				:startFromLine(0)
				,length(0)
				,itemText(0)
                ,scriptItem(0)
				{
				}

				UniscribeItem::~UniscribeItem()
				{
				}

				void UniscribeItem::ClearUniscribeData()
				{
					//pango_item_free(&scriptItem);
					charLogattrs.Resize(0);
				}

				bool UniscribeItem::BuildUniscribeData()
				{
					// generate break information
					charLogattrs.Resize(length + 1);
					Glib::ustring gstr = Glib::ustring::format(itemText);
					pango_default_break(gstr.c_str(), gstr.bytes(), scriptItem.get_analysis().gobj(), &charLogattrs[0], length);
                    /*console::Console::WriteLine(L"================================= ITEM =================================");
                    console::Console::WriteLine(L"text:" + WString((wchar_t *)g_convert(gstr.c_str(), -1, "wchar_t", "utf-8", NULL, NULL, NULL)));
                    for (auto attr : charLogattrs) { console::Console::Write( itow(attr.is_cursor_position) + L" "); }
                    console::Console::WriteLine(L"");
                    for (auto attr : charLogattrs) { console::Console::Write( itow(attr.is_line_break) + L" "); }
                    console::Console::WriteLine(L"");
                    for (auto attr : charLogattrs) { console::Console::Write( itow(attr.is_word_boundary) + L" "); }
                    console::Console::WriteLine(L"");*/
                    return true;

					BUILD_UNISCRIBE_DATA_FAILED:
					ClearUniscribeData();
					return false;
				}

				bool UniscribeItem::IsRightToLeft()
				{
					return scriptItem.get_analysis().get_level() % 2 == 1;
				}

/***********************************************************************
UniscribeRun
***********************************************************************/

				UniscribeRun::UniscribeRun()
						:documentFragment(0)
						,scriptItem(0)
						,startFromLine(0)
						,startFromFragment(0)
						,length(0)
						,runText(0)
				{
				}

				UniscribeRun::~UniscribeRun()
				{
				}

/***********************************************************************
UniscribeTextRun
***********************************************************************/

				UniscribeTextRun::UniscribeTextRun()
						:scriptCache()
						,advance(0)
						,needFontFallback(false)
				{
				}

				UniscribeTextRun::~UniscribeTextRun()
				{
					ClearUniscribeData();
				}

				void UniscribeTextRun::ClearUniscribeData()
				{
					if (scriptCache)
					{
						pango_glyph_string_free(static_cast<PangoGlyphString*>(scriptCache));
						scriptCache = 0;
					}
					else
					{
						scriptCache = pango_glyph_string_new();
					}
					advance=0;
					needFontFallback=false;
					wholeGlyph.ClearUniscribeData(0, 0);
				}

				void UniscribeTextRun::SearchSingleGlyphCluster(vint charStart, vint& charLength, vint& cluster, vint& nextCluster)
				{
					cluster=wholeGlyph.charCluster[charStart];
					vint nextChar=charStart;
					while(nextChar<wholeGlyph.charCluster.Count())
					{
						if(wholeGlyph.charCluster[nextChar]!=cluster)
						{
							break;
						}
						nextChar++;
					}
					charLength=nextChar-charStart;
					SearchGlyphCluster(charStart, charLength, cluster, nextCluster);
				}

				void UniscribeTextRun::SearchSingleChar(vint charStart, vint& charLength, vint& cluster, vint& nextCluster)
				{
					charLength=0;
					vint startFromItem=charStart+startFromLine-scriptItem->startFromLine;
					vint currentFromItem=startFromItem;
					while(++currentFromItem<scriptItem->length)
					{
						if(scriptItem->charLogattrs[currentFromItem].is_cursor_position)
						{
							break;
						}
					}
					charLength=currentFromItem-startFromItem;
					SearchGlyphCluster(charStart, charLength, cluster, nextCluster);
				}

				void UniscribeTextRun::SearchGlyphCluster(vint charStart, vint charLength, vint& cluster, vint& nextCluster)
				{
					cluster=wholeGlyph.charCluster[charStart];
					if(charStart+charLength>length)
					{
						charLength=length-charStart;
					}
					if(scriptItem->IsRightToLeft())
					{
						nextCluster
								=charStart+charLength==length
								 ?-1
								 :wholeGlyph.charCluster[charStart+charLength];
					}
					else
					{
						nextCluster
								=charStart+charLength==length
								 ?wholeGlyph.glyphs.Count()
								 :wholeGlyph.charCluster[charStart+charLength];
					}
				}

				bool UniscribeTextRun::BuildUniscribeData(Cairo::RefPtr<Cairo::Context> cr, List<vint>& breakings)
				{
					ClearUniscribeData();
                    static Cairo::FontExtents extentsOrigin;
                    if (extentsOrigin.height == 0) {
                        cr->get_font_extents(extentsOrigin);
                    }
                    cr->set_font_size(documentFragment->fontStyle.size);
                    Cairo::FontExtents extentsScaled;
                    cr->get_font_extents(extentsScaled);
					List<bool> breakingAvailabilities;
					if(!wholeGlyph.BuildUniscribeData(cr, scriptItem->scriptItem, static_cast<PangoGlyphString*>(scriptCache), runText, length, breakings, breakingAvailabilities, extentsScaled.height/extentsOrigin.height))
					{
						goto BUILD_UNISCRIBE_DATA_FAILED;
					}

					if(breakings.Count()==1 && !breakingAvailabilities[0])
					{
						PangoLogAttr* charLogattrs=&scriptItem->charLogattrs[0]+startFromLine-scriptItem->startFromLine;
						wholeGlyph.BuildUniscribeData(cr, scriptItem->scriptItem, charLogattrs, runText, length);
						needFontFallback=true;
					}
					advance = wholeGlyph.runAbc.abcA+wholeGlyph.runAbc.abcB+wholeGlyph.runAbc.abcC;

					return true;
					BUILD_UNISCRIBE_DATA_FAILED:
					ClearUniscribeData();
					return false;
				}

				vint UniscribeTextRun::SumWidth(vint charStart, vint charLength)
				{
					vint cluster=0;
					vint nextCluster=0;
					SearchGlyphCluster(charStart, charLength, cluster, nextCluster);
					vint width=0;
					if(scriptItem->IsRightToLeft())
					{
						for(vint i=cluster;i>nextCluster;i--)
						{
							width+=wholeGlyph.glyphAdvances[i];
						}
					}
					else
					{
						for(vint i=cluster;i<nextCluster;i++)
						{
							width+=wholeGlyph.glyphAdvances[i];
						}
					}
					return width;
				}

				vint UniscribeTextRun::SumHeight()
				{
					return documentFragment->fontStyle.size;
				}

				vint UniscribeTextRun::SumTextHeight()
				{
					return SumHeight();
				}

				void UniscribeTextRun::SearchForLineBreak(vint tempStart, vint maxWidth, bool firstRun, vint& charLength, vint& charAdvances)
				{
					vint width=0;
					charLength=0;
					charAdvances=0;
					for(vint i=tempStart;i<=length;)
					{
						if(i==length || scriptItem->charLogattrs[i+(startFromLine-scriptItem->startFromLine)].is_mandatory_break)
						{
							if(width<=maxWidth || (firstRun && charLength==0))
							{
								charLength=i-tempStart;
								charAdvances=width;
							}
							else
							{
								return;
							}
						}
						if(i==length) break;

						vint cluster=wholeGlyph.charCluster[i];
						vint clusterLength=1;
						while(i+clusterLength<length)
						{
							if(wholeGlyph.charCluster[i+clusterLength]==cluster)
							{
								clusterLength++;
							}
							else
							{
								break;
							}
						}

						if(scriptItem->IsRightToLeft())
						{
							vint nextCluster
									=i+clusterLength==length
									 ?-1
									 :wholeGlyph.charCluster[i+clusterLength];
							for(vint j=cluster;j>nextCluster;j--)
							{
								width+=wholeGlyph.glyphAdvances[j];
							}
						}
						else
						{
							vint nextCluster
									=i+clusterLength==length
									 ?wholeGlyph.glyphs.Count()
									 :wholeGlyph.charCluster[i+clusterLength];
							for(vint j=cluster;j<nextCluster;j++)
							{
								width+=wholeGlyph.glyphAdvances[j];
							}
						}
						i+=clusterLength;
					}
				}

				void UniscribeTextRun::Render(IRendererCallback* callback, vint fragmentBoundsIndex, vint offsetX, vint offsetY, bool renderBackground)
				{
					auto cr = callback->GetGGacContext();
					RunFragmentBounds& fragment=fragmentBounds[fragmentBoundsIndex];
					if(fragment.length==0) return;

					vint startFromFragmentBounds=0;
					vint accumulatedWidth=0;
					while(startFromFragmentBounds<fragment.length)
					{
						vint charIndex=fragment.startFromRun+startFromFragmentBounds;
						vint charLength=0;
						vint cluster=0;
						vint nextCluster=0;
						SearchSingleGlyphCluster(charIndex, charLength, cluster, nextCluster);

						vint clusterStart=0;
						vint clusterCount=0;
						if (scriptItem->IsRightToLeft())
						{
							clusterStart = nextCluster + 1;
							clusterCount = cluster - nextCluster;
						}
						else
						{
							clusterStart = cluster;
							clusterCount = nextCluster - cluster;
						}

						vint clusterWidth=0;
						for(vint i=0;i<clusterCount;i++)
						{
							clusterWidth+=wholeGlyph.glyphAdvances[i+clusterStart];
						}

						vint x=0;
						if(scriptItem->IsRightToLeft())
						{
							x=fragment.bounds.x2-accumulatedWidth-clusterWidth;
						}
						else
						{
							x=fragment.bounds.x1+accumulatedWidth;
						}
						Cairo::Rectangle rect;
						rect.x=(int)(x+offsetX);
						rect.y=(int)(fragment.bounds.y1+offsetY);
                        rect.width=(int)(clusterWidth);
						rect.height=(int)(fragment.bounds.Height()*1.5);

						UniscribeColor color=documentFragment->GetCharColor(charIndex+startFromFragment);
						if(renderBackground)
						{
							Color backgroundColor=color.backgroundColor;
                            if(backgroundColor.a>0)
							{
								cr->set_source_rgba(backgroundColor.r / 255.f, backgroundColor.g / 255.f, backgroundColor.b / 255.f, backgroundColor.a / 255.f);
								cr->rectangle(rect.x, rect.y, rect.width, rect.height);
								cr->fill();
							}
						}
						else
						{
							//render in cairo context
							Color fontColor=color.fontColor;
							cr->set_source_rgba(fontColor.r / 255.f, fontColor.g / 255.f, fontColor.b / 255.f, fontColor.a / 255.f);
                            if (needFontFallback)
                            {
                                //cr->show_text();
                            }
                            else
                            {
                                auto layout = Pango::Layout::create(cr);
                                layout->set_text(Glib::ustring::format(runText[charIndex]).substr(0, length));
                                layout->set_font_description(*documentFragment->fontObject.Obj());
                                cr->move_to(rect.x, rect.y);
                                Pango::AttrList attrs;
                                if (documentFragment->fontStyle.underline)
                                {
                                    Pango::Attribute attr = Pango::Attribute::create_attr_underline(Pango::UNDERLINE_LOW);
                                    attrs.insert(attr);
                                }
                                if (documentFragment->fontStyle.strikeline)
                                {
                                    Pango::Attribute attr = Pango::Attribute::create_attr_strikethrough(true);
                                    attrs.insert(attr);
                                }
                                layout->set_attributes(attrs);
                                layout->show_in_cairo_context(cr);
                            }
						}

						startFromFragmentBounds+=charLength;
						accumulatedWidth += clusterWidth;
					}
				}

/***********************************************************************
UniscribeEmbeddedObjectRun
***********************************************************************/

				UniscribeEmbeddedObjectRun::UniscribeEmbeddedObjectRun()
				{
				}

				UniscribeEmbeddedObjectRun::~UniscribeEmbeddedObjectRun()
				{
				}

				bool UniscribeEmbeddedObjectRun::BuildUniscribeData(Cairo::RefPtr<Cairo::Context> cr, List<vint>& breakings)
				{
					breakings.Add(0);
					return true;
				}

				vint UniscribeEmbeddedObjectRun::SumWidth(vint charStart, vint charLength)
				{
					return properties.size.x;
				}

				vint UniscribeEmbeddedObjectRun::SumHeight()
				{
					return properties.size.y;
				}

				vint UniscribeEmbeddedObjectRun::SumTextHeight()
				{
					return 0;
				}

				void UniscribeEmbeddedObjectRun::SearchForLineBreak(vint tempStart, vint maxWidth, bool firstRun, vint& charLength, vint& charAdvances)
				{
					if (firstRun || properties.size.x <= maxWidth)
					{
						charLength = length - tempStart;
						charAdvances = properties.size.x;
					}
					else
					{
						charLength = 0;
						charAdvances = 0;
					}
				}

				void UniscribeEmbeddedObjectRun::Render(IRendererCallback* callback, vint fragmentBoundsIndex, vint offsetX, vint offsetY, bool renderBackground)
				{
					auto cr = callback->GetGGacContext();
					RunFragmentBounds& fragment=fragmentBounds[fragmentBoundsIndex];
					if(renderBackground)
					{
						Cairo::Rectangle rect;
						rect.x=(int)(fragment.bounds.Left()+offsetX)-2;
						rect.y=(int)(fragment.bounds.Top()+offsetY)-2;
						rect.width=(int)(fragment.bounds.Right()+offsetX)+2-rect.x;
						rect.height=(int)(fragment.bounds.Bottom()+offsetY)+2-rect.y;

						Color backgroundColor=documentFragment->colors.Values()[0].backgroundColor;

						if(backgroundColor.a>0)
						{
							cr->set_source_rgba(backgroundColor.r / 255.f, backgroundColor.g / 255.f, backgroundColor.b / 255.f, backgroundColor.a / 255.f);
							cr->rectangle(rect.x, rect.y, rect.width, rect.height);
							cr->fill();
						}
					}
					else
					{
						if (properties.backgroundImage)
						{
							Rect bounds=fragment.bounds;
							bounds.x1+=offsetX;
							bounds.x2+=offsetX;
							bounds.y1+=offsetY;
							bounds.y2+=offsetY;
							IGuiGraphicsRenderer* renderer=properties.backgroundImage->GetRenderer();
							if(renderer)
							{
								renderer->Render(bounds);
							}
						}

						if (properties.callbackId != -1)
						{
							if (auto paragraphCallback = callback->GetParagraphCallback())
							{
								auto offset = callback->GetParagraphOffset();
								vint x = fragment.bounds.x1 + offsetX - offset.x;
								vint y = fragment.bounds.y1 + offsetY - offset.y;
								auto size = paragraphCallback->OnRenderInlineObject(properties.callbackId, Rect(Point(x, y), fragment.bounds.GetSize()));
								properties.size = size;
							}
						}
					}
				}

/***********************************************************************
UniscribeVirtualLine
***********************************************************************/

				UniscribeVirtualLine::UniscribeVirtualLine()
						:startFromLine(0)
						,length(0)
						,runText(0)
						,firstRunIndex(-1)
						,firstRunBoundsIndex(-1)
						,lastRunIndex(-1)
						,lastRunBoundsIndex(-1)
				{
				}

/***********************************************************************
UniscribeLine
***********************************************************************/

				UniscribeLine::UniscribeLine()
						:startFromParagraph(0)
				{
				}

				void UniscribeLine::ClearUniscribeData()
				{
					scriptItems.Clear();
					scriptRuns.Clear();
					virtualLines.Clear();
				}

				bool UniscribeLine::BuildUniscribeData()
				{
					lineText=L"";
					ClearUniscribeData();
					vint current=0;
					List<vint> fragmentStarts;
					for (Ptr<UniscribeFragment> fragment : documentFragments)
					{
						fragmentStarts.Add(current);
						lineText += fragment->text;
						current += fragment->text.Length();
					}

					if (lineText!=L"")
					{
						auto surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 1, 1);
						auto cr = Cairo::Context::create(surface);
						auto layout = Pango::Layout::create(cr);
						Glib::RefPtr<Pango::Context> pc = layout->get_context();
						{
							// itemize a line
							auto text = Glib::ustring::format(lineText.Buffer());
                            // TODO: set text attrs here
                            Pango::AttrList attrs;
                            auto list = pc->itemize(text, attrs);
                            vint offset = 0;
                            for (auto item : list)
							{
								Ptr<UniscribeItem> scriptItem = Ptr(new UniscribeItem);
                                scriptItem->itemText = (wchar_t *)g_convert(text.c_str() + item.get_offset(), item.get_length(), "wchar_t", "utf-8", NULL, NULL, NULL);
								scriptItem->startFromLine = offset;
                                offset += item.get_num_chars();
								scriptItem->length = item.get_num_chars();
								scriptItem->scriptItem = item;
								if (!scriptItem->BuildUniscribeData())
								{
									goto BUILD_UNISCRIBE_DATA_FAILED;
								}
								scriptItems.Add(scriptItem);
							}
						}
						{
                            // 1 paragraph => n lines
                            // 1 line => itemize => n items
                            // 1 item => n runs
							// use item and document fragment information to produce runs
							// one item is constructed by one or more runs
							// characters in each run contains the same style
							vint fragmentIndex=0;
							vint fragmentStart=0;
							for(vint i=0;i<scriptItems.Count();i++)
							{
								Ptr<UniscribeItem> scriptItem=scriptItems[i];
								vint currentStart=scriptItem->startFromLine;

								//build scriptRuns
								while(currentStart<scriptItem->startFromLine+scriptItem->length)
								{
									UniscribeFragment* fragment=0;
									vint itemRemainLength=scriptItem->length-(currentStart-scriptItem->startFromLine);
									vint fragmentRemainLength=0;
									while(true)
									{
										fragment=documentFragments[fragmentIndex].Obj();
										fragmentRemainLength=fragment->text.Length()-(currentStart-fragmentStart);
										if(fragmentRemainLength<=0)
										{
											fragmentStart+=fragment->text.Length();
											fragmentIndex++;
										}
										else
										{
											break;
										}
									}
									vint shortLength= MIN(itemRemainLength, fragmentRemainLength);
									bool skip=false;
									{
										vint elementCurrent=0;
										for (Ptr<UniscribeFragment> elementFragment : documentFragments)
										{
											vint elementLength = elementFragment->text.Length();
											//embeddedobject
											if (elementFragment->inlineObjectProperties)
											{
												if (elementCurrent <= currentStart && currentStart + shortLength <= elementCurrent + elementLength)
												{
													if (elementCurrent == currentStart)
													{
														auto run = Ptr(new UniscribeEmbeddedObjectRun());
														run->documentFragment = fragment;
														run->scriptItem = scriptItem.Obj();
														run->startFromLine = currentStart;
														run->startFromFragment = currentStart - fragmentStarts[fragmentIndex];
														run->length = elementLength;
														run->runText = lineText.Buffer() + currentStart;
														run->properties = elementFragment->inlineObjectProperties.Value();
														scriptRuns.Add(run);
													}
													skip = true;
													break;
												}
											}
											elementCurrent += elementLength;
										}
									}
									if (!skip)
									{
										//text
										Ptr<UniscribeTextRun> run = Ptr(new UniscribeTextRun);
										run->pc = pc;
										run->documentFragment = fragment;
										run->scriptItem = scriptItem.Obj();
										run->startFromLine = currentStart;
										run->startFromFragment = currentStart - fragmentStarts[fragmentIndex];
										run->length = shortLength;
										run->runText = lineText.Buffer() + currentStart;
										scriptRuns.Add(run);
									}
									currentStart+=shortLength;
								}
							}

							// for each run, generate shape information
							vint runIndex=0;
							while(runIndex<scriptRuns.Count())
							{
								Ptr<UniscribeRun> run=scriptRuns[runIndex];
								List<vint> breakings;
								if(!run->BuildUniscribeData(cr, breakings))
								{
									goto BUILD_UNISCRIBE_DATA_FAILED;
								}
								else if(breakings.Count()>1)
								{
									//set new text ??
									if(Ptr<UniscribeTextRun> textRun=run.Cast<UniscribeTextRun>())
									{
										scriptRuns.RemoveAt(runIndex);
										for(vint i=0;i<breakings.Count();i++)
										{
											vint start=breakings[i];
											vint length=i==breakings.Count()-1?textRun->length-start:breakings[i+1]-start;

											Ptr<UniscribeTextRun> newRun = Ptr(new UniscribeTextRun);
											newRun->documentFragment = run->documentFragment;
											newRun->scriptItem = run->scriptItem;
											newRun->startFromLine = start+run->startFromLine;
											newRun->startFromFragment = start+run->startFromFragment;
											newRun->length = length;
											newRun->runText = run->runText + newRun->startFromLine - run->startFromLine;
											scriptRuns.Insert(runIndex+i, newRun);
										}
										continue;
									}
								}
								runIndex++;
							}
						}
					}
					return true;
					BUILD_UNISCRIBE_DATA_FAILED:
					ClearUniscribeData();
					return false;
				}

				void UniscribeLine::Layout(vint availableWidth, Alignment alignment, vint top, vint& totalHeight)
				{
					vint cx=0;
					vint cy=top;
					virtualLines.Clear();
					if(scriptRuns.Count()==0)
					{
						// if this line doesn't contains any run, skip and render a blank line
						vint height=(vint)(documentFragments[0]->fontStyle.size*1.5);
						bounds=Rect(Point(cx, cy), Size(0, height));
						cy+=height;
					}
					else
					{
						for (auto run : scriptRuns)
						{
							run->fragmentBounds.Clear();
						}

						// render this line into lines with auto line wrapping
						vint startRun=0;
						vint startRunOffset=0;
						vint lastRun=0;
						vint lastRunOffset=0;
						vint currentWidth=0;

						while(startRun<scriptRuns.Count())
						{
							vint currentWidth=0;
							bool firstRun=true;
							// search for a range to fit in the given width
							for(vint i=startRun;i<scriptRuns.Count();i++)
							{
								vint charLength=0;
								vint charAdvances=0;
								UniscribeRun* run=scriptRuns[i].Obj();
								run->SearchForLineBreak(lastRunOffset, availableWidth-currentWidth, firstRun, charLength, charAdvances);
								firstRun=false;

								if(charLength==run->length-lastRunOffset)
								{
									lastRun=i+1;
									lastRunOffset=0;
									currentWidth+=charAdvances;
								}
								else
								{
									lastRun=i;
									lastRunOffset=lastRunOffset+charLength;
									break;
								}
							}

							// if the range is empty, then this should be the end of line, ignore it
							if(startRun<lastRun || (startRun==lastRun && startRunOffset<lastRunOffset))
							{
								// calculate the max line height in this range;
								vint availableLastRun=lastRun<scriptRuns.Count()-1?lastRun:scriptRuns.Count()-1;
								vint maxHeight=0;
								vint maxTextHeight=0;
								for(vint i=startRun;i<=availableLastRun;i++)
								{
									if(i==lastRun && lastRunOffset==0)
									{
										break;
									}
									{
										vint size=scriptRuns[i]->SumHeight();
										if(maxHeight<size) maxHeight=size;
									}
									{
										vint size=scriptRuns[i]->SumTextHeight();
										if(maxTextHeight<size) maxTextHeight=size;
									}
								}

								// determine the rendering order for all runs inside this range
								Array<BYTE> levels(availableLastRun-startRun+1);
								Array<int> runVisualToLogical(levels.Count());
								Array<int> runLogicalToVisual(levels.Count());
								for(vint i=startRun;i<=availableLastRun;i++)
								{
									levels[i - startRun] = scriptRuns[i]->scriptItem->scriptItem.get_analysis().get_level();
								}

								//ScriptLayout((int)levels.Count(), &levels[0], &runVisualToLogical[0], &runLogicalToVisual[0]);
								for (vint i = 0; i < levels.Count(); i++)
								{
									//what does level do here?
									runLogicalToVisual[i] = i;
									runVisualToLogical[i] = i;
								}

								// render all runs inside this range
								vint startRunFragmentCount=-1;
								for(vint i=startRun;i<=availableLastRun;i++)
								{
									vint runIndex=runVisualToLogical[i-startRun]+startRun;
									UniscribeRun* run=scriptRuns[runIndex].Obj();
									vint start=runIndex==startRun?startRunOffset:0;
									vint end=runIndex==lastRun?lastRunOffset:run->length;
									vint length=end-start;

									if(runIndex==startRun)
									{
										startRunFragmentCount=run->fragmentBounds.Count();
									}

									UniscribeRun::RunFragmentBounds fragmentBounds;
									fragmentBounds.startFromRun=start;
									fragmentBounds.length=length;
									fragmentBounds.bounds=Rect(
											Point(cx, cy+maxHeight-run->SumHeight()),
											Size(run->SumWidth(start, length), run->SumHeight())
									);
									run->fragmentBounds.Add(fragmentBounds);

									cx+=run->SumWidth(start, length);
								}

								// adjust alignment
								vint cxOffset=0;
								switch(alignment)
								{
									case Alignment::Center:
										cxOffset=(availableWidth-cx)/2;
										break;
									case Alignment::Right:
										cxOffset=availableWidth-cx;
										break;
								}

								// shift all bounds using alignment
								if(cxOffset!=0)
								{
									for(vint i=startRun;i<=availableLastRun;i++)
									{
										UniscribeRun* run=scriptRuns[i].Obj();
										for(vint j=(i==startRun?startRunFragmentCount:0);j<run->fragmentBounds.Count();j++)
										{
											UniscribeRun::RunFragmentBounds& fragmentBounds=run->fragmentBounds[j];
											fragmentBounds.bounds.x1+=cxOffset;
											fragmentBounds.bounds.x2+=cxOffset;
										}
									}
								}

								// create a virtual line
								{
									Ptr<UniscribeVirtualLine> virtualLine=Ptr(new UniscribeVirtualLine);
									virtualLine->firstRunIndex=startRun;
									virtualLine->firstRunBoundsIndex=startRunFragmentCount;
									virtualLine->lastRunIndex=availableLastRun;
									virtualLine->lastRunBoundsIndex=scriptRuns[availableLastRun]->fragmentBounds.Count()-1;

									UniscribeRun* firstRun=scriptRuns[virtualLine->firstRunIndex].Obj();
									UniscribeRun* lastRun=scriptRuns[virtualLine->lastRunIndex].Obj();
									UniscribeRun::RunFragmentBounds& firstBounds=firstRun->fragmentBounds[virtualLine->firstRunBoundsIndex];
									UniscribeRun::RunFragmentBounds& lastBounds=lastRun->fragmentBounds[virtualLine->lastRunBoundsIndex];

									virtualLine->startFromLine=firstRun->startFromLine+firstBounds.startFromRun;
									virtualLine->length=lastRun->startFromLine+lastBounds.startFromRun+lastBounds.length-virtualLine->startFromLine;
									virtualLine->runText=lineText.Buffer()+virtualLine->startFromLine;

									bool updateBounds=false;
									for(vint i=startRun;i<=availableLastRun;i++)
									{
										UniscribeRun* run=scriptRuns[i].Obj();
										for(vint j=(i==startRun?startRunFragmentCount:0);j<run->fragmentBounds.Count();j++)
										{
											UniscribeRun::RunFragmentBounds& fragmentBounds=run->fragmentBounds[j];
											if(updateBounds)
											{
												if(virtualLine->bounds.x1>fragmentBounds.bounds.x1) virtualLine->bounds.x1=fragmentBounds.bounds.x1;
												if(virtualLine->bounds.x2<fragmentBounds.bounds.x2) virtualLine->bounds.x2=fragmentBounds.bounds.x2;
												if(virtualLine->bounds.y1>fragmentBounds.bounds.y1) virtualLine->bounds.y1=fragmentBounds.bounds.y1;
												if(virtualLine->bounds.y2<fragmentBounds.bounds.y2) virtualLine->bounds.y2=fragmentBounds.bounds.y2;
											}
											else
											{
												virtualLine->bounds=fragmentBounds.bounds;
												updateBounds=true;
											}
										}
									}
									virtualLines.Add(virtualLine);
								}

								cx=0;
								cy+=(vint)(maxHeight + maxTextHeight*0.5);
							}

							startRun=lastRun;
							startRunOffset=lastRunOffset;
						}

						// calculate line bounds
						vint minX=0;
						vint minY=top;
						vint maxX=0;
						vint maxY=top;
						for (Ptr<UniscribeRun> run : scriptRuns)
						{
							for (UniscribeRun::RunFragmentBounds fragmentBounds : run->fragmentBounds)
							{
								Rect bounds = fragmentBounds.bounds;
								if (minX > bounds.Left()) minX = bounds.Left();
								if (minY > bounds.Top()) minY = bounds.Top();
								if (maxX < bounds.Right()) maxX = bounds.Right();
								if (maxY < bounds.Bottom()) maxY = bounds.Bottom();
							}
						}
						bounds=Rect(minX, minY, maxX, maxY);
					}
					totalHeight=cy;
				}

				void UniscribeLine::Render(UniscribeRun::IRendererCallback* callback, vint offsetX, vint offsetY, bool renderBackground)
				{
					for (Ptr<UniscribeRun> run : scriptRuns)
					{
						for (vint i = 0; i < run->fragmentBounds.Count(); i++)
						{
                            //Rect bounds = run->fragmentBounds[i].bounds;
                            //console::Console::WriteLine(itow(i) + L" " + itow(bounds.x1) + L" " + itow(bounds.y1) + L" " + itow(bounds.x2) + L" " + itow(bounds.y2));
							run->Render(callback, i, offsetX, offsetY, renderBackground);
						}
					}
				}

/***********************************************************************
UniscribeParagraph
***********************************************************************/

				UniscribeParagraph::UniscribeParagraph()
						:lastAvailableWidth(-1)
						,paragraphAlignment(Alignment::Left)
						,built(false)
				{
				}

				UniscribeParagraph::~UniscribeParagraph()
				{
					ClearUniscribeData();
				}

/***********************************************************************
UniscribeParagraph (Initialization)
***********************************************************************/

				void UniscribeParagraph::ClearUniscribeData()
				{
					for (Ptr<UniscribeFragment> fragment : documentFragments)
					{
						//GetGGacResourceManager()->DestroyGdiFont(fragment->fontStyle);
						fragment->fontObject = 0;
					}
					lines.Clear();
					lastAvailableWidth=-1;
				}

				bool UniscribeParagraph::BuildUniscribeData()
				{
					if(built) return false;

					built=true;
					ClearUniscribeData();

					//set $fonts
					Dictionary<WString, Ptr<Pango::FontDescription>> fonts;
					for (Ptr<UniscribeFragment> fragment : documentFragments)
					{
						if (!fragment->fontObject)
						{
							WString fragmentFingerPrint = fragment->GetFingerprint();
							vint index = fonts.Keys().IndexOf(fragmentFingerPrint);
							if (index == -1)
							{
								fragment->fontObject = GetGGacResourceManager()->CreateGGacFont(fragment->fontStyle);
								fonts.Add(fragmentFingerPrint, fragment->fontObject);
							}
							else
							{
								fragment->fontObject = fonts.Values().Get(index);
							}
						}
					}

					//split paragraph fragment into $lines
					{
						Regex regexLine(L"\r\n");
						Ptr<UniscribeLine> line;
						for (Ptr<UniscribeFragment> fragment : documentFragments)
						{
							if (fragment->inlineObjectProperties)
							{
                                if (!line)
                                {
                                    line=Ptr(new UniscribeLine);
                                    lines.Add(line);
                                }
                                line->documentFragments.Add(fragment);
                            }
                            else
                            {
                                RegexMatch::List textLines;
                                regexLine.Split(fragment->text, true, textLines);

                                for(vint i=0;i<textLines.Count();i++)
                                {
                                    RegexString rs=textLines[i]->Result();
                                    WString text=rs.Value();
                                    if(i>0)
                                    {
                                        line=0;
                                    }
                                    if(!line)
                                    {
                                        line=Ptr(new UniscribeLine);
                                        lines.Add(line);
                                    }

                                    if(textLines.Count()==1)
                                    {
                                        line->documentFragments.Add(fragment);
                                    }
                                    else
                                    {
                                        Ptr<UniscribeFragment> runFragment=fragment->Copy(rs.Start(), rs.Length());
                                        line->documentFragments.Add(runFragment);
                                    }
                                }
                            }
                        }
                    }

                    //build uniscribedata line by line from $lines
                    for (Ptr<UniscribeLine> line : lines)
                    {
						line->BuildUniscribeData();
					}

					//set $startFromParagraph of line line by line from $lines
					vint lineStart=0;
					for (Ptr<UniscribeLine> line : lines)
					{
						line->startFromParagraph = lineStart;
						lineStart += line->lineText.Length() + 2;
					}

					return true;
				}

				void UniscribeParagraph::Layout(vint availableWidth, Alignment alignment)
				{
					if(lastAvailableWidth==availableWidth && paragraphAlignment==alignment)
					{
						return;
					}
					lastAvailableWidth=availableWidth;
					paragraphAlignment=alignment;

					vint cy=0;
					for (Ptr<UniscribeLine> line : lines)
					{
						line->Layout(availableWidth, alignment, cy, cy);
					}

					// calculate paragraph bounds
					vint minX=0;
					vint minY=0;
					vint maxX=0;
					vint maxY=0;
					for (Ptr<UniscribeLine> line : lines)
					{
						Rect bounds = line->bounds;
						if (minX > bounds.Left()) minX = bounds.Left();
						if (minY > bounds.Top()) minX = bounds.Top();
						if (maxX < bounds.Right()) maxX = bounds.Right();
						if (maxY < bounds.Bottom()) maxY = bounds.Bottom();
					}

					vint offsetY=0;
					for (Ptr<UniscribeLine> line : lines)
					{
						for (Ptr<UniscribeFragment> fragment : line->documentFragments)
						{
							vint size = fragment->fontStyle.size / 3;
							if (size > offsetY)
							{
								offsetY = size;
							}
						}
					}
					bounds=Rect(minX, minY, maxX, maxY+offsetY);
				}

				void UniscribeParagraph::Render(UniscribeRun::IRendererCallback* callback, bool renderBackground)
				{
					auto offset = callback->GetParagraphOffset();
					for (Ptr<UniscribeLine> line : lines)
					{
						line->Render(callback, offset.x, offset.y, renderBackground);
					}
				}

/***********************************************************************
UniscribeParagraph (Formatting Helper)
***********************************************************************/

				void UniscribeParagraph::SearchFragment(vint start, vint length, vint& fs, vint& ss, vint& fe, vint& se)
				{
					fs=-1;
					ss=-1;
					fe=-1;
					se=-1;
					vint current=0;
					for(vint i=0;i<documentFragments.Count();i++)
					{
						vint fragmentLength=documentFragments[i]->text.Length();
						if(current<=start && start<current+fragmentLength)
						{
							fs=i;
							ss=start-current;
						}
						if(current<=start+length && start+length<=current+fragmentLength)
						{
							fe=i;
							se=start+length-current;
						}
						if(fs!=-1 && fe!=-1)
						{
							break;
						}
						current+=fragmentLength;
					}
				}

				bool UniscribeParagraph::CutFragment(vint fs, vint ss, vint fe, vint se, vint& f1, vint& f2)
				{
					f1=-1;
					f2=-1;
					if(fs==fe)
					{
						Ptr<UniscribeFragment> fragment=documentFragments[fs];
						if(fragment->inlineObjectProperties)
						{
							if(ss==0 && se==fragment->text.Length())
							{
								f1=f2=fs;
								return true;
							}
							else
							{
								return false;
							}
						}
					}
					for(vint i=fs;i<=fe;i++)
					{
						if(documentFragments[i]->inlineObjectProperties)
						{
							return false;
						}
					}
					if(fs==fe)
					{
						Ptr<UniscribeFragment> fragment=documentFragments[fs];
						vint length=fragment->text.Length();
						if(ss==0)
						{
							if(se==length)
							{
								f1=f2=fs;
							}
							else
							{
								f1=f2=fs;
								Ptr<UniscribeFragment> leftFragment=fragment->Copy(0, se);
								Ptr<UniscribeFragment> rightFragment=fragment->Copy(se, length-se);
								documentFragments.RemoveAt(fs);
								documentFragments.Insert(fs, leftFragment);
								documentFragments.Insert(fs+1, rightFragment);
							}
						}
						else
						{
							if(se==length)
							{
								f1=fs+1;
								f2=fs+1;
								Ptr<UniscribeFragment> leftFragment=fragment->Copy(0, ss);
								Ptr<UniscribeFragment> rightFragment=fragment->Copy(ss, length-ss);
								documentFragments.RemoveAt(fs);
								documentFragments.Insert(fs, leftFragment);
								documentFragments.Insert(fs+1, rightFragment);
							}
							else
							{
								f1=fs+1;
								f2=fs+1;
								Ptr<UniscribeFragment> leftFragment=fragment->Copy(0, ss);
								Ptr<UniscribeFragment> middleFragment=fragment->Copy(ss, se-ss);
								Ptr<UniscribeFragment> rightFragment=fragment->Copy(se, length-se);
								documentFragments.RemoveAt(fs);
								documentFragments.Insert(fs, leftFragment);
								documentFragments.Insert(fs+1, middleFragment);
								documentFragments.Insert(fs+2, rightFragment);
							}
						}
					}
					else
					{
						Ptr<UniscribeFragment> fragmentStart=documentFragments[fs];
						Ptr<UniscribeFragment> fragmentEnd=documentFragments[fe];
						if(ss==0)
						{
							f1=fs;
						}
						else
						{
							f1=fs+1;
							fe++;
							vint length=fragmentStart->text.Length();
							Ptr<UniscribeFragment> leftFragment=fragmentStart->Copy(0, ss);
							Ptr<UniscribeFragment> rightFragment=fragmentStart->Copy(ss, length-ss);
							documentFragments.RemoveAt(fs);
							documentFragments.Insert(fs, leftFragment);
							documentFragments.Insert(fs+1, rightFragment);
						}
						if(se==fragmentEnd->text.Length())
						{
							f2=fe;
						}
						else
						{
							f2=fe;
							fe++;
							vint length=fragmentEnd->text.Length();
							Ptr<UniscribeFragment> leftFragment=fragmentStart->Copy(0, se);
							Ptr<UniscribeFragment> rightFragment=fragmentEnd->Copy(se, length-se);
							documentFragments.RemoveAt(fe);
							documentFragments.Insert(fe, leftFragment);
							documentFragments.Insert(fe+1, rightFragment);
						}
					}
					return true;
				}

				void UniscribeParagraph::CutFragmentColors(vint fs, vint ss, vint fe, vint se, Color UniscribeColor::* colorField, Color color)
				{
					for(vint f=fs;f<=fe;f++)
					{
						Ptr<UniscribeFragment> fragment=documentFragments[f];
						vint start=f==fs?ss:0;
						vint end=f==fe?se:fragment->text.Length();

						fragment->CutColors(start, end-start);
						fragment->UpdateOverlappedColors(start, end-start, colorField, color);
						fragment->DefragmentColors();
					}
				}

/***********************************************************************
UniscribeParagraph (Formatting)
***********************************************************************/

				bool UniscribeParagraph::SetFont(vint start, vint length, const WString& value)
				{
					vint fs, ss, fe, se, f1, f2;
					SearchFragment(start, length, fs, ss, fe, se);
					if(CutFragment(fs, ss, fe, se, f1, f2))
					{
						for(vint i=f1;i<=f2;i++)
						{
							documentFragments[i]->fontStyle.fontFamily=value;
						}
						built=false;
						return true;
					}
					else
					{
						return false;
					}
				}

				bool UniscribeParagraph::SetSize(vint start, vint length, vint value)
				{
					vint fs, ss, fe, se, f1, f2;
					SearchFragment(start, length, fs, ss, fe, se);
					if(CutFragment(fs, ss, fe, se, f1, f2))
					{
						for(vint i=f1;i<=f2;i++)
						{
							documentFragments[i]->fontStyle.size=value;
						}
						built=false;
						return true;
					}
					else
					{
						return false;
					}
				}

				bool UniscribeParagraph::SetStyle(vint start, vint length, bool bold, bool italic, bool underline, bool strikeline)
				{
					vint fs, ss, fe, se, f1, f2;
					SearchFragment(start, length, fs, ss, fe, se);
					if(CutFragment(fs, ss, fe, se, f1, f2))
					{
						for(vint i=f1;i<=f2;i++)
						{
							documentFragments[i]->fontStyle.bold=bold;
							documentFragments[i]->fontStyle.italic=italic;
							documentFragments[i]->fontStyle.underline=underline;
							documentFragments[i]->fontStyle.strikeline=strikeline;
						}
						built=false;
						return true;
					}
					else
					{
						return false;
					}
				}

				bool UniscribeParagraph::SetColor(vint start, vint length, Color value)
				{
					vint fs, ss, fe, se;
					SearchFragment(start, length, fs, ss, fe, se);
					if(fs==-1 || ss==-1 || fe==-1 || se==-1) return false;

					CutFragmentColors(fs, ss, fe, se, &UniscribeColor::fontColor, value);
					return true;
				}

				bool UniscribeParagraph::SetBackgroundColor(vint start, vint length, Color value)
				{
					vint fs, ss, fe, se;
					SearchFragment(start, length, fs, ss, fe, se);
					if(fs==-1 || ss==-1 || fe==-1 || se==-1) return false;

					CutFragmentColors(fs, ss, fe, se, &UniscribeColor::backgroundColor, value);
					return true;
				}

				bool UniscribeParagraph::SetInlineObject(vint start, vint length, const IGuiGraphicsParagraph::InlineObjectProperties& properties)
				{
					vint fs, ss, fe, se, f1, f2;
					SearchFragment(start, length, fs, ss, fe, se);
					if(CutFragment(fs, ss, fe, se, f1, f2))
					{
						WString text;
						for(vint i=f1;i<=f2;i++)
						{
							text+=documentFragments[f1]->text;
						}
						Ptr<UniscribeFragment> elementFragment=Ptr(new UniscribeFragment(text));

						for(vint i=f1;i<=f2;i++)
						{
							elementFragment->cachedTextFragment.Add(documentFragments[f1]);
							documentFragments.RemoveAt(f1);
						}
						elementFragment->inlineObjectProperties=properties;
						documentFragments.Insert(f1, elementFragment);
						built=false;
						return true;
					}
					else
					{
						return false;
					}
				}

				InlineObject UniscribeParagraph::ResetInlineObject(vint start, vint length)
				{
					vint fs, ss, fe, se;
					SearchFragment(start, length, fs, ss, fe, se);
					Ptr<UniscribeFragment> fragment = documentFragments[fs];
					if(fs==fe && ss==0 && se==fragment->text.Length() && fragment->inlineObjectProperties)
					{
						documentFragments.RemoveAt(fs);
						for(vint i=0;i<fragment->cachedTextFragment.Count();i++)
						{
							documentFragments.Insert(fs+i, fragment->cachedTextFragment[i]);
						}
						built=false;
						return fragment->inlineObjectProperties;
					}
					return InlineObject();
				}

/***********************************************************************
UniscribeParagraph (Caret Helper)
***********************************************************************/

				void UniscribeParagraph::GetLineIndexFromTextPos(vint textPos, vint& frontLine, vint& backLine)
				{
					frontLine=-1;
					backLine=-1;
					if(!IsValidTextPos(textPos)) return;

					vint start=0;
					vint end=lines.Count()-1;
					while(start<=end)
					{
						vint middle=(start+end)/2;
						Ptr<UniscribeLine> line=lines[middle];
						vint lineStart=line->startFromParagraph;
						vint lineEnd=line->startFromParagraph+line->lineText.Length();
						if(textPos<lineStart)
						{
							if(textPos==lineStart-1)
							{
								frontLine=middle-1;
								backLine=middle;
								return;
							}
							else
							{
								end=middle-1;
							}
						}
						else if(textPos>lineEnd)
						{
							if(textPos==lineEnd+1)
							{
								frontLine=middle;
								backLine=middle+1;
								return;
							}
							else
							{
								start=middle+1;
							}
						}
						else
						{
							frontLine=middle;
							backLine=middle;
							return;
						}
					}
				}

				void UniscribeParagraph::GetVirtualLineIndexFromTextPos(vint textPos, vint lineIndex, vint& frontLine, vint& backLine)
				{
					frontLine=-1;
					backLine=-1;
					if(!IsValidTextPos(textPos)) return;
					if(lineIndex<0 || lineIndex>=lines.Count()) return;

					Ptr<UniscribeLine> line=lines[lineIndex];
					vint start=0;
					vint end=line->virtualLines.Count()-1;
					while(start<=end)
					{
						vint middle=(start+end)/2;
						Ptr<UniscribeVirtualLine> vline=line->virtualLines[middle];
						vint lineStart=line->startFromParagraph+vline->startFromLine;
						vint lineEnd=line->startFromParagraph+vline->startFromLine+vline->length;
						if(textPos<lineStart)
						{
							end=middle-1;
						}
						else if(textPos>lineEnd)
						{
							start=middle+1;
						}
						else if(textPos==lineStart)
						{
							frontLine=middle==0?0:middle-1;
							backLine=middle;
							return;
						}
						else if(textPos==lineEnd)
						{
							frontLine=middle;
							backLine=middle==line->virtualLines.Count()-1?middle:middle+1;
							return;
						}
						else
						{
							frontLine=middle;
							backLine=middle;
							return;
						}
					}
				}

				void UniscribeParagraph::GetItemIndexFromTextPos(vint textPos, vint lineIndex, vint& frontItem, vint& backItem)
				{
					frontItem=-1;
					backItem=-1;
					if(!IsValidTextPos(textPos)) return;
					if(lineIndex<0 || lineIndex>=lines.Count()) return;

					Ptr<UniscribeLine> line=lines[lineIndex];
					vint start=0;
					vint end=line->scriptItems.Count()-1;
					while(start<=end)
					{
						vint middle=(start+end)/2;
						Ptr<UniscribeItem> item=line->scriptItems[middle];
						vint lineStart=line->startFromParagraph+item->startFromLine;
						vint lineEnd=line->startFromParagraph+item->startFromLine+item->length;
						if(textPos<lineStart)
						{
							end=middle-1;
						}
						else if(textPos>lineEnd)
						{
							start=middle+1;
						}
						else if(textPos==lineStart)
						{
							frontItem=middle==0?0:middle-1;
							backItem=middle;
							return;
						}
						else if(textPos==lineEnd)
						{
							frontItem=middle;
							backItem=middle==line->scriptItems.Count()-1?middle:middle+1;
							return;
						}
						else
						{
							frontItem=middle;
							backItem=middle;
							return;
						}
					}
				}

				Rect UniscribeParagraph::GetCaretBoundsWithLine(vint caret, vint lineIndex, vint virtualLineIndex, bool frontSide)
				{
					Ptr<UniscribeLine> line=lines[lineIndex];
					if(line->startFromParagraph<=caret && caret<=line->startFromParagraph+line->lineText.Length())
					{
						if(line->lineText==L"") return line->bounds;
						Ptr<UniscribeVirtualLine> virtualLine=line->virtualLines[virtualLineIndex];

						for(vint i=virtualLine->firstRunIndex;i<=virtualLine->lastRunIndex;i++)
						{
							Ptr<UniscribeRun> run=line->scriptRuns[i];
							if(Ptr<UniscribeTextRun> textRun=run.Cast<UniscribeTextRun>())
							{
								vint firstBounds=i==virtualLine->firstRunIndex?virtualLine->firstRunBoundsIndex:0;
								vint lastBounds=i==virtualLine->lastRunIndex?virtualLine->lastRunBoundsIndex:run->fragmentBounds.Count()-1;

								for(vint j=firstBounds;j<=lastBounds;j++)
								{
									UniscribeRun::RunFragmentBounds& bounds=run->fragmentBounds[j];
									vint boundsStart=line->startFromParagraph+run->startFromLine+bounds.startFromRun;
									if(boundsStart==caret)
									{
										if(!frontSide || i==virtualLine->firstRunIndex && j==virtualLine->firstRunBoundsIndex)
										{
											if(run->scriptItem->IsRightToLeft())
											{
												return Rect(bounds.bounds.x2, bounds.bounds.y1, bounds.bounds.x2, bounds.bounds.y2);
											}
											else
											{
												return Rect(bounds.bounds.x1, bounds.bounds.y1, bounds.bounds.x1, bounds.bounds.y2);
											}
										}
									}
									else if(caret==boundsStart+bounds.length)
									{
										if(frontSide || i==virtualLine->lastRunIndex && j==virtualLine->lastRunBoundsIndex)
										{
											if(run->scriptItem->IsRightToLeft())
											{
												return Rect(bounds.bounds.x1, bounds.bounds.y1, bounds.bounds.x1, bounds.bounds.y2);
											}
											else
											{
												return Rect(bounds.bounds.x2, bounds.bounds.y1, bounds.bounds.x2, bounds.bounds.y2);
											}
										}
									}
									else if(boundsStart<caret && caret<boundsStart+bounds.length)
									{
										vint accumulatedWidth=0;
										vint lastRunChar=bounds.startFromRun;
										for(vint i=0;i<=bounds.length;i++)
										{
											vint charIndex=bounds.startFromRun+i;
											vint newLastRunChar=lastRunChar;
											if(i>0)
											{
												if(i==bounds.length)
												{
													newLastRunChar=charIndex;
												}
												else
												{
													WORD cluster1=textRun->wholeGlyph.charCluster[charIndex-1];
													WORD cluster2=textRun->wholeGlyph.charCluster[charIndex];
													if(cluster1!=cluster2)
													{
														newLastRunChar=charIndex;
													}
												}
											}

											if(newLastRunChar!=lastRunChar)
											{
												WORD glyph1=0;
												WORD glyph2=0;
												if(run->scriptItem->IsRightToLeft())
												{
													glyph2=textRun->wholeGlyph.charCluster[lastRunChar]+1;
													glyph1=newLastRunChar==run->length?0:textRun->wholeGlyph.charCluster[newLastRunChar]+1;
												}
												else
												{
													glyph1=textRun->wholeGlyph.charCluster[lastRunChar];
													glyph2=newLastRunChar==run->length?(WORD)textRun->wholeGlyph.glyphs.Count():textRun->wholeGlyph.charCluster[newLastRunChar];
												}

												vint glyphWidth=0;
												for(WORD g=glyph1;g<glyph2;g++)
												{
													glyphWidth+=textRun->wholeGlyph.glyphAdvances[g];
												}
												accumulatedWidth+=glyphWidth;
												lastRunChar=newLastRunChar;

												if(line->startFromParagraph+run->startFromLine+lastRunChar==caret)
												{
													vint x=0;
													if(run->scriptItem->IsRightToLeft())
													{
														x=bounds.bounds.x2-accumulatedWidth;
													}
													else
													{
														x=bounds.bounds.x1+accumulatedWidth;
													}
													return Rect(x, bounds.bounds.y1, x, bounds.bounds.y2);
												}
											}
										}
									}
								}
							}
						}
					}
					return Rect();
				}

				vint UniscribeParagraph::GetCaretFromXWithTextRunBounds(vint x, vint lineIndex, vint runIndex, vint runBoundsIndex)
				{
					Ptr<UniscribeLine> line=lines[lineIndex];
					if(line->lineText==L"") return line->startFromParagraph;
					Ptr<UniscribeTextRun> run=line->scriptRuns[runIndex].Cast<UniscribeTextRun>();
					UniscribeRun::RunFragmentBounds& bounds=run->fragmentBounds[runBoundsIndex];

					vint startFromFragmentBounds=0;
					vint accumulatedWidth=0;
					while(startFromFragmentBounds<bounds.length)
					{
						vint charIndex=bounds.startFromRun+startFromFragmentBounds;
						vint charLength=0;
						vint cluster=0;
						vint nextCluster=0;
						run->SearchSingleChar(charIndex, charLength, cluster, nextCluster);

						vint clusterStart=0;
						vint clusterCount=0;
						if(run->scriptItem->IsRightToLeft())
						{
							clusterStart=nextCluster+1;
							clusterCount=cluster-nextCluster;
						}
						else
						{
							clusterStart=cluster;
							clusterCount=nextCluster-cluster;
						}

						vint clusterWidth=0;
						for(vint i=0;i<clusterCount;i++)
						{
							clusterWidth+=run->wholeGlyph.glyphAdvances[i+clusterStart];
						}

						if(run->scriptItem->IsRightToLeft())
						{
							//from right to left
							vint x2=bounds.bounds.x2-accumulatedWidth;
							vint x1=x2-clusterWidth;
							if(x1<=x && x<x2)
							{
								vint d1=x-x1;
								vint d2=x2-x;
								if(d1<=d2)
								{
									return line->startFromParagraph+run->startFromLine+charIndex+charLength;
								}
								else
								{
									return line->startFromParagraph+run->startFromLine+charIndex;
								}
							}
						}
						else
						{
							//from left to right
							vint x1=bounds.bounds.x1+accumulatedWidth;
							vint x2=x1+clusterWidth;
							if(x1<=x && x<x2)
							{
								vint d1=x-x1;
								vint d2=x2-x;
								if(d1<=d2)
								{
									return line->startFromParagraph+run->startFromLine+charIndex;
								}
								else
								{
									return line->startFromParagraph+run->startFromLine+charIndex+charLength;
								}
							}
						}

						startFromFragmentBounds+=charLength;
						accumulatedWidth+=clusterWidth;
					}
					return -1;
				}

				vint UniscribeParagraph::GetCaretFromXWithLine(vint x, vint lineIndex, vint virtualLineIndex)
				{
					Ptr<UniscribeLine> line=lines[lineIndex];
					if(line->virtualLines.Count()==0) return line->startFromParagraph;
					Ptr<UniscribeVirtualLine> virtualLine=line->virtualLines[virtualLineIndex];
					if(x<virtualLine->bounds.x1) return line->startFromParagraph+virtualLine->startFromLine;
					if(x>=virtualLine->bounds.x2) return line->startFromParagraph+virtualLine->startFromLine+virtualLine->length;

					for(vint i=virtualLine->firstRunIndex;i<=virtualLine->lastRunIndex;i++)
					{
						Ptr<UniscribeRun> run=line->scriptRuns[i];
						if(Ptr<UniscribeTextRun> textRun=run.Cast<UniscribeTextRun>())
						{
							vint firstBounds=i==virtualLine->firstRunIndex?virtualLine->firstRunBoundsIndex:0;
							vint lastBounds=i==virtualLine->lastRunIndex?virtualLine->lastRunBoundsIndex:run->fragmentBounds.Count()-1;

							for(vint j=firstBounds;j<=lastBounds;j++)
							{
								UniscribeRun::RunFragmentBounds& bounds=run->fragmentBounds[j];
								if(bounds.bounds.x1<=x && x<bounds.bounds.x2)
								{
									return GetCaretFromXWithTextRunBounds(x, lineIndex, i, j);
								}
							}
						}
						else
						{
							Rect bounds=run->fragmentBounds[0].bounds;
							if(bounds.x1<=x && x<bounds.x2)
							{
								vint d1=x-bounds.x1;
								vint d2=bounds.x2-x;
								if(d1<=d2)
								{
									return line->startFromParagraph+run->startFromLine;
								}
								else
								{
									return line->startFromParagraph+run->startFromLine+run->length;
								}
							}
						}
					}
					return -1;
				}

				InlineObject UniscribeParagraph::GetInlineObjectFromXWithLine(vint x, vint lineIndex, vint virtualLineIndex, vint& start, vint& length)
				{
					Ptr<UniscribeLine> line=lines[lineIndex];
					if(line->virtualLines.Count()==0) return InlineObject();
					Ptr<UniscribeVirtualLine> virtualLine=line->virtualLines[virtualLineIndex];
					if(x<virtualLine->bounds.x1) return InlineObject();
					if(x>=virtualLine->bounds.x2) return InlineObject();

					for(vint i=virtualLine->firstRunIndex;i<=virtualLine->lastRunIndex;i++)
					{
						Ptr<UniscribeRun> run=line->scriptRuns[i];
						if(auto elementRun=run.Cast<UniscribeEmbeddedObjectRun>())
						{
							Rect bounds=run->fragmentBounds[0].bounds;
							if(bounds.x1<=x && x<bounds.x2)
							{
								start=line->startFromParagraph+elementRun->startFromLine;
								length=elementRun->length;
								return elementRun->properties;
							}
						}
					}
					return InlineObject();
				}

				vint UniscribeParagraph::GetLineY(vint lineIndex)
				{
					if(lineIndex==lines.Count())
					{
						return bounds.Height();
					}
					else
					{
						return lines[lineIndex]->bounds.y1;
					}
				}

				vint UniscribeParagraph::GetVirtualLineY(vint lineIndex, vint virtualLineIndex)
				{
					Ptr<UniscribeLine> line=lines[lineIndex];
					if(virtualLineIndex==line->virtualLines.Count())
					{
						return GetLineY(lineIndex+1);
					}
					else
					{
						return line->virtualLines[virtualLineIndex]->bounds.y1;
					}
				}

				vint UniscribeParagraph::GetLineIndexFromY(vint y)
				{
					if(y<lines[0]->bounds.y1) return 0;
					if(y>=lines[lines.Count()-1]->bounds.y2) return lines.Count()-1;

					vint start=0;
					vint end=lines.Count()-1;
					while(start<=end)
					{
						vint middle=(start+end)/2;
						vint minY=GetLineY(middle);
						vint maxY=GetLineY(middle+1);
						if(y<minY)
						{
							end=middle-1;
						}
						else if(y>=maxY)
						{
							start=middle+1;
						}
						else
						{
							return middle;
						}
					}
					return -1;
				}

				vint UniscribeParagraph::GetVirtualLineIndexFromY(vint y, vint lineIndex)
				{
					Ptr<UniscribeLine> line=lines[lineIndex];
					if(y<line->bounds.y1) return 0;
					if(y>=line->bounds.y2) return line->virtualLines.Count()-1;

					vint start=0;
					vint end=line->virtualLines.Count()-1;
					while(start<=end)
					{
						vint middle=(start+end)/2;
						vint minY=GetVirtualLineY(lineIndex, middle);
						vint maxY=GetVirtualLineY(lineIndex, middle+1);
						if(y<minY)
						{
							end=middle-1;
						}
						else if(y>=maxY)
						{
							start=middle+1;
						}
						else
						{
							return middle;
						}
					}
					return -1;
				}

/***********************************************************************
UniscribeParagraph (Caret)
***********************************************************************/

				vint UniscribeParagraph::GetCaret(vint comparingCaret, IGuiGraphicsParagraph::CaretRelativePosition position, bool& preferFrontSide)
				{
					if(position==IGuiGraphicsParagraph::CaretFirst) return 0;
					if(position==IGuiGraphicsParagraph::CaretLast) return paragraphText.Length();
					if(!IsValidCaret(comparingCaret)) return -1;

					if(position==IGuiGraphicsParagraph::CaretMoveLeft)
					{
						return comparingCaret==0?0:GetNearestCaretFromTextPos(comparingCaret-1, true);
					}
					if(position==IGuiGraphicsParagraph::CaretMoveRight)
					{
						return comparingCaret==paragraphText.Length()?paragraphText.Length():GetNearestCaretFromTextPos(comparingCaret+1, false);
					}

					vint frontLine=0;
					vint backLine=0;
					GetLineIndexFromTextPos(comparingCaret, frontLine, backLine);

					Ptr<UniscribeLine> line=lines[frontLine];
					if(line->virtualLines.Count()==0)
					{
						switch(position)
						{
							case IGuiGraphicsParagraph::CaretLineFirst:
							case IGuiGraphicsParagraph::CaretLineLast:
								return line->startFromParagraph;
						}
					}

					vint frontVirtualLine=0;
					vint backVirtualLine=0;
					GetVirtualLineIndexFromTextPos(comparingCaret, frontLine, frontVirtualLine, backVirtualLine);
					vint virtualLineIndex=preferFrontSide?frontVirtualLine:backVirtualLine;

					Ptr<UniscribeVirtualLine> virtualLine=virtualLineIndex==-1?nullptr:line->virtualLines[virtualLineIndex];

					switch(position)
					{
						case IGuiGraphicsParagraph::CaretLineFirst:
							return line->startFromParagraph+virtualLine->startFromLine;
						case IGuiGraphicsParagraph::CaretLineLast:
							return line->startFromParagraph+virtualLine->startFromLine+virtualLine->length;
						case IGuiGraphicsParagraph::CaretMoveUp:
						{
							if(frontLine==0 && virtualLineIndex<=0) return comparingCaret;
							Rect bounds=GetCaretBoundsWithLine(comparingCaret, frontLine, virtualLineIndex, preferFrontSide);
							if(bounds.Height()!=0)
							{
								if(virtualLineIndex<=0)
								{
									frontLine--;
									virtualLineIndex=lines[frontLine]->virtualLines.Count()-1;
								}
								else
								{
									virtualLineIndex--;
								}
								preferFrontSide=true;
								return GetCaretFromXWithLine(bounds.x1, frontLine, virtualLineIndex);
							}
						}
							break;
						case IGuiGraphicsParagraph::CaretMoveDown:
						{
							if(frontLine==lines.Count()-1 && virtualLineIndex==line->virtualLines.Count()-1) return comparingCaret;
							Rect bounds=GetCaretBoundsWithLine(comparingCaret, frontLine, virtualLineIndex, preferFrontSide);
							if(bounds.Height()!=0)
							{
								if(virtualLineIndex==line->virtualLines.Count()-1)
								{
									frontLine++;
									virtualLineIndex=0;
								}
								else
								{
									virtualLineIndex++;
								}
								preferFrontSide=false;
								return GetCaretFromXWithLine(bounds.x1, frontLine, virtualLineIndex);
							}
						}
							break;
					}
					return -1;
				}

				Rect UniscribeParagraph::GetCaretBounds(vint caret, bool frontSide)
				{
					if(!IsValidCaret(caret)) return Rect();

					vint frontLine=0;
					vint backLine=0;
					GetLineIndexFromTextPos(caret, frontLine, backLine);

					vint frontVirtualLine=0;
					vint backVirtualLine=0;
					GetVirtualLineIndexFromTextPos(caret, frontLine, frontVirtualLine, backVirtualLine);
					vint virtualLineIndex=frontSide?frontVirtualLine:backVirtualLine;

					Rect x = GetCaretBoundsWithLine(caret, frontLine, virtualLineIndex, frontSide);
					return x;
				}

				vint UniscribeParagraph::GetCaretFromPoint(Point point)
				{
					vint lineIndex=GetLineIndexFromY(point.y);
					if(lineIndex==-1) return -1;

					Ptr<UniscribeLine> line=lines[lineIndex];
					if(line->virtualLines.Count()==0) return line->startFromParagraph;

					vint virtualLineIndex=GetVirtualLineIndexFromY(point.y, lineIndex);
					if(virtualLineIndex==-1) return -1;

					return GetCaretFromXWithLine(point.x, lineIndex, virtualLineIndex);
				}

				InlineObject UniscribeParagraph::GetInlineObjectFromPoint(Point point, vint& start, vint& length)
				{
					start = -1;
					length = 0;
					vint lineIndex = GetLineIndexFromY(point.y);
					if (lineIndex == -1) return InlineObject();

					Ptr<UniscribeLine> line = lines[lineIndex];
					if (line->virtualLines.Count() == 0) return InlineObject();

					vint virtualLineIndex = GetVirtualLineIndexFromY(point.y, lineIndex);
					if (virtualLineIndex == -1) return InlineObject();

					return GetInlineObjectFromXWithLine(point.x, lineIndex, virtualLineIndex, start, length);
				}

				vint UniscribeParagraph::GetNearestCaretFromTextPos(vint textPos, bool frontSide)
				{
					if(!IsValidTextPos(textPos)) return -1;
					vint frontLine=0;
					vint backLine=0;
					GetLineIndexFromTextPos(textPos, frontLine, backLine);
					if(frontLine==-1 || backLine==-1) return -1;
					if(frontLine!=backLine)
					{
						return frontSide?textPos-1:textPos+1;
					}

					Ptr<UniscribeLine> line=lines[frontLine];
					if(textPos==line->startFromParagraph || textPos==line->startFromParagraph+line->lineText.Length())
					{
						return textPos;
					}


					vint frontItem=-1;
					vint backItem=-1;
					GetItemIndexFromTextPos(textPos, frontLine, frontItem, backItem);
					if(frontItem==-1 || backItem==-1) return -1;
					if(frontItem!=backItem) return textPos;

					Ptr<UniscribeItem> item=line->scriptItems[frontItem];
					vint lineTextPos=textPos-line->startFromParagraph;
					if(lineTextPos==item->startFromLine) return textPos;
					if(lineTextPos==item->startFromLine+item->length) return textPos;

					vint itemTextPos=lineTextPos-item->startFromLine;
					if(item->charLogattrs[itemTextPos].is_cursor_position) return textPos;

					if(frontSide)
					{
						for(vint i=itemTextPos-1;i>=0;i--)
						{
							if(item->charLogattrs[i].is_cursor_position) return i+line->startFromParagraph+item->startFromLine;
						}
						return line->startFromParagraph+item->startFromLine;
					}
					else
					{
						for(vint i=itemTextPos+1;i<item->length;i++)
						{
							if(item->charLogattrs[i].is_cursor_position) return i+line->startFromParagraph+item->startFromLine;
						}
						return line->startFromParagraph+item->startFromLine+item->length;
					}
				}

				bool UniscribeParagraph::IsValidCaret(vint caret)
				{
					if(!IsValidTextPos(caret)) return false;
					return GetNearestCaretFromTextPos(caret, true)==caret;
				}

				bool UniscribeParagraph::IsValidTextPos(vint textPos)
				{
					return 0<=textPos && textPos<=paragraphText.Length();
				}

				///

				class GGacParagraph : public Object, public IGuiGraphicsParagraph, public UniscribeRun::IRendererCallback
				{
				protected:
					IGuiGraphicsLayoutProvider*			provider;
					Ptr<UniscribeParagraph>				paragraph;
					WString								text;
					IGGacRenderTarget*					renderTarget;

					vint								caret;
					Color								caretColor;
					bool								caretFrontSide;
					//Ptr<WinPen>							caretPen;

					Cairo::RefPtr<Cairo::Context> 		paragraphCr;
					Point								paragraphOffset;
					IGuiGraphicsParagraphCallback*		paragraphCallback;

					void PrepareUniscribeData()
					{
						if(paragraph->BuildUniscribeData())
						{
							vint width=paragraph->lastAvailableWidth==-1?65536:paragraph->lastAvailableWidth;
							paragraph->Layout(width, paragraph->paragraphAlignment);
						}
					}

					Cairo::RefPtr<Cairo::Context> GetGGacContext()
					{
						return paragraphCr;
					}

					Point GetParagraphOffset()
					{
						return paragraphOffset;
					}

					IGuiGraphicsParagraphCallback* GetParagraphCallback()
					{
						return paragraphCallback;
					}
				public:
					GGacParagraph(IGuiGraphicsLayoutProvider* _provider, const WString& _text, IGuiGraphicsRenderTarget* _renderTarget, IGuiGraphicsParagraphCallback* _paragraphCallback)
					:provider(_provider)
					,text(_text)
					,renderTarget(dynamic_cast<IGGacRenderTarget*>(_renderTarget))
					,caret(-1)
					,caretFrontSide(false)
					,paragraphCr(nullptr)
					,paragraphCallback(_paragraphCallback)
					{
						paragraph=Ptr(new UniscribeParagraph);
						paragraph->paragraphText=text;

						Ptr<UniscribeFragment> fragment=Ptr(new UniscribeFragment(_text));
						fragment->fontStyle=GetCurrentController()->ResourceService()->GetDefaultFont();
						paragraph->documentFragments.Add(fragment);
					}

					~GGacParagraph()
					{
						CloseCaret();
					}

					IGuiGraphicsLayoutProvider* GetProvider()override
					{
						return provider;
					}

					IGuiGraphicsRenderTarget* GetRenderTarget()override
					{
						return renderTarget;
					}

					bool GetWrapLine()override
					{
						return true;
					}

					void SetWrapLine(bool value)override
					{
					}

					vint GetMaxWidth()override
					{
						return paragraph->lastAvailableWidth;
					}

					void SetMaxWidth(vint value)override
					{
						paragraph->BuildUniscribeData();
						paragraph->Layout(value, paragraph->paragraphAlignment);
					}

					Alignment GetParagraphAlignment()override
					{
						return paragraph->paragraphAlignment;
					}

					void SetParagraphAlignment(Alignment value)override
					{
						paragraph->BuildUniscribeData();
						paragraph->Layout(paragraph->lastAvailableWidth, value);
					}

					bool SetFont(vint start, vint length, const WString& value)override
					{
						if(length==0) return true;
						if(0<=start && start<text.Length() && length>=0 && 0<=start+length && start+length<=text.Length())
						{
							return paragraph->SetFont(start, length, value);
						}
						else
						{
							return false;
						}
					}

					bool SetSize(vint start, vint length, vint value)override
					{
						if(length==0) return true;
						if(0<=start && start<text.Length() && length>=0 && 0<=start+length && start+length<=text.Length())
						{
							return paragraph->SetSize(start, length, value);
						}
						else
						{
							return false;
						}
					}

					bool SetStyle(vint start, vint length, TextStyle value)override
					{
						if(length==0) return true;
						if(0<=start && start<text.Length() && length>=0 && 0<=start+length && start+length<=text.Length())
						{
							return paragraph->SetStyle(start, length, (value&Bold)!=0, (value&Italic)!=0, (value&Underline)!=0, (value&Strikeline)!=0);
						}
						else
						{
							return false;
						}
					}

					bool SetColor(vint start, vint length, Color value)override
					{
						if(length==0) return true;
						if(0<=start && start<text.Length() && length>=0 && 0<=start+length && start+length<=text.Length())
						{
							return paragraph->SetColor(start, length, value);
						}
						else
						{
							return false;
						}
					}

					bool SetBackgroundColor(vint start, vint length, Color value)override
					{
						if(length==0) return true;
						if(0<=start && start<text.Length() && length>=0 && 0<=start+length && start+length<=text.Length())
						{
							return paragraph->SetBackgroundColor(start, length, value);
						}
						else
						{
							return false;
						}
					}

					bool SetInlineObject(vint start, vint length, const InlineObjectProperties& properties)override
					{
						if(length==0) return true;
						if(0<=start && start<text.Length() && length>=0 && 0<=start+length && start+length<=text.Length())
						{
							if(paragraph->SetInlineObject(start, length, properties))
							{
								if (properties.backgroundImage)
								{
									IGuiGraphicsRenderer* renderer=properties.backgroundImage->GetRenderer();
									if(renderer)
									{
										renderer->SetRenderTarget(renderTarget);
									}
								}
								return true;
							}
						}
						return false;
					}

					bool ResetInlineObject(vint start, vint length)override
					{
						if(length==0) return true;
						if(0<=start && start<text.Length() && length>=0 && 0<=start+length && start+length<=text.Length())
						{
							if (auto inlineObject = paragraph->ResetInlineObject(start, length))
							{
								if (auto element = inlineObject.Value().backgroundImage)
								{
									auto renderer=element->GetRenderer();
									if(renderer)
									{
										renderer->SetRenderTarget(0);
									}
								}
								return true;
							}
						}
						return false;
					}

					vint GetHeight()override
					{
						PrepareUniscribeData();
						return paragraph->bounds.Height();
					}

					bool OpenCaret(vint _caret, Color _color, bool _frontSide)override
					{
						if(!IsValidCaret(_caret)) return false;
						if(caret!=-1) CloseCaret();
						caret=_caret;
						caretColor=_color;
						caretFrontSide=_frontSide;
						//caretPen=GetWindowsGDIResourceManager()->CreateGdiPen(caretColor);
						return true;
					}

					bool CloseCaret()override
					{
						if(caret==-1) return false;
						caret=-1;
						//GetWindowsGDIResourceManager()->DestroyGdiPen(caretColor);
						//caretPen=0;
						return true;
					}

					void Render(Rect bounds)override
					{
						PrepareUniscribeData();

						paragraphCr = renderTarget->GetGGacContext();
						paragraphOffset = bounds.LeftTop();
						paragraph->Render(this, true);
						paragraph->Render(this, false);

						if(caret!=-1)
						{
							Rect caretBounds=GetCaretBounds(caret, caretFrontSide);
							vint x=caretBounds.x1+bounds.x1;
							vint y1=caretBounds.y1+bounds.y1;
							vint y2=y1+(vint)(caretBounds.Height()*1.5);

							//dc->SetPen(caretPen);
							paragraphCr->set_source_rgba(caretColor.r / 255.f, caretColor.g / 255.f, caretColor.b / 255.f, caretColor.a / 255.f);
							paragraphCr->move_to(x-1, y1);
							paragraphCr->line_to(x-1, y2);
							paragraphCr->move_to(x, y1);
							paragraphCr->line_to(x, y2);
							paragraphCr->stroke();
						}
					}

					vint GetCaret(vint comparingCaret, CaretRelativePosition position, bool& preferFrontSide)override
					{
						PrepareUniscribeData();
						return paragraph->GetCaret(comparingCaret, position, preferFrontSide);
					}

					Rect GetCaretBounds(vint caret, bool frontSide)override
					{
						PrepareUniscribeData();
						return paragraph->GetCaretBounds(caret, frontSide);
					}

					vint GetCaretFromPoint(Point point)override
					{
						PrepareUniscribeData();
						return paragraph->GetCaretFromPoint(point);
					}

					Nullable<InlineObjectProperties> GetInlineObjectFromPoint(Point point, vint& start, vint& length)override
					{
						PrepareUniscribeData();
						return paragraph->GetInlineObjectFromPoint(point, start, length);
					}

					vint GetNearestCaretFromTextPos(vint textPos, bool frontSide)override
					{
						PrepareUniscribeData();
						return paragraph->GetNearestCaretFromTextPos(textPos, frontSide);
					}

					bool IsValidCaret(vint caret)override
					{
						PrepareUniscribeData();
						return paragraph->IsValidCaret(caret);
					}

					bool IsValidTextPos(vint textPos)override
					{
						PrepareUniscribeData();
						return paragraph->IsValidTextPos(textPos);
					}
				};

				///

				Ptr <IGuiGraphicsParagraph> GGacLayoutProvider::CreateParagraph(const WString &text, IGuiGraphicsRenderTarget *renderTarget, IGuiGraphicsParagraphCallback *callback)
				{
					return Ptr(new GGacParagraph(this, text, (IGGacRenderTarget*)renderTarget, callback));
				}

			}

		}

	}

}