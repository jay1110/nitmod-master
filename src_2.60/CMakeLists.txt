cmake_minimum_required(VERSION 3.20)
project(nitmod_260 C CXX)

include(CTest)

# This is intentionally separate from the historical SCons build.  It builds
# the same source tree as native ET modules or as Emscripten SIDE_MODULEs.
option(NITMOD_BUILD_CGAME "Build cgame" ON)
option(NITMOD_BUILD_QAGAME "Build qagame" ON)
option(NITMOD_BUILD_UI "Build ui" ON)
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(nitmod_default_arch "i386")
else()
    set(nitmod_default_arch "${CMAKE_SYSTEM_PROCESSOR}")
endif()
set(NITMOD_ARCH "${nitmod_default_arch}" CACHE STRING "ET module architecture suffix")
include("${CMAKE_CURRENT_SOURCE_DIR}/../tools/cmake/ModuleArtifactName.cmake")

if(EMSCRIPTEN)
    set(NITMOD_ARCH "wasm32" CACHE STRING "ET module architecture suffix" FORCE)
    # Permit real SIDE_MODULE linking before creating MODULE targets.
    set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)
    find_package(Python3 COMPONENTS Interpreter REQUIRED)
endif()

option(NITMOD_REQUIRE_LINUX_I386 "Reject a non-i386 Linux release toolchain" OFF)
include("${CMAKE_CURRENT_SOURCE_DIR}/../tools/cmake/ValidateLinuxI386.cmake")
nitmod_validate_linux_i386()
if(NITMOD_REQUIRE_LINUX_I386)
    include(CheckCSourceCompiles)
    # Do not let an earlier compiler/flag combination satisfy a new probe.
    unset(NITMOD_COMPILER_IS_LINUX_I386 CACHE)
    check_c_source_compiles("
        #include <limits.h>
        #if !defined(__linux__) || !defined(__i386__)
        #error Linux i386 compiler required
        #endif
        typedef char abi_sizes[(CHAR_BIT == 8 && sizeof(int) == 4 &&
            sizeof(long) == 4 && sizeof(void *) == 4 && sizeof(float) == 4) ? 1 : -1];
        int main(void) { return 0; }
    " NITMOD_COMPILER_IS_LINUX_I386)
    if(NOT NITMOD_COMPILER_IS_LINUX_I386)
        message(FATAL_ERROR "Compiler does not satisfy the native Linux-i386 data model")
    endif()
endif()

set(NITMOD_SHARED_GAME
    game/nitmod_weapon_reload_feedback.c
    game/bg_animation.c game/bg_animgroup.c game/bg_character.c
    game/bg_classes.c game/bg_misc.c game/bg_pmove.c game/bg_slidemove.c
    game/bg_sscript.c game/bg_stats.c game/bg_tracemap.c
    game/q_math.c game/q_shared.c game/nitmod_announcements.c game/nitmod_protocol.c
    game/nitmod_snapshots.c game/nitmod_skills.c game/nitmod_weapon_recoil.c
    game/nitmod_weapon_defaults.c game/nitmod_weapon_consumption.c
    game/nitmod_weapon_akimbo.c game/nitmod_weapon_clip.c game/nitmod_weapon_inventory.c game/nitmod_weapon_reload.c)

function(nitmod_module target base_name define)
    nitmod_artifact_name("${base_name}" artifact_name artifact_suffix)
    add_library(${target} MODULE ${ARGN})
    if(WIN32 AND NOT EMSCRIPTEN)
        target_sources(${target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../tools/cmake/nitmod_windows.def")
    endif()
    target_compile_definitions(${target} PRIVATE ${define}=1)
    target_include_directories(${target} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/game"
        "${CMAKE_CURRENT_SOURCE_DIR}/cgame"
        "${CMAKE_CURRENT_SOURCE_DIR}/ui"
        "${CMAKE_CURRENT_SOURCE_DIR}/omnibot/common"
        "${CMAKE_CURRENT_SOURCE_DIR}/omnibot/et")
    set_target_properties(${target} PROPERTIES
        PREFIX ""
        SUFFIX "${artifact_suffix}"
        OUTPUT_NAME "${artifact_name}"
        C_STANDARD 90
        C_STANDARD_REQUIRED ON)
    if(EMSCRIPTEN)
        # Required for independently loadable ET modules: cgame and ui expose
        # many same-named trap functions, so their internal symbols must stay
        # out of Emscripten's process-wide dynamic-symbol table.
        target_compile_options(${target} PRIVATE -fvisibility=hidden)
        target_link_options(${target} PRIVATE -sSIDE_MODULE=1)
        target_link_options(${target} PRIVATE "LINKER:--fatal-warnings")
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tools/verify_wasm_module.py" "$<TARGET_FILE:${target}>"
            VERBATIM)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        # Native modules use libm directly; engine traps use dllEntry's
        # function pointer, not unresolved ELF imports from the executable.
        target_link_libraries(${target} PRIVATE m)
        target_link_options(${target} PRIVATE "LINKER:--no-undefined")
    endif()
endfunction()

if(NITMOD_BUILD_CGAME)
    set(NITMOD_CGAME_SRC
        game/nitmod_weapon_paths.c
        cgame/cg_atmospheric.c cgame/cg_character.c cgame/cg_commandmap.c
        cgame/cg_consolecmds.c cgame/cg_debriefing.c cgame/cg_draw.c
        cgame/cg_drawtools.c cgame/cg_effects.c cgame/cg_ents.c cgame/cg_event.c
        cgame/cg_fireteamoverlay.c cgame/cg_fireteams.c cgame/cg_flamethrower.c
        cgame/cg_info.c cgame/cg_limbopanel.c cgame/cg_loadpanel.c
        cgame/cg_localents.c cgame/cg_main.c cgame/cg_nitmod.c
        cgame/cg_nitmod_config.c cgame/cg_nitmod_key.c cgame/cg_nitmod_debug.c cgame/cg_nitmod_autoexec.c cgame/cg_nitmod_animation.c cgame/cg_nitmod_lean.c cgame/cg_nitmod_ammo.c cgame/cg_nitmod_hud.c cgame/cg_nitmod_log.c cgame/cg_nitmod_locations.c cgame/cg_nitmod_hints.c cgame/cg_nitmod_names.c cgame/cg_nitmod_events.c cgame/cg_nitmod_obituary.c cgame/cg_nitmod_stats.c cgame/cg_nitmod_mapvote.c cgame/cg_marks.c cgame/cg_missionbriefing.c
        cgame/cg_multiview.c cgame/cg_newDraw.c cgame/cg_particles.c
        cgame/cg_nitmod_skill_rewards.c
        cgame/cg_nitmod_weapon_pose.c
        cgame/cg_nitmod_view.c
        cgame/cg_players.c cgame/cg_playerstate.c cgame/cg_polybus.c
        cgame/cg_popupmessages.c cgame/cg_predict.c cgame/cg_scoreboard.c cgame/cg_nitmod_scoreboard.c cgame/cg_nitmod_projectiles.c
        cgame/cg_servercmds.c cgame/cg_snapshot.c cgame/cg_sound.c
        cgame/cg_spawn.c cgame/cg_statsranksmedals.c cgame/cg_syscalls.c
        cgame/cg_trails.c cgame/cg_view.c cgame/cg_weapons.c cgame/cg_window.c)
    list(APPEND NITMOD_CGAME_SRC cgame/cg_nitmod_coronas.c)
    nitmod_module(cgame cgame CGAMEDLL ${NITMOD_CGAME_SRC} ${NITMOD_SHARED_GAME} ui/ui_shared.c)
endif()

if(NITMOD_BUILD_QAGAME)
    set(NITMOD_BOTAI_SRC
        botai/ai_cmd.c botai/ai_dmgoal_mp.c botai/ai_dmnet_mp.c botai/ai_dmq3.c
        botai/ai_main.c botai/ai_script.c botai/ai_script_actions.c botai/ai_team.c)
    set(NITMOD_QAGAME_SRC
        game/nitmod_weapon_reload_feedback.c
        game/bg_animation.c game/bg_animgroup.c game/bg_campaign.c game/bg_character.c
        game/bg_classes.c game/bg_misc.c game/bg_pmove.c game/bg_slidemove.c
        game/bg_sscript.c game/bg_stats.c game/bg_tracemap.c game/g_active.c
        game/g_alarm.c game/g_antilag.c game/g_bot.c game/g_buddy_list.c
        game/g_character.c game/g_client.c game/g_cmds.c game/g_cmds_ext.c
        game/g_combat.c game/g_config.c game/g_fireteams.c game/g_items.c
        game/g_main.c game/g_match.c game/g_mem.c game/g_misc.c game/g_missile.c
        game/g_mover.c game/g_multiview.c game/g_nitmod_config.c game/g_props.c
        game/g_referee.c game/g_save.c game/g_script.c game/g_script_actions.c
        game/g_session.c game/g_spawn.c game/g_stats.c game/g_sv_entities.c
        game/g_svcmds.c game/g_syscalls.c game/g_systemmsg.c game/g_target.c
        game/g_team.c game/g_teammapdata.c game/g_trigger.c game/g_utils.c
        game/g_vote.c game/g_weapon.c game/q_math.c game/q_shared.c
        game/nitmod_announcements.c game/nitmod_spree.c game/nitmod_config_index.c
        game/nitmod_config_store.c game/nitmod_protocol.c game/nitmod_entity_array.c
        game/g_nitmod_entities.c game/g_nitmod_map_cleanup.c game/g_nitmod_mine_sweep.c
        game/g_nitmod_satchel_free.c
        game/g_nitmod_satchel_die.c
        game/g_nitmod_weapon_damage.c
        game/g_nitmod_mine_contact.c
        game/nitmod_bot_handle.c
        game/g_nitmod_bot_entities.c
        game/g_nitmod_air.c game/nitmod_air.c game/g_nitmod_score.c game/nitmod_score.c game/nitmod_skills.c
        game/g_nitmod_abilities.c game/g_nitmod_adrenaline_grant.c game/g_nitmod_weapons.c game/g_nitmod_war.c
        game/g_nitmod_restrictions.c game/g_nitmod_teamcount.c game/g_nitmod_equipment.c
        game/g_nitmod_rifle.c game/nitmod_weapon_limits.c game/g_nitmod_weapon_policy.c
        game/g_nitmod_weapon_config.c game/g_nitmod_legacy_cvars.c game/g_nitmod_banners.c game/g_nitmod_omnibot.c game/g_nitmod_weapon_adapter.c game/g_nitmod_class_command.c game/g_nitmod_campaign_vote.c game/g_nitmod_team_vote.c game/g_nitmod_mapvote.c game/g_nitmod_surrender.c
        game/g_nitmod_etbot_interface.cpp omnibot/common/BotLoadLibrary.cpp
        game/g_nitmod_loadout.c game/g_nitmod_pickup.c game/nitmod_weapon_definition.c game/g_nitmod_canister.c game/g_nitmod_poison.c
        game/g_nitmod_weapon_definition.c game/g_nitmod_weapon_registry.c
        game/nitmod_weapon_paths.c game/nitmod_weapon_recoil.c game/nitmod_weapon_defaults.c
        game/nitmod_weapon_consumption.c game/nitmod_weapon_akimbo.c game/nitmod_weapon_clip.c game/nitmod_weapon_inventory.c game/nitmod_weapon_reload.c)
    nitmod_module(qagame qagame GAMEDLL ${NITMOD_QAGAME_SRC} ${NITMOD_BOTAI_SRC})
endif()

if(NITMOD_BUILD_UI)
    set(NITMOD_UI_SRC
        ui/ui_atoms.c ui/ui_gameinfo.c ui/ui_loadpanel.c ui/ui_main.c ui/ui_nitmod_actions.c ui/ui_nitmod_catalog.c ui/ui_nitmod_campaign.c ui/ui_nitmod_settings.c
        ui/ui_nitmod_status.c
        ui/ui_nitmod_search.c
        ui/ui_nitmod_browser.c
        ui/ui_nitmod_description.c
        ui/ui_players.c ui/ui_shared.c ui/ui_syscalls.c ui/ui_util.c)
    nitmod_module(ui ui UIDLL ${NITMOD_UI_SRC}
        game/bg_campaign.c game/bg_classes.c game/bg_misc.c game/q_math.c game/q_shared.c
        game/nitmod_weapon_akimbo.c)
endif()

if(BUILD_TESTING)
    if(TARGET cgame AND NOT CMAKE_CROSSCOMPILING)
        get_target_property(nitmod_charge_client_sources cgame SOURCES)
        add_executable(nitmod_original_charge_dispatch_test ../tests/test_original_charge_dispatch.c ${nitmod_charge_client_sources})
        target_include_directories(nitmod_original_charge_dispatch_test PRIVATE game cgame ui)
        target_compile_definitions(nitmod_original_charge_dispatch_test PRIVATE CGAMEDLL=1)
        if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
            target_link_libraries(nitmod_original_charge_dispatch_test PRIVATE m)
        endif()
        add_test(NAME nitmod_original_charge_dispatch COMMAND nitmod_original_charge_dispatch_test
            "${CMAKE_CURRENT_SOURCE_DIR}/../pak/animations/scripts/human_base.script"
            "${CMAKE_CURRENT_SOURCE_DIR}/../pak")
    endif()
    if(TARGET ui AND NOT CMAKE_CROSSCOMPILING)
        get_target_property(nitmod_ui_test_sources ui SOURCES)
        add_executable(nitmod_ui_bitflag_test ../tests/test_nitmod_ui_bitflag.c ${nitmod_ui_test_sources})
        target_include_directories(nitmod_ui_bitflag_test PRIVATE game cgame ui)
        target_compile_definitions(nitmod_ui_bitflag_test PRIVATE UIDLL=1)
        target_compile_definitions(nitmod_ui_bitflag_test PRIVATE NITMOD_GAMEINFO_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../pak/gameinfo.txt")
        if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
            target_link_libraries(nitmod_ui_bitflag_test PRIVATE m)
        endif()
        add_test(NAME nitmod_ui_bitflag COMMAND nitmod_ui_bitflag_test)
    endif()
    if(NOT CMAKE_CROSSCOMPILING)
        find_program(NITMOD_NODE_EXECUTABLE NAMES node node.exe)
        if(NITMOD_NODE_EXECUTABLE)
            add_test(NAME nitmod_wasm_import_audit COMMAND ${NITMOD_NODE_EXECUTABLE}
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_wasm_import_audit.cjs")
        endif()
    endif()
    if(NOT CMAKE_CROSSCOMPILING)
        add_executable(nitmod_module_load_contract_test ../tests/test_module_load_contract.c)
        set_target_properties(nitmod_module_load_contract_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_module_load_contract COMMAND nitmod_module_load_contract_test)
        if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT EMSCRIPTEN)
            add_executable(nitmod_linux_module_load_test ../tests/test_linux_module_load.c)
            target_link_libraries(nitmod_linux_module_load_test PRIVATE ${CMAKE_DL_LIBS})
            set_target_properties(nitmod_linux_module_load_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
            set(nitmod_load_paths)
            foreach(module IN ITEMS cgame qagame ui)
                if(TARGET ${module})
                    add_dependencies(nitmod_linux_module_load_test ${module})
                    list(APPEND nitmod_load_paths "$<TARGET_FILE:${module}>")
                    add_test(NAME nitmod_load_${module} COMMAND nitmod_linux_module_load_test "$<TARGET_FILE:${module}>")
                endif()
            endforeach()
            if(nitmod_load_paths)
                add_test(NAME nitmod_load_together COMMAND nitmod_linux_module_load_test ${nitmod_load_paths})
            endif()
        endif()
        add_executable(nitmod_weapon_source_test ../tests/test_nitmod_weapon_source.c
            game/g_nitmod_weapon_definition.c game/nitmod_weapon_definition.c game/nitmod_protocol.c
            game/nitmod_weapon_paths.c)
        target_include_directories(nitmod_weapon_source_test PRIVATE game)
        set_target_properties(nitmod_weapon_source_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_source COMMAND nitmod_weapon_source_test)
        add_executable(nitmod_weapon_paths_test ../tests/test_nitmod_weapon_paths.c
            game/nitmod_weapon_paths.c)
        target_include_directories(nitmod_weapon_paths_test PRIVATE game)
        set_target_properties(nitmod_weapon_paths_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_paths COMMAND nitmod_weapon_paths_test)
        add_executable(nitmod_weapon_definition_test ../tests/test_nitmod_weapon_definition.c
            game/nitmod_weapon_definition.c game/nitmod_protocol.c)
        target_include_directories(nitmod_weapon_definition_test PRIVATE game)
        set_target_properties(nitmod_weapon_definition_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_definition COMMAND nitmod_weapon_definition_test)
        add_executable(nitmod_weapon_ammo_test ../tests/test_nitmod_weapon_ammo.c
            game/nitmod_weapon_definition.c game/nitmod_protocol.c)
        target_include_directories(nitmod_weapon_ammo_test PRIVATE game)
        set_target_properties(nitmod_weapon_ammo_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_ammo COMMAND nitmod_weapon_ammo_test)
        add_executable(nitmod_weapon_parser_bounds_test ../tests/test_nitmod_weapon_parser_bounds.c
            game/nitmod_weapon_definition.c game/nitmod_protocol.c)
        target_include_directories(nitmod_weapon_parser_bounds_test PRIVATE game)
        set_target_properties(nitmod_weapon_parser_bounds_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_parser_bounds COMMAND nitmod_weapon_parser_bounds_test)
        add_executable(nitmod_weapon_recoil_test ../tests/test_nitmod_weapon_recoil.c
            game/nitmod_weapon_recoil.c game/nitmod_weapon_definition.c game/nitmod_protocol.c)
        target_include_directories(nitmod_weapon_recoil_test PRIVATE game)
        set_target_properties(nitmod_weapon_recoil_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        if(NOT MSVC)
            target_link_libraries(nitmod_weapon_recoil_test PRIVATE m)
        endif()
        add_test(NAME nitmod_weapon_recoil COMMAND nitmod_weapon_recoil_test)
        add_executable(nitmod_weapon_recoil_source_test ../tests/test_nitmod_weapon_recoil_source.c
            game/nitmod_weapon_reload.c game/nitmod_weapon_inventory.c game/nitmod_weapon_akimbo.c
            game/g_nitmod_weapon_definition.c game/g_nitmod_weapon_registry.c game/nitmod_weapon_paths.c
            game/nitmod_weapon_recoil.c game/nitmod_weapon_definition.c game/nitmod_protocol.c
            game/nitmod_weapon_defaults.c game/g_nitmod_abilities.c game/g_nitmod_adrenaline_grant.c)
        target_include_directories(nitmod_weapon_recoil_source_test PRIVATE game)
        set_target_properties(nitmod_weapon_recoil_source_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        if(NOT MSVC)
            target_link_libraries(nitmod_weapon_recoil_source_test PRIVATE m)
        endif()
        add_test(NAME nitmod_weapon_recoil_source COMMAND nitmod_weapon_recoil_source_test)
        add_executable(nitmod_weapon_consumption_test ../tests/test_nitmod_weapon_consumption.c
            game/nitmod_weapon_consumption.c)
        target_include_directories(nitmod_weapon_consumption_test PRIVATE game)
        set_target_properties(nitmod_weapon_consumption_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_consumption COMMAND nitmod_weapon_consumption_test)
        add_executable(nitmod_weapon_clip_test ../tests/test_nitmod_weapon_clip.c
            game/nitmod_weapon_akimbo.c game/nitmod_weapon_clip.c game/nitmod_weapon_consumption.c)
        target_include_directories(nitmod_weapon_clip_test PRIVATE game)
        set_target_properties(nitmod_weapon_clip_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_clip COMMAND nitmod_weapon_clip_test)
        add_executable(nitmod_native_weapon_aliases ../tests/dump_native_weapon_aliases.c
            game/nitmod_weapon_defaults.c
            ../tests/test_nitmod_reload_begin.c
            game/nitmod_weapon_reload_feedback.c
            ../tests/test_nitmod_weapon_reload.c
            game/nitmod_weapon_reload.c
            game/bg_misc.c game/nitmod_weapon_akimbo.c game/q_shared.c game/q_math.c
            game/nitmod_weapon_clip.c game/nitmod_weapon_consumption.c game/nitmod_weapon_inventory.c)
        target_compile_definitions(nitmod_native_weapon_aliases PRIVATE GAMEDLL=1)
        target_include_directories(nitmod_native_weapon_aliases PRIVATE game)
        set_target_properties(nitmod_native_weapon_aliases PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        if(NOT MSVC)
            target_link_libraries(nitmod_native_weapon_aliases PRIVATE m)
        endif()
        add_executable(nitmod_pickup_test ../tests/test_nitmod_pickup.c game/g_nitmod_pickup.c)
        target_include_directories(nitmod_pickup_test PRIVATE game)
        set_target_properties(nitmod_pickup_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_pickup COMMAND nitmod_pickup_test)
        add_executable(nitmod_loadout_test ../tests/test_nitmod_loadout.c game/g_nitmod_loadout.c)
        target_include_directories(nitmod_loadout_test PRIVATE game)
        set_target_properties(nitmod_loadout_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_loadout COMMAND nitmod_loadout_test)
        add_executable(nitmod_class_command_test ../tests/test_nitmod_class_command.c
            game/g_nitmod_class_command.c game/nitmod_protocol.c)
        target_include_directories(nitmod_class_command_test PRIVATE game)
        set_target_properties(nitmod_class_command_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_class_command COMMAND nitmod_class_command_test)
        add_executable(nitmod_team_votes_test ../tests/test_nitmod_team_votes.c game/g_nitmod_team_vote.c)
        target_include_directories(nitmod_team_votes_test PRIVATE game)
        set_target_properties(nitmod_team_votes_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_team_votes COMMAND nitmod_team_votes_test)
        add_executable(nitmod_surrender_test ../tests/test_nitmod_surrender.c game/g_nitmod_surrender.c)
        target_include_directories(nitmod_surrender_test PRIVATE game)
        set_target_properties(nitmod_surrender_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_surrender COMMAND nitmod_surrender_test)
        add_executable(nitmod_weapon_messages_test ../tests/test_nitmod_weapon_messages.c game/nitmod_protocol.c)
        target_include_directories(nitmod_weapon_messages_test PRIVATE game)
        set_target_properties(nitmod_weapon_messages_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_messages COMMAND nitmod_weapon_messages_test)
        add_executable(nitmod_weapon_adapter_test ../tests/test_nitmod_weapon_adapter.c
            game/g_nitmod_weapon_adapter.c game/g_nitmod_weapon_config.c game/nitmod_protocol.c
            game/g_nitmod_teamcount.c game/g_nitmod_restrictions.c
            game/g_nitmod_weapon_policy.c game/nitmod_weapon_limits.c game/g_nitmod_loadout.c
            game/g_nitmod_pickup.c)
        target_include_directories(nitmod_weapon_adapter_test PRIVATE game)
        set_target_properties(nitmod_weapon_adapter_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_adapter COMMAND nitmod_weapon_adapter_test)
        add_executable(nitmod_team_cache_test ../tests/test_nitmod_team_cache.c game/g_nitmod_teamcount.c)
        target_include_directories(nitmod_team_cache_test PRIVATE game)
        set_target_properties(nitmod_team_cache_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_team_cache COMMAND nitmod_team_cache_test)
        add_executable(nitmod_weapon_config_test ../tests/test_nitmod_weapon_config.c
            game/g_nitmod_weapon_config.c game/nitmod_protocol.c)
        target_include_directories(nitmod_weapon_config_test PRIVATE game)
        set_target_properties(nitmod_weapon_config_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_config COMMAND nitmod_weapon_config_test)
        add_executable(nitmod_weapon_policy_test ../tests/test_nitmod_weapon_policy.c
            game/g_nitmod_weapon_policy.c game/g_nitmod_restrictions.c game/nitmod_weapon_limits.c)
        target_include_directories(nitmod_weapon_policy_test PRIVATE game)
        set_target_properties(nitmod_weapon_policy_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_policy COMMAND nitmod_weapon_policy_test)
        add_executable(nitmod_restriction_policy_test ../tests/test_nitmod_restriction_policy.c game/g_nitmod_restrictions.c)
        target_include_directories(nitmod_restriction_policy_test PRIVATE game)
        set_target_properties(nitmod_restriction_policy_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_restriction_policy COMMAND nitmod_restriction_policy_test)
        add_executable(nitmod_weapon_limits_test ../tests/test_nitmod_weapon_limits.c game/nitmod_weapon_limits.c)
        target_include_directories(nitmod_weapon_limits_test PRIVATE game)
        set_target_properties(nitmod_weapon_limits_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_limits COMMAND nitmod_weapon_limits_test)
        add_executable(nitmod_rifle_revoke_test ../tests/test_nitmod_rifle_revoke.c game/g_nitmod_rifle.c)
        target_include_directories(nitmod_rifle_revoke_test PRIVATE game)
        set_target_properties(nitmod_rifle_revoke_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_rifle_revoke COMMAND nitmod_rifle_revoke_test)
        add_executable(nitmod_equipment_test ../tests/test_nitmod_equipment.c game/g_nitmod_equipment.c)
        target_include_directories(nitmod_equipment_test PRIVATE game)
        set_target_properties(nitmod_equipment_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_equipment COMMAND nitmod_equipment_test)
        add_executable(nitmod_rifle_count_test ../tests/test_nitmod_rifle_count.c
            game/g_nitmod_teamcount.c)
        target_include_directories(nitmod_rifle_count_test PRIVATE game)
        set_target_properties(nitmod_rifle_count_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_rifle_count COMMAND nitmod_rifle_count_test)
        add_executable(nitmod_teamcount_test ../tests/test_nitmod_teamcount.c
            game/g_nitmod_teamcount.c)
        target_include_directories(nitmod_teamcount_test PRIVATE game)
        set_target_properties(nitmod_teamcount_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_teamcount COMMAND nitmod_teamcount_test)
        add_executable(nitmod_weapon_precheck_test ../tests/test_nitmod_weapon_precheck.c
            game/g_nitmod_restrictions.c)
        target_include_directories(nitmod_weapon_precheck_test PRIVATE game)
        set_target_properties(nitmod_weapon_precheck_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_precheck COMMAND nitmod_weapon_precheck_test)
        add_executable(nitmod_war_entry_test ../tests/test_nitmod_war_entry.c
            game/g_nitmod_war.c game/g_nitmod_weapons.c game/g_nitmod_abilities.c)
        target_include_directories(nitmod_war_entry_test PRIVATE game)
        set_target_properties(nitmod_war_entry_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_war_entry COMMAND nitmod_war_entry_test)
        add_executable(nitmod_remove_weapons_test ../tests/test_nitmod_remove_weapons.c
            game/g_nitmod_weapons.c)
        target_include_directories(nitmod_remove_weapons_test PRIVATE game)
        set_target_properties(nitmod_remove_weapons_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_remove_weapons COMMAND nitmod_remove_weapons_test)
        add_executable(nitmod_weapon_guards_test ../tests/test_nitmod_weapon_guards.c
            game/g_nitmod_abilities.c)
        target_include_directories(nitmod_weapon_guards_test PRIVATE game)
        set_target_properties(nitmod_weapon_guards_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_guards COMMAND nitmod_weapon_guards_test)
        add_executable(nitmod_adrenaline_inventory_test ../tests/test_nitmod_adrenaline_inventory.c
            game/g_nitmod_abilities.c)
        target_include_directories(nitmod_adrenaline_inventory_test PRIVATE game)
        set_target_properties(nitmod_adrenaline_inventory_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_adrenaline_inventory COMMAND nitmod_adrenaline_inventory_test)
        add_executable(nitmod_abilities_test ../tests/test_nitmod_abilities.c
            game/g_nitmod_abilities.c)
        target_include_directories(nitmod_abilities_test PRIVATE game)
        set_target_properties(nitmod_abilities_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_abilities COMMAND nitmod_abilities_test)
        add_executable(nitmod_adrenaline_grant_test ../tests/test_nitmod_adrenaline_grant.c
            game/g_nitmod_adrenaline_grant.c game/g_nitmod_abilities.c)
        target_include_directories(nitmod_adrenaline_grant_test PRIVATE game)
        set_target_properties(nitmod_adrenaline_grant_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_adrenaline_grant COMMAND nitmod_adrenaline_grant_test)
        add_executable(nitmod_score_test ../tests/test_nitmod_score.c
            game/nitmod_score.c game/g_nitmod_score.c)
        target_include_directories(nitmod_score_test PRIVATE game)
        set_target_properties(nitmod_score_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_score COMMAND nitmod_score_test)
        add_executable(nitmod_rank_test ../tests/test_nitmod_rank.c
            game/nitmod_skills.c game/nitmod_protocol.c)
        target_include_directories(nitmod_rank_test PRIVATE game)
        set_target_properties(nitmod_rank_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_rank COMMAND nitmod_rank_test)
        add_executable(nitmod_skill_loss_test ../tests/test_nitmod_skill_loss.c
            game/nitmod_skills.c game/nitmod_protocol.c)
        target_include_directories(nitmod_skill_loss_test PRIVATE game)
        set_target_properties(nitmod_skill_loss_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_skill_loss COMMAND nitmod_skill_loss_test)
        add_executable(nitmod_air_adapter_test ../tests/test_nitmod_air_adapter.c
            game/g_nitmod_air.c game/nitmod_air.c)
        target_include_directories(nitmod_air_adapter_test PRIVATE game)
        set_target_properties(nitmod_air_adapter_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_air_adapter COMMAND nitmod_air_adapter_test)
        add_executable(nitmod_air_test ../tests/test_nitmod_air.c
            game/nitmod_air.c game/nitmod_skills.c game/nitmod_protocol.c)
        target_include_directories(nitmod_air_test PRIVATE game)
        set_target_properties(nitmod_air_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_air_semantics COMMAND nitmod_air_test)
        add_executable(nitmod_skill_rewards_test ../tests/test_nitmod_skill_rewards.c
            cgame/cg_nitmod_skill_rewards.c)
        target_include_directories(nitmod_skill_rewards_test PRIVATE cgame)
        set_target_properties(nitmod_skill_rewards_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_skill_rewards_bounds COMMAND nitmod_skill_rewards_test)
        add_executable(nitmod_skill_digits_test ../tests/test_nitmod_skill_digits.c
            game/nitmod_skills.c game/nitmod_protocol.c)
        target_include_directories(nitmod_skill_digits_test PRIVATE game)
        set_target_properties(nitmod_skill_digits_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_skill_digits COMMAND nitmod_skill_digits_test)
        add_executable(nitmod_skill_progress_test ../tests/test_nitmod_skill_progress.c
            game/nitmod_skills.c game/nitmod_protocol.c)
        target_include_directories(nitmod_skill_progress_test PRIVATE game)
        set_target_properties(nitmod_skill_progress_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_skill_progress COMMAND nitmod_skill_progress_test)
        add_executable(nitmod_skills_test ../tests/test_nitmod_skills.c
            game/nitmod_skills.c game/nitmod_protocol.c)
        target_include_directories(nitmod_skills_test PRIVATE game)
        set_target_properties(nitmod_skills_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_skill_thresholds COMMAND nitmod_skills_test)
        add_executable(nitmod_map_cleanup_test ../tests/test_nitmod_map_cleanup.c
            game/g_nitmod_entities.c game/nitmod_entity_array.c game/g_nitmod_map_cleanup.c)
        target_include_directories(nitmod_map_cleanup_test PRIVATE game)
        set_target_properties(nitmod_map_cleanup_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_map_cleanup COMMAND nitmod_map_cleanup_test)
        add_executable(nitmod_mine_sweep_test ../tests/test_nitmod_mine_sweep.c game/g_nitmod_mine_sweep.c)
        target_include_directories(nitmod_mine_sweep_test PRIVATE game)
        set_target_properties(nitmod_mine_sweep_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_mine_sweep COMMAND nitmod_mine_sweep_test)
        add_executable(nitmod_satchel_free_test ../tests/test_nitmod_satchel_free.c game/g_nitmod_satchel_free.c)
        target_include_directories(nitmod_satchel_free_test PRIVATE game)
        set_target_properties(nitmod_satchel_free_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_satchel_free COMMAND nitmod_satchel_free_test)
        add_executable(nitmod_satchel_die_test ../tests/test_nitmod_satchel_die.c game/g_nitmod_satchel_die.c)
        target_include_directories(nitmod_satchel_die_test PRIVATE game)
        set_target_properties(nitmod_satchel_die_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_satchel_die COMMAND nitmod_satchel_die_test)
        add_executable(nitmod_weapon_damage_test ../tests/test_nitmod_weapon_damage.c game/g_nitmod_weapon_damage.c)
        target_include_directories(nitmod_weapon_damage_test PRIVATE game)
        set_target_properties(nitmod_weapon_damage_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_weapon_damage COMMAND nitmod_weapon_damage_test)
        add_executable(nitmod_mine_contact_test ../tests/test_nitmod_mine_contact.c game/g_nitmod_mine_contact.c)
        target_include_directories(nitmod_mine_contact_test PRIVATE game)
        set_target_properties(nitmod_mine_contact_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_mine_contact COMMAND nitmod_mine_contact_test)
        add_executable(nitmod_bot_handle_test ../tests/test_nitmod_bot_handle.c game/nitmod_bot_handle.c)
        target_include_directories(nitmod_bot_handle_test PRIVATE game)
        set_target_properties(nitmod_bot_handle_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_bot_handle COMMAND nitmod_bot_handle_test)
        if(TARGET qagame)
            get_target_property(nitmod_damage_game_sources qagame SOURCES)
            add_executable(nitmod_projectile_damage_test ../tests/test_nitmod_projectile_damage.c ${nitmod_damage_game_sources})
            target_include_directories(nitmod_projectile_damage_test PRIVATE game cgame ui)
            target_compile_definitions(nitmod_projectile_damage_test PRIVATE GAMEDLL=1)
            set_target_properties(nitmod_projectile_damage_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
            if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
                target_link_libraries(nitmod_projectile_damage_test PRIVATE m)
            endif()
            add_test(NAME nitmod_projectile_damage COMMAND nitmod_projectile_damage_test)
        endif()
        add_executable(nitmod_satchel_detonation_test ../tests/test_nitmod_satchel_detonation.c
            game/g_nitmod_entities.c game/nitmod_entity_array.c)
        target_include_directories(nitmod_satchel_detonation_test PRIVATE game)
        set_target_properties(nitmod_satchel_detonation_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_satchel_detonation COMMAND nitmod_satchel_detonation_test)
        add_executable(nitmod_owned_cleanup_test ../tests/test_nitmod_owned_cleanup.c
            game/g_nitmod_entities.c game/nitmod_entity_array.c)
        target_include_directories(nitmod_owned_cleanup_test PRIVATE game)
        set_target_properties(nitmod_owned_cleanup_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_owned_cleanup COMMAND nitmod_owned_cleanup_test)
        add_executable(nitmod_landmine_test ../tests/test_nitmod_landmine_lifecycle.c
            game/g_nitmod_entities.c game/nitmod_entity_array.c)
        target_include_directories(nitmod_landmine_test PRIVATE game)
        set_target_properties(nitmod_landmine_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_landmine_lifecycle COMMAND nitmod_landmine_test)
        add_executable(nitmod_satchel_test ../tests/test_nitmod_satchel_lifecycle.c
            game/g_nitmod_entities.c game/nitmod_entity_array.c)
        target_include_directories(nitmod_satchel_test PRIVATE game)
        set_target_properties(nitmod_satchel_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_satchel_lifecycle COMMAND nitmod_satchel_test)
        add_executable(nitmod_entity_array_test
            ../tests/test_nitmod_entity_array.c game/nitmod_entity_array.c)
        target_include_directories(nitmod_entity_array_test PRIVATE game)
        set_target_properties(nitmod_entity_array_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_entity_array_semantics COMMAND nitmod_entity_array_test)
        add_executable(nitmod_announcement_test
            ../tests/test_nitmod_announcements.c game/nitmod_announcements.c game/nitmod_protocol.c)
        target_include_directories(nitmod_announcement_test PRIVATE game)
        set_target_properties(nitmod_announcement_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_announcement_semantics COMMAND nitmod_announcement_test)
        add_executable(nitmod_spree_test ../tests/test_nitmod_spree.c game/nitmod_spree.c)
        target_include_directories(nitmod_spree_test PRIVATE game)
        set_target_properties(nitmod_spree_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_spree_state COMMAND nitmod_spree_test)
        add_executable(nitmod_config_index_test
            ../tests/test_nitmod_config_index.c game/nitmod_config_index.c)
        target_include_directories(nitmod_config_index_test PRIVATE game)
        set_target_properties(nitmod_config_index_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_config_index_semantics COMMAND nitmod_config_index_test)
        add_executable(nitmod_config_store_test
            ../tests/test_nitmod_config_store.c game/nitmod_config_store.c)
        target_include_directories(nitmod_config_store_test PRIVATE game)
        set_target_properties(nitmod_config_store_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_config_store_semantics COMMAND nitmod_config_store_test)
        add_executable(nitmod_protocol_numbers_test
            ../tests/test_nitmod_protocol_numbers.c game/nitmod_protocol.c)
        target_include_directories(nitmod_protocol_numbers_test PRIVATE game)
        set_target_properties(nitmod_protocol_numbers_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_protocol_numbers COMMAND nitmod_protocol_numbers_test)
        add_executable(nitmod_snapshots_test
            ../tests/test_nitmod_snapshots.c game/nitmod_snapshots.c game/nitmod_protocol.c)
        target_include_directories(nitmod_snapshots_test PRIVATE game)
        set_target_properties(nitmod_snapshots_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
        add_test(NAME nitmod_snapshot_semantics COMMAND nitmod_snapshots_test)
    endif()
    find_package(Python3 COMPONENTS Interpreter QUIET)
    if(Python3_Interpreter_FOUND)
        add_test(NAME nitmod_original_event_map COMMAND ${Python3_EXECUTABLE} -B
            "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_original_event_map.py")
        add_test(NAME nitmod_global_stats_labels COMMAND ${Python3_EXECUTABLE} -B
            "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_global_stats_labels.py")
        add_test(NAME nitmod_client_stats_protocol COMMAND ${Python3_EXECUTABLE} -B
            "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_client_stats_protocol.py")
        add_test(NAME nitmod_debrief_protocol COMMAND ${Python3_EXECUTABLE} -B
            "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_debrief_protocol.py")
        add_test(NAME nitmod_drawgun_contract COMMAND ${Python3_EXECUTABLE} -B
            "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_drawgun_contract.py")
        add_test(NAME nitmod_legacy_cvar_surface COMMAND ${Python3_EXECUTABLE} -B
            "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_legacy_cvar_surface.py")
        add_test(NAME nitmod_original_ui_actions COMMAND ${Python3_EXECUTABLE} -B
            "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_original_ui_actions.py")
        add_test(NAME nitmod_loadpanel_contract COMMAND ${Python3_EXECUTABLE} -B
            "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_nitmod_loadpanel.py")
        add_test(NAME nitmod_mapvote_contract COMMAND ${Python3_EXECUTABLE} -B
            "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_nitmod_mapvote.py")
        add_test(NAME nitmod_pak_readonly COMMAND ${Python3_EXECUTABLE} -B
            "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_pak_readonly.py")
        if(TARGET nitmod_native_weapon_aliases)
            set(switch_test_bodies "${CMAKE_CURRENT_BINARY_DIR}/nitmod_weapon_change_bodies.h")
            add_custom_command(OUTPUT "${switch_test_bodies}"
                COMMAND "${Python3_EXECUTABLE}" -B "${CMAKE_CURRENT_SOURCE_DIR}/../tools/extract_weapon_change_test.py"
                    "${CMAKE_CURRENT_SOURCE_DIR}/game/bg_pmove.c" "${switch_test_bodies}"
                DEPENDS game/bg_pmove.c ../tools/extract_weapon_change_test.py VERBATIM)
            add_executable(nitmod_weapon_change_test ../tests/test_nitmod_weapon_change.c
                "${switch_test_bodies}" ../tests/dump_native_weapon_aliases.c
                game/nitmod_weapon_reload.c game/nitmod_weapon_inventory.c
                game/nitmod_weapon_reload_feedback.c
                game/nitmod_weapon_clip.c game/nitmod_weapon_consumption.c
                game/nitmod_weapon_akimbo.c game/bg_misc.c game/q_shared.c game/q_math.c)
            target_compile_definitions(nitmod_weapon_change_test PRIVATE GAMEDLL=1 NITMOD_SWITCH_HARNESS=1)
            target_include_directories(nitmod_weapon_change_test PRIVATE game "${CMAKE_CURRENT_BINARY_DIR}")
            set_target_properties(nitmod_weapon_change_test PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)
            if(NOT MSVC)
                target_link_libraries(nitmod_weapon_change_test PRIVATE m)
            endif()
            add_test(NAME nitmod_weapon_change COMMAND nitmod_weapon_change_test)
        endif()
        add_test(NAME nitmod_weapon_messages_reference
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_weapon_messages_reference.py"
                "${CMAKE_CURRENT_SOURCE_DIR}/..")
        add_test(NAME nitmod_team_cache_hooks
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_team_cache_hooks.py"
                "${CMAKE_CURRENT_SOURCE_DIR}/..")
        add_test(NAME nitmod_cvar_inventory
            COMMAND "${Python3_EXECUTABLE}" -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_cvar_inventory.py"
                "${CMAKE_CURRENT_SOURCE_DIR}/..")
        add_test(NAME nitmod_server_messages_reference
            COMMAND "${Python3_EXECUTABLE}" -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_server_messages_reference.py"
                "${CMAKE_CURRENT_SOURCE_DIR}/..")
        add_test(NAME nitmod_weapon_cvars_reference
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_weapon_cvars_reference.py"
                "${CMAKE_CURRENT_SOURCE_DIR}/..")
        add_test(NAME nitmod_bot_loader_reference
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_bot_loader_reference.py"
                "${CMAKE_CURRENT_SOURCE_DIR}/..")
        add_test(NAME nitmod_weapon_paths_reference
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_weapon_paths_reference.py"
                "${CMAKE_CURRENT_SOURCE_DIR}/..")
        add_test(NAME nitmod_weapon_banks_reference
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_weapon_banks_reference.py"
                "${CMAKE_CURRENT_SOURCE_DIR}/..")
        add_test(NAME nitmod_weapon_ammo_reference
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_weapon_ammo_reference.py"
                "${CMAKE_CURRENT_SOURCE_DIR}/..")
        if(TARGET nitmod_native_weapon_aliases)
            add_test(NAME nitmod_weapon_aliases_reference
                COMMAND ${Python3_EXECUTABLE} -B
                    "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_weapon_aliases_reference.py"
                    "${CMAKE_CURRENT_SOURCE_DIR}/.." "$<TARGET_FILE:nitmod_native_weapon_aliases>")
        endif()
        add_test(NAME nitmod_client_tokens_reference
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_client_tokens_reference.py"
                "${CMAKE_CURRENT_SOURCE_DIR}/..")
        add_test(NAME nitmod_weapon_items_reference
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_weapon_items_reference.py"
                "${CMAKE_CURRENT_SOURCE_DIR}/..")
        if(TARGET nitmod_rank_test)
            add_test(NAME nitmod_rank_reference
                COMMAND ${Python3_EXECUTABLE} -B
                    "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_rank_reference.py"
                    "${CMAKE_CURRENT_SOURCE_DIR}/.." $<TARGET_FILE:nitmod_rank_test>)
        endif()
        if(TARGET nitmod_skill_rewards_test)
            add_test(NAME nitmod_skill_rewards_reference
                COMMAND ${Python3_EXECUTABLE} -B
                    "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_skill_rewards_reference.py"
                    "${CMAKE_CURRENT_SOURCE_DIR}/.." "$<TARGET_FILE:nitmod_skill_rewards_test>")
        endif()
        add_test(NAME nitmod_reference_symbols
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_reference_symbols.py"
                "${CMAKE_CURRENT_SOURCE_DIR}/..")
        add_test(NAME nitmod_protocol_contract
            COMMAND ${Python3_EXECUTABLE}
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_nitmod_protocol_contract.py"
                "${CMAKE_CURRENT_SOURCE_DIR}")
        add_test(NAME nitmod_reference_artifacts
            COMMAND ${Python3_EXECUTABLE}
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_reference_artifacts.py"
                "${CMAKE_CURRENT_SOURCE_DIR}/..")
        add_test(NAME nitmod_original_death_causes
            COMMAND ${Python3_EXECUTABLE}
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_original_death_causes.py")
        add_test(NAME nitmod_port_inventory
            COMMAND ${Python3_EXECUTABLE}
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_port_inventory.py"
                "${CMAKE_CURRENT_SOURCE_DIR}/..")
        add_test(NAME nitmod_linux_i386_build_driver
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_linux_i386_build.py")
        add_test(NAME nitmod_wasm_build_contract
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_wasm_build_contract.py")
        add_test(NAME nitmod_wasm_artifacts
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_wasm_artifacts.py")
        add_test(NAME nitmod_wasm_build_driver
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_wasm_build_driver.py")
        add_test(NAME nitmod_wasm_load_smoke_driver
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_wasm_load_smoke_driver.py")
        add_test(NAME nitmod_engine_syscall_numbers
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_engine_syscall_numbers.py")
        add_test(NAME nitmod_wasm_layout_audit
            COMMAND ${Python3_EXECUTABLE} -B
                "${CMAKE_CURRENT_SOURCE_DIR}/../tests/test_wasm_layout_audit.py")
    endif()
endif()
