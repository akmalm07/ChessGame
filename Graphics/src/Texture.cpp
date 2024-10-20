#include "pch.h"
#include "Texture.h"
#include "stb/stb_image.h"

Texture::Texture()
{
	height = 0;
	width = 0;
	bitDepth = 0;
	textureID = 0;
	textureLoc = "";
}

Texture::Texture(const std::string& texAddress)  
{
	height = 0;
	width = 0;
	bitDepth = 0;
	textureID = 0;
	isLoaded = false;
	textureLoc = texAddress;
}


Texture::Texture(Texture&& other) noexcept :
	height(other.height), width(other.width), bitDepth(other.bitDepth), textureID(other.textureID), isLoaded(other.isLoaded)
{
	other.height = 0;
	other.width = 0;
	other.bitDepth = 0;
	other.textureID = 0;
	other.isLoaded = false;

}


Texture& Texture::operator=(Texture&& other) noexcept 
{
	if (this != &other)
	{
		height = other.height;
		width = other.width;
		bitDepth = other.bitDepth;
		textureID = other.textureID;
		isLoaded = other.isLoaded;


		other.height = 0;
		other.width = 0;
		other.bitDepth = 0;
		other.textureID = 0;
		other.isLoaded = false;
	}

	return *this;
}


bool Texture::LoadTexture()
{
	if (textureLoc.empty())
	{
		isLoaded = false;
		return false;
	}

	isLoaded = true;
	
	stbi_uc * texData = stbi_load(textureLoc.c_str(), &width, &height, &bitDepth, 0); 
	uint8_t numOfChannals = bitDepth; 

	if (!texData)
	{
		fprintf(stderr, "Error: Could not find the address %s for texture (Graphics : LoadTexture)", textureLoc.c_str());  
		isLoaded = false;
		return false;
	}

	glGenTextures(1, &textureID);
	if (!textureID)
	{
		fprintf(stderr, "Failed to generate texture"); 
		isLoaded = false;
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (numOfChannals == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, height, width, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	}
	else if (numOfChannals == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, height, width, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData); 
	}
	else
	{
		fprintf(stderr, "Error: %d channels are not supported! (Graphics : LoadTexture)", numOfChannals);
		isLoaded = false;
	}

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);

	return isLoaded; 
}

bool Texture::IsLoaded()
{
	return isLoaded; 
}

void Texture::UseTexture(GLenum texUnit, GLuint textureLoc)
{
	glActiveTexture(texUnit);
	
	glBindTexture(GL_TEXTURE_2D, textureID);

	switch (texUnit)
	{
	case GL_TEXTURE0: 
		glUniform1i(textureLoc, 0); 
	}
}

void Texture::ClearTexture()
{
	if (textureID != 0)
	{
		glDeleteTextures(1, &textureID);
		textureID = 0;
	}
	textureID = 0;
	height = 0;
	width = 0;
	bitDepth = 0;
	textureLoc = "";
}


Texture::~Texture()
{
	ClearTexture();
}
