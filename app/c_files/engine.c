#include "engine.h"

/* SCR000001: ignition + simple idle creep when ON & acc=0 (keeps tests deterministic) */
void scr000001_ignition(const Inputs* in, EcmState* st, const Calib* c){
  if(in->ignition_switch){                       /* ON */
    st->engine_state = 1;
    if(in->acc_pedal_position==0 && st->engine_speed < c->idle_rpm){
      int next = st->engine_speed + c->idle_gain; /* gradual rise */
      if(next > c->idle_rpm) next = c->idle_rpm;
      st->engine_speed = next;
    }
  }else{                                          /* OFF */
    st->engine_state = 0;
    st->engine_speed = 0;
    st->engine_stall = 0;
    st->stall_consec_iters = 0;
  }
}
