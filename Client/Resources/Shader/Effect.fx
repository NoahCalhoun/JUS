cbuffer ViewProjectMatrix : register(b0)
{
	matrix gMtxView : packoffset(c0);
	matrix gMtxProject : packoffset(c4);
};

cbuffer WorldMatrix : register(b1)
{
	matrix gMtxWorld : packoffset(c0);
}

Texture2D Texture : register(t0);
SamplerState Sampler : register(s0);

struct VS_IN
{
	float3 position : POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
	float2 ex : TEXCOORD0;
};

VS_OUT VS(VS_IN vs_in)
{
	VS_OUT value = (VS_OUT)0;
	value.position = mul(float4(vs_in.position, 1), gMtxWorld);
	value.position = mul(value.position, gMtxView);
	value.position = mul(value.position, gMtxProject);
	value.ex = vs_in.uv;
	return value;
}

float4 PS(VS_OUT vs_out) : SV_Target
{
	return Texture.Sample(Sampler, vs_out.ex);
}