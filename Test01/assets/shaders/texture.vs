// ========================================
// Filename: color.vs
// ========================================

// ========================================
// Globals
// ========================================
cbuffer MatrixBuffer {
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
}

// ========================================
// Typedefs
// ========================================
struct VertexInputType {
    float4 position : POSITION;
    float2 uv : TEXCOORD0;
};

struct PixelInputType {
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
};

// ========================================
// Vertex Shader
// ========================================
PixelInputType TextureVertexShader(VertexInputType input) {
    PixelInputType output;

    // Change the position vector to be 4 units for proper matrix calucations.
    input.position.w = 1.0f;

    // Calcuate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    // Store the texture coordinates for the pixel shader.
    output.uv = input.uv;

    return output;
}