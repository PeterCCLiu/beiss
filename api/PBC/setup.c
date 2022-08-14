//
// Created by PL on 2022/8/2.
// Based on Boneh-Franklin03 and Al-Riyami-Patterson03.
//
#include "../../pbc/include/pbc.h"
#include "string.h"
#include "setup.h"
#include <openssl/sha.h>

// Generate params and master pub/priv keys

void setup(){

    // pairing param init
    pbc_param_init_a_gen(par, RBITS ,QBITS); // Type A curve produces symmetric pairing, a necessity for Al-Riyami-Patterson03.
    pairing_init_pbc_param(p, par);
    if (!pairing_is_symmetric(p)) pbc_die("pairing must be symmetric");

    /*
     * Type F curve (Barreto and Naehrig 256) has shorter signature/key length, good for IoT. Not yet applicable for Al-Riyami-Patterson03, leave for future work.
     * pbc_param_init_f_gen(par, BITS);
     */

    // pairing param output
    FILE *fp;
    fp = fopen("pairing_params.txt", "wr+");
    pbc_param_out_str(fp, par);
    fclose(fp);
    // pairing param init complete, check in params.txt

    // generator init
    element_init_G1(g, p);
    element_random(g);
    // generator init complete

    // master pub/priv keygen
    element_init_Zr(masterPrivateKey, p);
    element_init_G1(masterPublicKey, p);

    element_random(masterPrivateKey); // How to securely store this after deployment?
    element_pow_zn(masterPublicKey, g, masterPrivateKey);

    element_init_G1(P0, p);
    element_set(P0, masterPublicKey);
    // master pub/priv keygen complete
}

void init_test(){
    // printf("Your length in bits to represent a G1 element is = %d\n", pairing_length_in_bytes_G1(p));
    printf("Is pairing is symmetric, 1 is symmetric? : %d\n", pairing_is_symmetric(p));

    // TODO: Your pairing is ready...? Output system parameters (eventually public)
    // TODO: This param needs public transmission. Find out least necessary params to transmit.

    element_printf("Your generator g is %B\n", g);
    element_printf("Your master sk is = %B\n", masterPrivateKey);
    element_printf("Your master pk is = %B\n", masterPublicKey);

    printf("Your master pk element_length_in_bytes is = %d\n", element_length_in_bytes(masterPrivateKey));
    printf("Your master pk element_length_in_bytes is = %d\n", element_length_in_bytes(masterPublicKey));

    // PBC_ASSERT(!(element_length_in_bytes(masterPublicKey)==pairing_length_in_bytes_G1(p)), "Your master pk element_length_in_bytes is correct");
    // Enable when in debug mode only: add #define PBC_DEBUG

    // TODO: Your (master) secret key is ready...? Output master secret key (eventually private)
    // TODO: really need some polishing

}


void FreeElements(){
    element_free(g);
    element_free(P0);
    element_free(masterPublicKey);
    element_free(masterPrivateKey);

    pairing_clear(p);
}