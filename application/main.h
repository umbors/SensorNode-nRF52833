#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "nordic_common.h"
#include "nrf.h"
#include "boards.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_delay.h"
#include "nrf_drv_clock.h"
#include "app_error.h"
#include "app_timer.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "Drv_BLE.h"

#define DEAD_BEEF                       0xDEADBEEF                              /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */

int main(void);
void all_init(void);
static void timers_init(void);
void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name);
static void log_init(void);
static void power_management_init(void);
static void idle_state_handle(void);
