#include "nvse/PluginAPI.h"
#include "GameData.hpp"
#include <algorithm>

// TLDR
// Game resets the External Emittance color (Sunlight color of the weather) every time Player moves to a new region.
// Game doesn't check if new region shares the weather with the last one - it just forces color recalculation.
// Issue? Since there's no history of the previous weather, color blend calculations start from black, which obv paints every EE user dark for the first minute or so.
// This code aims to fix that by reusing current Sky weather if applicable, and keeping the data of the last used weather.

static const TESWeather* pCurrentRegionWeather = nullptr;

TESWeather* __fastcall TESRegion_GetWeather(TESRegion* apThis) {
	if (apThis->pCurrentWeather) {
		pCurrentRegionWeather = apThis->pCurrentWeather;
		return apThis->pCurrentWeather;
	}
	// Pass current weather in case TESRegion has none - game will default to the... default weather otherwise.
	Sky* pSky = Sky::GetSingleton();
	if (pSky->pCurrentWeather) {
		if (!pCurrentRegionWeather)
			pCurrentRegionWeather = pSky->pCurrentWeather;
		return pSky->pCurrentWeather;
	}
	return nullptr;
}

void __fastcall Sky_FillColorBlendColors(Sky* apThis, void*, Sky::COLOR_BLEND* apColorBlend, const TESWeather* apCurrentWeather, const TESWeather* apLastWeather, uint32_t aeColorType, uint32_t& aeTime1, uint32_t& aeTime2) {
	const TESWeather* pCurrentNormalWeather = apThis->pCurrentWeather;
	const TESWeather* pLastNormalWeather = apThis->pLastWeather;

	// May seem like a duplicate from GetWeather, but it's to handle the case where world is first loaded in.
	// (There's no current weather in Sky or TESRegion, so game creates default one for TESRegion before calling this function.
	if (!pCurrentRegionWeather)
		pCurrentRegionWeather = apCurrentWeather;

	// Duplicate colors of the TESRegion weather itself in case next checks fail - prevents starting from black
	apColorBlend->uiRGBVal[2] = apCurrentWeather->uiColorData[4][aeTime1];
	apColorBlend->uiRGBVal[3] = apCurrentWeather->uiColorData[4][aeTime2];

	// Use blend colors from current Sky weather if it's shared with TESRegion
	if (pCurrentNormalWeather && (pCurrentRegionWeather == pCurrentNormalWeather)) {
		apColorBlend->uiRGBVal[2] = pCurrentNormalWeather->uiColorData[4][aeTime1];
		apColorBlend->uiRGBVal[3] = pCurrentNormalWeather->uiColorData[4][aeTime2];
	}
	// Use blend colors from the last known weather from the Sky if it happens to be reused
	else if (pLastNormalWeather && (pCurrentRegionWeather == pLastNormalWeather)) {
		apColorBlend->uiRGBVal[2] = pLastNormalWeather->uiColorData[4][aeTime1];
		apColorBlend->uiRGBVal[3] = pLastNormalWeather->uiColorData[4][aeTime2];
	}

	// Finally, set blend colors for TESRegion weather
	apColorBlend->uiRGBVal[0] = apCurrentWeather->uiColorData[4][aeTime1];
	apColorBlend->uiRGBVal[1] = apCurrentWeather->uiColorData[4][aeTime2];
}


CallDetour kUpdateMatColorOrg;
void __fastcall BSShaderNoLighting_UpdateMaterialColor(void* apThis, void*, BSShaderProperty* apShaderProp, NiMaterialProperty* apMaterialProp) {
	// Check if Unk8 flag is set. If it is not, call the original function
	if ((apShaderProp->ulFlags[1] & BSShaderProperty::ShaderFlags2::UNK8) != 0) {
		NiColorA* const pMatColor = reinterpret_cast<NiColorA*>(0x1202010);

		// Grab the value of env map scale, use it as an index for the sky color
		int32_t iColor = static_cast<int32_t>(apShaderProp->fEnvMapScale);
		float fColorMult = 1.f;

		// Negative values enable emissive mult
		if (iColor < 0) {
			iColor = -iColor;
			fColorMult = apMaterialProp->m_fEmitMult;
		}

		iColor = std::clamp(iColor, 0, 9);

		const Sky* pSky = Sky::GetSingleton();
		pMatColor->r = pSky->kColors[iColor].r * fColorMult;
		pMatColor->g = pSky->kColors[iColor].g * fColorMult;
		pMatColor->b = pSky->kColors[iColor].b * fColorMult;
		pMatColor->a = std::min(apShaderProp->fAlpha, 1.f);
	}
	else {
		ThisCall(kUpdateMatColorOrg.GetOverwrittenAddr(), apThis, apShaderProp, apMaterialProp);
	}
}

VirtFuncDetour kCreateCloneOrg;
BSShaderProperty* __fastcall BSShaderNoLightingProperty_CreateClone(BSShaderProperty* apThis, void*, void* apCloneProc) {
	BSShaderProperty* pClone = ThisCall<BSShaderProperty*>(kCreateCloneOrg.GetOverwrittenAddr(), apThis, apCloneProc);
	pClone->fEnvMapScale = apThis->fEnvMapScale;
	return pClone;
}

EXTERN_DLL_EXPORT bool NVSEPlugin_Query(const NVSEInterface* nvse, PluginInfo* info) {
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "External Emittance Fix";
	info->version = 131;

	return !nvse->isEditor;
}

EXTERN_DLL_EXPORT bool NVSEPlugin_Load(NVSEInterface* nvse) {
	ReplaceCall(0x551ECE, TESRegion_GetWeather);
	ReplaceCall(0x55215C, TESRegion_GetWeather);

	ReplaceCall(0x551F5F, Sky_FillColorBlendColors);
	ReplaceCall(0x552205, Sky_FillColorBlendColors);

	// Bonus feature creep - allows setting BSShaderNoLightingProperty's emissive color to one of the sky colors, by setting the Envmap_Light_Fade flag and using env map scale as an index for the color.
	// Credit to Xilandro
	{
		kUpdateMatColorOrg.ReplaceCall(0xBC9B15, BSShaderNoLighting_UpdateMaterialColor);

		// Fixes the issue with the env map scale not being copied over to the cloned shader property
		kCreateCloneOrg.ReplaceVirtualFunc(0x10AE6B8, BSShaderNoLightingProperty_CreateClone);
	}
	return true;
}