#include "std_include.hpp"

#include "components/modules/interfaces.hpp"

namespace glob
{
	bool spawned_external_console = false;
	bool has_debug_arg = false;
	HWND main_window = nullptr;
	sdk::InputContext_t* input_context = nullptr;
}

namespace game
{
	utils::mem::module_info shaderapidx9_module = {};
	utils::mem::module_info studiorender_module = {};
	utils::mem::module_info materialsystem_module = {};
	utils::mem::module_info engine_module = {};
	utils::mem::module_info client_module = {};
	utils::mem::module_info server_module = {};
	utils::mem::module_info vstdlib_module = {};

	const D3DXMATRIX IDENTITY =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	const D3DXMATRIX TC_TRANSLATE_TO_CENTER =
	{
		 1.0f,  0.0f, 0.0f, 0.0f,	// identity
		 0.0f,  1.0f, 0.0f, 0.0f,	// identity
		 0.0f,  0.0f, 1.0f, 0.0f,	// identity
		-0.5f, -0.5f, 0.0f, 1.0f,	// translate to center
	};

	const D3DXMATRIX TC_TRANSLATE_FROM_CENTER_TO_TOP_LEFT =
	{
		1.0f, 0.0f, 0.0f, 0.0f,	// identity
		0.0f, 1.0f, 0.0f, 0.0f,	// identity
		0.0f, 0.0f, 1.0f, 0.0f,	// identity
		0.5f, 0.5f, 0.0f, 1.0f,	// translate back to the top left corner
	};

	view_id saved_view_id = VIEW_ILLEGAL;

	// ----------

	ConVar* find_cvar(const char* name)
	{
		if (const auto ivar = interfaces::get()->m_cvar; ivar) {
			return ivar->find_var(name);
		}
		return nullptr;
	}

	const ConVar* find_cvar_const(const char* name)
	{
		if (const auto ivar = interfaces::get()->m_cvar; ivar) {
			return ivar->find_var(name);
		}
		return nullptr;
	}

	// adds a simple console command
	void con_add_command(ConCommand* cmd, const char* name, void(__cdecl* callback)(), const char* desc)
	{
		// ConCommand *this, const char *pName, void (__cdecl *callback)(), const char *pHelpString, int flags, int (__cdecl *completionFunc)(const char *, char (*)[64]
		utils::hook::call<void(__fastcall)(ConCommand* this_ptr, void* null, const char*, void(__cdecl*)(), const char*, int, int(__cdecl*)(const char*, char(*)[64]))>(p2::fn_addr__add_console_cmd)
			(cmd, nullptr, name, callback, desc, 0x20000, nullptr);
	}

	/**
	 * Calls CDebugOverlay::AddTextOverlay
	 * @param pos		Position of text in 3D Space
	 * @param duration	Duration in which text is visible - use 0.0f for per frame stuff
	 * @param text		The text
	 */
	void debug_add_text_overlay(const float* pos, float duration, const char* text)
	{
		utils::hook::call<void(__cdecl)(const float*, float, const char*)>(p2::fn_addr__debug_overlay_add_text)
			(pos, duration, text);
	}

	/**
	 * Calls CDebugOverlay::AddTextOverlay
	 * @param pos			Position of text in 3D Space
	 * @param text			The text
	 * @param line_offset	Offset text position
	 * @param r				red (0-1)
	 * @param g				green (0-1)
	 * @param b				blue (0-1)
	 * @param a				alpha (0-1)
	 */
	void debug_add_text_overlay(const float* pos, const char* text, const int line_offset, const float r, const float g, const float b, const float a)
	{
		utils::hook::call<void(__cdecl)(const float*, int, float, float, float, float, float, const char*)>(p2::fn_addr__debug_overlay_add_text_colored)
			(pos, line_offset, 0.0f, r, g, b, a, text);
	}

	// remove/destroy a given CBaseEntity - not needed with deprecated marker system
/*	void cbaseentity_remove(void* cbaseentity_ptr)
	{
		if (cbaseentity_ptr)
		{
			// UTIL_Remove
			utils::hook::call<void(__cdecl)(void* cbaseentity)>(SERVER_BASE + USE_OFFSET(0x283770, 0x27D690))(cbaseentity_ptr);
		}
	}*/

	int get_visframecount() {
		return *p2::r_visframecount; //*reinterpret_cast<int*>(ENGINE_BASE + USE_OFFSET(0x6AAE6C, 0x6A56B4));
	}

	const char* get_map_name() {
		return utils::hook::call<const char*(__cdecl)()>(p2::fn_addr__get_map_name)();
	}

	void r_flow_through_area(const int area, const Vector* vec_vis_origin, const CPortalRect* clip_rect, const VisOverrideData_t* vis_data, float* reflection_water_height)
	{
		utils::hook::call<void(__cdecl)(int, const Vector*, const CPortalRect*, const VisOverrideData_t*, float*)>(p2::fn_addr__r_flow_through_area)
			(area, vec_vis_origin, clip_rect, vis_data, reflection_water_height);
	}

	// Frustum_t::SetPlanes
	void frustum_set_planes(Frustum_t* frustum, const VPlane* planes)
	{
		utils::hook::call<void(__fastcall)(Frustum_t*, void* null, const VPlane*)>(p2::fn_addr__frustum_set_planes)
			(frustum, nullptr, planes);
	}

	// Frustum_t::CullBox
	bool frustum_cull_box(Frustum_t* frustum, const Vector* mins, const Vector* maxs)
	{
		return utils::hook::call<bool(__fastcall)(void* this_ptr, void* null, const Vector*, const Vector*)>(p2::fn_addr__frustum_cull_box)
			(frustum, nullptr, mins, maxs);
	}

	// was just var->m_nFlags &= ~0x4000;
	void cvar_uncheat(const char* name)
	{
		if (const auto ivar = interfaces::get()->m_cvar; ivar)
		{
			if (auto var = ivar->find_var(name); var)
			{
				var->m_nFlags &= ~(1 << 1); // FCVAR_DEVELOPMENTONLY
				var->m_nFlags &= ~(1 << 4); // FCVAR_HIDDEN
				var->m_nFlags &= ~(1 << 14); // FCVAR_CHEAT
			}
		}
	}

	void cvar_uncheat_and_set_int(const char* name, const int val)
	{
		if (const auto ivar = interfaces::get()->m_cvar; ivar)
		{
			if (auto var = ivar->find_var(name); var)
			{
				var->vtbl->SetValue_Int(var, val);
				var->m_nFlags &= ~(1 << 1); // FCVAR_DEVELOPMENTONLY
				var->m_nFlags &= ~(1 << 4); // FCVAR_HIDDEN
				var->m_nFlags &= ~(1 << 14); // FCVAR_CHEAT
			}
		}
	}

	void cvar_uncheat_and_set_float(const char* name, const float val)
	{
		if (const auto ivar = interfaces::get()->m_cvar; ivar)
		{
			if (auto var = ivar->find_var(name); var)
			{
				var->vtbl->SetValue_Float(var, val);
				var->m_nFlags &= ~(1 << 1); // FCVAR_DEVELOPMENTONLY
				var->m_nFlags &= ~(1 << 4); // FCVAR_HIDDEN
				var->m_nFlags &= ~(1 << 14); // FCVAR_CHEAT
			}
		}
	}

	typedef void(__cdecl* msg_fn)(const char* msg, va_list);
	void print_ingame(const char* msg, ...)
	{
		if (msg == nullptr) {
			return;
		}

		static msg_fn fn = (msg_fn)GetProcAddress(GetModuleHandleA("tier0.dll"), "Msg");
		char buffer[989];

		va_list list;
		va_start(list, msg);
		vsprintf(buffer, msg, list);
		perror(buffer);
		va_end(list);
		fn(buffer, list);
	}


	void lock_cursor()
	{
		const auto input = interfaces::get()->m_input_system;

		if (!glob::input_context) {
			glob::input_context = input->push_input_context();
		}

		input->enable_input_context(glob::input_context, true);
		input->set_cursor_visible(glob::input_context, false);
		input->set_mouse_capture(glob::input_context, true);

		ImGui::GetIO().MouseDrawCursor = true;
	}

	void unlock_cursor()
	{
		const auto input = interfaces::get()->m_input_system;

		const int width = (int)(ImGui::GetIO().DisplaySize.x / 2.0f);
		const int height = (int)(ImGui::GetIO().DisplaySize.y / 2.0f);

		if (glob::input_context)
		{
			if (input->is_topmost_enabled_context(glob::input_context)) {
				input->set_cursor_position(glob::input_context, width, height);
			}

			input->enable_input_context(glob::input_context, false);
		}

		ImGui::GetIO().MouseDrawCursor = false;
		//input->get_raw_mouse_accumulators(&width, &height);
	}

	C_BaseAnimating* get_base_animating_for_client_renderable(IClientRenderable* pRenderable)
	{
		if (pRenderable)
		{
			if (const auto unkown = pRenderable->vftable_iclientrenderable->GetIClientUnknown(pRenderable);
				unkown)
			{
				if (const auto base_handle = unkown->vftable_ihandleent->GetRefEHandle(unkown);
					base_handle)
				{
					if (const auto base_entity = interfaces::get()->m_entity_list->get_client_entity_from_handle(*base_handle); base_entity) {
						return base_entity->vtbl->GetBaseAnimating(base_entity);
					}
				}
			}
		}

		return nullptr;
	}
}
