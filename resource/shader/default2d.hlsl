cbuffer global
{
	matrix g_w : packoffset(c0);
	float2 g_viewport : packoffset(c4);

    float4 g_color : packoffset(c5);
};

struct PS_INPUT
{
	float4 position_ : SV_POSITION;
};

PS_INPUT VS( float4 position : POSITION ) 
{
	PS_INPUT output;

    matrix w = transpose(g_w);

    output.position_ = mul(position, w);

    output.position_.x = (output.position_.x / g_viewport) * 2;
    output.position_.y = (output.position_.y / g_viewport) * 2;

	return output;
}

float4 PS( PS_INPUT input ) : SV_Target
{
    return g_color;
}