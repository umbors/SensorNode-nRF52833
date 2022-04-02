#include "LED.h"

void led_off(uint8_t led)
{
    bsp_board_led_off(led);
}

void led_on(uint8_t led)
{
    bsp_board_led_on(led);
}

/**@brief Function for the LEDs initialization.
 *
 * @details Initializes all LEDs used by the application.
 */
void leds_init(void)
{
    bsp_board_init(BSP_INIT_LEDS);
}