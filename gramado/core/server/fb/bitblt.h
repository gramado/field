
// pixel.h

#ifndef __PIXEL_H
#define __PIXEL_H  1


int 
grBackBufferPutpixel ( 
    unsigned int color, 
    int x, 
    int y );


// put pixel
// low level.
int 
fb_BackBufferPutpixel ( 
    unsigned int color, 
    int x, 
    int y,
    unsigned long flags,
    unsigned long buffer_va );


int 
grBackBufferPutpixel2 ( 
    unsigned int color, 
    int x, 
    int y );


unsigned long
grBackBufferGetPixelColor ( 
    int x, 
    int y );
    

#endif    



