#pragma once

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
	typedef	bool(__cdecl* CM_LeafArea_t)(int leaf_num);
	extern CM_LeafArea_t CM_LeafArea;

	// - client
	typedef	C_BaseEntity* (__cdecl* GetSplitScreenViewPlayer_t)();
	extern GetSplitScreenViewPlayer_t GetSplitScreenViewPlayer;

	typedef	void* (__cdecl* ToPortalPlayer_t)(C_BaseEntity*);
	extern ToPortalPlayer_t ToPortalPlayer;

	// - shaderapidx9
	//


	// -------------------------------------------
	// game asm offsets

	// - server
	extern uint32_t hk_addr__scene_ent_on_start_event;
	extern uint32_t hk_addr__scene_ent_on_finish_event;

	// - engine


	// - client


	// - shaderapidx9


	// - studiorender


	// -------------------------------------------

	void main();

	extern bool g_installed_signature_patches;
	extern bool g_install_signature_patches_async;
}
