cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix transformationMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

PixelInputType TerrainVertexShader(VertexInputType input)
{
	PixelInputType output;

	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, mul(worldMatrix, transformationMatrix));
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input.tex;

	// Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3)mul(worldMatrix, transformationMatrix));

	// Normalize the normal vector.
	output.normal = normalize(output.normal);

	return output;
}

Texture2D grassTexture : register(t0);
Texture2D rockTexture : register(t1);
Texture2D snowTexture : register(t2);

SamplerState SampleType;

cbuffer LightBuffer
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightDirection;
	float padding;
};

float4 TerrainPixelShader(PixelInputType input) : SV_TARGET
{
	float4 textureColor;
	float4 grassColor, rockColor, snowColor;
	float3 lightDir;
	float lightIntensity;
	float4 color;

	float slopeGradient;
	float blendFactor;
	float3 upVector;

	grassColor = grassTexture.Sample(SampleType, input.tex);
	rockColor = rockTexture.Sample(SampleType, input.tex);
	snowColor = snowTexture.Sample(SampleType, input.tex);

	textureColor = rockColor;

	// Set the default output color to the ambient light value for all pixels.
	color = ambientColor;

	// Invert the light direction for calculations.
	lightDir = -lightDirection;

	// Calculate the amount of light on this pixel.
	lightIntensity = saturate(dot(input.normal, lightDir));

	color += (diffuseColor * lightIntensity);

	// Saturate the final light color.
	color = saturate(color);
	color = color * textureColor;

	return color;
}