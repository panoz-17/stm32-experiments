// Startup code
int main ();
//__attribute__ = specifica GCC per dare proprieta' alla funzione _reset
//naked = no prologo/epilogo 
//noreturn = la funzione non ritorna alcun valore
__attribute__((naked, noreturn)) void _reset(void) {

    /* setting stack pointer */
    asm( "ldr sp, = _estack");
    /* asm = assembly function */
    /* loads symbol _estack in register sp */

    /* copying .data in RAM and initializing .bss */
    extern long _sdata, _edata, _sidata, _sbss, _ebss;
    /* long = 4 bytes */
    /* however, _sdata is just a name for an address value */
    /* if i refer to _sdata, it reads the content of the address */

    for( long *src = &_sbss; src < &_ebss; src++ )
        *src = 0;

    for( long *dst = &_sdata, *src = &_sidata; dst < &_edata; )
        *dst++ = *src++;

    /* calling main() */
    main();

  for (;;) (void) 0;  // Infinite loop
}

int main()
{
    return 0;
}

// 16 standard and 91 STM32-specific handlers
// section = mette la variabile in un nuovo segmento di memoria .vectors
// creiamo un vettore di 16 + 91 puntatori a funzioni di tipo void fun (void) = IVT
__attribute__((section(".vectors"))) void (*tab[16 + 91])(void) = {
    //inizio a riempire la IVT
    //stack pointer
    0,

    //entry point
    _reset
};
