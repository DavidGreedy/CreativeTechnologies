cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix rotationMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
};

PixelInputType TerrainColorVertexShader(VertexInputType input)
{
	PixelInputType output;

	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, mul(worldMatrix, rotationMatrix));
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.color = input.color;

	// Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3) mul(worldMatrix, rotationMatrix));

	// Normalize the normal vector.
	output.normal = normalize(output.normal);

	return output;
}

cbuffer LightBuffer
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightDirection;
	float padding;
};

float4 TerrainColorPixelShader(PixelInputType input) : SV_TARGET
{
	return float4(1, 1, 1, 1);
//	//float4 sourceColor;
//	//float3 lightDir;
//	//float lightIntensity;
//	//float4 color;
//
//	////input.color.w = 1.0f;
//
//	//// Set the default output color to the ambient light value for all pixels.
//	//color = ambientColor;
//
//	//// Invert the light direction for calculations.
//	//lightDir = -lightDirection;
//
//	//// Calculate the amount of light on this pixel.
//	//lightIntensity = saturate(dot(input.normal, lightDir));
//
//	//if (lightIntensity > 0.0f)
//	//{
//	//	// Determine the final diffuse color based on the diffuse color and the amount of light intensity.
//	//	color += (diffuseColor * lightIntensity);
//	//}
//
//	//// Saturate the final light color.
//	//color = saturate(color);
//	//color = color * input.color;
//
//	return input.color;
}