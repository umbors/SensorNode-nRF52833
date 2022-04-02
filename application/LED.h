#include "nordic_common.h"
#include "nrf.h"
#include "boards.h"

#define ADVERTISING_LED                 1                         /**< Is on when device is advertising. */
#define CONNECTED_LED                   3                        /**< Is on when device has connected. */
#define LEDBUTTON_LED                   0                         /**< LED to be toggled with the help of the LED Button Service. */

void led_off(uint8_t led);
void led_on(uint8_t led);
void leds_init(void);

