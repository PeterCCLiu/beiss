//
// Created by PL on 2022/8/2.
//
#include "../../pbc/include/pbc.h"
#include "../../pbc/include/pbc_test.h"
#include "string.h"
#include "setup.h"
#include <openssl/sha.h>
#include <stdbool.h>

// KGC does
char ** ExtractPartialPrivateKey(void * ID){
    unsigned char * hash = (unsigned char *) malloc(SHA256_DIGEST_LENGTH);
    SHA256(ID, strlen(ID), hash);
    int hashlen = strlen((char *) hash);
//    printf("Your hash is = %s\n", hash);
//    printf("Your hashlen is = %d\n", hashlen);

    element_t QA;
    element_init_G1(QA, p);
    element_from_hash(QA, hash, hashlen);
    element_printf("Your correct QA is = %B\n", QA);

    element_t DA;
    element_init_G1(DA, p);
    element_pow_zn(DA, QA, masterPrivateKey);
    element_printf("Your correct DA is = %B\n", DA);

    free(hash);
//    element_free(QA); // error exist

    char * QA_string = (char *) malloc(100000000);
    element_snprint(QA_string, 100000000, QA);
    puts(QA_string);

    char * DA_string = (char *) malloc(100000000);
    element_snprint(DA_string, 100000000, DA);
    puts(DA_string);

    char ** output = (char **) malloc(sizeof(QA_string)+sizeof(DA_string));
    output[0] = QA_string;
    output[1] = DA_string;
    return output;
}

// also a transmission. leave this to Node.js
// KGC does finish

// IoT device does

int VerifyPartialPrivateKeyIsCorrect(char ** PartialPrivateKeyParams){

    element_t QA;
    element_init_G1(QA, p);
    element_set_str(QA, PartialPrivateKeyParams[0], 10); // why is base=10, idk
    element_printf("Your QA after transmission in Verify is = %B\n", QA);

    element_t DA;
    element_init_G1(DA, p);
    element_set_str(DA, PartialPrivateKeyParams[1], 10);
    element_printf("Your DA after transmission in Verify is = %B\n", DA);

    element_t result1, result2;
    element_init_GT(result1, p);
    element_init_GT(result2, p);

    element_pairing(result1, DA, g);
    element_pairing(result2, QA, P0);

    int result = element_cmp(result1, result2);
    printf("Your partial secret verification result is = %d, 0 if Partial Secret is correctly generated\n", result);

    return 0;
}

char * SetSecretValue(char * ID){
    char * xA;
    return xA;
}

char * SetPrivateKey(char * xA, char * ID){
    char * SA;
    return SA;
}

char * SetPublicKey(char * xA){
    char * PA;
    return PA;
}

void RegisterPublicKey(char * PA){
    return;
}

int Sign(char * message, char * ID){
    return 0;
}

int Verify(char * signature, char * ID){
    return 0;
}
// IoT device finish

int main(int argc, char *argv[]){

    setup();
    init_test();

    void * ID = "00111101111111111110000000011111111";

    char ** PartialPrivateKeyParams = ExtractPartialPrivateKey(ID);
    // printf("Your PartialPrivateKey is = %s\n", PartialPrivateKey);

    // puts((char *) PartialPrivateKey[0]);
    // puts((char *) PartialPrivateKey[1]);
    // puts((char *) ID);

    element_t QA;
    element_init_G1(QA, p);
    element_set_str(QA, PartialPrivateKeyParams[0], 10); // why is base=10, idk
    element_printf("Your QA after transmission is = %B\n", QA);

    element_t DA;
    element_init_G1(DA, p);
    element_set_str(DA, PartialPrivateKeyParams[1], 10);
    element_printf("Your DA after transmission is = %B\n", DA);

    VerifyPartialPrivateKeyIsCorrect(PartialPrivateKeyParams);

    return 0;
}

