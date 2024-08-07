//
// Created by roodkcab on 6/28/21.
//

#include "GuiColorizedTextElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				void GuiColorizedTextElementRenderer::OnElementStateChanged()
				{

				}

				void GuiColorizedTextElementRenderer::InitializeInternal()
				{
					gFont = 0;
					element->SetCallback(this);
				}

				void GuiColorizedTextElementRenderer::FinalizeInternal()
				{

				}

				void GuiColorizedTextElementRenderer::RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget)
				{
				}

				void GuiColorizedTextElementRenderer::Render(Rect bounds)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();

					if (renderTarget)
					{
						wchar_t passwordChar = element->GetPasswordChar();
						Point viewPosition = element->GetViewPosition();
						Rect viewBounds(viewPosition, bounds.GetSize());
						vint startRow = element->GetLines().GetTextPosFromPoint(Point(viewBounds.x1, viewBounds.y1)).row;
						vint endRow = element->GetLines().GetTextPosFromPoint(Point(viewBounds.x2, viewBounds.y2)).row;
						TextPos selectionBegin = element->GetCaretBegin() < element->GetCaretEnd() ? element->GetCaretBegin() : element->GetCaretEnd();
						TextPos selectionEnd = element->GetCaretBegin() > element->GetCaretEnd() ? element->GetCaretBegin() :element->GetCaretEnd();
						bool focused = element->GetFocused();

						//draw each line of text
						for (vint row = startRow; row <= endRow; row++)
						{
							Rect startRect = element->GetLines().GetRectFromTextPos(TextPos(row, 0));
							Point startPoint = startRect.LeftTop();
							vint startColumn = element->GetLines().GetTextPosFromPoint(Point(viewBounds.x1, startPoint.y)).column;
							vint endColumn = element->GetLines().GetTextPosFromPoint(Point(viewBounds.x2, startPoint.y)).column;
							text::TextLine& line = element->GetLines().GetLine(row);
							vint x = startColumn == 0 ? 0 : line.att[startColumn-1].rightOffset;
							vint sx = 0, sy = 0;

							//draw each column of text
							for (vint column = startColumn; column <= endColumn; column++)
							{
								bool inSelection = false;
								if (selectionBegin.row == selectionEnd.row)
								{
									inSelection = (row == selectionBegin.row && selectionBegin.column <= column && column < selectionEnd.column);
								}
								else if (row == selectionBegin.row)
								{
									inSelection = selectionBegin.column <= column;
								}
								else if (row == selectionEnd.row)
								{
									inSelection = column<selectionEnd.column;
								}
								else
								{
									inSelection = selectionBegin.row < row && row < selectionEnd.row;
								}

								bool crlf = (column == line.dataLength);
								vint colorIndex = crlf ? 0 : line.att[column].colorIndex;
								if (colorIndex >= colors.Count())
								{
									colorIndex = 0;
								}
								ColorItemResource& color = !inSelection ? colors[colorIndex].normal : (focused ? colors[colorIndex].selectedFocused : colors[colorIndex].selectedUnfocused);

								vint x2 = crlf ? x + startRect.Height() / 2 : line.att[column].rightOffset;
								vint tx = x - viewPosition.x + bounds.x1;
								vint ty = startPoint.y - viewPosition.y + bounds.y1;

								if (color.background.a > 0)
								{
									Color c = color.background;
									cr->set_source_rgba(c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f);
									cr->rectangle(tx, ty + 2, (x2 - x), startRect.Height() + 2);
									cr->fill();
								}

								if (!crlf)
								{
									if (column == startColumn)
									{
										sx = tx;
										sy = ty;
									}
									if (column == endColumn - 1)
									{
										cr->move_to(sx, sy);
										if (color.text.a > 0)
										{
											Color c = color.text;
											cr->set_source_rgba(c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f);
										}
                                        auto layout = Pango::Layout::create(cr);
                                        layout->set_font_description(*gFont.Obj());
                                        layout->set_auto_dir(false);
										if (passwordChar)
										{
											WString text = L"";
											for (vint i = 0; i < endColumn - startColumn; i++) { text += WString::FromChar(passwordChar); }
											layout->set_text(Glib::ustring::format(text.Buffer()));
										}
										else
										{
											layout->set_text(Glib::ustring::format(WString(line.text).Sub(startColumn, endColumn - startColumn).Buffer()));
										}
                                        layout->show_in_cairo_context(cr);
                                        cr->move_to(tx, ty);
                                    }
								}
                                x = x2;
                            }

                        }

                        //draw caret
                        if (element->GetCaretVisible() && element->GetLines().IsAvailable(element->GetCaretEnd()))
						{
							Point caretPoint = element->GetLines().GetPointFromTextPos(element->GetCaretEnd());
							vint height = element->GetLines().GetRowHeight();
							Point p1(caretPoint.x - viewPosition.x + bounds.x1,
									 caretPoint.y - viewPosition.y + bounds.y1 + 2);

							Point p2(caretPoint.x - viewPosition.x + bounds.x1,
									 caretPoint.y - viewPosition.y + bounds.y1 + 2 + height);

							Color c = element->GetCaretColor();
							cr->set_source_rgba(c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f);
							cr->set_line_width(2.f);
							cr->move_to(p1.x, p1.y);
							cr->line_to(p2.x, p2.y);
							cr->stroke();
						}
					}
				}

				void GuiColorizedTextElementRenderer::FontChanged()
				{
					IGGacResourceManager* rm = GetGGacResourceManager();
					auto oldFont = element->GetFont();
					gFont = rm->CreateGGacFont(oldFont);
					element->GetLines().SetCharMeasurer(rm->CreateCharMeasurer(oldFont).Obj());
				}

				void GuiColorizedTextElementRenderer::ColorChanged()
				{
					colors.Resize(element->GetColors().Count());
					for(vint i = 0; i < colors.Count(); i++)
					{
						text::ColorEntry entry=element->GetColors().Get(i);
						ColorEntryResource newEntry;

						newEntry.normal.text=entry.normal.text;
						newEntry.normal.background=entry.normal.background;

						newEntry.selectedFocused.text=entry.selectedFocused.text;
						newEntry.selectedFocused.background=entry.selectedFocused.background;

						newEntry.selectedUnfocused.text=entry.selectedUnfocused.text;
						newEntry.selectedUnfocused.background=entry.selectedUnfocused.background;

						colors[i] = newEntry;
					}
				}

			}

		}

	}

}