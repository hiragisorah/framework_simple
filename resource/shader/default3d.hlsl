//グローバル
cbuffer global
{
    matrix g_w;
    matrix g_v;
    matrix g_p;
    
    float4 g_color;
};

//構造体
struct PS_INPUT
{
	float4 position_ : SV_POSITION;
};

//
//
//バーテックスシェーダー
PS_INPUT VS( float4 position : POSITION ) 
{
    matrix wvp = transpose(mul(g_p, mul(g_v, g_w)));

	PS_INPUT output;

	output.position_ = mul(position, wvp);

	return output;
}
//
//
//ピクセルシェーダー
float4 PS( PS_INPUT Input ) : SV_Target
{
	return g_color;
}