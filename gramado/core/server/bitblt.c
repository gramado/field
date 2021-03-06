
// bitblt.c 



#include "gws.h"


//
// ## putpixel: 
// backbuffer e lfb ##
//
// IN: cor, x, y



// Put pixel using the kernel service.
int 
grBackBufferPutpixel2 ( 
    unsigned int color, 
    int x, 
    int y )
{

    if (x<0){ return -1; }
    if (y<0){ return -1; }

// Service number 6.
    return (int) gramado_system_call ( 6, color, x, y );
}


// Plot pixel into the raster.
// The origin is top/left of the viewport. (0,0).
int 
grBackBufferPutpixel ( 
    unsigned int color, 
    int x, 
    int y )
{

    // ...

// put pixel into the backbuffer.
    return (int) fb_BackBufferPutpixel( 
                     color,
                     x,
                     y,
                     0, // ROP
                     ____BACKBUFFER_VA );  // Target buffer.

// #todo
// put pixel into another buffer.
    //return (int) fb_BackBufferPutpixel(color,x,y,0,____ANOTHER_BUFFER_VA);
}



/*
 *******************************************
 * fb_BackBufferPutpixel:
 *     Put pixel in the device screen.
 */

// #??
// Usando o endereço virtual do backbuffer
// Será que está mapeado ???
// Está em ring 3 ??? ou ring 0???

// Pinta um pixel no backbuffer.
// O buffer tem o tamanho da janela do dispositivo.
// A origem está em top/left.

// #bugbug
// #todo
// Precismos considerar o limite do backbuffer.
// Então teremos um Offset máximo.

// #todo
// Check some flags, just like rasterizations.
// We will need a lot of parameters in this kind of function
// Including the address of the backbuffer.


// Clipping against the device limits

// #todo
// rop_flags   ... raster operations
// See the same routine in the kernel side.

// Plot pixel into the raster.
// The origin is top/left of the viewport. (0,0).

int 
fb_BackBufferPutpixel ( 
    unsigned int color, 
    int x, 
    int y,
    unsigned long flags, // #todo: Change to 'rop_flags'
    unsigned long buffer_va )  
{

    //debug_print("Pixel\n");

    unsigned char *where = (unsigned char *) ____BACKBUFFER_VA;
    //unsigned char *where = (unsigned char *) buffer_va;

// Device context
    unsigned long deviceLeft   = 0;
    unsigned long deviceTop    = 0;
    unsigned long deviceWidth  = (__device_width  & 0xFFFF );
    unsigned long deviceHeight = (__device_height & 0xFFFF );
    // #todo
    // Precismos considerar o limite do backbuffer.
    // Então teremos um Offset máximo.

    unsigned long tmpOffset=0;
    unsigned long MaxOffset=0;

    int Offset=0;
    
    // #todo
    // raster operation. rasterization.
    // unsigned long rop;


// 2MB limit
// Our buffer size.
// 2mb is the limit for 64bit full pagetable.
// #bubug: Não fazer multilicações
//MaxOffset = (int) (1024*10124*4);
//MaxOffset = (int) 0x00400000;
    MaxOffset = (int) 0x00200000;


    char b, g, r, a;
    b = (color & 0xFF);
    g = (color & 0xFF00)   >> 8;
    r = (color & 0xFF0000) >> 16;
    a = (color >> 24) + 1;

    // 3 = 24 bpp
    int bytes_count=0;


//
// Clipping
//

// Clipping against the device limits

    if (x<0){ goto fail; }
    if (y<0){ goto fail; }
    if ( x >= deviceWidth ) { goto fail; }
    if ( y >= deviceHeight ){ goto fail; }


// Purify
    x = ( x & 0xFFFF);
    y = ( y & 0xFFFF);

//
// bpp
//

// #danger
// Esse valor foi herdado do bootloader.

    switch (SavedBPP){
        case 32:  bytes_count = 4;  break;
        case 24:  bytes_count = 3;  break;
        //case 16:  bytes_count = 2;  break;
        //case 8:   bytes_count = 1;  break;
        default:
            printf("grBackBufferPutpixel: [ERROR] SavedBPP\n");
            goto fail;
            break;
    };

// #importante
// Pegamos a largura do dispositivo.

    //width = (int) SavedX; 


// unsigned long
// Nao pode ser maior que 2MB.
// Que eh o tamanho do buffer que temos ate agora.
    unsigned long pitch=0; 

    if (bytes_count!=3 && bytes_count!=4 )
        return -1;

    if (bytes_count==3)
    {
        pitch = (unsigned long) (deviceWidth*bytes_count);
        tmpOffset = (unsigned long) ( (pitch*y) + (x*bytes_count) );
    }

    if (bytes_count==4)
    {
        pitch = (unsigned long) (deviceWidth<<2);
        tmpOffset = (unsigned long) ( (pitch*y) + (x<<2) );
    }

    if( tmpOffset >= MaxOffset )
    {
        debug_print ("grBackBufferPutpixel: [ERROR] backbuffer limits > Max\n"); 
        return -1;
        //asm("int $3");
        
        //printf ("pixelBackBufferPutpixel: [ERROR] backbuffer limits > Max\n");
        //printf ("tmpOffset=%x\n",tmpOffset);
        //printf ("x=%d\n",x);
        //printf ("y=%d\n",y);
        //printf ("width=%d\n",width);
        //exit(1);
        //goto fail;
    }

    // int. menor que 4MB
    Offset = (int) tmpOffset;

    // #bugbug
    // #todo
    // Para não termos problemas com o offset, temos que checar
    // os limites de x e y.
//
// Backbuffer limit
//

// #bugbug
// Escrever fora do backbuffer pode gerar PF.

// #todo
// The rop_flags will give us some informations.
// the lsb is the operation code.
// See the same routine in the kernel side.


/*
//
// == Modify ==============================
//

    char b2, g2, r2, a2;

// get
    b2 = where[Offset];
    g2 = where[Offset +1];
    r2 = where[Offset +2];
    if ( SavedBPP == 32 ){ a2 = where[Offset +3]; };

// change
    b = (b2 & 1);
*/

//
// == Record ==============================
//

//
// BGR and A
//

    where[Offset]    = b;
    where[Offset +1] = g;
    where[Offset +2] = r;
    if ( SavedBPP == 32 ){ where[Offset +3] = a; };

    //debug_print("Pixel done\n");
    
    return 0;

fail:
    //debug_print("Pixel fail\n");
    return -1;
}


//==============
//#test

/*
 * putpixel0:
 *     Ok. 
 *     O servidor kgws pode acessar um buffer. Mas não tem acesso
 * ao frontbuffer. Para isso ele precisa usasr o diálogo do driver 
 * de vídeo.
 * IN: 
 *     color, x, y, rop_flags
 */

// #todo
// + Change the names of these parameters.
// + Create a parameter for the address of the buffer.

void 
putpixel0 ( 
    unsigned int  _color,
    unsigned long _x, 
    unsigned long _y, 
    unsigned long _rop_flags,
    unsigned long buffer_va )
{

    //unsigned char *where = (unsigned char *) BACKBUFFER_VA;
    unsigned char *where = (unsigned char *) buffer_va;
    
    unsigned int Color = (unsigned int) (_color & 0xFFFFFFFF);

// A cor passada via argumento.
// Color bytes
    char b, g, r, a;

    // bgra
    b = (Color & 0xFF);
    g = (Color & 0xFF00) >> 8;
    r = (Color & 0xFF0000) >> 16;
    a = (Color >> 24) + 1;


// Positions
    int x = (int) (_x & 0xFFFF);
    int y = (int) (_y & 0xFFFF);



// 3 = 24 bpp
// 2 = 16 bpp
// ...

    int bytes_count=0;


// Buffer address validation.

    if(buffer_va == 0){
        //panic("putpixel0: buffer_va\n");
        gwssrv_debug_print("putpixel0: buffer_va\n");
        return;
    }

//
// bpp
//

// #danger
// This is a global variable.
// Esse valor foi herdado do bootloader.

    switch (SavedBPP){
    case 32:  bytes_count=4;  break;
    case 24:  bytes_count=3;  break;
    //#testando
    //case 16:
    //    bytes_count = 2;
    //    break;
    //case 8:
    //    bytes_count = 1;
    //    break;
    default:
        //#todo: Do we have panic ar this moment?
        //panic ("putpixel0: SavedBPP\n");
        gwssrv_debug_print("putpixel0: SavedBPP\n");
        while(1){}
        break;
    };

// #importante
// Pegamos a largura do dispositivo.

    int width = (int) (SavedX & 0xFFFF);
    
    width = (int) (width & 0xFFFF);


    int offset=0;
    //int offset = (int) ( (bytes_count*width*y) + (bytes_count*x) );

// Offset.

// 32bpp
    if (bytes_count==4){
        offset = (int) ( ((width<<2)*y) + (x<<2) );
    }

// 24bpp
    if (bytes_count==3){
        offset = (int) ( (bytes_count*width*y) + (bytes_count*x) );
    }

// 16bpp
    //if (bytes_count==2){
    //    offset = (int) ( ((width<<1)*y) + (x<<1) );
    //}


//
// == Modify ==============================
//

// a cor no framebuffer
    unsigned char b2, g2, r2, a2;

// get
    b2 = where[offset];
    g2 = where[offset +1];
    r2 = where[offset +2];
    if ( SavedBPP == 32 ){ a2 = where[offset +3]; };


// A cor transformada.
// A cor a ser gravada.
    unsigned char b3, g3, r3, a3;

// The first byte;
// 0 ~ FF
    int operation = (int) (_rop_flags & 0xFF);

// flags
// 16, 32, 64, 128 


// Sem modificação
// A cor a ser registrada é a mesma enviada por argumento.
    if ( operation == 0 ){
        r3=r;  g3=g;  b3=b;  a3=a;
    }

// 1 = or
    if ( operation == 1 )
    {
        r3 = (r2 | r);
        g3 = (g2 | g);
        b3 = (b2 | b);
        a3 = a2;
    }

// 2 = and
    if ( operation == 2 )
    {
        r3 = (r2 & r);
        g3 = (g2 & g);
        b3 = (b2 & b);
        a3 = a2;
    }

    // 3 = xor
    if ( operation == 3 )
    {
        r3 = (r2 ^ r);
        g3 = (g2 ^ g);
        b3 = (b2 ^ b);
        a3 = a2;
    }

// ============

    // red
    if ( operation == 10)
    {
        r3 = (r2 & 0xFE);
        g3 = g2;
        b3 = b2; 
        a3 = a2;
    }

    // green
    if ( operation == 11)
    {
        r3 = r2;
        g3 = (g2 & 0xFE);
        b3 = b2; 
        a3 = a2;
    }

    // blue
    if ( operation == 12)
    {
        r3 = r2;
        g3 = g2;
        b3 = (b2 & 0xFE); 
        a3 = a2;
    }


// ============

    // gray
    if ( operation == 20)
    {
        r3 = (r2 & 0x80);
        g3 = (g2 & 0x80);
        b3 = (b2 & 0x80);
        a3 = a2;
    }

    // gray
    if ( operation == 21)
    {
        r3 = (r2 & 0x00);
        g3 = (g2 & 0xFF);
        b3 = (b2 & 0xFF);
        a3 = a2;
    }

// luminosity
// Gray: luminosity = R*0.3 + G*0.59 + B *0.11

/*
 // #test
 // This is a test yet.
    unsigned char common_gray=0;
    if ( operation == 22 )
    {
        r3 = ((r2 * 30 )/100);
        g3 = ((g2 * 59 )/100);
        b3 = ((b2 * 11 )/100);
        common_gray = (unsigned char) (r3+g3+b3);
        r3=(unsigned char)common_gray;
        g3=(unsigned char)common_gray;
        b3=(unsigned char)common_gray;
        a3 = a2;
    }
*/


//
// == Register =====================
// 

// BGR and A

    where[offset]    = b3;
    where[offset +1] = g3;
    where[offset +2] = r3;
    if ( SavedBPP == 32 ){ where[offset +3] = a3; };
}


void 
backbuffer_putpixel ( 
    unsigned int  _color,
    unsigned long _x, 
    unsigned long _y, 
    unsigned long _rop_flags )
{

// Putpixel at the given buffer address.
    putpixel0(
        _color,
        _x,
        _y,
        _rop_flags,
        ____BACKBUFFER_VA );
}

// #todo: Not tested yet.
void 
frontbuffer_putpixel ( 
    unsigned int  _color,
    unsigned long _x, 
    unsigned long _y, 
    unsigned long _rop_flags )
{

// Putpixel at the given buffer address.
    putpixel0(
        _color,
        _x,
        _y,
        _rop_flags,
        ____FRONTBUFFER_VA );
}





//============

// pega uma cor dado sua posição
unsigned long
grBackBufferGetPixelColor ( 
    int x, 
    int y )
{

    // 0xC0800000
    unsigned char *where = (unsigned char *) ____BACKBUFFER_VA;


	// 3 = 24 bpp

    int bytes_count=0;


    // #bugbug
    // Essa funçao eta errada,
    // precisamos passar o ponteiro para o retorno via parametro
    // e o retorno da funçao deve ser int, pra indicar sucesso ou nao.

    if (x<0){ return 0; }
    if (y<0){ return 0; }



    //
    // bpp
    //
    
    // #danger
    // Esse valor foi herdado do bootloader.

    switch (SavedBPP){

        case 32:  bytes_count = 4;  break;
        case 24:  bytes_count = 3;  break;
        //case 16:  bytes_count = 2;  break;
        //case 8:   bytes_count = 1;  break;
        
        default:
            printf("backbuffer_putpixel: [ERROR] SavedBPP\n");
            //panic ("backbuffer_putpixel: SavedBPP");
            break;
    };

	// #importante
	// Pegamos a largura do dispositivo.
	
    //int width = (int) SavedX; 
    
    int width = (int) SavedX; 
    
    int offset = (int) ( (bytes_count*width*y) + (bytes_count*x) );

    //
    // BGR and A
    //

    // bgra
    char b, g, r, a;

    // Get bytes.

    b = where[offset];
    g = where[offset +1];
    r = where[offset +2];
    if ( SavedBPP == 32 ){ a = where[offset +3]; };
    
    unsigned long ColorBuffer=0;
    unsigned char *c = (unsigned char *) &ColorBuffer;

    // Set bytes of ColorBuffer.

    c[0] = b; 
    c[1] = g;
    c[2] = r;
    c[3] = a;

    // return the color value.
    return (unsigned long) ColorBuffer;
}



//
// End.
//



