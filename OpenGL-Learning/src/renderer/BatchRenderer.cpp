#include "BatchRenderer.h"

static const size_t MaxQaudCount = 1000;
static const size_t MaxVertexCount = MaxQaudCount * 4;
static const size_t MaxIndexCount = MaxQaudCount * 6;
static const size_t MaxTextures = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;

static RendererData s_Data;

void BatchRenderer::Init()
{
	s_Data.QuadBuffer = new Vertex[MaxVertexCount];

	GLCall(glCreateVertexArrays(1, &s_Data.QuadVA));
	glBindVertexArray(s_Data.QuadVA);

	GLCall(glCreateBuffers(1, &s_Data.QuadVB));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, s_Data.QuadVB));
	GLCall(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	GLCall(glEnableVertexArrayAttrib(s_Data.QuadVA, 0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position)));

	GLCall(glEnableVertexArrayAttrib(s_Data.QuadVA, 1));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color)));

	GLCall(glEnableVertexArrayAttrib(s_Data.QuadVA, 2));
	GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoord)));

	GLCall(glEnableVertexArrayAttrib(s_Data.QuadVA, 3));
	GLCall(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexIndex)));

	uint32_t indices[MaxIndexCount];
	uint32_t offset = 0;

	for (int i = 0; i < MaxIndexCount; i += 6) {
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}

	GLCall(glCreateBuffers(1, &s_Data.QuadIB));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.QuadIB));
	GLCall(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLCall(glCreateBuffers(1, &s_Data.QuadIB));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.QuadIB));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

	GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &s_Data.WhiteTexture));
	GLCall(glBindTexture(GL_TEXTURE_2D, s_Data.WhiteTexture));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	uint32_t color = 0xffffffff;
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color));

	s_Data.TextureSlots[0] = s_Data.WhiteTexture;
	for (size_t i = 1; i < MaxTextures; i++){
		s_Data.TextureSlots[i] = 0;
	}
}

void BatchRenderer::Shutdown()
{
	GLCall(glDeleteVertexArrays(1, &s_Data.QuadVA));
	GLCall(glDeleteBuffers(1, &s_Data.QuadVB));
	GLCall(glDeleteBuffers(1, &s_Data.QuadIB));

	delete[] s_Data.QuadBuffer;
}

void BatchRenderer::BeginBatch()
{
	s_Data.QuadBufferPtr = s_Data.QuadBuffer;
}

void BatchRenderer::EndBatch()
{
	GLsizeiptr size = (uint8_t*)s_Data.QuadBufferPtr - (uint8_t*)s_Data.QuadBuffer;
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, s_Data.QuadVB));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Data.QuadBuffer));
}

void BatchRenderer::Flush()
{
}

void BatchRenderer::CreateQuad(glm::vec2& position, glm::vec2& size, glm::vec4& color)
{
}

void BatchRenderer::CreateQuad(glm::vec2& position, glm::vec2& size, unsigned int textureID)
{
}

//const State& BatchRenderer::getState()
//{
//	// TODO: hier return-Anweisung eingeben
//	return State();
//}

void BatchRenderer::ResetState()
{
}
