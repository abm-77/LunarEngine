#pragma once

class ElementBuffer
{

public:

	ElementBuffer(const void* data, unsigned int ct);

	~ElementBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int GetBufferID();
	inline int GetCount() const { return count;  }

private:
	unsigned int rendererID;
	unsigned int count;
};