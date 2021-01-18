#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#pragma once
#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

class VertexArray {
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void bind() const;
	void unbind() const;
};

#endif //VERTEX_ARRAY_H