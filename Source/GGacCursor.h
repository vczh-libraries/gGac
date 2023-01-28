//
// Created by roodkcab on 1/19/23.
//

#ifndef GGAC_GGACCURSOR_H
#define GGAC_GGACCURSOR_H

#include "GacUI.h"
#include <gtkmm.h>

namespace vl {

    namespace presentation {

        namespace gtk {

            class GGacCursor : public vl::presentation::INativeCursor {
            protected:
                Glib::RefPtr<Gdk::Cursor> cursor;
                bool isSystemCursor;
                SystemCursorType systemCursorType;
            public:
                GGacCursor(Glib::RefPtr<Gdk::Cursor> _cursor);

                GGacCursor(SystemCursorType _type);

                ~GGacCursor();

                bool IsSystemCursor() override;

                SystemCursorType GetSystemCursorType() override;

                Glib::RefPtr<Gdk::Cursor> GetCursor();
            };

        }
    }
}



#endif //GGAC_GGACCURSOR_H
