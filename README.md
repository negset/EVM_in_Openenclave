A runnable demo that combines Miscrosoft eEVM and OpenEnclave in Ubuntu18.04 Intel SGX

Based on [Miscrosoft eEVM](https://github.com/microsoft/eEVM), I modified the code of eEVM to solve the compatibility problems while running in an [OpenEnclave](https://github.com/openenclave/openenclave). 

## To set up the environments
- OS: Ubuntu 18.04 (Ubuntu 16.04 untested)
- refer to [this](https://github.com/openenclave/openenclave/blob/master/docs/GettingStartedDocs/install_oe_sdk-Ubuntu_18.04.md) to install Openenclave SDK.

## Build by CMake

clone the source code:
> git clone https://github.com/liangyihuai/EVM_in_Openenclave.git

compile the source code:
> cd EVM_in_Openenclave

> mkdir build

> cd build

> cmake ..

compile and execute the main function:
> make run

## Output of this demo

```
Hello world from the enclave
Hello world from wrapHelloWorld1
Hello world from Greeting
Hello world!
Hello world from Greeting2
Test SUMTest
sum result = 
0x7
Enclave called into host to print: Hello World!
```

One issue needs to fix:
I did not use this source code of eEVM. [rlp](https://github.com/liangyihuai/EVM_in_Openenclave/blob/master/enclave/eEVM/rlp.h)

