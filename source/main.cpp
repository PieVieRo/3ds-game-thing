#include <citro2d.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

class Sprite {
    public:
        C2D_Sprite spr;
        float dx, dy;
};

static C2D_SpriteSheet spriteSheet;

int main() {
    romfsInit();
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    consoleInit(GFX_BOTTOM, 0);

    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    u32 green = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
    int x = SCREEN_WIDTH/2;
    int y = SCREEN_HEIGHT/2;

    printf("\x1b[8;1HHejka!");


    while(aptMainLoop()) {
        gspWaitForVBlank();
        gfxSwapBuffers();
        hidScanInput();

        u32 kDown = hidKeysDown();
        if(kDown & KEY_START)
             break;

        u32 kHeld = hidKeysHeld();
        if(kHeld & KEY_UP) {
            y-=3;
            if(y<0) y=0;
        }
        if(kHeld & KEY_DOWN) {
            y+=3;
            if(y+50>SCREEN_HEIGHT) y=SCREEN_HEIGHT-50;
        }
        if(kHeld & KEY_RIGHT) {
            x+=3;
            if(x+50>SCREEN_WIDTH) x=SCREEN_WIDTH-50;
        }
        if(kHeld & KEY_LEFT) {
            x-=3;
            if(x<0) x=0;
        }


		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(top);

        C2D_DrawRectSolid(x, y, 0, 50, 50, green);

		C3D_FrameEnd(0);
    }

    C2D_Fini();
    C3D_Fini();
    gfxExit();
    romfsExit();
    return 0;
}
