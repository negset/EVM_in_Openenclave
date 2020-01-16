A runnable demo that combines Miscrosoft eEVM and OpenEnclave in Ubuntu18.04 Intel SGX

Based on [Miscrosoft eEVM](https://github.com/microsoft/eEVM), I modified the code of eEVM to solve the compatibility problems while running in an [OpenEnclave](https://github.com/openenclave/openenclave). 

## To set up the environments
- OS: Ubuntu 18.04 (Ubuntu 16.04 untested)
- refer to [this](https://github.com/openenclave/openenclave/blob/master/docs/GettingStartedDocs/install_oe_sdk-Ubuntu_18.04.md) to install Openenclave SDK.

## Build by CMake

- step1: clone the source code:
> git clone https://github.com/liangyihuai/EVM_in_Openenclave.git

- step2: compile the source code:
> cd EVM_in_Openenclave

> mkdir build

> cd build

> cmake ..

- step3: compile and execute the main function:
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
## One more thing
Current version of this repository does not ure the source code [rlp](https://github.com/liangyihuai/EVM_in_Openenclave/blob/master/enclave/eEVM/rlp.h) that belongs to eEVM. Because eEVM in C++ 17, and OpenEnclave in C and C++ 14. 

If it is very necessary for you to use it  [rlp](https://github.com/liangyihuai/EVM_in_Openenclave/blob/master/enclave/eEVM/rlp.h), you can follow this to modify the source code.

- step1: before compiling the source code of Openenclave, add this comment to its CMakeLists.txt file. 
> set(CMAKE_CXX_STANDARD 17)

- step2: 
recover this source code: [rlp](https://github.com/liangyihuai/EVM_in_Openenclave/blob/master/enclave/eEVM/rlp.h), and recover the function `generate_address` in [utils.cpp](https://github.com/liangyihuai/EVM_in_Openenclave/blob/master/enclave/eEVM/util.cpp) with the below code.
```
Address generate_address(const Address& sender, uint64_t nonce)
  {
    const auto rlp_encoding = rlp::encode(sender, nonce);

    uint8_t buffer[32u];

      keccak_256(
        rlp_encoding.data(),
        static_cast<unsigned int>(rlp_encoding.size()),
        buffer);

    return from_big_endian(buffer + 12u, 20u);
  }
```


