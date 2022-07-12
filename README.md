# BEISS
Blockchain-enabled IoT Security Suite

## How to use: (for now)
```sh
cd api
npm run devStart
browser: localhost:3000/healthcheck
```

TODOS:
- docker:
  - docker-compose file `build:`
  - `dockerfile` 
    - brew install: LLVM, wasm2wat
  - docker image registry and publish
- mongo:
  - Define schema, collection, db
  - CRUD
- frontend:
  - HTML boilerplate, CSS
  - React (use template)

## Other Dependencies:
This project (inevitably) uses C/C++ code. 
Therefore we compile *.c &rarr; *.wasm &rarr; JS module.

- [LLVM clang](https://shareup.app/blog/compiling-c-to-wasm/): *.c &rarr; *.wasm (compile when building docker image)
- WebAssembly: *.wasm &rarr; JS module (runtime async)

## Known issues:
-[_fixed_] In local testing, `fetch` a local *.wasm file is prohibited and will cause a CORS error that looks like this:
```
TypeError [ERR_INVALID_URL]: Invalid URL
```
This is due to security concerns and is caused by Chrome. See [this link](https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS/Errors/CORSRequestNotHttp) and [this](https://developer.mozilla.org/en-US/docs/Learn/Common_questions/set_up_a_local_testing_server) for solution.

Fix: See [commit](cd13ddc97e45cbf223b509ec1c5580ccceaebd0f)