#pragma once

#include <array>

#include "glm/glm.hpp"
#include "GLEW/glew.h"

#include "../Debug.hpp"

struct Vertex {
	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec2 TexCoord;
	unsigned int TexIndex;
};

struct RendererData {
	GLuint QuadVA = 0;
	GLuint QuadVB = 0;
	GLuint QuadIB = 0;

	GLuint WhiteTexture = 0;
	uint32_t WhiteTextureSlot = 0;

	uint32_t IndexCount = 0;
	Vertex* QuadBuffer = nullptr;
	Vertex* QuadBufferPtr = nullptr;

	std::array<uint32_t, MaxTextures> TextureSlots;
	uint32_t TextureSlotIndex = 0;

	BatchRenderer::State RendererState;
};

class BatchRenderer
{
private:

public:
	static void Init();
	static void Shutdown();

	static void BeginBatch();
	static void EndBatch();
	static void Flush();

	static void CreateQuad(glm::vec2& position, glm::vec2& size, glm::vec4& color);
	static void CreateQuad(glm::vec2& position, glm::vec2& size, unsigned int textureID);

	struct State {
		unsigned int drawCount = 0;
		unsigned int quadCount = 0;
	};

	static const State& getState();
	static void ResetState();
};

