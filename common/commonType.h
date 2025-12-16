#pragma once
enum geoType
{
	box,
	pyramid,
	skull,
	shapes
};

struct FRVertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};

struct SkullVertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT3 Normal;
};