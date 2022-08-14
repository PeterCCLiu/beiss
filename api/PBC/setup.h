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
#define PARAM_BUFFER_LENGTH_TYPE_A 362 // empirically tested minimal buffer space to store a param string
#define SIGNATURE_LENGTH 148 // 128+20
#define DEBUG_MODE 0 // set to 1 to trigger debug mode and see my commented internal variable prints, TODO

/*
 * Public params for global visibility
 */

element_t g; // generator, also is P in Al-Riyami-Patterson03 paper
element_t masterPublicKey, masterPrivateKey; // master priv/pub key
element_t P0; // P0

/*
 * Use only basic data structures, since it needs I/O
 */
struct params {
    char par_param_buffer[PARAM_BUFFER_LENGTH_TYPE_A];
    char g[QBITS];
    char P0[QBITS]; // masterPubKey
};

void setup(pairing_t p, pbc_param_t par);
void setup_with_param_buffer(pairing_t p, char * par_param_buffer, int len);
void init_test(pairing_t p);
void FreeElements(pairing_t p);
char * extract_pairing_param_buffer();

#endif //PBC_SETUP_H
