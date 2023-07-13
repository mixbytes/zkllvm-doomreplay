#!/bin/bash

# Stop execution if any step returns non-zero (non success) status
set -e


CLANG_BINARY=${HOME}/zkllvm/build/libs/circifier/llvm/bin/clang
LLVM_LINKER_BINARY=${HOME}/zkllvm/build/libs/circifier/llvm/bin/llvm-link
ASSIGNER_BINARY=${HOME}/zkllvm/build/bin/assigner/assigner

ZKLLVM_VERSION=0.0.58
TOOLCHAIN_VERSION=0.0.31

WORKDIR=${HOME}/zkllvm-doomreplay
BUILD_DIR=${WORKDIR}/zkbuild
CCT=main
cd ${WORKDIR}

if [ ${#BUILD_DIR} -lt 1 ]; then 
    echo "BUILD_DIR var is empty, exiting";
    exit 2;
fi
echo "Removing previous build dir ./$BUILD_DIR to create new empty"
rm -rf $BUILD_DIR
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

set -x


# -S used when CIRCUIT_ASSEMBLY_OUTPUT
# -O0 - no optimizations, allow to be sure that even non-used parts of code are compiled


#    -I${HOME}/zkllvm/libs/crypto3/block/include -I${HOME}/zkllvm/libs/crypto3/codec/include -I${HOME}/zkllvm/libs/crypto3/containers/include -I${HOME}/zkllvm/libs/crypto3/hash/include -I${HOME}/zkllvm/libs/crypto3/kdf/include -I${HOME}/zkllvm/libs/crypto3/mac/include -I${HOME}/zkllvm/libs/crypto3/marshalling/core/include -I -I${HOME}/zkllvm/libs/crypto3/marshalling/algebra/include -I${HOME}/zkllvm/libs/crypto3/marshalling/multiprecision/include -I${HOME}/zkllvm/libs/crypto3/marshalling/zk/include -I${HOME}/zkllvm/libs/crypto3/math/include -I${HOME}/zkllvm/libs/crypto3/modes/include -I${HOME}/zkllvm/libs/crypto3/multiprecision/include -I${HOME}/zkllvm/libs/crypto3/passhash/include -I${HOME}/zkllvm/libs/crypto3/pbkdf/include -I${HOME}/zkllvm/libs/crypto3/pkmodes/include -I${HOME}/zkllvm/libs/crypto3/pkpad/include -I${HOME}/zkllvm/libs/crypto3/pubkey/include -I${HOME}/zkllvm/libs/crypto3/random/include -I${HOME}/zkllvm/libs/crypto3/stream/include -I${HOME}/zkllvm/libs/crypto3/vdf/include -I${HOME}/zkllvm/libs/crypto3/zk/include \
#    -I${HOME}/zkllvm/libs/blueprint/include \
#    -I${HOME}/zkllvm/libs/crypto3/algebra/include \
#    -I${HOME}/zkllvm/libs/stdlib/libcpp \
#    -I${HOME}/zkllvm/build/include \
    #-I/usr/local/include \

cd ${BUILD_DIR}

${CLANG_BINARY} -target assigner \
    -Xclang -no-opaque-pointers \
    -Xclang -fpreserve-vec3-type \
    -std=c99 \
    -emit-llvm -O0 -S \
    -I${HOME}/zkllvm/libs/stdlib/libc/include \
    -D__ZKLLVM__ \
    -o ${BUILD_DIR}/${CCT}.ll \
    ../zkldoom/z_main.c
   

#${LLVM_LINKER_BINARY} \
#    -opaque-pointers=0 \
#    -o ${BUILD_DIR}/${CCT}.ll \
#    ${BUILD_DIR}/z_main.ll ${BUILD_DIR}/d_main.ll



#
#    -I${HOME}/zkllvm/libs/stdlib/libc/include \
#    -I${HOME}/zkllvm/build/include \
#    -I/usr/local/include \

# run zkllvm in docker
#docker run --rm -it --platform=linux/amd64 --user $(id -u ${USER}):$(id -g ${USER}) --volume ${WORKDIR}:${WORKDIR} --name myzkllvm myzkllvm


#docker exec  \
#   --workdir ${WORKDIR} \
#   myzkllvm \
#   /usr/bin/clang \
#    -target assigner \
#    -Xclang -no-opaque-pointers \
#    -Xclang -fpreserve-vec3-type \
#    -std=c99 \
#    -emit-llvm -O1 -S \
#    -D__ZKLLVM__ \
#    -o ${BUILD_DIR}/${CCT}.ll \
#    ${WORKDIR}/zkldoom/z_main.c

# --detach

#echo "[{\"int\": 4, \"int\": 5}]" > ${BUILD_DIR}/${CCT}.inp

echo "[{\"int\": \"118\"}, {\"int\": \"42\"}]" > ${BUILD_DIR}/${CCT}.inp.json
# echo "4" > ${BUILD_DIR}/${CCT}.inp

cat ${BUILD_DIR}/${CCT}.inp.json

${ASSIGNER_BINARY} \
    -b ${BUILD_DIR}/${CCT}.ll \
    -i ${BUILD_DIR}/${CCT}.inp.json \
    -t ${BUILD_DIR}/${CCT}.tbl \
    -c ${BUILD_DIR}/${CCT}.crct \
    -e pallas \
    --check

#head -n 5 ${BUILD_DIR}/${CCT}.tbl

exit 0


#docker exec  \
#   --workdir ${WORKDIR} \
#   myzkllvm \
#   assigner \
#    -b ${BUILD_DIR}/${CCT}.ll \
#    -i ${BUILD_DIR}/${CCT}.inp \
#    -t ${BUILD_DIR}/${CCT}.tbl \
#    -c ${BUILD_DIR}/${CCT}.crct \
#    -e pallas




# run proof market in docker
# docker run --rm -it --platform=linux/amd64 --user $(id -u ${USER}):$(id -g ${USER}) --volume ${WORKDIR}:${WORKDIR} --name myproofmkt myproofmkt

#docker exec \
#   --workdir ${WORKDIR} \
#   myproofmkt \
#   python3 /proof-market-toolchain/scripts/prepare_statement.py \
#     -c ${BUILD_DIR}/${CCT}.ll \
#     -o ${BUILD_DIR}/${CCT}.json \
#     -n ${CCT} -t placeholder-zkllvm # help="statement type: placeholder-zkllvm or placeholder-vanilla",


#python3 ${HOME}/proof-market-toolchain/scripts/prepare_statement.py \
#    -c ${BUILD_DIR}/${CCT}.ll \
#    -o ${BUILD_DIR}/${CCT}.json \
#    -n ${CCT} -t placeholder-zkllvm # help="statement type: placeholder-zkllvm or placeholder-vanilla",


#docker exec \
#   --workdir ${WORKDIR} \
#   myproofmkt \
#   /proof-market-toolchain/build/bin/proof-generator/proof-generator \
#   --proof_out=${BUILD_DIR}/${CCT}.proof \
#   --circuit_input=${BUILD_DIR}/${CCT}.json \
#   --public_input=${BUILD_DIR}/${CCT}.inp.json


#ls -la ${BUILD_DIR}

set +x

exit 
