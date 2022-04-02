#include "app_button.h"
#include "boards.h"
#include "app_timer.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define LEDBUTTON_BUTTON                BUTTON_1                  /**< Button that will trigger the notification event with the LED Button Service */
#define BUTTON_DETECTION_DELAY          APP_TIMER_TICKS(50)                     /**< Delay from a GPIOTE event until a button is reported as pushed (in number of timer ticks). */

extern void button_event_handler(uint8_t pin_no, uint8_t button_action);
void buttons_init(void);
