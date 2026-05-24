#include "bsp.h"

void Sys_Init(void)
{
    // Initialize hardware components
    // This is a placeholder for actual initialization code.
    LedInit();
}

void Sys_Run(void)
{
    // Main loop for the system. This is where the application logic would go.
    KeyScan();
    // Placeholder for main loop code.

}