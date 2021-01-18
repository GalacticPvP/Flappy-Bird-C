#pragma once
#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

class IndexBuffer {
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	const void bind();
	const void unbind();

	const inline unsigned int getCount() {
		return m_Count;
	}
};

#endif //INDEX_BUFFER_H