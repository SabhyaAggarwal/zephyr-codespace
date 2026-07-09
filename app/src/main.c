#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

static const struct gpio_dt_spec red_led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec green_led = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);
static const struct gpio_dt_spec blue_led = GPIO_DT_SPEC_GET(DT_ALIAS(led2), gpios);

static void set_rgb(bool red_on, bool green_on, bool blue_on)
{
	gpio_pin_set_dt(&red_led, red_on);
	gpio_pin_set_dt(&green_led, green_on);
	gpio_pin_set_dt(&blue_led, blue_on);
}

int main(void)
{
	if (!gpio_is_ready_dt(&red_led) || !gpio_is_ready_dt(&green_led) || !gpio_is_ready_dt(&blue_led)) {
		return 0;
	}

	gpio_pin_configure_dt(&red_led, GPIO_OUTPUT_INACTIVE);
	gpio_pin_configure_dt(&green_led, GPIO_OUTPUT_INACTIVE);
	gpio_pin_configure_dt(&blue_led, GPIO_OUTPUT_INACTIVE);

	while (1) {
		set_rgb(true, false, false);
		k_msleep(250);
		set_rgb(true, true, false);
		k_msleep(250);
		set_rgb(false, true, false);
		k_msleep(250);
		set_rgb(false, true, true);
		k_msleep(250);
		set_rgb(false, false, true);
		k_msleep(250);
		set_rgb(true, false, true);
		k_msleep(250);
	}

	return 0;
}
