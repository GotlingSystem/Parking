#include <pebble.h>
#include "config.h"
#include "common/tools.h"

#define DAYS_PKEY 10
#define FINES_PKEY 11
#define PAID_PKEY 12

#define DAYS_DEFAULT 0
#define FINES_DEFAULT 0
#define PAID_DEFAULT 0

int days = DAYS_DEFAULT;
int fines = FINES_DEFAULT;
int paid = PAID_DEFAULT;

void read_persistent() {
	days = persist_exists(DAYS_PKEY) ? persist_read_int(DAYS_PKEY) : DAYS_DEFAULT;
	fines = persist_exists(FINES_PKEY) ? persist_read_int(FINES_PKEY) : FINES_DEFAULT;
	paid = persist_exists(PAID_PKEY) ? persist_read_int(PAID_PKEY) : PAID_DEFAULT;
}

void write_persistent() {
	persist_write_int(DAYS_PKEY, days);
	persist_write_int(FINES_PKEY, fines);
	persist_write_int(PAID_PKEY, paid);
}

char *tostring(char *output, int length) {
	char days_text[3];
	format_time(days_text, days);
	
	char fines_text[3];
	format_time(fines_text, fines);
	
	snprintf(output, length, "Dagar: %s Böter: %s", days_text, fines_text);
	
	return output;
}