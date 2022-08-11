# This project uses PBC

What is PBC? 

- PBC is Paring-Based Crypto Library implemented by Ben Lynn from Stanford.

Why do we use PBC?

- It provides reliable pairing primitive implementation which we can build on.

What are our value-adds?

- We are a JS-based wrapper and implementation. Future devs can use our lib to directly achieve IBE and IB-signature in Node.js environment. 

What now?

- I implemented BLS signature in playground.c, try it with
``` 
    cd /Users/pl/beiss/api/PBC
    make && ./playground
```

What next?

- I am implementing certificateless cryptosystem according to [Boneh-Franklin03](https://crypto.stanford.edu/~dabo/papers/bfibe.pdf) IBE Signature and [Al-Riyami-Patterson03](https://eprint.iacr.org/2003/126.pdf) certificateless cryptosystem.

Status?
- Server-side crypto OK: KGC setup, partial-private-key extract, some tests, completed.

Next?
- IoT side crypto: other half generation, secure transmission (SSL/TLS), registration to KGC/blockchain. 
- Deployment to cloud of choice. mongo and blockchain stuff
- Docs