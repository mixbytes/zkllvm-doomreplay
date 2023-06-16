#!/bin/bash

# Stop execution if any step returns non-zero (non success) status
set -e


ASSIGNER_BINARY=${HOME}/zkllvm/build/bin/assigner/assigner
CLANG_BINARY=${HOME}/zkllvm/build/libs/circifier/llvm/bin/clang


WORKDIR=${HOME}/zkllvm-doomreplay
BUILD_DIR=${WORKDIR}/zkbuild
CCT=main

if [ ${#BUILD_DIR} -lt 1 ]; then 
    echo "BUILD_DIR var is empty, exiting";
    exit 2;
fi
echo "Removing previous build dir ./$BUILD_DIR to create new empty"
rm -rf ./$BUILD_DIR
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

set -x


cd ${WORKDIR}/zkldoom

# -S used when CIRCUIT_ASSEMBLY_OUTPUT

${CLANG_BINARY} -target assigner \
    -Xclang -no-opaque-pointers \
    -Xclang -fpreserve-vec3-type \
    -std=c99 \
    -emit-llvm -O1 -S \
    -I${HOME}/zkllvm/libs/stdlib/libc/include \
    -I${HOME}/zkllvm/libs/stdlib/libcpp \
    -I${HOME}/zkllvm/libs/crypto3/algebra/include \
    -I${HOME}/zkllvm/build/include \
    -I${HOME}/zkllvm/libs/blueprint/include \
    -I${HOME}/zkllvm/libs/crypto3/block/include -I${HOME}/zkllvm/libs/crypto3/codec/include -I${HOME}/zkllvm/libs/crypto3/containers/include -I${HOME}/zkllvm/libs/crypto3/hash/include -I${HOME}/zkllvm/libs/crypto3/kdf/include -I${HOME}/zkllvm/libs/crypto3/mac/include -I${HOME}/zkllvm/libs/crypto3/marshalling/core/include -I -I${HOME}/zkllvm/libs/crypto3/marshalling/algebra/include -I${HOME}/zkllvm/libs/crypto3/marshalling/multiprecision/include -I${HOME}/zkllvm/libs/crypto3/marshalling/zk/include -I${HOME}/zkllvm/libs/crypto3/math/include -I${HOME}/zkllvm/libs/crypto3/modes/include -I${HOME}/zkllvm/libs/crypto3/multiprecision/include -I${HOME}/zkllvm/libs/crypto3/passhash/include -I${HOME}/zkllvm/libs/crypto3/pbkdf/include -I${HOME}/zkllvm/libs/crypto3/pkmodes/include -I${HOME}/zkllvm/libs/crypto3/pkpad/include -I${HOME}/zkllvm/libs/crypto3/pubkey/include -I${HOME}/zkllvm/libs/crypto3/random/include -I${HOME}/zkllvm/libs/crypto3/stream/include -I${HOME}/zkllvm/libs/crypto3/vdf/include -I${HOME}/zkllvm/libs/crypto3/zk/include \
    -D__ZKLLVM__ \
    -o ${BUILD_DIR}/${CCT}.ll \
    ./z_main.c

exit

echo "2" > ${BUILD_DIR}/${CCT}.inp
echo "4" >> ${BUILD_DIR}/${CCT}.inp

${ASSIGNER_BINARY} \
    -b ${BUILD_DIR}/${CCT}.ll \
    -i ${BUILD_DIR}/${CCT}.inp \
    -t ${BUILD_DIR}/${CCT}.tbl \
    -c ${BUILD_DIR}/${CCT}.crct \
    -e pallas

python3 ${HOME}/proof-market-toolchain/scripts/prepare_statement.py \
    -c ${BUILD_DIR}/${CCT}.crct \
    -o ${BUILD_DIR}/${CCT}.json \
    -n ${CCT} -t placeholder-zkllvm # help="statement type: placeholder-zkllvm or placeholder-vanilla",


# docker exec proof-market /proof-market-toolchain/build/bin/proof-generator/proof-generator \
#    --proof_out=${BUILD_DIR}/${CCT}_proof.json \
#    --circuit_input=${BUILD_DIR}/${CCT}.json \
#    --public_input=${BUILD_DIR}/${CCT}.inp

ls -la ${BUILD_DIR}

set +x
exit 

# ${CLANG_BINARY} -target assigner -Xclang -no-opaque-pointers -Xclang -fpreserve-vec3-type -std=c++20 -D__ZKLLVM__ -I${HOME}/zkllvm/libs/crypto3/algebra/include -I${HOME}/zkllvm/build/include -I/usr/local/include -I -I${HOME}/zkllvm/libs/crypto3/block/include -I/usr/local/include -I${HOME}/zkllvm/libs/blueprint/include -I${HOME}/zkllvm/libs/crypto3/codec/include -I${HOME}/zkllvm/libs/crypto3/containers/include -I${HOME}/zkllvm/libs/crypto3/hash/include -I${HOME}/zkllvm/libs/crypto3/kdf/include -I${HOME}/zkllvm/libs/crypto3/mac/include -I${HOME}/zkllvm/libs/crypto3/marshalling/core/include -I -I${HOME}/zkllvm/libs/crypto3/marshalling/algebra/include -I${HOME}/zkllvm/libs/crypto3/marshalling/multiprecision/include -I${HOME}/zkllvm/libs/crypto3/marshalling/zk/include -I${HOME}/zkllvm/libs/crypto3/math/include -I${HOME}/zkllvm/libs/crypto3/modes/include -I${HOME}/zkllvm/libs/crypto3/multiprecision/include -I${HOME}/zkllvm/libs/crypto3/passhash/include -I${HOME}/zkllvm/libs/crypto3/pbkdf/include -I${HOME}/zkllvm/libs/crypto3/pkmodes/include -I${HOME}/zkllvm/libs/crypto3/pkpad/include -I${HOME}/zkllvm/libs/crypto3/pubkey/include -I${HOME}/zkllvm/libs/crypto3/random/include -I${HOME}/zkllvm/libs/crypto3/stream/include -I${HOME}/zkllvm/libs/crypto3/vdf/include -I${HOME}/zkllvm/libs/crypto3/zk/include -I${HOME}/zkllvm/libs/stdlib/libcpp -I${HOME}/zkllvm/libs/stdlib/libc/include -emit-llvm -O1 -S -o ${BUILD_DIR}/poseidon.ll ${BUILD_DIR}/poseidon.cpp
