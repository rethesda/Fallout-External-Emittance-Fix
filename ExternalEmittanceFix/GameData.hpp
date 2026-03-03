#pragma once

class NiColor {
public:
	float r, g, b;
};

class NiColorA {
public:
	float r, g, b, a;
};

class BSShaderProperty {
public:
	struct ALIGN4 _ShaderFlags {
		struct _Bits {
			enum Bits {
				SPECULAR						= 0,
				SKINNED							= 1,
				LOW_DETAIL						= 2,
				VERTEX_ALPHA					= 3,
				MOTION_BLUR						= 4,
				SINGLE_PASS						= 5,
				FALLOFF							= 6,
				ENVIRONMENT_MAPPING				= 7,
				ALPHA_TEXTURE					= 8,
				ZPREPASS						= 9,
				FACEGEN							= 10,
				PARALLAX						= 11,
				MODEL_SPACE_NORMALS				= 12,
				NON_PROJECTIVE_SHADOWS			= 13,
				LANDSCAPE						= 14,
				REFRACTION						= 15,
				FIRE_REFRACTION					= 16,
				EYE_ENVIRONMENT_MAPPING			= 17,
				HAIR							= 18,
				DYNAMIC_ALPHA					= 19,
				LOCAL_MAP_HIDE_SECRET			= 20,
				WINDOW_ENVIRONMENT_MAPPING		= 21,
				TREE_BILLBOARD					= 22,
				SHADOW_FRUSTUM					= 23,
				MULTIPLE_TEXTURES				= 24,
				REMAPPABLE_TEXTURES				= 25,
				DECAL							= 26,
				DYNAMIC_DECAL					= 27,
				PARALLAX_OCCLUSION				= 28,
				EXTERNAL_EMITTANCE				= 29,
				SHADOW_MAP						= 30,
				ZBUFFER_TEST					= 31,
				ZBUFFER_WRITE					= 32,
				LOD_LANDSCAPE					= 33,
				LOD_BUILDING					= 34,
				NO_FADE							= 35,
				REFRACTION_TINT					= 36,
				VERTEX_COLORS					= 37,
				FIRST_PERSON					= 38,
				FIRST_LIGHT_IS_POINTLIGHT		= 39,
				SECOND_LIGHT					= 40,
				THIRD_LIGHT						= 41,
				VERTEX_LIGHTING					= 42,
				UNIFORM_SCALE					= 43,
				FIT_SLOPE						= 44,
				BILLBOARD_ENV_FADE				= 45,
				NO_LOD_LAND_BLEND				= 46,
				ENVMAP_LIGHT_FADE				= 47,
				WIRE_FRAME						= 48,
				VATS_SELECTION					= 49,
				SHOW_IN_LOCAL_MAP				= 50,
				PREMULT_ALPHA					= 51,
				SKIP_NORMAL_MAPS				= 52,
				ALPHA_DECAL						= 53,
				NO_TRANSPARENCY_MULTISAMPLING	= 54,
				STINGER_PROP					= 55,
				UNK3							= 56,
				UNK4							= 57,
				UNK5							= 58,
				UNK6							= 59,
				UNK7							= 60,
				UNK8							= 61,
				SOFT_DEPTH						= 62,
				REALTIME_CUBEMAP				= 63,
				MAX_FLAGS						= 64
			};
		};
		using Bits = _Bits::Bits;

		struct _Flags {
			enum Flags1 : uint32_t {
				SPECULAR						= 1u << Bits::SPECULAR,
				SKINNED							= 1u << Bits::SKINNED,
				LOW_DETAIL						= 1u << Bits::LOW_DETAIL,
				VERTEX_ALPHA					= 1u << Bits::VERTEX_ALPHA,
				MOTION_BLUR						= 1u << Bits::MOTION_BLUR,
				SINGLE_PASS						= 1u << Bits::SINGLE_PASS,
				FALLOFF							= 1u << Bits::FALLOFF,
				ENVIRONMENT_MAPPING				= 1u << Bits::ENVIRONMENT_MAPPING,
				ALPHA_TEXTURE					= 1u << Bits::ALPHA_TEXTURE,
				ZPREPASS						= 1u << Bits::ZPREPASS,
				FACEGEN							= 1u << Bits::FACEGEN,
				PARALLAX						= 1u << Bits::PARALLAX,
				MODEL_SPACE_NORMALS				= 1u << Bits::MODEL_SPACE_NORMALS,
				NON_PROJECTIVE_SHADOWS			= 1u << Bits::NON_PROJECTIVE_SHADOWS,
				LANDSCAPE						= 1u << Bits::LANDSCAPE,
				REFRACTION						= 1u << Bits::REFRACTION,
				FIRE_REFRACTION					= 1u << Bits::FIRE_REFRACTION,
				EYE_ENVIRONMENT_MAPPING			= 1u << Bits::EYE_ENVIRONMENT_MAPPING,
				HAIR							= 1u << Bits::HAIR,
				DYNAMIC_ALPHA					= 1u << Bits::DYNAMIC_ALPHA,
				LOCAL_MAP_HIDE_SECRET			= 1u << Bits::LOCAL_MAP_HIDE_SECRET,
				WINDOW_ENVIRONMENT_MAPPING		= 1u << Bits::WINDOW_ENVIRONMENT_MAPPING,
				TREE_BILLBOARD					= 1u << Bits::TREE_BILLBOARD,
				SHADOW_FRUSTUM					= 1u << Bits::SHADOW_FRUSTUM,
				MULTIPLE_TEXTURES				= 1u << Bits::MULTIPLE_TEXTURES,
				REMAPPABLE_TEXTURES				= 1u << Bits::REMAPPABLE_TEXTURES,
				DECAL							= 1u << Bits::DECAL,
				DYNAMIC_DECAL					= 1u << Bits::DYNAMIC_DECAL,
				PARALLAX_OCCLUSION				= 1u << Bits::PARALLAX_OCCLUSION,
				EXTERNAL_EMITTANCE				= 1u << Bits::EXTERNAL_EMITTANCE,
				SHADOW_MAP						= 1u << Bits::SHADOW_MAP,
				ZBUFFER_TEST					= 1u << Bits::ZBUFFER_TEST,
			};
			
			enum Flags2 : uint32_t {
				ZBUFFER_WRITE					= 1u << (Bits::ZBUFFER_WRITE - 32),
				LOD_LANDSCAPE					= 1u << (Bits::LOD_LANDSCAPE - 32),
				LOD_BUILDING					= 1u << (Bits::LOD_BUILDING - 32),
				NO_FADE							= 1u << (Bits::NO_FADE - 32),
				REFRACTION_TINT					= 1u << (Bits::REFRACTION_TINT - 32),
				VERTEX_COLORS					= 1u << (Bits::VERTEX_COLORS - 32),
				FIRST_PERSON					= 1u << (Bits::FIRST_PERSON - 32),
				FIRST_LIGHT_IS_POINTLIGHT		= 1u << (Bits::FIRST_LIGHT_IS_POINTLIGHT - 32),
				SECOND_LIGHT					= 1u << (Bits::SECOND_LIGHT - 32),
				THIRD_LIGHT						= 1u << (Bits::THIRD_LIGHT - 32),
				VERTEX_LIGHTING					= 1u << (Bits::VERTEX_LIGHTING - 32),
				UNIFORM_SCALE					= 1u << (Bits::UNIFORM_SCALE - 32),
				FIT_SLOPE						= 1u << (Bits::FIT_SLOPE - 32),
				BILLBOARD_ENV_FADE				= 1u << (Bits::BILLBOARD_ENV_FADE - 32),
				NO_LOD_LAND_BLEND				= 1u << (Bits::NO_LOD_LAND_BLEND - 32),
				ENVMAP_LIGHT_FADE				= 1u << (Bits::ENVMAP_LIGHT_FADE - 32),
				WIRE_FRAME						= 1u << (Bits::WIRE_FRAME - 32),
				VATS_SELECTION					= 1u << (Bits::VATS_SELECTION - 32),
				SHOW_IN_LOCAL_MAP				= 1u << (Bits::SHOW_IN_LOCAL_MAP - 32),
				PREMULT_ALPHA					= 1u << (Bits::PREMULT_ALPHA - 32),
				SKIP_NORMAL_MAPS				= 1u << (Bits::SKIP_NORMAL_MAPS - 32),
				ALPHA_DECAL						= 1u << (Bits::ALPHA_DECAL - 32),
				NO_TRANSPARENCY_MULTISAMPLING	= 1u << (Bits::NO_TRANSPARENCY_MULTISAMPLING - 32),
				STINGER_PROP					= 1u << (Bits::STINGER_PROP - 32),
				UNK3							= 1u << (Bits::UNK3 - 32),
				UNK4							= 1u << (Bits::UNK4 - 32),
				UNK5							= 1u << (Bits::UNK5 - 32),
				UNK6							= 1u << (Bits::UNK6 - 32),
				UNK7							= 1u << (Bits::UNK7 - 32),
				UNK8							= 1u << (Bits::UNK8 - 32),
				SOFT_DEPTH						= 1u << (Bits::SOFT_DEPTH - 32),
				REALTIME_CUBEMAP				= 1u << (Bits::REALTIME_CUBEMAP - 32),
			};
		};
		using Flags1 = _Flags::Flags1;
		using Flags2 = _Flags::Flags2;
	};
	using ShaderBits = _ShaderFlags::_Bits::Bits;
	using ShaderFlags1 = _ShaderFlags::_Flags::Flags1;
	using ShaderFlags2 = _ShaderFlags::_Flags::Flags2;

	uint32_t	padding[8];
	uint32_t	ulFlags[2];
	float		fAlpha;
	float		fFadeAlpha;
	float		fEnvMapScale;
};

class NiMaterialProperty {
public:
	uint32_t	padding[16];
	float		m_fEmitMult;
};

class TESWeather {
public:
	enum COLOR_TYPE : uint32_t {
		COLOR_SKY_UPPER		= 0,
		COLOR_FOG			= 1,
		COLOR_CLOUDS_LOWER	= 2,
		COLOR_AMBIENT		= 3,
		COLOR_SUNLIGHT		= 4,
		COLOR_SUN			= 5,
		COLOR_STARS			= 6,
		COLOR_SKY_LOWER		= 7,
		COLOR_HORIZON		= 8,
		COLOR_CLOUDS_UPPER	= 9,
		COLOR_COUNT,
	};

	enum COLOR_TIME : uint32_t {
		TIME_SUNRISE	= 0,
		TIME_DAY		= 1,
		TIME_SUNSET		= 2,
		TIME_NIGHT		= 3,
		TIME_HIGH_NOON	= 4,
		TIME_MIDNIGHT	= 5,
		TIME_COUNT,
	};

	uint32_t	padding[66];
	uint32_t	uiColorData[COLOR_COUNT][TIME_COUNT];
};

class TESRegion {
public:
	uint32_t		padding[9];
	TESWeather*		pCurrentWeather;
};

class Sky {
public:
	struct COLOR_BLEND {
		uint32_t	uiRGBVal[4];
		float		fBlend[4];
	};

	enum SkyColors {
		SC_SKY_UPPER	= 0,
		SC_FOG			= 1,
		SC_CLOUDS_LOWER = 2,
		SC_AMBIENT		= 3,
		SC_SUNLIGHT		= 4,
		SC_SUN			= 5,
		SC_STARS		= 6,
		SC_SKY_LOWER	= 7,
		SC_HORIZON		= 8,
		SC_CLOUDS_UPPER = 9,
		SC_COUNT,
	};

	uint32_t						padding[4];
	TESWeather*						pCurrentWeather;
	TESWeather*						pLastWeather;
	TESWeather*						pDefaultWeather;
	TESWeather*						pOverrideWeather;
	class Atmosphere*				pAtmosphere;
	class Stars*					pStars;
	class Sun*						pSun;
	class Clouds*					pClouds;
	class Moon*						pMasser;
	class Moon*						pSecunda;
	class Precipitation*			pPrecipitation;
	NiColor							kColors[SC_COUNT];

	static Sky* GetSingleton() {
		return *reinterpret_cast<Sky**>(0x11DEA20);
	}
};