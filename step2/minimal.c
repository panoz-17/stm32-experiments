#include <inttypes.h>

//getting GPIO address
#define GPIO(bank) ((struct gpio_t *) (0x4002 0000 + 0x400 * ((bank) - 'A')))
//getting pin address, 2 bytes: higher = bank, lower = pin
#define PIN(bank, number) ((((bank) - 'A') <<8) | (number))
#define PINNUM(pin) ((pin) & 0xFF)2
#define PINBANK(pin) ((pin) >> 8)

//GPIO described by registers; each gpio banks controls 16 pins
typedef struct gpio_t 
{
    uint32_t MODER, OTYPER, OSPEEDER, PUPDR, IDR, ODR, BSRR, LCKR, AFRL, AFRH;
    //Alternate Function registers are divided in High and Low, work 4 bits per pin
} gpio_t;

//from datasheet, 0 = input, 1 = ouput, 2 = alternate function, 3 = analog
enum {GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_AF, GPIO_MODE_ANALOG};

static inline void gpio_set_mode(uint16_t pin, uint8_t mode)
{
    //TO BE MPLEMENTED
}

int main ()
{
    return 0;
}

__attribute__((naked, noreturn)) void _reset(void) {

    asm( "ldr sp, = _estack");

    extern long _sdata, _edata, _sidata, _sbss, _ebss;

    for( long *src = &_sbss; src < &_ebss; src++ )
        *src = 0;

    for( long *dst = &_sdata, *src = &_sidata; dst < &_edata; )
        *dst++ = *src++;

    main();

  for (;;) (void) 0;  // Infinite loop
}

__attribute__((section(".vectors"))) void (*tab[16 + 91])(void) = {
    0,
    _reset
};
