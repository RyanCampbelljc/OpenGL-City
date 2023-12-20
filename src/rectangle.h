//-----------------------------------------------------------------------------
// File:			Rectangle.h
// Original Author:	Ryan Campbell
//
// class to represent a rectangle
// mostly used for the ground in this project(gradd/roads)
//-----------------------------------------------------------------------------
#pragma once
#include "cityRenderable.h"
#include "environment/Observer.h"

class Rectangle
	: public CityRenderable
	, public Observer
{
public:
	//------------------------------------
	// PUBLIC INTERFACE
	//------------------------------------
	Rectangle(const char* pathToTexture);
	virtual ~Rectangle();

	void setPosition(const glm::vec3& pos)
	{
		m_pos = pos;
	}
	void setScale(const glm::vec3& scale)
	{
		m_scale = scale;
	}
	void setRotation(const glm::vec3& rot)
	{
		m_rot = rot;
	}

	void render(const glm::mat4& proj, const glm::mat4& view) const override;

	void update() override;
	//------------------------------------
private:
	//------------------------------------
	// PRIVATE MEMBERS
	//------------------------------------
	static wolf::VertexBuffer* s_pVertexBuffer;
	static wolf::IndexBuffer* s_pIndexBuffer;
	static wolf::VertexDeclaration* s_pDecl;
	static wolf::Material* s_pMaterial;
	static int s_refCount;
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
	wolf::Texture* m_pTexture;
	const char* m_tex;

	void freeBuffers();
	//--------------------------------------
};
