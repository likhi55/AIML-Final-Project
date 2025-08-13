#ifndef CALIBRATION_H
#define CALIBRATION_H
typedef struct {
    int idle_rpm;
    int idle_gain;
} Calib;
void calib_defaults(Calib* c);
int  calib_load_from_file(Calib* c, const char* path);
#endif
