cbuffer global
{
    matrix g_w;
    matrix g_v;
    matrix g_p;

    float4 g_lightdir;
    float4 g_diffuse;
};

struct VS_OUTPUT
{
    float4 position_ : SV_POSITION;
    float4 color_ : COLOR0;
};

VS_OUTPUT VS(float4 position : POSITION, float4 normal : NORMAL)
{
    matrix wvp = transpose(mul(g_p, mul(g_v, g_w)));
    matrix w = transpose(g_w);

    VS_OUTPUT output = (VS_OUTPUT) 0;
	
    output.position_ = mul(position, wvp);
    normal.w = 0;
    normal = mul(normal, w);
    normal = normalize(normal);

    output.color_ = 1.0 * g_diffuse * dot(normal, normalize(g_lightdir));

    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    return input.color_;
}