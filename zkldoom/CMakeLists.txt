function(process_circuit example_target)
    set(prefix ARG)
    set(noValues "")
    set(singleValues INPUT)
    set(multiValues SOURCES)
    cmake_parse_arguments(${prefix}
                        "${noValues}"
                        "${singleValues}"
                        "${multiValues}"
                        ${ARGN})
    add_circuit(${example_target}
                SOURCES ${ARG_SOURCES}

                LINK_LIBRARIES
#                crypto3::algebra
#                crypto3::block
#                crypto3::codec
#                crypto3::containers
#                crypto3::hash
#                crypto3::kdf
#                crypto3::mac
#                marshalling::core
#                marshalling::crypto3_algebra
#                marshalling::crypto3_multiprecision
#                marshalling::crypto3_zk
#                crypto3::math
#                crypto3::modes
#                crypto3::multiprecision
#                crypto3::passhash
#                crypto3::pbkdf
#                crypto3::threshold
#                crypto3::pkpad
#                crypto3::pubkey
#                crypto3::random
#                crypto3::stream
#                crypto3::vdf
#                crypto3::zk

                ${Boost_LIBRARIES})
endfunction()

process_circuit(zkldoom SOURCES z_main.c doomgeneric_dr.c doomgeneric.c d_main.c 
                z_zone.c i_system.c
                d_loop.c i_video.c g_game.c doomstat.c d_net.c m_controls.c r_sky.c m_menu.c p_inter.c 
                tables.c p_setup.c p_saveg.c r_main.c m_argv.c 
                d_items.c st_lib.c am_map.c 
                p_spec.c
                info.c
                p_plats.c p_floor.c p_doors.c p_ceilng.c p_lights.c p_switch.c
                d_think.c
                p_mobj.c
                p_pspr.c
                p_tick.c
                p_enemy.c
                r_segs.c p_map.c p_maputl.c 
                p_sight.c 
                m_misc.c
                r_data.c
                p_user.c
                p_enemy.c
INPUT test-input.json)
