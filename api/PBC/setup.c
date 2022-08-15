//
// Created by PL on 2022/8/2.
// Based on Boneh-Franklin03 and Al-Riyami-Patterson03.
//
#include "../../pbc/include/pbc.h"
#include "string.h"
#include "setup.h"
#include <openssl/sha.h>

// Generate params and master pub/priv keys

void setup(pairing_t p, pbc_param_t par){

    // pairing param init
    pbc_param_init_a_gen(par, RBITS ,QBITS); // Type A curve produces symmetric pairing, a necessity for Al-Riyami-Patterson03.
    pairing_init_pbc_param(p, par);
    if (!pairing_is_symmetric(p)) pbc_die("Al-Riyami-Patterson03 scheme requires a symmetric pairing, exiting.");

    /*
     * Type F curve (Barreto and Naehrig 256) has shorter signature/key length, good for IoT. Not yet applicable for Al-Riyami-Patterson03, leave for future work.
     * pbc_param_init_f_gen(par, BITS);
     */

    // pairing param output
    FILE *fp;
    fp = fopen("pairing_params.txt", "wr+");
    pbc_param_out_str(fp, par);
    fclose(fp);
    // pairing param init complete, check in pairing_params.txt

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

void setup_with_param_buffer(pairing_t p, char * par_param_buffer, int len){
    pairing_init_set_buf(p, par_param_buffer, len);

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

char * extract_pairing_param_buffer_from_file(){
    char * par_param_buffer = malloc(PARAM_BUFFER_LENGTH_TYPE_A);
    FILE *fp;
    fp = fopen("pairing_params.txt", "r");
    fread(par_param_buffer, PARAM_BUFFER_LENGTH_TYPE_A, 1, fp);
    fclose(fp);

    puts("Your par_param_buffer is: ");
    puts(par_param_buffer);

    return par_param_buffer;
}

void init_test(pairing_t p){
    // printf("Your length in bits to represent a G1 element is = %d\n", pairing_length_in_bytes_G1(p));
    printf("Is pairing is symmetric, 1 is symmetric? : %d\n", pairing_is_symmetric(p));

    // TODO: Your pairing is ready...? Output system parameters (eventually public)
    // TODO: This param needs public transmission. Find out least necessary params to transmit.

    element_printf("Your generator g is %B\n", g);
    element_printf("Your master sk is = %B\n", masterPrivateKey);
    element_printf("Your master pk is = %B\n", masterPublicKey);

    printf("Your master sk element_length_in_bytes is = %d\n", element_length_in_bytes(masterPrivateKey));
    printf("Your master pk element_length_in_bytes is = %d\n", element_length_in_bytes(masterPublicKey));

    printf("Your pairing_length_in_bytes_G1(p) is = %d\n", pairing_length_in_bytes_G1(p));
    printf("Your pairing_length_in_bytes_G2(p) is = %d\n", pairing_length_in_bytes_G2(p));
    printf("Your pairing_length_in_bytes_compressed_G1(p) is = %d\n", pairing_length_in_bytes_compressed_G1(p));
    printf("Your pairing_length_in_bytes_compressed_G2(p) is = %d\n", pairing_length_in_bytes_compressed_G2(p));
    printf("Your pairing_length_in_bytes_x_only_G1(p) is = %d\n", pairing_length_in_bytes_x_only_G1(p));
    printf("Your pairing_length_in_bytes_x_only_G2(p) is = %d\n", pairing_length_in_bytes_x_only_G2(p));
    printf("Your pairing_length_in_bytes_GT(p) is = %d\n", pairing_length_in_bytes_GT(p));
    printf("Your pairing_length_in_bytes_Zr(p) is = %d\n", pairing_length_in_bytes_Zr(p));


    // PBC_ASSERT(!(element_length_in_bytes(masterPublicKey)==pairing_length_in_bytes_G1(p)), "Your master pk element_length_in_bytes is correct");
    // Enable when in debug mode only: add #define PBC_DEBUG

    // TODO: Your (master) secret key is ready...? Output master secret key (eventually private)
    // TODO: really need some polishing

}


void FreeElements(pairing_t p){
    element_free(g);
    element_free(P0);
    element_free(masterPublicKey);
    element_free(masterPrivateKey);

    pairing_clear(p);
}