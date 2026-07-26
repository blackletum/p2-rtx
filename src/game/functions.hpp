#pragma once

#define RENDERER_MOD			game::shaderapidx9_module
#define STUDIORENDER_MOD		game::studiorender_module
#define MATERIALSTYSTEM_MOD		game::materialsystem_module
#define ENGINE_MOD				game::engine_module
#define CLIENT_MOD				game::client_module
#define SERVER_MOD				game::server_module
#define VSTDLIB_MOD				game::vstdlib_module

#define RENDERER_BASE			game::shaderapidx9_module.handle
#define STUDIORENDER_BASE		game::studiorender_module.handle
#define MATERIALSTYSTEM_BASE	game::materialsystem_module.handle
#define ENGINE_BASE				game::engine_module.handle
#define CLIENT_BASE				game::client_module.handle
#define SERVER_BASE				game::server_module.handle
#define VSTDLIB_BASE			game::vstdlib_module.handle

using namespace components;

namespace glob
{
	extern bool spawned_external_console;
	extern bool has_debug_arg;
	extern HWND main_window;
	extern sdk::InputContext_t* input_context;
}

namespace game
{
	extern utils::mem::module_info shaderapidx9_module;
	extern utils::mem::module_info studiorender_module;
	extern utils::mem::module_info materialsystem_module;
	extern utils::mem::module_info engine_module;
	extern utils::mem::module_info client_module;
	extern utils::mem::module_info server_module;
	extern utils::mem::module_info vstdlib_module;

	extern const D3DXMATRIX IDENTITY;
	extern const D3DXMATRIX TC_TRANSLATE_TO_CENTER;
	extern const D3DXMATRIX TC_TRANSLATE_FROM_CENTER_TO_TOP_LEFT;

	extern ConVar* find_cvar(const char* name);
	extern const ConVar* find_cvar_const(const char* name);
	extern void con_add_command(ConCommand* cmd, const char* name, void(__cdecl* callback)(), const char* desc);
	extern void debug_add_text_overlay(const float* pos, float duration, const char* text);
	extern void debug_add_text_overlay(const float* pos, const char* text, int line_offset = 0, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	extern void cbaseentity_remove(void* cbaseentity_ptr);

	extern int get_visframecount();
	extern const char* get_map_name();

	extern void r_flow_through_area(int area, const Vector* vec_vis_origin, const CPortalRect* clip_rect, const VisOverrideData_t* vis_data, float* reflection_water_height);
	inline int* get_visible_areas_num() { return reinterpret_cast<int*>(ENGINE_BASE + USE_OFFSET(0x61ABE0, 0x615468)); } // 0125
	inline std::uint16_t* get_visible_areas() { return reinterpret_cast<std::uint16_t*>(ENGINE_BASE + USE_OFFSET(0x61ABE8, 0x615470)); } // 0125
	inline bool* get_viewer_in_solid_space() { return reinterpret_cast<bool*>(ENGINE_BASE + USE_OFFSET(0x61C228, 0x616AB0)); } // 0125
	inline CPortalRect* get_area_rect() { return reinterpret_cast<CPortalRect*>(ENGINE_BASE + USE_OFFSET(0x61ADE8, 0x615670)); } // 0125
	inline Frustum_t* get_area_frustum() { return reinterpret_cast<Frustum_t*>(*(DWORD*)(ENGINE_BASE + USE_OFFSET(0x61C35C, 0x616BE4))); } // 0125 // + 0x10 to pElements

	extern void frustum_set_planes(Frustum_t* frustum, const VPlane* planes);

	extern bool frustum_cull_box(Frustum_t* frustum, const Vector* mins, const Vector* maxs);
	inline Frustum_t* get_g_frustum() { return reinterpret_cast<Frustum_t*>(ENGINE_BASE + USE_OFFSET(0x615390, 0x60FC20)); } // 0125

	extern void cvar_uncheat(const char* name);
	extern void cvar_uncheat_and_set_int(const char* name, const int val);
	extern void cvar_uncheat_and_set_float(const char* name, const float val);

	extern void print_ingame(const char* msg, ...);

	// CRender gRender
	inline components::CRender* get_engine_renderer() { return reinterpret_cast<components::CRender*>(ENGINE_BASE + USE_OFFSET(0x615100, 0x60F880)); } // 0125
	inline IDirect3DDevice9* get_d3d_device() { return reinterpret_cast<IDirect3DDevice9*>(*(DWORD*)(RENDERER_BASE + USE_OFFSET(0xDA5D8, 0x179F38))); } // 0125
	inline components::IShaderAPIDX8* get_shaderapi() { return reinterpret_cast<components::IShaderAPIDX8*>(*(DWORD*)(RENDERER_BASE + USE_OFFSET(0xD0C74, 0x164C48))); } // 0125
	inline components::CShaderAPIDx8* get_cshaderapi() { return reinterpret_cast<components::CShaderAPIDx8*>((RENDERER_BASE + USE_OFFSET(0xD7040, 0x1769A0))); } // 0125
	inline components::worldbrushdata_t* get_hoststate_worldbrush_data() { return reinterpret_cast<components::CCommonHostState*>(ENGINE_BASE + USE_OFFSET(0x43F028, 0x439C1C))->worldbrush; } // 0125
	inline components::CGlobalVarsBase* get_global_vars() { return reinterpret_cast<components::CGlobalVarsBase*>(*(DWORD*)(CLIENT_BASE + USE_OFFSET(0x92A37C, 0x9220BC))); } // 0125
	inline components::CCvar* get_icvar() { return reinterpret_cast<components::CCvar*>((VSTDLIB_BASE + USE_OFFSET(0x315B0, 0x31550))); } // 0125

	inline components::CStaticPropMgr* get_cstatic_prop_mgr() { return reinterpret_cast<components::CStaticPropMgr*>((ENGINE_BASE + USE_OFFSET(0x442998, 0x43D490))); } // 0125

	inline Vector* get_current_view_origin() { return reinterpret_cast<Vector*>(ENGINE_BASE + USE_OFFSET(0x513380, 0x50DB50)); } // 0125
	inline Vector* get_current_view_forward() { return reinterpret_cast<Vector*>(ENGINE_BASE + USE_OFFSET(0x4351D0, 0x42FFE4)); } // 0125
	inline Vector* get_current_view_right() { return reinterpret_cast<Vector*>(ENGINE_BASE + USE_OFFSET(0x4351DC, 0x42FFF0)); } // 0125
	inline Vector* get_current_view_up() { return reinterpret_cast<Vector*>(ENGINE_BASE + USE_OFFSET(0x4351E8, 0x42FFFC)); } // 0125

	// note: this might be ILLEGAL when within 'CBaseWorldView::DrawSetup' -> use 'game::saved_view_id' instead
	inline view_id* get_current_view_id() { return reinterpret_cast<view_id*>(CLIENT_BASE + USE_OFFSET(0x937F40, 0x92FB00)); } // 0125
	extern view_id saved_view_id;

	inline bool is_puzzlemaker_active()
	{
		struct puzz
		{
			int pad;
			bool m_bShowing;
			bool m_bActive;
			float m_flTransition;
			float m_flZoomScale;
			bool m_bInputEnabled;
			int m_LastUpdateFrame;
			bool m_bIsInLevel;
			bool m_bCanQuitGame;
			int m_nCachedSSSlot;
		};

		const auto p = reinterpret_cast<puzz*>(*(DWORD*)(CLIENT_BASE + USE_OFFSET(0x94EAE8, 0x946438))); // 0125
		return p && p->m_bActive;
	}
	// 946438

	// CM_PointLeafnum
	inline int get_leaf_from_position(const Vector& pos) { return utils::hook::call<int(__cdecl)(const float*)>(ENGINE_BASE + USE_OFFSET(0x159C80, 0x158540))(&pos.x); } // 0125

	inline bool is_paused()
	{
		// GetBaseLocalClient
		const auto cclientstate_ptr = utils::hook::call<void*(__cdecl)()>(ENGINE_BASE + USE_OFFSET(0x9EAF0, 0x9E7E0))(); // 0125

		// CClientState::IsPaused
		return utils::hook::call<BOOL(__fastcall)(void* this_ptr, void* null)>(ENGINE_BASE + USE_OFFSET(0xAB850, 0xAB140))(cclientstate_ptr, nullptr); // 0125
	}


	// returns C_BaseAnimating class pointer for a given IClientRenderable
	C_BaseAnimating* get_base_animating_for_client_renderable(IClientRenderable* pRenderable);

	namespace namespaces
	{
		namespace C_BaseAnimating
		{
			// returns bone matrix for given bone index
			/// @param this_ptr			C_BaseAnimating ptr
			/// @param bone				bone index
			/// @param boneToWorld		out bone matrix
			inline void GetBoneTransform(void* this_ptr, const int bone, matrix3x4_t* boneToWorld)
			{
				// 55 8B EC 56 8B F1 83 BE ? ? ? ? ? 57 75 ? 8B 46 ? 8B 50 ? 8D 4E ? FF D2 85 C0 74 ? 8B CE E8 ? ? ? ? 8B 86
				utils::hook::call<void(__fastcall)(void* this_ptr, void* null, int bone, matrix3x4_t* boneToWorld)>(CLIENT_BASE + USE_OFFSET(0x5F4E0, 0x5C380))
					(this_ptr, nullptr, bone, boneToWorld);
			}

			// returns bone index for given bone name
			/// @param this_ptr			C_BaseAnimating ptr
			/// @param bone_name		bone name
			/// @return					bone index
			inline int LookupBone(void* this_ptr, const char* bone_name)
			{
				// xref "weapon_bone"
				return utils::hook::call<int(__fastcall)(void* this_ptr, void* null, const char* bone_name)>(CLIENT_BASE + USE_OFFSET(0x5CE30, 0x59D30))
					(this_ptr, nullptr, bone_name);
			}

			// returns CStudioHdr pointer for given C_BaseAnimating pointer
			/// @param this_ptr			C_BaseAnimating ptr
			/// @return					CStudioHdr ptr
			inline CStudioHdr* GetModelPtr(void* this_ptr)
			{
				return utils::hook::call<CStudioHdr * (__fastcall)(void* this_ptr, void* null)>(CLIENT_BASE + USE_OFFSET(0x3FEA0, 0x3D040))
					(this_ptr, nullptr);
			}
		}
	}
	

	extern void lock_cursor();
	extern void unlock_cursor();


	// ::
	// debug print console redirects

	static void(WINAPI* OriginalOutputDebugStringA)(LPCSTR lpOutputString) = nullptr;
	static void(WINAPI* OriginalOutputDebugStringW)(LPCWSTR lpOutputString) = nullptr;

	inline void WINAPI HookedOutputDebugStringA(LPCSTR lpOutputString)
	{
		// guard against messages that came through the detoured "Warning/Msg" funcs as these were already printed to the console
		if (lpOutputString && !globals::detoured_warning_fn_origin && !globals::detoured_msg_fn_origin) {
			common::log("Game:Dbg >", lpOutputString, common::LOG_TYPE::LOG_TYPE_DEFAULT, false, false, true);
		}

		// og func
		if (OriginalOutputDebugStringA) {
			OriginalOutputDebugStringA(lpOutputString);
		}
	}

	inline void WINAPI HookedOutputDebugStringW(LPCWSTR lpOutputString)
	{
		if (lpOutputString)
		{
			char buffer[1024];
			WideCharToMultiByte(CP_UTF8, 0, lpOutputString, -1, buffer, sizeof(buffer), NULL, NULL);

			// guard against messages that came through the detoured "Warning/Msg" funcs as these were already printed to the console
			if (!globals::detoured_warning_fn_origin && !globals::detoured_msg_fn_origin) {
				common::log("Game:Dbg >", buffer, common::LOG_TYPE::LOG_TYPE_DEFAULT, true, false, true);
			}
		}

		// og func
		if (OriginalOutputDebugStringW) {
			OriginalOutputDebugStringW(lpOutputString);
		}
	}

	inline void SetupDebugOutputHook()
	{
		if (MH_CreateHook(&OutputDebugStringA, &HookedOutputDebugStringA, reinterpret_cast<LPVOID*>(&OriginalOutputDebugStringA)) != MH_OK)
		{
			common::log("Functions", "Failed to create hook for OutputDebugStringA", common::LOG_TYPE::LOG_TYPE_ERROR);
			return;
		}

		if (MH_CreateHook(&OutputDebugStringW, &HookedOutputDebugStringW, reinterpret_cast<LPVOID*>(&OriginalOutputDebugStringW)) != MH_OK)
		{
			common::log("Functions", "Failed to create hook for OutputDebugStringW", common::LOG_TYPE::LOG_TYPE_ERROR);
			return;
		}

		if (MH_EnableHook(&OutputDebugStringA) != MH_OK || MH_EnableHook(&OutputDebugStringW) != MH_OK)
		{
			common::log("Functions", "Failed to enable hooks for OutputDebugStringA & OutputDebugStringW", common::LOG_TYPE::LOG_TYPE_ERROR);
			return;
		}
	}
}
