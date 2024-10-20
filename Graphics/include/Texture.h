#pragma once


#include "pch.h"






class Texture
{
public:

	Texture();

	Texture(Texture&& other) noexcept; 

	Texture& operator= (Texture&& other) noexcept;

	Texture(const std::string& texAddress);

	bool LoadTexture();
	bool IsLoaded();
	void UseTexture(GLenum texUnit, GLuint textureLoc);
	void ClearTexture();

	~Texture();

private:

	std::string textureLoc; 

	GLuint textureID;
	int height, width, bitDepth;
	bool isLoaded;


};

