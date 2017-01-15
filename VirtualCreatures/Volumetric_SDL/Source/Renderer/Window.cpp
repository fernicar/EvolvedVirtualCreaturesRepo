#include <Renderer/Window.h>
#include <SDL_image.h>
#include <GL/wglew.h>

#include <assert.h>

Window::Window()
	: m_created(false),
	m_fov(45.0f),
	m_zNear(0.1f), m_zFar(2000.0f),
	m_win(NULL),m_glc(NULL)
{
}

Window::~Window()
{
	IMG_Quit();
	if(m_glc)
		SDL_GL_DeleteContext(m_glc);
	if(m_win)
		SDL_DestroyWindow(m_win);
	if(m_created)
		SDL_Quit();
}

bool Window::Create(unsigned int pixel_width, unsigned int pixel_height, bool fullScreen)
{
	m_pixel_width = pixel_width;
	m_pixel_height = pixel_height;
	m_projected_width = static_cast<float>(m_pixel_width);
	m_projected_height = static_cast<float>(m_pixel_height);

#ifdef SDL_MAIN_HANDLED
	// IF SDL_MAIN_HANDLED is defined before #indlude <SDL2/SDL.h> then SDL_SetMainReady() should be called right before SDL_Init()
	SDL_SetMainReady();
#endif

//	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) /* Initialize SDL's Video subsystem */
		return false;
	/* Request opengl 3.2 context.
	* SDL doesn't have the ability to choose which profile at this time of writing,
	* but it should default to the core profile */
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);

	wglCreateContextAttribsARB;
	//SDL_GL_SetAttribute(WGL_CONTEXT_CORE_PROFILE_BIT_ARB,1);

	/* Turn on double buffering with a 24bit Z buffer.
	* You may need to change this to 16 or 32 for your system */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);


	if(fullScreen)
	{
//		if(SDL_SetVideoMode(pixel_width, pixel_height, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL | SDL_FULLSCREEN) == NULL)
		m_win=SDL_CreateWindow("Virtual Creatures",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,pixel_width,pixel_height,SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN);
	}
	else
	{
//		if(SDL_SetVideoMode(pixel_width, pixel_height, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL) == NULL)
		m_win=SDL_CreateWindow("Virtual Creatures",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,pixel_width,pixel_height,SDL_WINDOW_OPENGL);
	}
	if(!m_win)return false;
	static SDL_GLContext glc=SDL_GL_CreateContext(m_win);
	m_glc=&glc;

	/* This makes our buffer swap syncronized with the monitor's vertical refresh */
	SDL_GL_SetSwapInterval(1);

	if(!IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG))
		SDL_ShowSimpleMessageBox(0,"Image init error",IMG_GetError(),m_win);//return false;

	if(glewInit() != GLEW_OK)
		return false;

	glEnable(GL_MULTISAMPLE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glFrontFace(GL_CCW);

	m_created = true;

	return true;
}

void Window::SetViewport()
{
	glViewport(0, 0, m_pixel_width, m_pixel_height);
}

void Window::SetProjection()
{
	assert(m_created);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_fov, m_projected_width / m_projected_height, m_zNear, m_zFar);
	glMatrixMode(GL_MODELVIEW);
}

void Window::SetOrtho()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Doesn't use m_zNear and m_zFar since ortho projections never really need anything adjustable
	glOrtho(0, m_projected_width, 0, m_projected_height, -1, 1); 
	glMatrixMode(GL_MODELVIEW);
}

unsigned int Window::GetPixelWidth() const
{
	return m_pixel_width;
}

unsigned int Window::GetPixelHeight() const
{
	return m_pixel_height;
}