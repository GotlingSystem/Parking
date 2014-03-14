#include <pebble.h>
#include "main.h"
#include "ticket/config.h"
#include "ticket/config_menu.h"

static struct MainUi {
	Window *window;
	TextLayer *header;
	TextLayer *data;
	TextLayer *result;
} ui;

/*
Parkering

Dagar 4
Böter 0

+ 320:- :)

*/


static char data_buffer[40];
static char result_buffer[20];

static void update_ui() {
	snprintf(data_buffer, sizeof data_buffer, "Dagar: %d\nBetalat: %d kr\nBöter: %d", days, paid, fines);
	text_layer_set_text(ui.data, data_buffer);

	int money = days * COST_PER_DAY - fines * COST_PER_FINE - paid;
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "Money: %d", money);
	if (money >= 0) {
		snprintf(result_buffer, sizeof result_buffer, "+ %d kr :-)", money);
	} else {
		snprintf(result_buffer, sizeof result_buffer, "%d kr :'(", money);
	}
	text_layer_set_text(ui.result, result_buffer);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	config_menu_init(&update_ui);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	update_ui();
}

static void click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
}

static void window_load(Window *window) {
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);

	ui.header = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { bounds.size.w, 32 } });
	text_layer_set_text(ui.header, "Parkering");
	text_layer_set_text_alignment(ui.header, GTextAlignmentCenter);
	text_layer_set_font(ui.header, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	layer_add_child(window_layer, text_layer_get_layer(ui.header));

	ui.data = text_layer_create((GRect) { .origin = { 10, 32 }, .size = { bounds.size.w, 78 } });
	text_layer_set_text_alignment(ui.data, GTextAlignmentLeft);
	text_layer_set_font(ui.data, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	layer_add_child(window_layer, text_layer_get_layer(ui.data));

	ui.result = text_layer_create((GRect) { .origin = { 0, 110 }, .size = { bounds.size.w, 64 } });
	text_layer_set_text_alignment(ui.result, GTextAlignmentCenter);
	text_layer_set_font(ui.result, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	layer_add_child(window_layer, text_layer_get_layer(ui.result));

	update_ui();
}

static void window_unload(Window *window) {
	text_layer_destroy(ui.header);
	text_layer_destroy(ui.data);
	text_layer_destroy(ui.result);
}

void main_init(void) {
	ui.window = window_create();
	window_set_click_config_provider(ui.window, click_config_provider);
	window_set_window_handlers(ui.window, (WindowHandlers) {
		.load = window_load,
		.unload = window_unload,
	});
	const bool animated = true;
	window_stack_push(ui.window, animated);

	read_persistent();
	update_ui();
}

void main_deinit(void) {
	window_destroy(ui.window);
}
