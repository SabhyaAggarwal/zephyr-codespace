#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>
#include <stdint.h>

#define STEP_DELAY_MS 5
#define LEVEL_MAX     255U

static const struct pwm_dt_spec red_led =
	PWM_DT_SPEC_GET(DT_ALIAS(red_pwm_led));
static const struct pwm_dt_spec green_led =
	PWM_DT_SPEC_GET(DT_ALIAS(green_pwm_led));
static const struct pwm_dt_spec blue_led =
	PWM_DT_SPEC_GET(DT_ALIAS(blue_pwm_led));

static int set_channel(const struct pwm_dt_spec *led, uint8_t value)
{
	uint32_t pulse = ((uint64_t)led->period * value) / LEVEL_MAX;
	return pwm_set_pulse_dt(led, pulse);
}

static int set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	int ret;

	ret = set_channel(&red_led, r);
	if (ret < 0) {
		return ret;
	}

	ret = set_channel(&green_led, g);
	if (ret < 0) {
		return ret;
	}

	ret = set_channel(&blue_led, b);
	if (ret < 0) {
		return ret;
	}

	return 0;
}

int main(void)
{
	int ret;

	if (!pwm_is_ready_dt(&red_led) ||
	    !pwm_is_ready_dt(&green_led) ||
	    !pwm_is_ready_dt(&blue_led)) {
		return -1;
	}

	while (1) {
		for (uint16_t i = 0; i <= 255; i++) {
			ret = set_rgb(255, i, 0);
			if (ret < 0) {
				return ret;
			}
			k_msleep(STEP_DELAY_MS);
		}

		for (int i = 255; i >= 0; i--) {
			ret = set_rgb(i, 255, 0);
			if (ret < 0) {
				return ret;
			}
			k_msleep(STEP_DELAY_MS);
		}

		for (uint16_t i = 0; i <= 255; i++) {
			ret = set_rgb(0, 255, i);
			if (ret < 0) {
				return ret;
			}
			k_msleep(STEP_DELAY_MS);
		}

		for (int i = 255; i >= 0; i--) {
			ret = set_rgb(0, i, 255);
			if (ret < 0) {
				return ret;
			}
			k_msleep(STEP_DELAY_MS);
		}

		for (uint16_t i = 0; i <= 255; i++) {
			ret = set_rgb(i, 0, 255);
			if (ret < 0) {
				return ret;
			}
			k_msleep(STEP_DELAY_MS);
		}

		for (int i = 255; i >= 0; i--) {
			ret = set_rgb(255, 0, i);
			if (ret < 0) {
				return ret;
			}
			k_msleep(STEP_DELAY_MS);
		}
	}

	return 0;
}
