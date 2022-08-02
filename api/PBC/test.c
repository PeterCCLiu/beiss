// Boneh-Lynn-Shacham short signatures demo.
//
// See the PBC_sig library for a practical implementation.
//
// Ben Lynn
#include "../../pbc/include/pbc.h"
#include "../../pbc/include/pbc_test.h"

int main(int argc, char **argv) {
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
    return 0;
}
