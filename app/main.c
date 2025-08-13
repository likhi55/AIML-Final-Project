#include <stdio.h>
#include <string.h>
#include "h_files/app.h"
#include "h_files/engine.h"
#include "calibration/calibration.h"

static void write_header(FILE* fo){
  fprintf(fo,"time,ignition,acc,brake,gear,engine_state,engine_speed,engine_stall\n");
}

int main(int argc,char**argv){
  if(argc<3){ fprintf(stderr,"Usage: %s <in.csv> <out.csv> [cal.txt]\n",argv[0]); return 1; }
  const char* in_path=argv[1]; const char* out_path=argv[2];
  const char* cal_path=(argc>=3)? (argc>=4?argv[3]:"app/calibration/calibration.txt") : "app/calibration/calibration.txt";

  Calib C; calib_defaults(&C); calib_load_from_file(&C,cal_path);

  FILE* fi=fopen(in_path,"r"); if(!fi){fprintf(stderr,"Cannot open %s\n",in_path); return 2;}
  FILE* fo=fopen(out_path,"w"); if(!fo){fclose(fi); fprintf(stderr,"Cannot open %s\n",out_path); return 3;}

  long pos=ftell(fi); char hdr[256];
  if(fgets(hdr,sizeof hdr,fi)){ if(strstr(hdr,"time")==NULL) fseek(fi,pos,SEEK_SET); } else { fclose(fi); fclose(fo); return 0; }

  write_header(fo);
  Inputs in; EcmState st={0,0,0,0}; int t=0;
  while(read_inputs_csv_line(fi,&in)){
    clamp_inputs(&in);
    scr000001_ignition(&in,&st,&C);
    fprintf(fo,"%d,%d,%d,%d,%d,%d,%d,%d\n", t, in.ignition_switch, in.acc_pedal_position, in.brake_pedal_position,
            in.current_gear, st.engine_state, st.engine_speed, st.engine_stall);
    t++;
  }
  fclose(fi); fclose(fo); return 0;
}
