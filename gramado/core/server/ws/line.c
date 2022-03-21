/*
 * File: line.c 
 * 
 */


#include <gws.h>


//#bugbug: use ul for 'color'.
void 
plotLineRect4 ( 
    int x1, int y1, 
    int x2, int y2, 
    int color )
{
    plotLine3d ( x1,y1,0, x2,y1,0, color );
    plotLine3d ( x2,y1,0, x2,y2,0, color );
    plotLine3d ( x2,y2,0, x1,y2,0, color );
    plotLine3d ( x1,y2,0, x1,y1,0, color );
}


//#bugbug: use ul for 'color'.
void 
plotLineRectZ ( 
    int x1, int y1, int z1, 
    int x2, int y2, int z2, 
    int color )
{
    plotLine3d ( x1,y1,z1, x2,y1,z2, color );
    plotLine3d ( x2,y1,z1, x2,y2,z2, color );
    plotLine3d ( x2,y2,z1, x1,y2,z2, color );
    plotLine3d ( x1,y2,z1, x1,y1,z2, color );
}

//#bugbug: use ul for 'color'.
//ok triangulo invertido.
void 
testLines ( 
    int x1, int y1, 
    int x2, int y2, 
    int color )
{
   int dx = x2-x1;
   int dy = y2-y1;
     
  plotLine3d(   x1,  y1-dy, 0,   x1+dx, y1   , 0, color);
  plotLine3d(x1+dx,     y1, 0,     x1, y1+dy , 0, color);
  plotLine3d(   x1,  y1+dy, 0,  x1-dx, y1    , 0, color);
  plotLine3d(x1-dx,     y1, 0,     x1, y1-dy , 0, color);
}


//#bugbug: use ul for 'color'.
//ok triangulo invertido.
void 
testLinesZ ( 
    int x1, int y1, int z1, 
    int x2, int y2, int z2, 
    int color )
{
    int dx = (x2-x1);
    int dy = (y2-y1);

    plotLine3d (   x1,  y1-dy, z1,   x1+dx, y1   , z2, color);
    plotLine3d (x1+dx,     y1, z1,     x1, y1+dy , z2, color);
    plotLine3d (   x1,  y1+dy, z1,  x1-dx, y1    , z2, color);
    plotLine3d (x1-dx,     y1, z1,     x1, y1-dy , z2, color);
}



// ...
//dx = x2 − x1
//dy = y2 − y1
//for x from x1 to x2 do
//    y = y1 + dy × (x − x1) / dx
//    plot(x, y)
// See: https://en.wikipedia.org/wiki/Line_drawing_algorithm

void
A_naive_line_drawing_algorithm(
    unsigned long x1,
    unsigned long x2, 
    unsigned long y1, 
    unsigned long y2, 
    unsigned long color)
{

    //loop
    register unsigned long x=0;
    register unsigned long y=0;

    unsigned long dx =  (x2 - x1);
    unsigned long dy =  (y2 - y1);

    for ( x = x1; x < x2; x++ )
    {
         // ugly
         y = (y1 + dy * (x - x1) / dx);
         
         grBackBufferPutpixel(color,x,y);
    }; 
}


//test1
void test_draw_line(void)
{
    register int g=0;

    for( g=0; g<400; g++ )
    {
            A_naive_line_drawing_algorithm ( 
                8, 750,                 //x1,x2
                8, (50 + (g*4)) ,       //y1,y2
                COLOR_YELLOW );
     };

    gwssrv_show_backbuffer();
}


// test2
// illusion
void test_draw_line2(void)
{
    register int g=0;
    
    unsigned long vertex1[2];
    unsigned long vertex2[2]; 

    unsigned long w = gws_get_device_width();
    unsigned long h = gws_get_device_height();

    // #todo
    // Check the w h validation.

    // horizontal
    for ( g=0; g<h; g=g+10 )
    {
            vertex1[0]=0;  //x1
            vertex1[1]=g;  //y1

            vertex2[0]=g;  //x2
            vertex2[1]=g;  //y2
            
            A_naive_line_drawing_algorithm ( 
                vertex1[0], vertex2[0],   //x1,x2
                vertex1[1], vertex2[1],   //y1,y2
                COLOR_YELLOW );
     };

    // horizontal
    for ( g=0; g<h; g=g+10 )
    {
            vertex1[0]=g;  //x1
            vertex1[1]=g;  //y1

            vertex2[0]=w;  //x2
            vertex2[1]=g;  //y2
            
            A_naive_line_drawing_algorithm ( 
                vertex1[0], vertex2[0],   //x1,x2
                vertex1[1], vertex2[1],   //y1,y2
                COLOR_BLUE );
     };

    gwssrv_show_backbuffer();
}




/* 
 * grBackbufferDrawHorizontalLine:
 *     Draw a horizontal line on backbuffer. 
 */

// It's using the ring3 routine.

void 
grBackbufferDrawHorizontalLine ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2,  
    unsigned int color )
{

    unsigned long __x1 = (unsigned long) x1;
    unsigned long __x2 = (unsigned long) x2;
    unsigned long __y  = (unsigned long) y;
    
    //debug_print("Line\n");
    
    if (__x1 > __x2){
        debug_print("grBackbufferDrawHorizontalLine: __x1 > __x2\n");
        return;
    }

    if (__x2 > 800){
        debug_print("grBackbufferDrawHorizontalLine: __x2 > 800\n");
        return;
    }

// It's using the ring3 routine.

    while (__x1 < __x2)
    {
        grBackBufferPutpixel( color, __x1, __y );
        __x1++;  
    };

    //debug_print("Line done\n");
}


/*
 * backbuffer_draw_horizontal_line:
 *     Draw a horizontal line on backbuffer. 
 */

void 
backbuffer_draw_horizontal_line ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2, 
    unsigned int color,
    unsigned long rop_flags )
{

// #todo
// Maybe we need checking some limits here.

    if (x1 > x2){
        return;
    }

    while (x1 < x2)
    {
        // IN: color, x, y, rop flags.
        backbuffer_putpixel ( 
            color, x1, y, rop_flags ); 

        x1++;
    };
}


void 
frontbuffer_draw_horizontal_line ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2, 
    unsigned int color,
    unsigned long rop_flags )
{

// #todo
// Maybe we need checking some limits here.

    if (x1 > x2){
        return;
    }

    while (x1 < x2)
    {
        // IN: color, x, y, rop flags.
        frontbuffer_putpixel ( 
            color, x1, y, rop_flags ); 

        x1++;
    };
}




//
// End.
//






