//
// Created by PL on 2022/8/2.
//
#ifndef PBC_SETUP_H
#define PBC_SETUP_H
#include "../../pbc/include/pbc.h"

/*
 * RBITS is the modulo of the ring Zr, secret key length in bits
 * QBITS is the modulo of G in bits, also points coordinate length in bits on ec curve
 * only use BITS when using Type F Internals (Barreto and Naehrig, BN256 Curve), where QBITS=RBITS=BITS
 */

#define RBITS 160
#define QBITS 512
#define BITS 160
#define ELEMENT_STRING_LENGTH 512 // In bytes, both G1, Zr, GT
#define PARAM_BUFFER_LENGTH_TYPE_A 370 // empirically tested minimal buffer space to store a param string
#define SIGNATURE_LENGTH 148 // 128+20
#define DEBUG_MODE 0 // set to 1 to trigger debug mode and see my commented internal variable prints, TODO

/*
 * Public params for global use (in local device or server)
 * Initialized in this order
 */

pairing_t p;
pbc_param_t par;
char * par_param_buffer;
element_t g; // generator, also is P in Al-Riyami-Patterson03 paper
element_t masterPublicKey, masterPrivateKey; // master priv/pub key
element_t P0; // P0

/*
 * Public params for transmission between device and server
 */
struct params {
    // PICK UP FROM HERE: make sure these are all necessary params, and marshall them for transmission
    char par_param_buffer[PARAM_BUFFER_LENGTH_TYPE_A];
    char g[ELEMENT_STRING_LENGTH];
    char P0[ELEMENT_STRING_LENGTH]; // also is masterPubKey
} param;

void setup();
void init_global_public_params();
void set_public_param_transmission_buffer();
void setup_with_param_buffer(char * par_param_buffer, int len);
void init_test();
void FreeElements(pairing_t p);
char * extract_pairing_param_buffer_from_file();

char * simpleSHA256(const unsigned char * message, int len);
char * string_times_G2_to_Zr_SHA256(const unsigned char * message, element_t r);

// char * marshall_all_params_to_buffer(struct params param);

#endif //PBC_SETUP_H
