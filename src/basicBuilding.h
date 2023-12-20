//-----------------------------------------------------------------------------
// File:			BasicBuilding.h
// Original Author:	Ryan Campbell
//-----------------------------------------------------------------------------

#pragma once
#include "cityRenderable.h"
#include "environment/Observer.h"
#include "utility.h"
#include <iostream>
#include <stdexcept>
class BasicBuilding
	: public CityRenderable
	, public Observer
{
public:
	//------------------------------------
	// PUBLIC INTERFACE
	//------------------------------------
	BasicBuilding(const Utility::TexturePair& texPair);
	virtual ~BasicBuilding();

	void setPosition(const glm::vec3& pos);
	void setScale(const glm::vec3& scale);
	void setRotation(const glm::vec3& rot);
	void update() override;
	void render(const glm::mat4& proj, const glm::mat4& view) const override;
	//------------------------------------
private:
	//------------------------------------
	// PRIVATE MEMBERS
	//------------------------------------
	static wolf::VertexBuffer* s_pVertexBuffer;
	static wolf::VertexDeclaration* s_pDecl;
	static wolf::IndexBuffer* s_pIndexBuffer;
	static wolf::Material* s_pMaterial;
	static int s_refCount;
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
	wolf::Texture* m_pTexture;
	wolf::Texture* m_pSpecTex;
	// const char* m_tex;

	void freeBuffers();
	//------------------------------------
};