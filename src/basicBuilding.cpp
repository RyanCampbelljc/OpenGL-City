//-----------------------------------------------------------------------------
// File:			basicBuilding.cpp
// Original Author:	Ryan Campbell
//
// See header for notes
//-----------------------------------------------------------------------------
#include "BasicBuilding.h"

// struct to represent a vertice on the basicBuilding
struct Vertex {
	GLfloat x, y, z;
	GLfloat u, v;
	glm::vec3 normal;
	glm::vec3 tangent;
};

// init static members
wolf::VertexBuffer* BasicBuilding::s_pVertexBuffer = 0;
wolf::VertexDeclaration* BasicBuilding::s_pDecl = 0;
wolf::IndexBuffer* BasicBuilding::s_pIndexBuffer = 0;
wolf::Material* BasicBuilding::s_pMaterial = 0;
int BasicBuilding::s_refCount = 0;

// vertices for a base basicBuilding
const Vertex gs_basicBuildingVertices[] = {
	// Front
	{-0.5f, 0.0f, 0.5f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // bottom left 0
	{-0.5f, 1.0f, 0.5f, 0.0f, 5.0f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // top left 1
	{0.5f, 1.0f, 0.5f, 1.0f, 5.0f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // top right 2
	{0.5f, 0.0f, 0.5f, 1.0f, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // bottom right 3

	// Back
	{-0.5f, 0.0f, -0.5f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)}, // bottom left 4
	{-0.5f, 1.0f, -0.5f, 0.0f, 5.0f, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)}, // top left 5
	{0.5f, 1.0f, -0.5f, 1.0f, 5.0f, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)}, // top right 6
	{0.5f, 0.0f, -0.5f, 1.0f, 0.0f, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)}, // bottom right 7

	// left
	{-0.5f, 0.0f, -0.5f, 0.0f, 0.0f, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)}, // bottom back 8
	{-0.5f, 1.0f, -0.5f, 0.0f, 5.0f, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)}, // top back 9
	{-0.5f, 1.0f, 0.5f, 1.0f, 5.0f, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)}, // top front 10
	{-0.5f, 0.0f, 0.5f, 1.0f, 0.0f, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)}, // bottom front 11

	// right
	{0.5f, 0.0f, 0.5f, 0.0f, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // bottom front 12
	{0.5f, 1.0f, 0.5f, 0.0f, 5.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // top front 13
	{0.5f, 1.0f, -0.5f, 1.0f, 5.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // top back 14
	{0.5f, 0.0f, -0.5f, 1.0f, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // bottom back 15

	// top
	{-0.5f, 1.0f, 0.5f, 0.0f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // left front 16
	{-0.5f, 1.0f, -0.5f, 0.0f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // left back 17
	{0.5f, 1.0f, -0.5f, 0.0f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // right back 18
	{0.5f, 1.0f, 0.5f, 0.0f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // right front 19
};

// indices for a base basicBuilding
const GLushort gs_basicBuildingIndices[] = {
	0,  1,  2,  0,  2,  3, // front
	6,  5,  4,  6,  4,  7, // back
	8,  9,  10, 8,  10, 11, // left
	12, 13, 14, 12, 14, 15, // right
	16, 17, 18, 16, 18, 19 // top
};

// constructor for BasicBuilding
BasicBuilding::BasicBuilding(const Utility::TexturePair& texPair)
	//: m_tex(texPair.first.c_str())
	: m_pos(0.0f, 0.0f, 0.0f)
	, m_rot(0.0f, 0.0f, 0.0f)
	, m_scale(1.0f, 1.0f, 1.0f)
	, m_pTexture(nullptr)
	, m_pSpecTex(nullptr)
{
	if (s_refCount == 0) {
		// Initialzing the static members
		s_pMaterial = wolf::MaterialManager::CreateMaterial("building");
		s_pMaterial->SetProgram("data/globalLighting.vsh", "data/globalLighting.fsh");
		s_pMaterial->EnableKeyword("ENABLE_DIFFUSE_AMBIENT");
		s_pMaterial->EnableKeyword("ENABLE_SPECULAR");
		s_pMaterial->EnableKeyword("SPECULAR_MAP");
		s_pMaterial->SetUniform("u_sunDirection", -glm::vec3(0, 1, 0));
		s_pMaterial->SetUniform("u_ambientLight", glm::vec3(0.4, 0.4, 0.4));
		s_pMaterial->SetUniform("shininess", 1000.0f);
		s_pVertexBuffer = wolf::BufferManager::CreateVertexBuffer(gs_basicBuildingVertices, sizeof(Vertex) * 20);
		s_pIndexBuffer = wolf::BufferManager::CreateIndexBuffer(gs_basicBuildingIndices, 30);

		s_pDecl = new wolf::VertexDeclaration();
		s_pDecl->Begin();
		s_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
		s_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
		s_pDecl->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float);
		s_pDecl->AppendAttribute(wolf::AT_Tangent, 3, wolf::CT_Float);
		s_pDecl->SetVertexBuffer(s_pVertexBuffer);
		s_pDecl->SetIndexBuffer(s_pIndexBuffer);
		s_pDecl->End();
	}
	// m_pTexture = wolf::TextureManager::CreateTexture(pathToTexture);
	m_pTexture = wolf::TextureManager::CreateTexture(texPair.first.c_str());
	m_pTexture->SetWrapMode(wolf::Texture::WM_Repeat);
	// wolf does by default
	// m_pTexture->SetFilterMode(wolf::Texture::FM_TrilinearMipmap, wolf::Texture::FM_Linear);
	m_pSpecTex = wolf::TextureManager::CreateTexture(texPair.second.c_str());
	m_pSpecTex->SetWrapMode(wolf::Texture::WM_Repeat);
	++s_refCount;
}

BasicBuilding::~BasicBuilding()
{
	--s_refCount;
	if (s_refCount == 0) {
		freeBuffers();
	}
	wolf::TextureManager::DestroyTexture(m_pTexture);
	wolf::TextureManager::DestroyTexture(m_pSpecTex);
}

void BasicBuilding::setPosition(const glm::vec3& pos)
{
	m_pos = pos;
}

void BasicBuilding::setScale(const glm::vec3& scale)
{
	m_scale = scale;
}

void BasicBuilding::setRotation(const glm::vec3& rot)
{
	m_rot = rot;
}

void BasicBuilding::freeBuffers()
{
	wolf::MaterialManager::DestroyMaterial(s_pMaterial);
	wolf::BufferManager::DestroyBuffer(s_pVertexBuffer);
	wolf::BufferManager::DestroyBuffer(s_pIndexBuffer);
	delete s_pDecl;
	std::cout << "BasicBuilding buffers freed" << std::endl;
}

void BasicBuilding::render(const glm::mat4& proj, const glm::mat4& view) const
{
	glm::mat4 mWorld = glm::translate(glm::mat4(1.0f), m_pos);
	mWorld = glm::rotate(mWorld, m_rot.x, glm::vec3(1, 0, 0));
	mWorld = glm::rotate(mWorld, m_rot.y, glm::vec3(0, 1, 0));
	mWorld = glm::rotate(mWorld, m_rot.z, glm::vec3(0, 0, 1));
	mWorld = glm::scale(mWorld, m_scale);

	glm::mat4 WVP = proj * view * mWorld;

	s_pMaterial->SetUniform("u_worldIT", glm::transpose(glm::inverse(mWorld)));
	s_pMaterial->SetUniform("u_mWVP", WVP);
	s_pMaterial->SetUniform("u_world", mWorld);

	s_pMaterial->SetTexture("u_texture1", m_pTexture);
	s_pMaterial->SetTexture("u_specMap", m_pSpecTex);

	s_pMaterial->Apply(); // pipeline configuration
	s_pDecl->Bind(); // pipeline data

	glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_SHORT, 0);
}

/**
 * update function overridden from Observer
 * This function is call by an Observable so this
 * class can update certain values
 */
void BasicBuilding::update()
{
	s_pMaterial->SetUniform("u_sunDirection", WorldEnvironment::instance().getSunDirection());
	s_pMaterial->SetUniform("u_viewPos", WorldEnvironment::instance().getCamPos());
}
