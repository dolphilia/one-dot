
#include <SDL.h>

void set_pixel(SDL_Surface* surface, int x, int y, Uint32 pixel)
{
    Uint32* const target_pixel = (Uint32*)((Uint8*)surface->pixels
        + y * surface->pitch
        + x * surface->format->BytesPerPixel);
    *target_pixel = pixel;
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

    surface = SDL_CreateRGBSurface(0, width, height, 32,
        rmask, gmask, bmask, amask);
    if (surface == NULL) {
        //SDL_Log("CreateRGBSurface 失敗: %s", SDL_GetError());
        exit(1);
    }

    set_pixel(surface, 100, 100, 0xFFFFFFFF);

    //int* pixels = surface->pixels;
    //for (int i = 0; i < 1000; i++) {
    //    pixels[i] = 255;
    //}


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

	return 0;
}