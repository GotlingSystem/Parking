#pragma once

#define COST_PER_DAY 80
#define COST_PER_FINE 300

extern int days;
extern int fines;
extern int paid;

void read_persistent();
void write_persistent();

char *tostring(char *output, int length);