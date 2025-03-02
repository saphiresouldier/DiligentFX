"#ifndef _BASIC_STRUCTURES_FXH_\n"
"#define _BASIC_STRUCTURES_FXH_\n"
"\n"
"\n"
"#ifdef __cplusplus\n"
"\n"
"#   ifndef BOOL\n"
"#      define BOOL int32_t // Do not use bool, because sizeof(bool)==1 !\n"
"#   endif\n"
"\n"
"#   ifndef CHECK_STRUCT_ALIGNMENT\n"
"        // Note that defining empty macros causes GL shader compilation error on Mac, because\n"
"        // it does not allow standalone semicolons outside of main.\n"
"        // On the other hand, adding semicolon at the end of the macro definition causes gcc error.\n"
"#       define CHECK_STRUCT_ALIGNMENT(s) static_assert( sizeof(s) % 16 == 0, \"sizeof(\" #s \") is not multiple of 16\" )\n"
"#   endif\n"
"\n"
"#   ifndef DEFAULT_VALUE\n"
"#       define DEFAULT_VALUE(x) =x\n"
"#   endif\n"
"\n"
"#else\n"
"\n"
"#   ifndef BOOL\n"
"#       define BOOL bool\n"
"#   endif\n"
"\n"
"#   ifndef DEFAULT_VALUE\n"
"#       define DEFAULT_VALUE(x)\n"
"#   endif\n"
"\n"
"#endif\n"
"\n"
"\n"
"struct CascadeAttribs\n"
"{\n"
"	float4 f4LightSpaceScale;\n"
"	float4 f4LightSpaceScaledBias;\n"
"    float4 f4StartEndZ;\n"
"\n"
"    // Cascade margin in light projection space ([-1, +1] x [-1, +1] x [-1(GL) or 0, +1])\n"
"    float4 f4MarginProjSpace;\n"
"};\n"
"#ifdef CHECK_STRUCT_ALIGNMENT\n"
"    CHECK_STRUCT_ALIGNMENT(CascadeAttribs);\n"
"#endif\n"
"\n"
"#define SHADOW_MODE_PCF 1\n"
"#define SHADOW_MODE_VSM 2\n"
"#define SHADOW_MODE_EVSM2 3\n"
"#define SHADOW_MODE_EVSM4 4\n"
"#ifndef SHADOW_MODE\n"
"#   define SHADOW_MODE SHADOW_MODE_PCF\n"
"#endif\n"
"\n"
"#define MAX_CASCADES 8\n"
"struct ShadowMapAttribs\n"
"{\n"
"    // 0\n"
"#ifdef __cplusplus\n"
"    float4x4 mWorldToLightViewT; // Matrices in HLSL are COLUMN-major while float4x4 is ROW major\n"
"#else\n"
"    matrix mWorldToLightView;  // Transform from view space to light projection space\n"
"#endif\n"
"    // 16\n"
"    CascadeAttribs Cascades[MAX_CASCADES];\n"
"\n"
"#ifdef __cplusplus\n"
"    float4x4 mWorldToShadowMapUVDepthT[MAX_CASCADES];\n"
"    float fCascadeCamSpaceZEnd[MAX_CASCADES];\n"
"#else\n"
"    matrix mWorldToShadowMapUVDepth[MAX_CASCADES];\n"
"    float4 f4CascadeCamSpaceZEnd[MAX_CASCADES/4];\n"
"#endif\n"
"\n"
"    float4 f4ShadowMapDim;    // Width, Height, 1/Width, 1/Height\n"
"\n"
"    // Number of shadow cascades\n"
"    int   iNumCascades                  DEFAULT_VALUE(0);\n"
"    float fNumCascades                  DEFAULT_VALUE(0);\n"
"    // Do not use bool, because sizeof(bool)==1 !\n"
"	BOOL  bVisualizeCascades            DEFAULT_VALUE(0);\n"
"    BOOL  bVisualizeShadowing           DEFAULT_VALUE(0);\n"
"\n"
"    float fReceiverPlaneDepthBiasClamp  DEFAULT_VALUE(10);\n"
"    float fFixedDepthBias               DEFAULT_VALUE(1e-5f);\n"
"    float fCascadeTransitionRegion      DEFAULT_VALUE(0.1f);\n"
"    int   iMaxAnisotropy                DEFAULT_VALUE(4);\n"
"\n"
"    float fVSMBias                      DEFAULT_VALUE(1e-4f);\n"
"    float fVSMLightBleedingReduction    DEFAULT_VALUE(0);\n"
"    float fEVSMPositiveExponent         DEFAULT_VALUE(40);\n"
"    float fEVSMNegativeExponent         DEFAULT_VALUE(5);\n"
"\n"
"    BOOL  bIs32BitEVSM                  DEFAULT_VALUE(1);\n"
"    int   iFixedFilterSize              DEFAULT_VALUE(3); // 3x3 filter\n"
"    float fFilterWorldSize              DEFAULT_VALUE(0);\n"
"    bool  fDummy;\n"
"};\n"
"#ifdef CHECK_STRUCT_ALIGNMENT\n"
"    CHECK_STRUCT_ALIGNMENT(ShadowMapAttribs);\n"
"#endif\n"
"\n"
"struct LightAttribs\n"
"{\n"
"    float4 f4Direction      DEFAULT_VALUE(float4(0, 0,-1, 0));\n"
"    float4 f4AmbientLight   DEFAULT_VALUE(float4(0, 0, 0, 0));\n"
"    float4 f4Intensity      DEFAULT_VALUE(float4(1, 1, 1, 1));\n"
"\n"
"    ShadowMapAttribs ShadowAttribs;\n"
"};\n"
"#ifdef CHECK_STRUCT_ALIGNMENT\n"
"    CHECK_STRUCT_ALIGNMENT(LightAttribs);\n"
"#endif\n"
"\n"
"struct CameraAttribs\n"
"{\n"
"    float4 f4Position;     // Camera world position\n"
"    float4 f4ViewportSize; // (width, height, 1/width, 1/height)\n"
"\n"
"    float2 f2ViewportOrigin; // (min x, min y)\n"
"    float fNearPlaneZ;\n"
"    float fFarPlaneZ; // fNearPlaneZ < fFarPlaneZ\n"
"\n"
"#ifdef __cplusplus\n"
"    float4x4 mViewT;\n"
"    float4x4 mProjT;\n"
"    float4x4 mViewProjT;\n"
"    float4x4 mViewInvT;\n"
"    float4x4 mProjInvT;\n"
"    float4x4 mViewProjInvT;\n"
"#else\n"
"    matrix mView;\n"
"    matrix mProj;\n"
"    matrix mViewProj;\n"
"    matrix mViewInv;\n"
"    matrix mProjInv;\n"
"    matrix mViewProjInv;\n"
"#endif\n"
"\n"
"    float4 f4ExtraData[5]; // Any appliation-specific data\n"
"    // Sizeof(CameraAttribs) == 256*2\n"
"};\n"
"#ifdef CHECK_STRUCT_ALIGNMENT\n"
"    CHECK_STRUCT_ALIGNMENT(CameraAttribs);\n"
"#endif\n"
"\n"
"#endif //_BASIC_STRUCTURES_FXH_\n"
