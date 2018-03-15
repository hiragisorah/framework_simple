//�O���[�o��
cbuffer global
{
    matrix g_w;
    matrix g_v;
    matrix g_p;
    
    float4 g_color;
};

//�\����
struct PS_INPUT
{
	float4 position_ : SV_POSITION;
};

//
//
//�o�[�e�b�N�X�V�F�[�_�[
PS_INPUT VS( float4 position : POSITION ) 
{
    matrix wvp = transpose(mul(g_p, mul(g_v, g_w)));

	PS_INPUT output;

	output.position_ = mul(position, wvp);

	return output;
}
//
//
//�s�N�Z���V�F�[�_�[
float4 PS( PS_INPUT Input ) : SV_Target
{
	return g_color;
}