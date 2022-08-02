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

- I am implementing certless signature.