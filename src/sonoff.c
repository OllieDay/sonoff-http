#include "fw/src/mgos_gpio.h"
#include "fw/src/mgos_sys_config.h"
#include "sonoff.h"

static struct sys_config_sonoff sonoff;

void sonoff_init(void) {
	sonoff = get_cfg()->sonoff;

	mgos_gpio_set_mode(sonoff.led, MGOS_GPIO_MODE_OUTPUT);
	mgos_gpio_set_mode(sonoff.relay, MGOS_GPIO_MODE_OUTPUT);

	// Synchronize LED and relay state
	mgos_gpio_write(sonoff.led, !sonoff_read());
}

enum sonoff_state sonoff_read(void) {
	return mgos_gpio_read(sonoff.relay);
}

void sonoff_write(enum sonoff_state state) {
	mgos_gpio_write(sonoff.relay, state);

	// Set LED state to that of the relay's
	mgos_gpio_write(sonoff.led, !state);
}
