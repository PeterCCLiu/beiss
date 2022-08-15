#include "setup.h"
__attribute__((export_name("writer")))
int writeBuffer(char * s){
    strcpy(public_param_transmission_buffer, s);
    return 0;
}