// comp.c


// window server routines.
#include <gws.h>

// #todo
// Create some configuration globals here
// int gUseSomething = TRUE;
// ...


static long __old_mouse_x=0;
static long __old_mouse_y=0;
static long __new_mouse_x=0;
static long __new_mouse_y=0;


// + Apaga o cursor antigo, copiando o conteudo do backbuffer
// + Pinta o novo cursor diretamente no lfb.
void __display_mouse_cursor(void)
{

//------
//#dangerdanger
//#todo: show the backbuffer
// APAGA
    gws_refresh_rectangle( 
        __old_mouse_x, 
        __old_mouse_y,
        8,
        8 );

// save
    __old_mouse_x = __new_mouse_x;
    __old_mouse_y = __new_mouse_y;

// #todo: 
// print directly into the lfb.
// DRAW
    frontbuffer_draw_rectangle( 
        __new_mouse_x, 
        __new_mouse_y, 
        8, 
        8, 
        COLOR_YELLOW, 
        0 );


//------        
}

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
        __display_mouse_cursor();
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


// mouse
    __display_mouse_cursor();

// Validate the frame.
    validate();
}


void comp_set_mouse_position(long x, long y)
{
    __new_mouse_x=x;
    __new_mouse_y=y;
}







