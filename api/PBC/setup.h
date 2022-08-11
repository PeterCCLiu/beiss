//
// Created by PL on 2022/8/2.
//
#ifndef PBC_SETUP_H
#define PBC_SETUP_H
#define RBITS 160 // rbits is the modulo of the ring Zr, secret key length in bits
#define QBITS 512 // qbits is the modulo of G in bits, points coordinate length in bits on ec curve
#define BITS 160 // only use when using Type F Internals (Barreto and Naehrig, BN256 Curve), where BITS=RBITS=QBITS
//#define K 160 // k is the system security parameter, usually secret key length in bits, BITS=K, omitted, use BITS directly.

element_t g; // generator
element_t masterPublicKey, masterPrivateKey; // master priv/pub key
element_t P0; // P0
pbc_param_t par; // pairing params
pairing_t p; // pairing object
FILE *fp; // file stream instance
void setup();
void init_test();

#endif //PBC_SETUP_H
