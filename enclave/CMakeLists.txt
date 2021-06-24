# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License.

# Use the edger8r to generate C bindings from the EDL file.
add_custom_command(
  OUTPUT helloworld_t.h helloworld_t.c helloworld_args.h
  DEPENDS ${CMAKE_SOURCE_DIR}/helloworld.edl
  COMMAND
    openenclave::oeedger8r --trusted ${CMAKE_SOURCE_DIR}/helloworld.edl
    --search-path ${OE_INCLUDEDIR} --search-path
    ${OE_INCLUDEDIR}/openenclave/edl/sgx)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib")

#link_directories("/home/liang/ethereumwork/eEVM/build/")
#link_libraries("/home/liang/ethereumwork/eEVM/build/")
#link_libraries(eevm)

aux_source_directory(${CMAKE_SOURCE_DIR}/enclave/eEVM  EEVM_SOURCE1)
aux_source_directory(${CMAKE_SOURCE_DIR}/enclave/eEVM/simple EEVM_SIMPLE_SOURCE)
aux_source_directory(${CMAKE_SOURCE_DIR}/enclave/eEVM/fmt 3RD_PARTY_FMT)
aux_source_directory(${CMAKE_SOURCE_DIR}/enclave/eEVM/intx/lib/intx 3RD_PARTY_INTX1)
aux_source_directory(${CMAKE_SOURCE_DIR}/enclave/eEVM/intx/include/intx 3RD_PARTY_INTX2)
aux_source_directory(${CMAKE_SOURCE_DIR}/enclave/eEVM/keccak 3RD_PARTY_KECCAK)
aux_source_directory(${CMAKE_SOURCE_DIR}/enclave/eEVM/nlohmann 3RD_PARTY_NLOHMANN)


add_executable(enclave enc.c ${CMAKE_CURRENT_BINARY_DIR}/helloworld_t.c
        wrapper.c wrapper.h util.h
        ${CMAKE_SOURCE_DIR}/enclave/eEVM/intx/include/intx/intx.hpp
        ${EEVM_SOURCE1}
        ${EEVM_SIMPLE_SOURCE}
        ${3RD_PARTY_FMT}
        ${3RD_PARTY_INTX1}
        ${3RD_PARTY_INTX2}
        ${3RD_PARTY_KECCAK}
        ${3RD_PARTY_NLOHMANN}
        Greeting.cpp Greeting.h SumTest.cpp SumTest.h)

if (WIN32)
  maybe_build_using_clangw(enclave)
endif ()

target_compile_definitions(enclave PUBLIC OE_API_VERSION=2)

# Need for the generated file helloworld_t.h
target_include_directories(enclave PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

#target_include_directories(enclave
#        PRIVATE
#        /home/liang/ethereumwork/eEVM/include
#        /home/liang/ethereumwork/eEVM/3rdparty
#        /home/liang/ethereumwork/eEVM/3rdparty/intx/include
#        )

#TARGET_LINK_LIBRARIES(enclave libeevm.a)

#target_link_libraries(enclave /home/liang/ethereumwork/eEVM/build/libeevm.a)

target_link_libraries(enclave openenclave::oeenclave openenclave::oecrypto${OE_CRYPTO_LIB} openenclave::oelibc openenclave::oelibcxx)



