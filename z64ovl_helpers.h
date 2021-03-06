#ifndef Z64OVL_HELPERS_H_INCLUDED_MAIN
#define Z64OVL_HELPERS_H_INCLUDED_MAIN

/****
 * helpers.h
 * A collection of functions and macros to
 * help simplify custom enemies/NPCs/bosses.
 ***/

#if 0
	/* helpers.h is meant to work with both OoT and MM.   *
	 * This way, shared helpers needn't be maintained     *
	 * separately, names remain consistent, and compiling *
	 * overlays for both games will be easier.            *
	 * Write helpers using the following structure:       */
	static
	inline
	z64_player_t *
	zh_get_player(z64_global_t *global)
	{
	#if ZH_OOT
		/* OoT-specific code */
	#elif ZH_MM
		/* MM-specific code */
	#endif
	}
#endif

/* external, self-contained helpers */
#include "zh/sprintf.h"
/*
void
zh_sprintf(char *dst, char *fmt, struct va_arr *va_arr)

example:
	char buf[128];
	int x = 0xABC;
	zh_sprintf(
		buf
		, "%s-%c, under the sea... 0x%X, %d, %f"
		, VA_ARR(
			"tunafish"
			, VA_ARR_c('Z')
			, &x
			, VA_ARR_d(256)
			, VA_ARR_f(1024.56789f)
		)
	);
*/

#if OOT_DEBUG || OOT_U_1_0
#	define ZH_OOT 1
#elif MM_U_1_0
#	define ZH_MM  1
#else
#	error z64_helpers.h: must define OOT_DEBUG, OOT_U_1_0, or MM_U_1_0 before including!
#endif

/*** Macros ***/

 /* Shorthand for referencing Graphics Context display list buffers "Zelda Quick Display List" */
#define ZQDL(ZQDL_A0, ZQDL_A1) ZQDL_A0->common.gfx_ctxt->ZQDL_A1

static inline float zh_math_fminf(float a, float b)
{
	return a < b ? a : b;
}

static inline float zh_math_fmaxf(float a, float b)
{
	return a > b ? a : b;
}

/****
 * convert a relative segment address to an absolute RAM address
 ***/
static
inline
uint32_t
zh_seg2ram(uint32_t addr)
{
	return (
		AVAL(
			(RAM_SEGMENT_TABLE + (addr >> 22) )
			, uint32_t
			, 0
		) + (addr & 0x00FFFFFF)) | 0x80000000
	;
}

/****
 * _Printf printer. Write text to a RAM address.
 ***/
 static
 inline
 void
 *zh_ram_printer(void *a0, const char *a1, size_t a2)
 {
 	if (a2 == 0) return 0;
 	char *dst = a0;
 	while (a2--)
 	*(dst++) = *(a1++);
 	return dst;
 }

/****
 * test for Link's age
 ***/
static
inline
int
zh_link_is_child(void)
{
	return AVAL(Z64GL_SAVE_CONTEXT, int, 0x0004);
}

static
inline
int
zh_link_is_adult(void)
{
	return !zh_link_is_child();
}

/****
 * zh_player_textbox_selection
 * use this function if player_responded_to_textbox() returns true (1).
 * returns the last textbox selection made by the player
 * 0 = first option was selected
 * 1 = second
 * 2 = third
 ***/
static
inline
int
zh_player_textbox_selection(z64_global_t *global)
{
	/* TODO use named structure element instead *
	 *      of AVAL + magic number              */
	return
		AVAL(
			global
			, uint8_t
			#if ZH_OOT
			, 0x104BD
			#elif ZH_MM
			, 0x16929
			#warning needs (NZSE) confirmation!
			#endif
		)
	;
}


/****
 * zh_get_pointer_to_object_data
 * given an object ID, returns a pointer to its location in ram, or NULL if not loaded
 ***/
static
inline
void *
zh_get_pointer_to_object_data(uint16_t object_id, z64_global_t *global)
{
	/* TODO use named structure element *
	 *      instead of magic number     */

	int index;

	index =
		object_get_index
		(
			(u32)AADDR
			(
				global
				#if ZH_OOT
				, 0x117A4
				#elif ZH_MM
				, 0x17D88
				#warning needs (NZSE) confirmation!
				#endif
			)
			, object_id
		)
	;

	if(index < 0)
		return NULL;

	return
		*(u32*)AADDR
		(
			(((index << 4) + index) << 2) + (u32)global
			, 0x117B4
		)
	;
}


/****
 * zh_get_save_context
 * Returns a pointer to Save Context
 ***/
static
inline
void *
zh_get_save_context(z64_global_t *global)
{
	/* TODO returning type z64_saveContext_t would be nice */
	/* TODO also, grab it from within global to avoid magic numbers */
	return (void*)AADDR(Z64GL_SAVE_CONTEXT, 0);
}

/****
 * zh_get_player
 * Used to return a pointer to the player's instance.
 ***/
static
inline
z64_player_t *
zh_get_player(z64_global_t *global)
{
	/* TODO cleanup */
	/* TODO eliminate magic numbers; grab from global directly */
	/* TODO must also support MM */
	uint8_t *g = (uint8_t*) global;
#if ZH_OOT
	g += 0x1C44;
#elif ZH_MM
	g += 0x1CCC;
#endif
	uint32_t p32 = (g[0]<<24)|(g[1]<<16)|(g[2]<<8)|g[3];
	return (z64_player_t*)p32;
}

/****
 * Tests if object can be lifted with "grab" action.
 * Give an Item ID of 0
 ****/
static
inline
void
helper_lift_test(
	z64_actor_t *a
	, z64_global_t *gl
	, float range_xz
	, float range_y
)
{
	int temp_v0;
	int phi_v1;

	temp_v0 =
		(int)
		(
			(a->rot_toward_link_y - (zh_get_player(gl)->actor.xz_dir))
			<< 0x10
		) >> 0x10
	;

	phi_v1 = (0 - temp_v0);

	if (temp_v0 >= 0)
		phi_v1 = temp_v0;

	if (phi_v1 >= 0x5556)
		actor_give_item(a, gl, 0, range_xz, range_y);
}

 /****
 * makes helper_limb_focus available
 * helper_limb_focus sets the limb to be Z-Targeted as well as camera focus information
 * the address of the function helper_limb_focus can then be used inside actor_skelanime_draw_mtx
 * TODO a2 and a3; names would be nice, although they do seem to be abstracted for us
 * TODO does this work in MM?
 * example, from Grog:
 * * #include <z64ovl/helpers.h>
 * * ...
 * * HELPER_INCLUDE_helper_limb_focus( 9, 300.0f, 1000.0f, 0.0f )
 * * ...
 * * actor_skelanime_draw_mtx(x, x, x, x, x, &helper_limb_focus, x);
 ***/
#define HELPER_INCLUDE_helper_limb_focus( TARGET_LIMB, IN_VEC3_X, IN_VEC3_Y, IN_VEC3_Z )\
static void helper_limb_focus(z64_global_t *global, uint8_t limb, uint32_t dlist, vec3s_t *rot, z64_actor_t *actor)\
{\
	if (limb == TARGET_LIMB)\
	{\
		vec3f_t in = { IN_VEC3_X, IN_VEC3_Y, IN_VEC3_Z };\
		external_func_800D1AF4(&in, &actor->pos_3);\
	}\
}

/****
 * basic eye blink function
 * returns a value 0, 1, or 2, for use with an array of eye texture offsets, corresponding to open, half-open, and closed eye textures, respectively
 * this function is identical to how NPC eye blinking works in OoT:
 * 1 the random value range (30, 30) comes from OoT
 * 2 eyes are open for a random number of frames
 * 3 half-open for one frame
 * 4 closed for one frame
 * 5 back open, restart from the beginning with a new random value
 ***/
static
inline
unsigned char
helper_eye_blink(int16_t *frame) {
	if( *frame == 0 ) // get random number of frames until next blink
		*frame = math_rand_s16_offset(30, 30);
	*frame -= 1;
	if( *frame > 1 ) // open
		return 0;
	return 2 - *frame; // half-open for a frame, then closed for a frame
}

/****
* Overlay Display List Drawing
*****/

#include "zh/colors.h"
#include "zh/gfx.h"


#endif /* Z64OVL_HELPERS_H_INCLUDED_MAIN */
