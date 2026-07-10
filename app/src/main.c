#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

// Identify the main user LED directly using the on-board alias link
#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void) {
    // Check if the NXP GPIO peripheral block is ready for use
    if (!gpio_is_ready_dt(&led)) {
        return 0;
    }

    // Configure the pin path as a standard active output line
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

    while (1) {
        // Toggle the state of the pin 
        gpio_pin_toggle_dt(&led);
        
        // Let the processor core sleep for 500 milliseconds
        k_msleep(500);
    }
    return 0;
}
