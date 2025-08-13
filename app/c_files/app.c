#include <stdio.h>
#include <stdlib.h>
#include "app.h"

int read_inputs_csv_line(FILE* f, Inputs* in){
  char buf[256]; if(!fgets(buf,sizeof buf,f)) return 0;
  if(buf[0]=='#'||buf[0]=='\n'||buf[0]=='\r') return read_inputs_csv_line(f,in);
  int time,ign,acc,brk,gear;
  if(sscanf(buf," %d , %d , %d , %d , %d",&time,&ign,&acc,&brk,&gear)!=5 &&
     sscanf(buf,"%d,%d,%d,%d,%d",&time,&ign,&acc,&brk,&gear)!=5) return 0;
  in->ignition_switch=ign?1:0; in->acc_pedal_position=acc; in->brake_pedal_position=brk; in->current_gear=gear;
  return 1;
}
void clamp_inputs(Inputs* in){
  if(in->acc_pedal_position<0) in->acc_pedal_position=0;
  if(in->acc_pedal_position>45) in->acc_pedal_position=45;
  if(in->brake_pedal_position<0) in->brake_pedal_position=0;
  if(in->brake_pedal_position>45) in->brake_pedal_position=45;
  if(in->current_gear<0) in->current_gear=0;
  if(in->current_gear>3) in->current_gear=3;
}

