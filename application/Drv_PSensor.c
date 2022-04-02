#include "Drv_PSensor.h"
#include "nrf_gpio.h"

APP_TIMER_DEF(psensor_timer_id);
volatile bool adc_is_ready = true;
volatile uint8_t psensor_direction = 0;
volatile uint8_t psensor_pointer = 1;
uint8_t voltage_buffer[8];
const uint8_t row [] = ROW_LIST;

void psensor_init(void)
{
		ret_code_t err_code;
		err_code = nrfx_saadc_init(NRFX_SAADC_CONFIG_IRQ_PRIORITY);
    APP_ERROR_CHECK(err_code);

    err_code = nrfx_saadc_channels_config(channels, SAADC_CHANNEL_COUNT);
    APP_ERROR_CHECK(err_code);
		
		err_code = app_timer_create(&psensor_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                psensor_timer_handler);
    APP_ERROR_CHECK(err_code);
		//init SCVx
		nrf_gpio_cfg_output(13);
		nrf_gpio_cfg_output(8);
		nrf_gpio_cfg_output(4);
		nrf_gpio_cfg_output(12);
		nrf_gpio_cfg_output(7);
}

void psensor_start(void)
{
		ret_code_t err_code;
		err_code = app_timer_start(psensor_timer_id, APP_TIMER_TICKS(SAADC_SAMPLE_INTERVAL_MS), NULL);
    APP_ERROR_CHECK(err_code);
}

void psensor_stop(void)
{
		ret_code_t err_code;
		err_code = app_timer_stop(psensor_timer_id);
    APP_ERROR_CHECK(err_code);
}

void psensor_timer_handler(void * p_context)
{
    if(adc_is_ready)
    {
				if(psensor_direction == 0){
				//SCV0 = VCC			
					for(int i = 0;i<ARRAY_SIZE(row);i++){
						nrf_gpio_pin_set(row[i]);
					}
					nrf_gpio_pin_clear(row[psensor_pointer]);
					//nrfx_saadc_offset_calibrate(NULL);
				}
				else{
				//SCV0 = GND
					for(int i = 0;i<ARRAY_SIZE(row);i++){
						nrf_gpio_pin_clear(row[i]);
					}
					nrf_gpio_pin_set(row[psensor_pointer]);	
				}
        ret_code_t err_code;
        err_code = nrfx_saadc_simple_mode_set((1<<0|1<<1|1<<2|1<<3),
                                              NRF_SAADC_RESOLUTION_12BIT,
                                              NRF_SAADC_OVERSAMPLE_4X,
                                              psensor_event_handler);
        APP_ERROR_CHECK(err_code);
        err_code = nrfx_saadc_buffer_set(samples, SAADC_CHANNEL_COUNT);
        APP_ERROR_CHECK(err_code);

        err_code = nrfx_saadc_mode_trigger();
        APP_ERROR_CHECK(err_code);
			  
        adc_is_ready = false;
    }
}
