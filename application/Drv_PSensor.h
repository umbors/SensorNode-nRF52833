#include "nrfx_saadc.h"
#include "app_timer.h"

#define SAADC_CHANNEL_COUNT   4
#define SAADC_SAMPLE_INTERVAL_MS 3

#define ROW1 8
#define ROW2 4
#define ROW3 7
#define ROW4 12
#define ROW_LIST {ROW3,ROW4,ROW2,ROW1}

#define COL1 24
#define COL2 13
#define COL3 20
#define COL4 17
#define COL_LIST {COL1,COL2,COL3,COL4}

extern volatile bool adc_is_ready;
extern volatile uint8_t psensor_row;
extern volatile uint8_t psensor_col;
extern uint8_t voltage_buffer[8];

static nrf_saadc_value_t samples[SAADC_CHANNEL_COUNT];
static nrfx_saadc_channel_t channels[SAADC_CHANNEL_COUNT] = {NRFX_SAADC_DEFAULT_CHANNEL_SE(NRF_SAADC_INPUT_AIN6, 0),
                                                             NRFX_SAADC_DEFAULT_CHANNEL_SE(NRF_SAADC_INPUT_AIN7, 1),
                                                             NRFX_SAADC_DEFAULT_CHANNEL_SE(NRF_SAADC_INPUT_AIN5, 2),
                                                             NRFX_SAADC_DEFAULT_CHANNEL_SE(NRF_SAADC_INPUT_AIN0, 3)};

extern void psensor_event_handler(nrfx_saadc_evt_t const * p_event);
void psensor_init(void);
void psensor_start(void);
void psensor_stop(void);
void psensor_timer_handler(void * p_context);
