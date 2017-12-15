

#include <chrono>

#include <SDL.h>

#include "KinectInit.h"
#include "TESToPENCV.h"
#include "Contours.h"
using namespace std::chrono;
typedef steady_clock Clock;

void DrawPixelbuffer(SDL_Texture* texture, SDL_Renderer* renderer,
	const UINT32* pixelBuffer)
{
	//upload the pixel buffer to a texture
	void* pixels;
	int pitch;
	SDL_LockTexture(texture, nullptr, &pixels, &pitch);
	if (pitch == IMG_W * 4)
		memcpy(pixels, pixelBuffer, IMG_W * IMG_H * 4);
	else
	{
		const UINT32* src = pixelBuffer;
		char* dst = (char*)pixels;
		for (int y = 0; y < IMG_H; ++y)
		{
			memcpy(dst, src, IMG_W * 4);
			src += IMG_W;
			dst += pitch;
		}
	}
	SDL_UnlockTexture(texture);

	//copy the texture to the frame buffer
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);

	//present the frame buffer on the screen
	SDL_RenderPresent(renderer);
}
void DrawColorPixelbuffer(SDL_Texture* texture, SDL_Renderer* renderer,
	const UINT32* pixelBuffer)
{
	//upload the pixel buffer to a texture
	void* pixels;
	int pitch;
	SDL_LockTexture(texture, nullptr, &pixels, &pitch);
	if (pitch == CIMG_W * 4)
		memcpy(pixels, pixelBuffer, CIMG_W * CIMG_H * 4);
	else
	{
		const UINT32* src = pixelBuffer;
		char* dst = (char*)pixels;
		for (int y = 0; y < CIMG_H; ++y)
		{
			memcpy(dst, src, CIMG_W * 4);
			src += CIMG_W;
			dst += pitch;
		}
	}
	SDL_UnlockTexture(texture);

	//copy the texture to the frame buffer
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);

	//present the frame buffer on the screen
	SDL_RenderPresent(renderer);
}

#undef main
int main(int argc, char** argv)
{
	//initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	//create a window
	SDL_Window* window = SDL_CreateWindow(
		"title", 100, 100, IMG_W, IMG_H, 0);
	if (window == nullptr)
		return 1;

	//create a renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
		return 2;

	//create a texture
	SDL_Texture* texture = SDL_CreateTexture(
		renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		IMG_W, IMG_H);
	if (texture == nullptr)
		return 3;

	SDL_Window* window2 = SDL_CreateWindow(
		"title", 100, 100, IMG_W, IMG_H, 0);
	if (window2 == nullptr)
		return 1;

	//create a renderer
	SDL_Renderer* renderer2 = SDL_CreateRenderer(
		window2, -1, SDL_RENDERER_ACCELERATED);
	if (renderer2 == nullptr)
		return 2;

	//create a texture
	SDL_Texture* texture2 = SDL_CreateTexture(
		renderer2, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		IMG_W, IMG_H);
	if (texture2 == nullptr)
		return 3;

	SDL_Window* window3 = SDL_CreateWindow(
		"title", 100, 100, CIMG_W, CIMG_H, 0);
	if (window3 == nullptr)
		return 1;

	//create a renderer
	SDL_Renderer* renderer3 = SDL_CreateRenderer(
		window3, -1, SDL_RENDERER_ACCELERATED);
	if (renderer3 == nullptr)
		return 2;

	//create a texture
	SDL_Texture* texture3 = SDL_CreateTexture(
		renderer3, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		CIMG_W, CIMG_H);
	if (texture3 == nullptr)
		return 3;

	//allocate a pixel buffer
	UINT32* pixelBuffer = new UINT32[IMG_W * IMG_H];
	if (pixelBuffer == nullptr)
		return 4;

	UINT32* pixelBuffer2 = new UINT32[IMG_W * IMG_H];
	if (pixelBuffer2 == nullptr)
		return 4;

	UINT32* pixelBuffer3 = new UINT32[CIMG_W * CIMG_H];
	if (pixelBuffer3 == nullptr)
		return 4;
	//clear the pixel buffer
	memset(pixelBuffer, 0, IMG_W * IMG_H * 4);
	memset(pixelBuffer2, 0, IMG_W * IMG_H * 4);
	memset(pixelBuffer3, 0, CIMG_W * CIMG_H * 4);

	//draw pixel buffer to the screen
	DrawPixelbuffer(texture, renderer, pixelBuffer);
	DrawPixelbuffer(texture2, renderer2, pixelBuffer2);
	DrawColorPixelbuffer(texture3, renderer3, pixelBuffer3);

	KinectSensor app;
	KinectSensor app2;
	KinectSensor app3;
	app.SetPixelBuffer(pixelBuffer);
	app2.SetPixelBuffer(pixelBuffer2);
	app3.SetPixelBuffer(pixelBuffer3);
	app.init();
	app2.init(1);
	app3.init(2);
	auto lastTime = Clock::now();
	OpenCV(argc, argv);
	//contour(argc, argv);
	bool running = true;
	while (running)
	{
		//get events
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				//pressing the cross or pressing escape will quit the application
			case SDL_QUIT:
				running = false;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					running = false;
				break;

			default: //ignore other events for this demo
				break;
			}
		}

		//calculate delta time
		const auto now = Clock::now();
		const auto duration = duration_cast<microseconds>(now - lastTime);
		const float deltaTime = duration.count() / 1000000.0f;
		lastTime = now;

		//update the application
		app.draw();
		app2.draw();
		app3.colordraw();

		//draw pixel buffer to the screen
		DrawPixelbuffer(texture, renderer, pixelBuffer);
		DrawPixelbuffer(texture2, renderer2, pixelBuffer2);
		DrawColorPixelbuffer(texture3, renderer3, pixelBuffer3);
	}

	
	//clean up
	app.end();
	app2.end();
	app3.end();
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(texture2);
	SDL_DestroyRenderer(renderer2);
	SDL_DestroyWindow(window2);
	SDL_DestroyTexture(texture3);
	SDL_DestroyRenderer(renderer3);
	SDL_DestroyWindow(window3);
	SDL_Quit();

	

	return 0;
}


