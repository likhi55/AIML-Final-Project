#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calibration.h"

void calib_defaults(Calib* c) { c->idle_rpm = 700; c->idle_gain = 20; }

static int parse_kv(const char* line, char* k, char* v){
  const char* e = strchr(line,'='); if(!e) return 0;
  size_t kl=(size_t)(e-line), vl=strlen(e+1);
  while(kl && (line[kl-1]==' '||line[kl-1]=='\t')) kl--;
  while(vl && ((e[1+vl-1]=='\n')||(e[1+vl-1]=='\r')||(e[1+vl-1]==' '))) vl--;
  strncpy(k,line,kl); k[kl]='\0'; strncpy(v,e+1,vl); v[vl]='\0'; return 1;
}

int calib_load_from_file(Calib* c, const char* path){
  FILE* f=fopen(path,"r"); if(!f) return 0; char ln[128],k[64],v[64];
  while(fgets(ln,sizeof ln,f)){
    if(ln[0]=='#'||ln[0]=='\n'||ln[0]=='\r') continue;
    if(!parse_kv(ln,k,v)) continue;
    if(!strcmp(k,"idle_rpm"))  c->idle_rpm  = atoi(v);
    else if(!strcmp(k,"idle_gain")) c->idle_gain = atoi(v);
  }
  fclose(f); return 1;
}
