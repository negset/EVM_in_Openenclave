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

If it is very necessary to use it  [rlp](https://github.com/liangyihuai/EVM_in_Openenclave/blob/master/enclave/eEVM/rlp.h), you can follow this to modify the source code.

- step1: before compiling the source code of Openenclave, add this comment to its CMakeLists.txt file. 
> set(CMAKE_CXX_STANDARD 17)

- step2: 
recover this source code: [rlp](https://github.com/liangyihuai/EVM_in_Openenclave/blob/master/enclave/eEVM/rlp.h), and replace [utils.cpp]() with the below code.

```
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "util.h"

#include "rlp.h"

#include <iomanip>

using namespace std;

namespace eevm
{
  string strip(const string& s)
  {
    return (s.size() >= 2 && s[1] == 'x') ? s.substr(2) : s;
  }

  uint64_t to_uint64(const std::string& s)
  {
    return strtoull(s.c_str(), nullptr, 16);
  }

  vector<uint8_t> to_bytes(const string& _s)
  {
    auto s = strip(_s);

    const size_t byte_len = (s.size() + 1) / 2; // round up
    vector<uint8_t> v(byte_len);

    // Handle odd-length strings
    size_t n = 0;
    if (s.size() % 2 != 0)
    {
      v[0] = static_cast<uint8_t>(strtoul(s.substr(0, 1).c_str(), nullptr, 16));
      ++n;
    }

    auto x = n;
    for (auto i = n; i < byte_len; ++i, x += 2)
    {
      v[i] = static_cast<uint8_t>(strtoul(s.substr(x, 2).c_str(), nullptr, 16));
    }
    return v;
  }

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
} // namespace eevm

```
