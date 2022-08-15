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

    // First time pairing param init with NO inputs, server side only
    pbc_param_init_a_gen(par, RBITS ,QBITS); // Type A curve produces symmetric pairing, a necessity for Al-Riyami-Patterson03.
    pairing_init_pbc_param(p, par);
    if (!pairing_is_symmetric(p)) pbc_die("Al-Riyami-Patterson03 scheme requires a symmetric pairing, exiting.");

    /*
     * Type F curve (Barreto and Naehrig 256) has shorter signature/key length, good for IoT. Not yet applicable for Al-Riyami-Patterson03, leave for future work.
     * pbc_param_init_f_gen(par, BITS);
     */

    // pairing param write to file (backup)
    FILE *fp;
    fp = fopen("pairing_params.txt", "wr+");
    pbc_param_out_str(fp, par);
    fclose(fp);

    par_param_buffer = extract_pairing_param_buffer_from_file();
    init_global_public_params();
    set_public_param_transmission_struct();

    return;
}

void init_global_public_params(){

    // generator init, g is also P in Al-Riyami-Patterson03 paper
    element_init_G1(g, p);
    element_random(g);

    // master pub/priv keygen
    element_init_Zr(masterPrivateKey, p);
    element_init_G1(masterPublicKey, p);
    element_random(masterPrivateKey); // How to securely store this after deployment?
    element_pow_zn(masterPublicKey, g, masterPrivateKey);

    element_init_G1(P0, p);
    element_set(P0, masterPublicKey);
    // master pub/priv keygen complete

    return;
}

void set_public_param_transmission_struct(){
    // set struct params param for C-NodeJS I/O

    char * g_string = malloc(ELEMENT_STRING_LENGTH);
    char * P0_string = malloc(ELEMENT_STRING_LENGTH);
    element_snprint(g_string, ELEMENT_STRING_LENGTH, g);
    element_snprint(P0_string, ELEMENT_STRING_LENGTH, P0);

    // UNSTABLE BUG: the size of element_string (element convert to string, like P0_string) is not stable.

    strcpy(param.par_param_buffer, par_param_buffer);
    strcpy(param.g, g_string);
    strcpy(param.P0, P0_string);
}

void setup_with_param_buffer(char * par_param_buffer, int len){
    pairing_init_set_buf(p, par_param_buffer, len);
    init_global_public_params();
    set_public_param_transmission_struct();
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

void init_test(){
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

char * simpleSHA256(const unsigned char * message, int len){
    unsigned char * hash = malloc(SHA256_DIGEST_LENGTH+1);
    SHA256(message, len, hash);
    return (char *) hash;
}

char * string_times_G2_to_Zr_SHA256(const unsigned char * message, element_t r){

    char * r_string = malloc(ELEMENT_STRING_LENGTH);
    element_snprint(r_string, ELEMENT_STRING_LENGTH, r);

    unsigned char * hash = malloc(SHA256_DIGEST_LENGTH+1);
    unsigned char * hash1 = malloc(SHA256_DIGEST_LENGTH+1);
    unsigned char * hash2 = malloc(SHA256_DIGEST_LENGTH+1);

    memset(hash, 0, SHA256_DIGEST_LENGTH+1);
    memset(hash1, 0, SHA256_DIGEST_LENGTH+1);
    memset(hash2, 0, SHA256_DIGEST_LENGTH+1);

    SHA256((const unsigned char *) message, strlen((char *) message), hash1);
    SHA256((const unsigned char *) r_string, strlen(r_string), hash2);

    unsigned char * prehash = malloc(SHA256_DIGEST_LENGTH*2);
    memset(prehash, 0, SHA256_DIGEST_LENGTH*2);

    strcat((char *)prehash, (char *)hash1);
    strcat((char *)prehash, (char *)hash2);

    SHA256((const unsigned char *) (prehash), strlen((char *)prehash), hash);

    return (char *) hash;
}