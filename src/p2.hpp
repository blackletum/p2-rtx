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
	typedef	bool(__cdecl* R_CullNode_t)(mnode_t*);
	extern R_CullNode_t R_CullNode;

	typedef	bool(__cdecl* CM_LeafArea_t)(int leaf_num);
	extern CM_LeafArea_t CM_LeafArea;

	typedef	void(__cdecl* ComputeViewMatrices_t)(VMatrix* pWorldToView, VMatrix* pViewToProjection, VMatrix* pWorldToProjection, const CViewSetup* viewSetup);
	extern ComputeViewMatrices_t ComputeViewMatrices;

	// - client
	typedef	C_BaseEntity* (__cdecl* GetSplitScreenViewPlayer_t)();
	extern GetSplitScreenViewPlayer_t GetSplitScreenViewPlayer;

	typedef	void* (__cdecl* ToPortalPlayer_t)(C_BaseEntity*);
	extern ToPortalPlayer_t ToPortalPlayer;

	typedef	void (__fastcall* CPortalRenderable__AddToVisAsExitPortal_t)(void* this_ptr, void* null, ViewCustomVisibility_t*);
	extern CPortalRenderable__AddToVisAsExitPortal_t CPortalRenderable__AddToVisAsExitPortal;

	typedef	void (__fastcall* CViewRender__ViewDrawScene_t)(void* this_ptr, void* null, bool, int, const CViewSetup*, int, int, bool, int, ViewCustomVisibility_t*);
	extern CViewRender__ViewDrawScene_t CViewRender__ViewDrawScene;

	// - shaderapidx9
	//


	// -------------------------------------------
	// game asm offsets

	// - server
	extern uint32_t hk_addr__scene_ent_on_start_event;
	extern uint32_t hk_addr__scene_ent_on_finish_event;

	// - engine
	extern uint32_t hk_addr__on_map_load;
	extern uint32_t hk_addr__on_host_disconnect;
	extern uint32_t hk_addr__on_host_change_level;
	extern uint32_t hk_addr__pre_recursive_world_node;
	extern uint32_t hk_addr__while_recursive_world_node;
	extern uint32_t hk_addr__while_recursive_world_node_og_retn;
	extern uint32_t hk_addr__while_recursive_world_node_force_retn;

	// - client
	extern uint32_t hk_addr__cviewrenderer_renderview;
	extern uint32_t hk_addr__cviewrenderer_drawonemonitor;

	// - shaderapidx9


	// - studiorender


	// -------------------------------------------

	void main();

	extern bool g_installed_signature_patches;
	extern bool g_install_signature_patches_async;
}
