#include <pebble.h>
#include "main.h"

static void init(void) {
  main_init();
}

static void deinit(void) {
  main_deinit();
}

int main(void) {
  init();
  app_event_loop();
  deinit();

  return 0;
}
