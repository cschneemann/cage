#include <wayland-server-core.h>
#include <wlr/types/wlr_output.h>
#include <wlr/types/wlr_output_power_management_v1.h>
#include <wlr/util/log.h>

#include "output_power_manager_v1.h"
#include "server.h"

void
handle_output_power_manager_set_mode(struct wl_listener *listener, void *data)
{
	struct wlr_output_power_v1_set_mode_event *event = data;
	bool enabled = (event->mode == ZWLR_OUTPUT_POWER_V1_MODE_ON);

	wlr_log(WLR_DEBUG, "%s output %s via output power management",
		enabled ? "Enabling" : "Disabling", event->output->name);

	struct wlr_output_state state = {0};
	wlr_output_state_set_enabled(&state, enabled);
	wlr_output_commit_state(event->output, &state);
}
