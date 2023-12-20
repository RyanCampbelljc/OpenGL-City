//-----------------------------------------------------------------------------
// File:			Rectangle.cpp
// Original Author:	Ryan Campbell
//
// class to represent a rectangle
// mostly used for the ground in this project(gradd/roads)
//-----------------------------------------------------------------------------
#include "rectangle.h"

struct Vertex {
	GLfloat x, y, z;
	GLfloat u, v;
	glm::vec3 normal;
};

// init static members
wolf::VertexBuffer* Rectangle::s_pVertexBuffer = 0;
wolf::IndexBuffer* Rectangle::s_pIndexBuffer = 0;
wolf::VertexDeclaration* Rectangle::s_pDecl = 0;
wolf::Material* Rectangle::s_pMaterial = 0;
int Rectangle::s_refCount = 0;

const Vertex gs_rectangleVertices[] = {
	{-0.5f, 0.0f, 0.5f, 0.0f, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f)}, // front left
	{-0.5f, 0.0f, -0.5f, 0.0f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f)}, // back left
	{0.5f, 0.0f, -0.5f, 1.0f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f)}, // back right
	{0.5f, 0.0f, 0.5f, 1.0f, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f)}, // front right

};

const GLushort gs_rectangleIndices[]{
	0, 1, 2, // left tri
	0, 2, 3 // right tri
};

Rectangle::Rectangle(const char* pathToTexture)
	: m_tex(pathToTexture)
	, m_pos(glm::vec3(0.0f, 0.0f, 0.0f))
	, m_rot(glm::vec3(0.0f, 0.0f, 0.0f))
	, m_scale(glm::vec3(1.0f, 1.0f, 1.0f))
	, m_pTexture(nullptr)
{
	if (s_refCount == 0) {
		// gives values to static members
		s_pMaterial = wolf::MaterialManager::CreateMaterial("ground");
		s_pMaterial->SetProgram("data/globalLighting.vsh", "data/globalLighting.fsh");
		s_pMaterial->EnableKeyword("ENABLE_DIFFUSE_AMBIENT");
		s_pMaterial->EnableKeyword("ENABLE_SPECULAR");
		s_pMaterial->SetUniform("u_sunDirection", -glm::vec3(0, 1, 0));
		s_pMaterial->SetUniform("u_ambientLight", glm::vec3(0.4, 0.4, 0.4));
		s_pMaterial->SetUniform("shininess", 500.0f);
		s_pVertexBuffer = wolf::BufferManager::CreateVertexBuffer(gs_rectangleVertices, sizeof(Vertex) * 4);
		s_pIndexBuffer = wolf::BufferManager::CreateIndexBuffer(gs_rectangleIndices, 6);

		s_pDecl = new wolf::VertexDeclaration();
		s_pDecl->Begin();
		s_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
		s_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
		s_pDecl->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float);
		s_pDecl->SetVertexBuffer(s_pVertexBuffer);
		s_pDecl->SetIndexBuffer(s_pIndexBuffer);
		s_pDecl->End();
	}
	m_pTexture = wolf::TextureManager::CreateTexture(pathToTexture);
	m_pTexture->SetWrapMode(wolf::Texture::WM_Clamp);
	// wolf does by default
	// m_pTexture->SetFilterMode(wolf::Texture::FM_TrilinearMipmap);
	++s_refCount;
}

Rectangle::~Rectangle()
{
	--s_refCount;
	if (s_refCount == 0) {
		freeBuffers();
	}
	wolf::TextureManager::DestroyTexture(m_pTexture);
}

void Rectangle::render(const glm::mat4& proj, const glm::mat4& view) const
{
	glm::mat4 mWorld = glm::translate(glm::mat4(1.0f), m_pos);
	mWorld = glm::rotate(mWorld, m_rot.x, glm::vec3(1, 0, 0));
	mWorld = glm::rotate(mWorld, m_rot.y, glm::vec3(0, 1, 0));
	mWorld = glm::rotate(mWorld, m_rot.z, glm::vec3(0, 0, 1));
	mWorld = glm::scale(mWorld, m_scale);

	glm::mat4 WVP = proj * view * mWorld;

	s_pMaterial->SetUniform("u_mWVP", WVP);
	s_pMaterial->SetTexture("u_texture1", m_pTexture);
	s_pMaterial->SetUniform("u_worldIT", glm::transpose(glm::inverse(mWorld)));
	s_pMaterial->SetUniform("u_world", mWorld);

	s_pMaterial->Apply();
	s_pDecl->Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

/**
 * update function overridden from Observer
 * This function is call by an Observable so this
 * class can update certain values
 */
void Rectangle::update()
{
	s_pMaterial->SetUniform("u_sunDirection", WorldEnvironment::instance().getSunDirection());
	s_pMaterial->SetUniform("u_viewPos", WorldEnvironment::instance().getCamPos());
}

void Rectangle::freeBuffers()
{
	wolf::MaterialManager::DestroyMaterial(s_pMaterial);
	wolf::BufferManager::DestroyBuffer(s_pVertexBuffer);
	wolf::BufferManager::DestroyBuffer(s_pIndexBuffer);
	delete s_pDecl;
	printf("rectangle buffers freed\n");
}
