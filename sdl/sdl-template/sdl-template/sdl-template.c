
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>


// ピクセル領域を直接操作する
void set_pixel_(SDL_Surface* surface, int x, int y, Uint32 abgr32)
{
    Uint32* const target_pixel = (Uint32*)((Uint8*)surface->pixels
        + y * surface->pitch
        + x * surface->format->BytesPerPixel);
    *target_pixel = abgr32;
}

// ピクセル領域を直接操作する
void set_pixel(SDL_Surface* surface, int x, int y, uint32_t abgr32) {
    uint32_t* pixels = surface->pixels;
    pixels[x + y * 640] = abgr32;
}

uint32_t rgba_to_abgr32(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    uint32_t ret = 0x00000000;
    ret = ret + a;
    ret = ret << 8;
    ret = ret + b;
    ret = ret << 8;
    ret = ret + g;
    ret = ret << 8;
    ret = ret + r;
    return ret;
}

uint32_t rgb_to_abgr32(uint8_t r, uint8_t g, uint8_t b) {
    return rgba_to_abgr32(r, g, b, 255);
}

void init_rnd() {
    srand((unsigned int)time(NULL));
}

int rnd(int min, int max) {
    return min + rand() % max;
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);

    /* OpenGLのテクスチャとして使うために
   各ピクセルがR,G,B,A順の32bitサーフェイスを生成する */
    SDL_Surface* surface;
    Uint32 rmask, gmask, bmask, amask;

    /* SDLはピクセルを32bitの値として解釈する.
       よって, マスクはマシンのエンディアン(バイト順)に依存する */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    int width = 640;
    int height = 480;

    //uint8_t* pixels = calloc(100, sizeof(uint8_t));
    //surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels,width,height,24,3 * 100, SDL_PIXELFORMAT_RGB24);

    surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
    if (surface == NULL) {
        printf("CreateRGBSurface 失敗: %s", SDL_GetError());
        exit(1);
    }

    // ピクセル操作関数を使ってランダムノイズを生成する
    for (int y = 0; y < 480; y++) {
        for (int x = 0; x < 640; x++) {
            uint32_t abgr = rgb_to_abgr32(rnd(0,255), rnd(0, 255), rnd(0, 255));
            set_pixel(surface, x, y, abgr);
        }
    }

    /* 画像読み込み */
    //image = SDL_LoadBMP("sample.bmp");

    /* 画像の矩形情報設定 */
    SDL_Rect rect, scr_rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 640;
    rect.h = 480;

    /* 画像配置位置情報の設定 */
    scr_rect.x = 0;
    scr_rect.y = 0;

    /* サーフェスの複写 */
    SDL_BlitSurface(surface, &rect, SDL_GetVideoSurface(), &scr_rect);

    /* サーフェスフリップ */
    SDL_Flip(SDL_GetVideoSurface());

	SDL_Delay(3000);

    SDL_FreeSurface(surface);

	SDL_Quit();
    //free(pixels);

	return 0;
}