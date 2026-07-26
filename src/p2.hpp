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
	extern uint32_t hk_addr__spawn_all_entities;
	extern uint32_t retn_addr__spawn_all_entities;

	// - engine
	extern uint32_t hk_addr__on_map_load;
	extern uint32_t hk_addr__on_host_disconnect;
	extern uint32_t hk_addr__on_host_change_level;
	extern uint32_t hk_addr__pre_recursive_world_node;
	extern uint32_t hk_addr__while_recursive_world_node;
	extern uint32_t hk_addr__while_recursive_world_node_og_retn;
	extern uint32_t hk_addr__while_recursive_world_node_force_retn;
	extern uint32_t mod_addr__while_recursive_world_node_01;
	extern uint32_t nop_addr__while_recursive_world_node_02;
	extern uint32_t mod_addr__while_recursive_world_node_03;
	extern uint32_t nop_addr__draw_leaf;
	extern uint32_t nop_addr__cbrushbatchrender_draw_opaque_bmodel;
	extern uint32_t nop_addr__draw_displacements_in_leaf;
	extern uint32_t mod_addr__shader_draw_chains;
	extern uint32_t mod_addr__cbrushbatchrender_draw_opaque_bmodel;
	extern uint32_t nop_addr__cbrushbatchrender_compute_lmap_pages;
	extern uint32_t hk_addr__flow_through_area;
	extern uint32_t nop_addr__flow_through_area;
	extern uint32_t mod_addr__cstaticpropmgr_update_prop_visibility;
	extern uint32_t nop_addr__cstaticpropmgr_update_prop_visibility;

	// - client
	extern uint32_t hk_addr__cviewrenderer_renderview;
	extern uint32_t hk_addr__cviewrenderer_drawonemonitor;
	extern uint32_t mod_addr__clientleafsystem_extract_culled_renderables;
	extern uint32_t nop_addr__vguiscreen_draw_model;
	extern uint32_t nop_addr__csimpleworldview_setup;
	extern uint32_t mod_addr__csimpleworldview_setup;
	extern uint32_t hk_addr__cportalghost_should_draw;
	extern uint32_t hk_addr__draw_our_3rd_person_body_mesh;
	extern uint32_t hk_addr__draw_our_3rd_person_weapon_mesh;
	extern uint32_t fn_addr__draw_our_3rd_person_weapon_mesh;
	extern uint32_t hk_addr__viewdrawscene_push_args;
	extern uint32_t hk_addr__cbaseworldview_draw_setup;
	extern uint32_t hk_addr__cbaseentity_update_visibility;
	extern uint32_t hk_addr__cbaseentity_update_visibility_retn;
	extern uint32_t nop_addr__cpropportal_create_attached_particles;
	extern uint32_t nop_addr__write_savegame_screenshot_of_size;
	extern uint32_t mod_addr__envprojectedtexture_should_update;
	extern uint32_t hk_addr__cviewrenderer_init_fade_data;
	extern uint32_t mod_addr__cbaseentity_should_draw;

	// - shaderapidx9
	extern uint32_t nop_addr__cshadermgr_set_pixel_shader;

	// - studiorender


	// -------------------------------------------

	void main();

	extern bool g_installed_signature_patches;
	extern bool g_install_signature_patches_async;
}
