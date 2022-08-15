#include "setup.h"
__attribute__((export_name("reader")))
char * readBuffer(){
    return public_param_transmission_buffer;
}