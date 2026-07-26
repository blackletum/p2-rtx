#include "std_include.hpp"

#include "components/common/flags.hpp"
#include "components/common/remix_api.hpp"
#include "components/modules/choreo_events.hpp"
#include "components/modules/game_settings.hpp"
#include "components/modules/imgui.hpp"
#include "components/modules/interfaces.hpp"
#include "components/modules/main_module.hpp"
#include "components/modules/model_render.hpp"
#include "components/modules/remix_lights.hpp"
#include "components/modules/remix_rayportal.hpp"
#include "components/modules/sound_events.hpp"

namespace p2
{
	// -------------------------------------------
	// game variables

	// - server


	// - engine


	// - client


	// - shaderapidx9


	// -------------------------------------------
	// game functions

	// - server


	// - engine
	R_CullNode_t R_CullNode = nullptr;
	CM_LeafArea_t CM_LeafArea = nullptr;
	ComputeViewMatrices_t ComputeViewMatrices = nullptr;

	// - client
	GetSplitScreenViewPlayer_t GetSplitScreenViewPlayer = nullptr;
	ToPortalPlayer_t ToPortalPlayer = nullptr;
	CPortalRenderable__AddToVisAsExitPortal_t CPortalRenderable__AddToVisAsExitPortal = nullptr;
	CViewRender__ViewDrawScene_t CViewRender__ViewDrawScene = nullptr;

	// - shaderapidx9
	//


	// -------------------------------------------
	// game asm offsets

	// - server
	uint32_t hk_addr__scene_ent_on_start_event = 0u;
	uint32_t hk_addr__scene_ent_on_finish_event = 0u;

	// - engine
	uint32_t hk_addr__on_map_load = 0u;
	uint32_t hk_addr__on_host_disconnect = 0u;
	uint32_t hk_addr__on_host_change_level = 0u;
	uint32_t hk_addr__pre_recursive_world_node = 0u;
	uint32_t hk_addr__while_recursive_world_node = 0u;
	uint32_t hk_addr__while_recursive_world_node_og_retn = 0u;
	uint32_t hk_addr__while_recursive_world_node_force_retn = 0u;

	// - client
	uint32_t hk_addr__cviewrenderer_renderview = 0u;
	uint32_t hk_addr__cviewrenderer_drawonemonitor = 0u;

	// - shaderapidx9


	// - studiorender


	// -------------------------------------------

#define PATTERN_OFFSET_SIMPLE(mod, var, pattern, byte_offset, static_addr) \
		if (const auto offset = utils::mem::find_pattern(mod, ##pattern, byte_offset, #var, use_pattern, static_addr); offset) { \
			(var) = offset; found_pattern_count++; \
		} total_pattern_count++;

#define PATTERN_OFFSET_SIMPLE_CAST(mod, var, type, pattern, byte_offset, static_addr) \
		if (const auto offset = utils::mem::find_pattern(mod, ##pattern, byte_offset, #var, use_pattern, static_addr); offset) { \
			(var) = (type)offset; found_pattern_count++; \
		} total_pattern_count++;

#define PATTERN_OFFSET_DWORD_PTR_CAST_TYPE(mod, var, type, pattern, byte_offset, static_addr) \
		if (const auto offset = utils::mem::find_pattern(mod, ##pattern, byte_offset, #var, use_pattern, static_addr); offset) { \
			(var) = (type)*(DWORD*)offset; found_pattern_count++; \
		} total_pattern_count++;

	// init any adresses here
	void init_game_addresses()
	{
		const bool use_pattern = !common::flags::has_flag("no_pattern") && IS_LATEST_BUILD;
		if (use_pattern) {
			common::log("P2", "Getting offsets ...", common::LOG_TYPE::LOG_TYPE_DEFAULT, false);
		}

		std::uint32_t total_pattern_count = 0u;
		std::uint32_t found_pattern_count = 0u;

#pragma region GAME_VARIABLES

		// --------------------------
		// - server - variables


		// - server - functions


		// - server - asm
		PATTERN_OFFSET_SIMPLE(SERVER_MOD, hk_addr__scene_ent_on_start_event, "8B 7D ? 8B F1 68 ? ? ? ? 8B CF E8 ? ? ? ? 50 E8 ? ? ? ? 83 C4 ? 85 C0 75 ? 8B 76", 0, USE_OFFSET(0x233618, 0x22D428));
		PATTERN_OFFSET_SIMPLE(SERVER_MOD, hk_addr__scene_ent_on_finish_event, "8B 86 ? ? ? ? 85 C0 75 ? B8 ? ? ? ? F3 0F 10 86 ? ? ? ? 53", 0, USE_OFFSET(0x238483, 0x232273));


		// --------------------------
		// - engine - variables

		// - engine - functions
		PATTERN_OFFSET_SIMPLE_CAST(ENGINE_MOD, R_CullNode, R_CullNode_t, "55 8B EC 80 3D ? ? ? ? ? 8B 4D", 0, USE_OFFSET(0x10F950, 0x10E7E0));
		PATTERN_OFFSET_SIMPLE_CAST(ENGINE_MOD, CM_LeafArea, CM_LeafArea_t, "55 8B EC 56 8B 75 ? 85 F6 78 ? 3B 35 ? ? ? ? 7C ? 68 ? ? ? ? FF 15 ? ? ? ? 83 C4 ? A1 ? ? ? ? 03 F6 66 8B 4C F0", 0, USE_OFFSET(0x15ACE0, 0x159470));
		PATTERN_OFFSET_SIMPLE_CAST(ENGINE_MOD, ComputeViewMatrices, ComputeViewMatrices_t, "55 8B EC 0F 57 C9 F3 0F 10 15", 0, USE_OFFSET(0xDDE10, 0xDD4A0));

		// - engine - asm
		PATTERN_OFFSET_SIMPLE(ENGINE_MOD, hk_addr__on_map_load, "8D 4F ? 33 D2", 0, USE_OFFSET(0xFD8FC, 0xFCD5C));
		PATTERN_OFFSET_SIMPLE(ENGINE_MOD, hk_addr__on_host_disconnect, "8B EC 83 EC ? 53 8B 5D ? 57 BF", 0, USE_OFFSET(0x19A3E1, 0x197DF1));
		PATTERN_OFFSET_SIMPLE(ENGINE_MOD, hk_addr__on_host_change_level, "68 ? ? ? ? 8D 8D ? ? ? ? 56 51 E8 ? ? ? ? 83 C4 ? 83 3D", 0, USE_OFFSET(0x19620D, 0x193C6D));
		PATTERN_OFFSET_SIMPLE(ENGINE_MOD, hk_addr__pre_recursive_world_node, "8B 52 ? 8B CB E8", 0, USE_OFFSET(0xE76CD, 0xE6D6D));
		PATTERN_OFFSET_SIMPLE(ENGINE_MOD, hk_addr__while_recursive_world_node, "8B 4B ? 3B 0D", 0, USE_OFFSET(0xE7246, 0xE68E6));
		
		if (hk_addr__while_recursive_world_node) {
			hk_addr__while_recursive_world_node_og_retn = USE_OFFSET(utils::mem::resolve_relative_jump_address(hk_addr__while_recursive_world_node + 9u, 6u, 2u), 0xE6A42); found_pattern_count++;
		} total_pattern_count++;

		if (hk_addr__while_recursive_world_node) {
			hk_addr__while_recursive_world_node_force_retn = USE_OFFSET(utils::mem::resolve_relative_jump_address(hk_addr__while_recursive_world_node + 18u, 2u, 1u), 0xE690B); found_pattern_count++;
		} total_pattern_count++;


		// --------------------------
		// - client - variables

		// - client - functions
		PATTERN_OFFSET_SIMPLE_CAST(CLIENT_MOD, GetSplitScreenViewPlayer, GetSplitScreenViewPlayer_t, "8B 0D ? ? ? ? ? ? 8B 90 ? ? ? ? FF D2 50 E8 ? ? ? ? 83 C4 ? C3", 0, USE_OFFSET(0x17B8B0, 0x176460));
		PATTERN_OFFSET_SIMPLE_CAST(CLIENT_MOD, ToPortalPlayer, ToPortalPlayer_t, "55 8B EC 56 8B 75 ? 85 F6 74 ? ? ? 8B 90 ? ? ? ? 8B CE FF D2 84 C0 74 ? 8B C6", 0, USE_OFFSET(0x3FEE0, 0x14BF30));
		PATTERN_OFFSET_SIMPLE_CAST(CLIENT_MOD, CPortalRenderable__AddToVisAsExitPortal, CPortalRenderable__AddToVisAsExitPortal_t, "55 8B EC 51 57 8B 7D ? 89 4D ? 85 FF 0F 84 ? ? ? ? 53", 0, USE_OFFSET(0x2C2DC0, 0x2BBDA0));
		PATTERN_OFFSET_SIMPLE_CAST(CLIENT_MOD, CViewRender__ViewDrawScene, CViewRender__ViewDrawScene_t, "55 8B EC 51 A1 ? ? ? ? 53 56 57 8B F9 8B 48", 0, USE_OFFSET(0x1EDFA0, 0x1E84E0));

		// - client - asm
		PATTERN_OFFSET_SIMPLE(CLIENT_MOD, hk_addr__cviewrenderer_renderview, "C7 45 ? ? ? ? ? 0F 85 ? ? ? ? 68", 0, USE_OFFSET(0x1F2885, 0x1ECDC5));
		PATTERN_OFFSET_SIMPLE(CLIENT_MOD, hk_addr__cviewrenderer_drawonemonitor, "8B 5D ? 6A ? 6A ? 6A ? 6A", 0, USE_OFFSET(0x1EEDB4, 0x1E92F4));

		// --------------------------
		// - shaderapidx9 - variables
		

		// - shaderapidx9 - functions
		//

		// - shaderapidx9 - asm


		// --------------------------
		// - studiorender - variables
		//

		// - studiorender - functions
		//

		// - studiorender - asm


#pragma endregion

		if (use_pattern)
		{
			if (found_pattern_count == total_pattern_count) {
				common::log("P2", std::format("Found all '{:d}' Patterns.", total_pattern_count), common::LOG_TYPE::LOG_TYPE_GREEN, true);
			}
			else
			{
				common::log("P2", std::format("Only found '{:d}' out of '{:d}' Patterns.", found_pattern_count, total_pattern_count), common::LOG_TYPE::LOG_TYPE_ERROR, true);
				common::log("P2", ">> Please create an issue on GitHub and attach this console log and information about your game (version, platform etc.)", common::LOG_TYPE::LOG_TYPE_STATUS, true);
			}
		}
	}

#undef PATTERN_OFFSET_SIMPLE

	void main()
	{
		init_game_addresses();

		// init remix api
		common::remix_api::initialize(nullptr, nullptr, []
		{
			main_module::hud_draw_area_info();
		}, false);

		common::loader::module_loader::register_module(std::make_unique<interfaces>());
		common::loader::module_loader::register_module(std::make_unique<imgui>());
		common::loader::module_loader::register_module(std::make_unique<game_settings>());
		common::loader::module_loader::register_module(std::make_unique<choreo_events>());
		common::loader::module_loader::register_module(std::make_unique<sound_events>());
		common::loader::module_loader::register_module(std::make_unique<remix_vars>());
		common::loader::module_loader::register_module(std::make_unique<remix_rayportal>());
		common::loader::module_loader::register_module(std::make_unique<remix_lights>());
		common::loader::module_loader::register_module(std::make_unique<map_settings>());
		common::loader::module_loader::register_module(std::make_unique<model_render>());
		common::loader::module_loader::register_module(std::make_unique<main_module>());

		MH_EnableHook(MH_ALL_HOOKS);
	}
}
