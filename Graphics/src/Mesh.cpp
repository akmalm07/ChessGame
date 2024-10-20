#include "pch.h"
#include "Mesh.h"

Mesh::Mesh()
{
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indexCount = 0;
}


Mesh::Mesh (Mesh&& other) noexcept :
    VAO(other.VAO), VBO(other.VBO), IBO(other.IBO), indexCount(other.indexCount)
{
    other.VAO = 0;
    other.VBO = 0;
    other.IBO = 0;
    other.indexCount = 0;
}


Mesh& Mesh::operator=(Mesh&& other) noexcept 
{
    if (this != &other)
    {
        ClearMesh(); 
         
        VAO = other.VAO;
        VBO = other.VBO; 
        IBO = other.IBO;
        indexCount = other.indexCount;

        other.VAO = 0;
        other.VBO = 0;
        other.IBO = 0;
        other.indexCount = 0;
 
    }

    return *this;
}


void Mesh::RenderMesh()
{

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}



void Mesh::ClearMesh()
{
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (IBO != 0) {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }
    indexCount = 0;
}

Mesh::~Mesh()
{
    ClearMesh();
}