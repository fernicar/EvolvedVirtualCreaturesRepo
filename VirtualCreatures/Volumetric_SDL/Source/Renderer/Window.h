#pragma once
#include <Renderer/SDL_OpenGL.h>


class Window
{
private:
	unsigned int m_pixel_width, m_pixel_height;

	bool m_created;
	SDL_Window *m_win;
	SDL_GLContext *m_glc;

public:
	Window();
	~Window();

	float m_projected_width, m_projected_height;
	float m_fov;
	float m_zNear, m_zFar;

	// Returns true if created successfully, otherwise returns false
	bool Create(unsigned int pixel_width, unsigned int pixel_height, bool fullScreen);

	void SetViewport();
	void SetProjection();
	void SetOrtho();

	unsigned int GetPixelWidth() const;
	unsigned int GetPixelHeight() const;
};

