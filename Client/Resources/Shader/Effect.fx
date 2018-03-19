float4 VS(float4 pos : POSITION) : SV_POSITION
{
	return pos;
}

float4 PS(float4 pos : SV_POSITION) : SV_Target
{
	return float4(1.f, 1.f, 0.f, 1.f);
}