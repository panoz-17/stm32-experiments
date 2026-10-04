//IVT
__attribute__((section(".vectors"))) void (*ivt[16+91]) (void) = {(void(*)(void)) &_estack, _startup}; 


//main
int main()
{
    int c = 0;
    while(c < 100000)
        c++;
    return 0;
}

__attribute__((naked, noreturn)) void _startup (void)
{
    //stack pointer
    //asm ("ldr sp, =_estack");
    //not needed because it was initialized in ivt declaration

    //data
    extern long _sdata, _sidata, _edata;
    for( *src = &_sidata, *dst = &_sdata; dst < &_edata; )
        *dst++ = *src++;

    //bss 
    extern long _sbss, _ebss;
    for( *src = &_sbss; src < &_ebss; src ++)
        *src = 0;

    //if present, upload rodata

    //calling main
    main();

    //infinite waiting loop when main finishes
    while(1);

}
