#include <LVGL_thread.h>
#include "board_init.h"
#include "lvgl/demos/lv_demos.h"

#include "ui/ui.h"
#define USE_EEZ_DEMO 1

#if USE_EEZ_DEMO

#include <sys/time.h>

int _gettimeofday( struct timeval *tv, void *tzvp )
{
    uint64_t t = 0; // __your_system_time_function_here__();  // get uptime in nanoseconds
    tv->tv_sec = t / 1000000000;  // convert to seconds
    tv->tv_usec = ( t % 1000000000 ) / 1000;  // get remaining microseconds
    return 0;  // return non-zero for error
} // end _gettimeofday()

#endif

void timer_tick_callback(timer_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    lv_tick_inc(1);
}

void vApplicationMallocFailedHook( void )
{
    __BKPT(0);
}

/* New Thread entry function */
/* pvParameters contains TaskHandle_t */
void LVGL_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);
    fsp_err_t err;

    lv_init();

    board_init();

#if USE_EEZ_DEMO

    ui_init();

#else

#if (1 == LV_USE_DEMO_BENCHMARK)
    lv_demo_benchmark();
#endif

#if (1 == LV_USE_DEMO_MUSIC)
    lv_demo_music();
#endif

#if (1 == LV_USE_DEMO_KEYPAD_AND_ENCODER)
    lv_demo_keypad_encoder();

#endif

#if (1 == LV_USE_DEMO_STRESS)
    lv_demo_stress();
#endif

#if (1 == LV_USE_DEMO_WIDGETS && 0 == LV_USE_DEMO_BENCHMARK)
    lv_demo_widgets();
#endif

#endif

    err = R_GPT_Open(&g_timer0_ctrl, &g_timer0_cfg);
    if (FSP_SUCCESS != err)
    {
        __BKPT(0);
    }

    err = R_GPT_Start(&g_timer0_ctrl);
    if (FSP_SUCCESS != err)
    {
        __BKPT(0);
    }

    /* TODO: add your own code here */
    while (1)
    {
        lv_timer_handler();

#if USE_EEZ_DEMO
        ui_tick();
#endif

        vTaskDelay (1);
    }
}
