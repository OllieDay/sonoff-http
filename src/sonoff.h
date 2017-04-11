#ifndef SONOFF_H
#define SONOFF_H

enum sonoff_state {
	SONOFF_STATE_OFF,
	SONOFF_STATE_ON
};

void sonoff_init(void);

enum sonoff_state sonoff_read(void);
void sonoff_write(enum sonoff_state state);

#endif
