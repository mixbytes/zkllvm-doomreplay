#---------------------------------------------------------------------------#
# Copyright (c) 2018-2022 Mikhail Komarov <nemo@nil.foundation>
# Copyright (c) 2020-2022 Nikita Kaskov <nbering@nil.foundation>
# Copyright (c) 2022 Mikhail Aksenov <maksenov@nil.foundation>
#
# Distributed under the Boost Software License, Version 1.0
# See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt
#---------------------------------------------------------------------------#
include(CMakePrintHelpers)


function(add_circuit name)
    set(prefix ARG)
    set(noValues "")
    set(singleValues)
    set(multiValues SOURCES INCLUDE_DIRECTORIES LINK_LIBRARIES)
    cmake_parse_arguments(${prefix}
                          "${noValues}"
                          "${singleValues}"
                          "${multiValues}"
                          ${ARGN})

    if(NOT ARG_SOURCES)
        message(FATAL_ERROR "SOURCES for ${name} circuit was not defined")
    endif()

    foreach(source ${ARG_SOURCES})
        if(NOT IS_ABSOLUTE ${include_dir})
            list(APPEND CIRCUIT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
        else()
            list(APPEND CIRCUIT_SOURCES "${source}")
        endif()
    endforeach()
    list(REMOVE_DUPLICATES CIRCUIT_SOURCES)

    foreach(ITR ${CIRCUIT_SOURCES})
        if(NOT EXISTS ${ITR})
            message(SEND_ERROR "Cannot find circuit source file: ${source}")
        endif()
    endforeach()

    


    set(INCLUDE_DIRS_LIST "")
    # Collect include directories from dependencies first
    foreach(lib ${ARG_LINK_LIBRARIES})
        get_target_property(lib_include_dirs ${lib} INTERFACE_INCLUDE_DIRECTORIES)
        foreach(dir ${lib_include_dirs})
            list(APPEND INCLUDE_DIRS_LIST "-I${dir}")
        endforeach()
    endforeach()
    # Add passed include directories
    foreach(include_dir ${ARG_INCLUDE_DIRECTORIES})
        if(NOT IS_ABSOLUTE ${include_dir})
            set(include_dir "${CMAKE_CURRENT_SOURCE_DIR}/${include_dir}")
        endif()
        list(APPEND INCLUDE_DIRS_LIST "-I${include_dir}")
    endforeach()

    # add stdlib from zkllvm for Doom
    list(APPEND INCLUDE_DIRS_LIST -I${CMAKE_SOURCE_DIR}/../zkllvm/libs/stdlib/libc/include)
    list(REMOVE_DUPLICATES INCLUDE_DIRS_LIST)

    

    set(CIRCUIT_ASSEMBLY_OUTPUT 1)
    if(CIRCUIT_ASSEMBLY_OUTPUT)
        set(extension ll)
        set(format_option -S)
        list(APPEND link_options "-S")
    else()
        set(extension bc)
        set(format_option -c)
    endif()


    # set(ZKLLVM_DIR zkllvm) # to change between Release and Debug versions
    set(ZKLLVM_DIR tmp/zkLLVM) # to change between Release and Debug versions
    
    # TEMP (to use different self-compiled parts of zkllvm)
    set(CLANG ${CMAKE_SOURCE_DIR}/../${ZKLLVM_DIR}/build/libs/circifier/llvm/bin/clang)
    set(LIBC_STDLIB_LL ${CMAKE_SOURCE_DIR}/../${ZKLLVM_DIR}/build/libs/stdlib/libc/zkllvm-libc.ll)
    set(LINKER ${CMAKE_SOURCE_DIR}/../${ZKLLVM_DIR}/build/libs/circifier/llvm/bin/llvm-link)
    set(ASSIGNER ${CMAKE_SOURCE_DIR}/../${ZKLLVM_DIR}/build/bin/assigner/assigner)
    set(TEST_INPUT_JSON ${CMAKE_SOURCE_DIR}/zkldoom/test-input.json)
    set(STATEMENT_PREPARE ${CMAKE_SOURCE_DIR}/../proof-market-toolchain/scripts/prepare_statement.py)
    set(PROVER ${CMAKE_SOURCE_DIR}/../proof-market-toolchain/build/bin/proof-generator/proof-generator)
    
    #if (ZKLLVM_DEV_ENVIRONMENT)
    #    set(CLANG $<TARGET_FILE:clang>)
    #    set(LINKER $<TARGET_FILE:llvm-link>)
    #else()
    #    set(CLANG clang)
    #    set(LINKER llvm-link)
    #endif()

    # Compile sources
    set(compiler_outputs "")
    add_custom_target(${name}_compile_sources)
    foreach(source ${CIRCUIT_SOURCES})
        get_filename_component(source_base_name ${source} NAME)
        add_custom_target(${name}_${source_base_name}_${extension}
                        COMMAND ${CLANG} 
                        -target assigner 
                        -Xclang -fpreserve-vec3-type

                        -Wno-deprecated-non-prototype
                        -Wno-macro-redefined
                        -Wno-excess-initializers
                        -Wno-multichar
                        -std=c17
                        -D__ZKLLVM__
                        ${INCLUDE_DIRS_LIST}
                        -emit-llvm -O1 
                        ${format_option}
                        -o ${source_base_name}.${extension}
                        ${source}

                        VERBATIM COMMAND_EXPAND_LISTS

                        SOURCES ${source})
        add_dependencies(${name}_compile_sources ${name}_${source_base_name}_${extension})
        list(APPEND compiler_outputs "${source_base_name}.${extension}")
    endforeach()

    # Link sources

    # [NOTE] we include pre-compiled ${LIBC_STDLIB_LL} to avoid duplicate
    # stdlib functions in multiple .ll files

    add_custom_target(${name}_link_sources
                      DEPENDS ${name}_compile_sources
                      COMMAND ${LINKER}
                      ${link_options}
                      -o ${name}.ll
                      ${compiler_outputs}
                      ${LIBC_STDLIB_LL}
                      VERBATIM COMMAND_EXPAND_LISTS)

    
    add_custom_target(${name}_run_assigner
                      DEPENDS ${name}_link_sources
                      COMMAND
                      ${ASSIGNER}
                      -b ${name}.${extension}
                      -i ${TEST_INPUT_JSON}
                      -t ${name}.tbl
                      -c ${name}.crct
                      -e pallas
                      --verbose
                      
                      VERBATIM COMMAND_EXPAND_LISTS
                      )
                      # --check
    
    add_custom_target(${name}_run_prepare_statement
                      DEPENDS ${name}_run_assigner
                      COMMAND 
                      python3 ${STATEMENT_PREPARE} 
                      -c ${name}.${extension}
                      -o ${name}-statement.json
                      -n ${name}
                      -t placeholder-zkllvm
                      --public
                      
                      VERBATIM COMMAND_EXPAND_LISTS
                      )

    add_custom_target(${name}_run_prover
                      DEPENDS ${name}_run_prepare_statement
                      COMMAND 
                      ${PROVER}
                      --circuit_input=${name}-statement.json
                      --public_input=${TEST_INPUT_JSON}
                      --proof_out=${name}-proof.bin
                      VERBATIM COMMAND_EXPAND_LISTS
                      )




endfunction(add_circuit)

#function(add_circuit_assignable)
#    #list(POP_FRONT ARGV circuit_name)
#    #list(PREPEND ARGV ${circuit_name}_no_stdlib)
#    add_circuit(${ARGV})
#
#    set(LINKER ${CMAKE_SOURCE_DIR}/../zkllvm/build/libs/circifier/llvm/bin/llvm-link)
#    set(link_options "-opaque-pointers=0;-S")
#    set(libc_stdlib ${CMAKE_SOURCE_DIR}/../zkllvm/build/libs/stdlib/libc/zkllvm-libc.ll)
#
#    add_custom_target(${circuit_name}
#                      COMMAND ${LINKER} ${link_options} -o ${circuit_name}.ll ${circuit_name}_no_stdlib.ll ${libc_stdlib}
#                      DEPENDS ${circuit_name}_no_stdlib
#                      VERBATIM COMMAND_EXPAND_LISTS)
#endfunction()
