// comp.c


// window server routines.
#include <gws.h>

// #todo
// Create some configuration globals here
// int gUseSomething = TRUE;
// ...


// Flush
// The compositor.
// Called by wmCompose
void compose(void)
{
    int Dirty = FALSE;

// Dirty background.
// Check the background validation.
// The background is dirty.
// Show the whole screen.
// #todo: update fps
// Yes. The whole background is dirty.
// Refresh it and validate the background.

    Dirty = (int) is_background_dirty();

    if (Dirty == TRUE)
    {
        gws_show_backbuffer();
        validate_background();  
        return;
    }

//
// Rectangles.
//

// Refresh the rectangles of the windows.
    wmRefreshDirtyRectangles();

//flush all the screens?
//Do we have more than one monitor?
    //for( ...
    //gws_show_backbuffer();

// #todo
// call a helper function for that.

    //__update_fps();

// Validate the frame.
    validate();
}

