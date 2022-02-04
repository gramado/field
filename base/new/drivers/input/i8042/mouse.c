
// mouse.c

#include <kernel.h>  

// Quando tem uma interrupção de mouse eu 
// desligo o teclado e espero por ack
// mas quando tem uma interrupção de teclado, 
// então eu desligo o mouse mas não espero o ack.

// ps/2 mouse handler.
__VOID_IRQ 
irq12_MOUSE (void)
{
    debug_print ("irq12_MOUSE: [TODO]\n");

// Not initialized.
// Uma interrupção ocorreu antes mesmo de inicializarmos 
// o dispositivo e o handler ja estava conectado.
// apenas drenamos um byte pra evitar problemas.
// Mas antes deveríamos checar se a flag indica que
// o buffer está cheio.

    if ( PS2.mouse_initialized != TRUE )
    {
        in8(0x60);
        return;
    }

    // Disable keyboard port.
    wait_then_write (0x64,0xAD);    
    //keyboard_expect_ack();


//
// #todo
//

// #bugbug
// This is a good routine.
// It works easily on qemu.
// But we need to fix some stuff to work
// also in the real machine.

    DeviceInterface_PS2Mouse();

    //#debug
    //printf("$\n");
    //refresh_screen();


// Reanable keyboard port.
    wait_then_write (0x64,0xAE);
    //keyboard_expect_ack();

    debug_print ("irq12_MOUSE: Done\n");
}




