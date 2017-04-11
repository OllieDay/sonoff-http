#include "fw/src/mgos_app.h"
#include "fw/src/mgos_mongoose.h"
#include "fw/src/mgos_wifi.h"
#include "sonoff.h"

static void sonoff_handler(struct mg_connection *c, int ev, void *p, void *user_data) {
	if (ev == MG_EV_HTTP_REQUEST) {
		c->flags |= MG_F_SEND_AND_CLOSE;

		struct http_message *message = (struct http_message *) p;

		if (mg_vcmp(&message->method, "GET") == 0) {
			mg_printf(c, "HTTP/1.0 200 OK\n\n%d", sonoff_read());

			return;
		}

		if (mg_vcmp(&message->method, "POST") == 0) {
			sonoff_write(atoi(message->body.p));
			mg_printf(c, "HTTP/1.0 200 OK\n\n");

			return;
		}

		mg_printf(c, "HTTP/1.0 400 Bad Request\n\n");
	}

	(void) user_data;
}

enum mgos_app_init_result mgos_app_init(void) {
	sonoff_init();
	mgos_register_http_endpoint("/sonoff", sonoff_handler, NULL);

	return MGOS_APP_INIT_SUCCESS;
}
