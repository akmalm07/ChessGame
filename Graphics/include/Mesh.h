#pragma once

#include "pch.h"


class Mesh
{
public:
	Mesh();

    Mesh(Mesh&& other) noexcept;

    Mesh& operator=(Mesh&& other) noexcept;


	template <size_t VerticiesN, size_t IndiciesN>  
	inline void Initalize(const std::array<float, VerticiesN>& vertices, const std::array<unsigned int, IndiciesN>& indices, bool usingTextures, bool using3D);

	void RenderMesh();

	void ClearMesh();

	~Mesh();

private:

	GLuint VAO, VBO, IBO;
	GLsizei indexCount; 
};



//Template function
template <size_t VerticiesN, size_t IndiciesN>
inline void Mesh::Initalize(const std::array<float, VerticiesN>& vertices, const std::array<unsigned int, IndiciesN>& indices, bool usingTextures, bool using3D) 
{
    indexCount = indices.size();

    glGenVertexArrays(1, &VAO);
    //static_assert(VAO == 0, "VAO is ZERO");
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);




    if (using3D)
    {
        if (usingTextures) {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)(sizeof(GLfloat) * 3));
            glEnableVertexAttribArray(1);
        }
        else {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);
            glEnableVertexAttribArray(0);
        }
    }
    else
    {
        if (usingTextures) {
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void*)(sizeof(GLfloat) * 2));
            glEnableVertexAttribArray(1);
        }
        else {
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, 0);
            glEnableVertexAttribArray(0);
        }
    }


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}