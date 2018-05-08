#include <chrono>

#include <SDL.h>

#include "KinectInit.h"


#include "ImageProcess.h"
using namespace std::chrono;


inline void DrawPixelbuffer(SDL_Texture* texture, SDL_Renderer* renderer,
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
inline void DrawColorPixelbuffer(SDL_Texture* texture, SDL_Renderer* renderer,
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