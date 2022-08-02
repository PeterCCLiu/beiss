// Boneh-Lynn-Shacham short signatures demo.
//
// See the PBC_sig library for a practical implementation.
//
// Ben Lynn
#include "../../pbc/include/pbc.h"
#include "string.h"
// #include "../../pbc/include/pbc_test.h"


int main() {

    // test gmp
    mpz_t op1, op2;
    unsigned one = 1, two = 2;
    mpz_inits(op1, op2);

    mpz_set_ui(op1, one);
    mpz_set_ui(op2, two);

    gmp_printf("%Zd\n", op1);
    gmp_printf("%Zd\n", op2);

    printf("These two mpz integers are equal to each other = %d\n", !mpz_cmp(op2, op1));

    // BLS signature test implementation:
    // Init pairing
    element_t g, h, sig; // Generator
    pairing_t p;
    pbc_param_t par;
    pbc_param_init_a_gen(par, 160, 512); // example params. why?
    pairing_init_pbc_param(p, par);

    element_init_G1(g, p); // element_init functions assign algebraic structures
    element_init_G1(h, p);
    element_init_G1(sig, p);
    element_random(g);

    element_printf("Generator g1 is %B\n", g);
    element_printf("Another element is %B\n", h);

    // pbc_param_clear(par);

    // key generation
    element_t sk, pk;
    element_init_Zr(sk, p); // Zr means the ring of integers modulo.
    // Why not use pbc_mpz_random() since it's integer anyway? Maybe it's bad practice.
    element_init_G1(pk, p);

    element_random(sk);

    element_printf("sk is %B\n", sk);

    element_pow_zn(pk, g, sk);

    element_printf("pk is %B\n", pk);

    // message
    const char * _msg = "You use BLS Signature";
    const void * message = _msg;
    const int len = strlen(message);
    printf("Your message is = %s\n", (char *) message);
    element_from_hash(h, message, len);

    element_printf("Message hash is %B\n", h);

    element_pow_zn(sig, h, sk);

    element_printf("Signature is %B\n", sig);

    // Verify

    element_t res_1, res_2;
    element_init_GT(res_1, p);
    element_init_GT(res_2, p);

    element_pairing(res_1, sig, g);
    element_pairing(res_2, h, pk);

    element_printf("Your verification left is = %B\n", res_1);
    element_printf("Your verification right is = %B\n", res_2);

    element_printf("Your verification result is = %d\n", !element_cmp(res_1, res_2));
    //element_cmp returns 0 if equals.

    // PICK UP FROM HERE: VERIFY SIGNATURE, SEE bls.c and Wikipedia

    // printf("Pairing is symmetric ?= %d\n", pairing_is_symmetric(p));

    // mpz_clears(op1, op2); // returns a segmentation fault, why?
    return 0;
}
