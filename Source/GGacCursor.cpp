//
// Created by css on 1/19/23.
//

#include "GGacCursor.h"
#include <gtkmm.h>

namespace vl {

    namespace presentation {

        namespace gtk {

            GGacCursor::GGacCursor(Glib::RefPtr<Gdk::Cursor> _cursor)
                    :cursor(_cursor),
                     isSystemCursor(false),
                     systemCursorType(Arrow)
            {

            }

            GGacCursor::GGacCursor(SystemCursorType _type)
                    :cursor(NULL),
                     isSystemCursor(true),
                     systemCursorType(_type)
            {
            }

            GGacCursor::~GGacCursor() noexcept
            {
            }

            Glib::RefPtr<Gdk::Cursor> GGacCursor::GetCursor()
            {
                if (!cursor)
                {
                    Gdk::CursorType type = Gdk::CursorType::ARROW;
                    switch (systemCursorType)
                    {
                        case SizeAll:
                        case SizeNESW:
                        case SizeNWSE:
                        case SizeNS:
                        case SizeWE:
                            type = Gdk::CursorType::SIZING;
                    }
                    cursor = Gdk::Cursor::create(type);
                }
                return cursor;
            }

            bool GGacCursor::IsSystemCursor()
            {
                return isSystemCursor;
            }

            INativeCursor::SystemCursorType GGacCursor::GetSystemCursorType()
            {
                return systemCursorType;
            }
        }

    }

}
