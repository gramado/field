/*
 * rect.c 
 *     Rectangle support for gws.
 */


#include <gws.h>


/*
void invalidate_rectangle( struct gws_rect_d *rect );
void invalidate_rectangle( struct gws_rect_d *rect )
{
    if ( (void*) rect == NULL ){
        return FALSE;
    }
    rect->dirty = TRUE;
}
*/


/*
int
rect_intersect(
    struct gws_rect_d *r1, 
    struct gws_rect_d *r2 );
int
rect_intersect(
    struct gws_rect_d *r1, 
    struct gws_rect_d *r2 )
{

    if ( (void *) r1 == NULL ){ return FALSE; }
    if ( (void *) r2 == NULL ){ return FALSE; }

    if ( (r1->left   < r2->right)  &&
         (r1->top    < r2->bottom) &&
         (r1->right  > r2->left)   &&
         (r1->bottom > r2->top) )
    {
        return TRUE;
    }
    return FALSE;
}
*/


int
set_rect ( 
    struct gws_rect_d *rect, 
    unsigned long left, 
    unsigned long top,
    unsigned long width,
    unsigned long height )
{
    if ( (void*) rect == NULL )
    {
        return FALSE;
    }
    
    rect->left   = left;
    rect->top    = top;
    rect->width  = width;
    rect->height = height;

    // #text
    // rect->is_empty = TRUE;

    return TRUE;
}


// See: window.h
void 
inflate_rect ( 
    struct gws_rect_d *rect, 
    unsigned long cx, 
    unsigned long cy )
{
    if ( (void*) rect == NULL ){
        return;
    }
    
    rect->left   -= cx;
    rect->top    -= cy;
    rect->right  += cx;
    rect->bottom += cy;

    rect->width  = (rect->right  - rect->left);
    rect->height = (rect->bottom - rect->top);
}


// #todo: Explain
void 
copy_inflate_rect ( 
    struct gws_rect_d *rectDest, 
    struct gws_rect_d *rectSrc, 
    unsigned long cx, 
    unsigned long cy )
{
    if ( (void*) rectDest == NULL ){
        return;
    }

    if ( (void*) rectSrc == NULL ){
        return;
    }


    // inflate and copy.
    // todo: fazer isso em duas etapas.
    rectDest->left   = rectSrc->left   -= cx;
    rectDest->top    = rectSrc->top    -= cy;
    rectDest->right  = rectSrc->right  += cx;
    rectDest->bottom = rectSrc->bottom += cy;

    //update width and height
    rectSrc->width   = (rectSrc->right   - rectSrc->left);
    rectSrc->height  = (rectSrc->bottom  - rectSrc->top);
    rectDest->width  = (rectDest->right  - rectDest->left);
    rectDest->height = (rectDest->bottom - rectDest->top);
}


// ??
// #todo: Comment what is happening here.
// Move
void 
offset_rect ( 
    struct gws_rect_d *rect, 
    unsigned long cx, 
    unsigned long cy )
{
    if ( (void*) rect == NULL ){
        return;
    }
    
    //offset rect
    rect->left   += cx;
    rect->top    += cy;
    rect->right  += cx;
    rect->bottom += cy;

    //update width and height
    rect->width  = (rect->right  - rect->left);
    rect->height = (rect->bottom - rect->top);
}

// ??
// #todo: Comment what is happening here.
void 
copy_offset_rect ( 
    struct gws_rect_d *rectDest, 
    struct gws_rect_d *rectSrc, 
    unsigned long cx, 
    unsigned long cy )
{
    if ( (void*) rectDest == NULL ){
        return;
    }

    if ( (void*) rectSrc == NULL ){
        return;
    }

    // offset and copy the rect.
    rectDest->left   = rectSrc->left   += cx;
    rectDest->top    = rectSrc->top    += cy;
    rectDest->right  = rectSrc->right  += cx;
    rectDest->bottom = rectSrc->bottom += cy;

    //update width and height,
    rectSrc->width   = (rectSrc->right  - rectSrc->left);
    rectSrc->height  = (rectSrc->bottom - rectSrc->top);
    rectDest->width  = (rectDest->right  - rectDest->left);
    rectDest->height = (rectDest->bottom - rectDest->top);
}


// ??
// #todo: Comment what is happening here.
// Checando alguma falha nos valores.
// Devemos ajustar quando falhar?
// Talvez o termo empty nao seja o apropriado aqui,
// pois empty pode significar apenas nao pintado. not fill.
int rect_validate_size( struct gws_rect_d *rect )
{
    if ( (void*) rect == NULL ){
        return -1;
    }

    if ((rect->left >= rect->right) || 
        (rect->top  >= rect->bottom))
    {
        return FALSE;
    }

    return TRUE;
}

int rect_validate_size2( struct gws_rect_d *rect )
{
    if ( (void*) rect == NULL ){
        return -1;
    }

    if ( (rect->width  <= 0 ) || 
         (rect->height <= 0 ) )
    {
        return FALSE;
    }
     
    return TRUE;
}

int is_rect_null( struct gws_rect_d *rect )
{
    if ( (void*) rect == NULL ){
        return -1;
    }
    
    if (rect->width == 0 && rect->height == 0 )
    {
        return TRUE;
    }
    
    return FALSE;
}



int is_rect_empty( struct gws_rect_d *rect )
{
    if ( (void*) rect == NULL ){
        return -1;
    }

    if (rect->is_empty == TRUE)
    {
        return (int) TRUE;
    }
 
    rect->is_empty = FALSE;
    return FALSE;
}


// ??
// #todo: Comment what is happening here.
int is_rect_dirty( struct gws_rect_d *rect )
{
    // Error!
    if ( (void*) rect == NULL ){
        return -1;
    }

    // true
    if ( rect->dirty == TRUE  ){
        return (int) TRUE;
    }
    
    //false
    return FALSE;
}


int 
rect_contains_vertically ( 
    struct gws_rect_d *rect,  
    unsigned long y ) 
{
    if ( (void*) rect == NULL ){
        return -1;
    }

    // ta dentro
    if ( y >= rect->top &&
         y <= rect->bottom )
    {
        return TRUE;
    }

    // ta fora
    return FALSE;
}


int 
rect_contains_horizontally ( 
    struct gws_rect_d *rect,
    unsigned long x )
{
    if ( (void*) rect == NULL ){
        return -1;
    }
    
    // ta dentro
    if ( x >= rect->left &&
         x <= rect->right )
    {
        return TRUE;
    }

    // ta fora
    return FALSE;
}


void 
rect_set_left ( 
    struct gws_rect_d *rect, 
    unsigned long value )
{
    if ( (void*) rect == NULL ){
        return;
    }
    
    rect->left = value;
}

void 
rect_set_top ( 
    struct gws_rect_d *rect, 
    unsigned long value )
{
    if ( (void*) rect == NULL ){
        return;
    }
    
    rect->top = value;
}

void 
rect_set_right ( 
    struct gws_rect_d *rect, 
    unsigned long value )
{
    if ( (void*) rect == NULL ){
        return;
    }
    
    rect->right = value;
}

void 
rect_set_bottom ( 
    struct gws_rect_d *rect, 
    unsigned long value )
{
    if ( (void*) rect == NULL ){
        return;
    }
    
    rect->bottom = value;
}

// #todo
// Do not check the validation.
// We need a prefix that tellus that we will no chack the validation
// os the addresses

void *rect_memcpy32 ( 
    void *v_dst, 
    const void *v_src, 
    unsigned long c )
{

    // Copiaremos 32bit por vez.

    unsigned int *src = (unsigned int *) v_src;
    unsigned int *dst = (unsigned int *) v_dst;

    register unsigned long Copy = c;

	//const char *src = v_src;
	//char *dst = v_dst;


    /* Simple, byte oriented memcpy. */
    while (Copy--)
    {
        *dst++ = *src++;
    };

    return (void *) v_dst;
}


// Flush the rectangle into the framebuffer.
// Here we are flushing the content of a given
// dirty retangle into the frame buffer.
// We are using a flag to guide us if we realy need to refresh 
// the given rectangle.

int gwssrv_refresh_this_rect ( struct gws_rect_d *rect )
{

// validations

    if ( (void*) rect == NULL ){ 
        return -1; 
    }
    
    if ( rect->dirty != TRUE  ){ 
        return -1; 
    }

// refresh
    gws_refresh_rectangle ( 
        rect->left, rect->top, rect->width, rect->height );

// Validate
    rect->dirty = FALSE;

    return 0;
}


// Flush the rectangle into the framebuffer.
int flush_rectangle(struct gws_rect_d *rect)
{
    return (int) gwssrv_refresh_this_rect(rect);
}


//======================================
// Calling kgws in the kernel.
// Using the kgws to draw the rectangle.

// #todo
// At this moment, no structure ware invalidated.
// So, the caller needs to specify a rect structure,
// this way we can invalidated it.

void 
draw_rectangle_via_kgws ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height,
    unsigned int color,
    unsigned long rop_flags )
{
    unsigned long Buffer[6];

// Set parameters.
    Buffer[0] = (unsigned long) x;
    Buffer[1] = (unsigned long) y;
    Buffer[2] = (unsigned long) (width  & 0xFFFF);
    Buffer[3] = (unsigned long) (height & 0xFFFF);
    Buffer[4] = (unsigned long) (color & 0xFFFFFFFF);
    Buffer[5] = (unsigned long) rop_flags;

// Refresh rectangle using the kernel service number 9.
    gramado_system_call ( 
        9, (unsigned long) &Buffer[0], 0, 0 );
}


// atualiza o retângulo da surface da thread.
void 
setup_surface_retangle ( 
    unsigned long left, 
    unsigned long top, 
    unsigned long width, 
    unsigned long height )
{
    unsigned long Buffer[5];
    
    Buffer[0] = (unsigned long) left;
    Buffer[1] = (unsigned long) top;
    Buffer[2] = (unsigned long) (width  & 0xFFFF);
    Buffer[3] = (unsigned long) (height & 0xFFFF);
    Buffer[4] = 0; 

    gramado_system_call ( 
        892, (unsigned long) &Buffer[0], 0, 0 );
}


void invalidate_surface_retangle (void)
{
    gramado_system_call ( 893, 0, 0, 0 );
}


//======================================
// Calling kgws in the kernel.
// Using the kgws to refresh the rectangle.

void 
refresh_rectangle_via_kgws ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height )
{
    unsigned long Buffer[5];
    
    Buffer[0] = (unsigned long) x;
    Buffer[1] = (unsigned long) y;
    Buffer[2] = (unsigned long) (width  & 0xFFFF);
    Buffer[3] = (unsigned long) (height & 0xFFFF);
    Buffer[4] = 0; 

    gramado_system_call ( 
        10, (unsigned long) &Buffer[0], 0, 0 );
}


/*
 *************************************************** 
 * gws_refresh_rectangle:
 * 
 */

// From backbuffer to frontbuffer.

void 
gws_refresh_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height )
{

//
// flag
//

// #todo
// Maybe we can include this flag into the
// function's parameters.

    //int RefreshRectangleUsingKGWS = FALSE;
    int RefreshRectangleUsingKGWS = TRUE;

// #todo
// Maybe we can include the 'source pointer' into the
// function's parameters.

    void       *dest = (void *)      ____FRONTBUFFER_VA;
    const void *src  = (const void*) ____BACKBUFFER_VA;

    //loop?
    register unsigned int i=0;
    register int count=0; 
    register unsigned int lines=0;      // quantas linhas.
    unsigned int line_size=0;  // rectangle line size in pixels.

    // screen line size in pixels * bytes per pixel.
    unsigned int pitch=0;  
    // rectangle line size in pixels * bytes per pixel.
    register unsigned int rectangle_pitch=0;  //loop

    unsigned int offset=0;


// 4 = 32bpp
// 3 = 24bpp
    int bytes_count=0;


    debug_print("gws_refresh_rectangle: :)\n");


    unsigned long X = (unsigned long) (x & 0xFFFF);
    unsigned long Y = (unsigned long) (y & 0xFFFF);
    unsigned long Width  = (unsigned long) (width  & 0xFFFF);
    unsigned long Height = (unsigned long) (height & 0xFFFF);


//
// Refresh in the kernel using the kgws.
//

    if ( RefreshRectangleUsingKGWS == TRUE )
    {
        debug_print("gws_refresh_rectangle: Using R0\n");
        refresh_rectangle_via_kgws(X,Y,Width,Height);
        return;
    }


//
// Refresh using the routine inside the ws.
//

// ==========================================================

    debug_print("gws_refresh_rectangle: Using R3\n");

    // Device info.
    unsigned long ScreenWidth  = (unsigned long) gws_get_device_width();
    unsigned long ScreenHeight = (unsigned long) gws_get_device_height();


    if ( ScreenWidth == 0 )
    {
        debug_print("gws_refresh_rectangle: [ERROR] ScreenWidth\n");
        printf     ("gws_refresh_rectangle: [ERROR] ScreenWidth\n");  
        exit(1);
    }

    if ( ScreenHeight == 0 )
    {
        debug_print("gws_refresh_rectangle: [ERROR] ScreenHeight\n");
        printf     ("gws_refresh_rectangle: [ERROR] ScreenHeight\n");  
        exit(1);
    }

    ScreenWidth  = (ScreenWidth  & 0xFFFF );
    ScreenHeight = (ScreenHeight & 0xFFFF );


//
// Internal
//

    line_size = (unsigned int) (width  & 0xFFFF); 
    lines     = (unsigned int) (height & 0xFFFF);

// #test
// Não podemos fazer refresh fora da tela.
// Não por enquanto. 
// precisamos conhecer melhor nossos limites.

    if ( Y >= ScreenHeight )
    {
        debug_print("gws_refresh_rectangle: [ERROR]  Y > ScreenHeight\n");
        return;
        //printf     ("gws_refresh_rectangle: [ERROR]  Y > ScreenHeight\n");  
        //exit(1);
    }

    if ( lines > (ScreenHeight-Y) )
    {
        debug_print("gws_refresh_rectangle: [ERROR] lines\n");
        return;
        //printf     ("gws_refresh_rectangle: [ERROR] lines\n");  
        //exit(1);
    }


    switch (SavedBPP){
        case 32:  bytes_count = 4;  break;
        case 24:  bytes_count = 3;  break;
        // ... #todo
        default:
            debug_print ("gws_refresh_rectangle: [ERROR] SavedBPP\n");  
            printf      ("gws_refresh_rectangle: [ERROR] SavedBPP\n");  
            exit(1);
            break;
    };

//
// pitch - (largura da tela em bytes)
//

    // screen line size in pixels * bytes per pixel.
    pitch = (unsigned int) (bytes_count * ScreenWidth);

//
// rectangle_pitch - (largura do retângulo em bytes)
//

    // rectangle line size in pixels * bytes per pixel.
    rectangle_pitch = (unsigned int) (bytes_count * line_size);

// #atenção.
    //offset = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );

// 32bpp
    if(bytes_count==4)
        offset = (unsigned int) ( (Y*pitch) + (X<<2) );

// 24bpp
    if(bytes_count==3)
        offset = (unsigned int) ( (Y*pitch) + (bytes_count*X) );

    
    dest = (void *)       (dest + offset);    
    src  = (const void *) (src  + offset);    


	// #bugbug
	// Isso pode nos dar problemas.
	// ?? Isso ainda é necessário nos dias de hoje ??
	
	//vsync ();	
		
	//(line_size * bytes_count) é o número de bytes por linha. 

	//#importante
	//É bem mais rápido com múltiplos de 4.	


    
    // Se for divisível por 4.
    // Copia uma linha ou um pouco mais caso não seja divisível por 4.
    if ( (rectangle_pitch % 4) == 0 )
    {
        debug_print("gws_refresh_rectangle: [1]\n");
    
        count = (rectangle_pitch / 4); 

        for ( i=0; i < lines; i++ ){
            rect_memcpy32 ( (void *) dest, (const void *) src, count );
            dest += pitch;
            src  += pitch;
        };
        
        /* doom style.
        i=0;
        do{
            rect_memcpy32 ( (void *) dest, (const void *) src, count );
            dest += pitch;
            src  += pitch;
            i++;
        }while(i<lines);
        */
    }

    // Se não for divisível por 4.
    if ( (rectangle_pitch % 4) != 0 )
    {
        debug_print("gws_refresh_rectangle: [2]\n");
        
        for ( i=0; i < lines; i++ ){
             memcpy ( (void *) dest, (const void *) src, rectangle_pitch );
             dest += pitch;
             src  += pitch;
        };
        
        /* doom style
        i=0;
        do{
            memcpy ( (void *) dest, (const void *) src, rectangle_pitch );
            dest += pitch;
            src  += pitch;
            i++;
        }while(i<lines);
        */
    }

    debug_print("gws_refresh_rectangle: done :)\n");
}


/*
 *******************************************************
 * rectBackbufferDrawRectangle: (API)
 *     Draw a rectangle on backbuffer. 
 */

// #todo
// At this moment, no structure ware invalidated.
// So, the caller needs to specify a rect structure,
// this way we can invalidated it.

// use_kgws?
// TRUE = use kgws.
// FALSE = do not use kgws. #bugbug

void 
rectBackbufferDrawRectangle0 ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned int color,
    int fill,
    unsigned long rop_flags,
    int use_kgws )
{

//
// flag
//

// The rectangle can be painted by the kgws inside the base kernel.
// #todo
// Let's include this flag into the function's parameters.
// #bugbug
// The ws routine is not working everytime we call it.

    //int DrawRectangleUsingKGWS = FALSE;  // #bugbug
    //int DrawRectangleUsingKGWS = TRUE;     // ok
    int DrawRectangleUsingKGWS = use_kgws;

    debug_print("rectBackbufferDrawRectangle0:\n");

    struct gws_rect_d rect;
    
//
// device
//

    unsigned long device_w = (unsigned long) gws_get_device_width();
    unsigned long device_h = (unsigned long) gws_get_device_height();
    device_w = (unsigned long) (device_w & 0xFFFF);
    device_h = (unsigned long) (device_h & 0xFFFF);
// #provisório
// limites do dispositivo
    if(device_w > 800)
    {
        debug_print("rectBackbufferDrawRectangle0: [FAIL] device_w\n");
        return; 
    }
    if(device_h > 600)
    {
        debug_print("rectBackbufferDrawRectangle0: [FAIL] device_h\n");
        return; 
    }


// set values

    rect.left   =  (unsigned long) (x      & 0xFFFF);
    rect.top    =  (unsigned long) (y      & 0xFFFF);
    rect.width  =  (unsigned long) (width  & 0xFFFF);
    rect.height =  (unsigned long) (height & 0xFFFF);

//Margins.
    rect.right  = (unsigned long) (rect.left + rect.width);
    rect.bottom = (unsigned long) (rect.top  + rect.height); 

    rect.bg_color = (unsigned int)(color & 0xFFFFFF);


//
// Fail
//

// #bugbug
// O início não pode ser depois do fim.

    if ( rect.left > rect.right )
    { 
        debug_print("rectBackbufferDrawRectangle0: [FAIL] left > right\n");
        
        //#debug
        printf ("rectBackbufferDrawRectangle0: l:%d r:%d\n",
            rect.left,rect.right);
        exit(0);

        return; 
    }
    if ( rect.top > rect.bottom )
    { 
        debug_print("rectBackbufferDrawRectangle0: [FAIL] top  > bottom\n");

        //#debug
        printf ("rectBackbufferDrawRectangle0: t:%d b:%d\n",
            rect.top,rect.bottom);
        exit(0);

        return; 
    }


// Clip

    // se a largura for maior que largura do dispositivo.
    if ( rect.width > device_w ){
        rect.width = (unsigned long) device_w;
        debug_print("rectBackbufferDrawRectangle0: [FAIL] rect.width > device_w\n");
        return;
    }
    
    // se a altura for maior que altura do dispositivo.
    if ( rect.height > device_h ){
        rect.height = (unsigned long) device_h;
        debug_print("rectBackbufferDrawRectangle0: [FAIL] rect.height > device_h\n");
        return;
    }


// limits
// Se for maior que o espaço que sobre, 
// então será igual ao espaço que sobra.

    if ( rect.width > (device_w - rect.left) )
    {
        rect.width = (unsigned long) (device_w - rect.left);
        debug_print("rectBackbufferDrawRectangle0: [AJUST] rect.width\n");
    }
    
    if (rect.height > (device_h - rect.top) )
    {
        rect.height = (unsigned long) (device_h - rect.top);
        debug_print("rectBackbufferDrawRectangle0: [AJUST] rect.height\n");
    }



// check
    if ( rect.right > device_w )
    {
        debug_print("rectBackbufferDrawRectangle0: [FAIL] rect.right > device_w\n");
        return;
    }
    if ( rect.bottom > device_h )
    {
        debug_print("rectBackbufferDrawRectangle0: [FAIL] rect.bottom > device_h\n");
        return;
    }


//
// empty
//

    if ( fill == FALSE ){
        rect.is_empty = TRUE;
    }


    /*

    // #todo
    // Desenhar as bordas com linhas
    // ou com retangulos
   
    if (fill==0)
    {
            //  ____
            // |
            //
            
            //board1, borda de cima e esquerda.
            rectBackbufferDrawRectangle ( 
                window->left, window->top,
                window->width, 1, 
                color, 1 );
            rectBackbufferDrawRectangle ( 
                window->left, window->top, 
                1, window->height,
                color, 1 );

            //  
            //  ____|
            //

            //board2, borda direita e baixo.
            rectBackbufferDrawRectangle ( 
                 ((window->left) + (window->width) -1), window->top, 
                 1, window->height, 
                 color, 1 );
            rectBackbufferDrawRectangle ( 
                 window->left, ( (window->top) + (window->height) -1 ),  
                 window->width, 1, 
                 color, 1 );
          
        return;
    }
    */


//
// fill
//
    
    if ( fill == TRUE ){
        rect.is_empty = FALSE;
    }


//
// Draw
//

// Drawing in the kernel using kgws.
// Draw lines on backbuffer.
// Invalidate the rectangle.

    if ( DrawRectangleUsingKGWS == TRUE )
    {
         debug_print("rectBackbufferDrawRectangle0: Using R0\n");
         draw_rectangle_via_kgws (
             rect.left, rect.top, rect.width, rect.height,
             rect.bg_color,
             rop_flags );
         rect.dirty = TRUE;
         return;
    }

//===============================================================

//
// Drawing
// Using the routine inside the ws.
//

    // ws routine is not working.
    //if(DrawRectangleUsingKGWS == FALSE)
        //debug_print("rectBackbufferDrawRectangle:\n");

    debug_print("rectBackbufferDrawRectangle0: Using R3 #bugbug\n");


/*
// Clip
    if ( rect.width > device_w )
        rect.width = (unsigned long) device_w;

    if ( rect.height > device_h )
        rect.height = (unsigned long) device_h;
*/

/*
// Fail
    if ( rect.left > rect.width  )
    { 
        debug_print("rectBackbufferDrawRectangle0: [FAIL] rect.left > rect.width\n");
        return; 
    }
    if ( rect.top  > rect.height )
    { 
        debug_print("rectBackbufferDrawRectangle0: [FAIL] rect.top  > rect.height\n");
        return; 
    }
*/

    //#debug
    //printf ("w=%d h=%d l=%d t=%d \n",
        //rect.width, rect.height, rect.left, rect.top );
    //exit(1);
    //asm ("int $3");

// ===============================
// Draw lines on backbuffer.
// It's using the ws routine.

    unsigned long number_of_lines=0;
    number_of_lines = (unsigned long) rect.height;

    while (number_of_lines--)
    {
        
        if (rect.top >= rect.bottom){ break; }
        if (rect.top >= device_h)   { break; }
        
        grBackbufferDrawHorizontalLine ( 
            rect.left, rect.top, rect.right, 
            (unsigned int) rect.bg_color );
        
        rect.top++;
    };

//done:
// Invalidate rectangle.
    rect.dirty = TRUE;
    debug_print("rectBackbufferDrawRectangle0: done\n");
}


void 
rectBackbufferDrawRectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned int color,
    int fill,
    unsigned long rop_flags )
{

// TRUE = use kgws.
// FALSE = do not use kgws. #bugbug

    // ok: It's working
    rectBackbufferDrawRectangle0(
        x,
        y,
        width,
        height,
        color,
        fill,
        rop_flags,
        TRUE );   // TRUE = use kgws. (kernel service)

    /*
    // ok: It's working
    rectBackbufferDrawRectangle0(
        x,
        y,
        width,
        height,
        color,
        fill,
        rop_flags,
        FALSE );   // FALSE = do not use kgws. (kernel service)
    */
}


// #todo
// The structure needs to have all the information
// we need to redraw the given rectangle.
// # not tested yet.
int update_rectangle( struct gws_rect_d *rect )
{

    unsigned long left=0;    // left
    unsigned long top=0;     // top
    unsigned long width=0;   // width
    unsigned long height=0;  // height
    unsigned int color=0;    // color

// validations

    if ( (void*) rect == NULL )
        return -1;

    if (rect->used != TRUE)
        return -1;

    if (rect->magic != 1234)
        return -1;


// Values

    left   = (unsigned long) (rect->left   & 0xFFFF); 
    top    = (unsigned long) (rect->top    & 0xFFFF); 
    width  = (unsigned long) (rect->width  & 0xFFFF); 
    height = (unsigned long) (rect->height & 0xFFFF); 
    color  = (unsigned int)  (rect->bg_color & 0xFFFFFFFF); 

//
// Paint it into the backbuffer.
//

// no return
    rectBackbufferDrawRectangle ( 
        (unsigned long) left,     // left
        (unsigned long) top,      // top
        (unsigned long) width,    // width
        (unsigned long) height,   // height
        (unsigned int) color,     // color
        (int) TRUE,               // fill it?
        (unsigned long) 0 );      // rop_flags


    rect->dirty = TRUE;

    return 0;
}


//
// End
//

