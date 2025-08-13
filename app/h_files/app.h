#ifndef APP_H
#define APP_H
#include <stdio.h>
#include "calibration.h"

typedef struct { int ignition_switch; int acc_pedal_position; int brake_pedal_position; int current_gear; } Inputs;
typedef struct { int engine_state; int engine_speed; int engine_stall; int stall_consec_iters; } EcmState;

int  read_inputs_csv_line(FILE* f, Inputs* in);     /* time,ignition,acc,brake,gear */
void clamp_inputs(Inputs* in);
#endif
