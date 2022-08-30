/*!
 * @brief セピア
 */

#include "../util/ColorSpace.h"

cbuffer cb : register(b0)
{
    float4x4 mvp;       // MVP行列
    float4 mulColor;    // 乗算カラー
};
/*!
 *@brief    セピア用の定数バッファ。
 */
cbuffer cb2 : register(b1)
{
    float alphaNum;
}

struct VSInput
{
    float4 pos : POSITION;
    float2 uv  : TEXCOORD0;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv  : TEXCOORD0;
};

/*!
 * @brief 頂点シェーダー
 */
PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    return psIn;
}

Texture2D<float4> mainRenderTargetTexture : register(t0);   // メインレンダリングターゲットのテクスチャ
sampler Sampler : register(s0);

/*!
 * @brief ピクセルシェーダー
 */
float4 PSOut(PSInput In) : SV_Target0
{
    // メインレンダリングターゲットからカラーをサンプリング
    float4 color = mainRenderTargetTexture.Sample(Sampler, In.uv);
    color.a = alphaNum;
    float4 r_color;
    //r_color.r = color.r * 0.393 + color.g * 0.769 + color.b * 0.189;
    //r_color.g = color.r * 0.349 + color.g * 0.686 + color.b * 0.168;
    //r_color.b = color.r * 0.272 + color.g * 0.534 + color.b * 0.131;
    
    r_color.r = color.r * 0.2 + color.g * 0.5 + color.b * 0.08;
    r_color.g = color.r * 0.15 + color.g * 0.4 + color.b * 0.06;
    r_color.b = color.r * 0.07 + color.g * 0.3 + color.b * 0.03;
    
    r_color.a = color.a;
    
    return r_color;
}