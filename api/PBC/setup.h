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
#define ELEMENT_STRING_LENGTH 1024 // In bytes, both G1, Zr, GT
#define DEBUG_MODE 0 // set to 1 to trigger debug mode and see my commented internal variable prints, TODO

/*
 * Public params for global visibility
 */

element_t g; // generator, also is P in Al-Riyami-Patterson03 paper
element_t masterPublicKey, masterPrivateKey; // master priv/pub key
element_t P0; // P0
pbc_param_t par; // pairing params
pairing_t p; // pairing object

void setup();
void init_test();
void FreeElements();

#endif //PBC_SETUP_H
