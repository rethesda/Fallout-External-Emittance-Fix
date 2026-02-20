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