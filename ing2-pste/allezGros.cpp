#include "allezGros.h"

allezGros::allezGros(int resX, int resY, int depth)
    : buffer(NULL), m_resX(resX), m_resY(resY), m_depth(depth) {}

allezGros::~allezGros() {}


bool allezGros::Init()
{
    set_color_depth(m_depth); // profondeur des couleurs 8, 16, 24 ou 32
    set_uformat(U_ASCII); // pour gérer les accents

    allegro_init();

    if (install_mouse() == -1)
    {
        allegro_message("Failed to install mouse");
        return false;
    }
    if (install_keyboard() != 0)
    {
        allegro_message("Failed to install keyboard");
        return false;
    }
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, m_resX, m_resY, 0, 0) != 0)
    {
        allegro_message("Failed to enter in graphic mode");
        return false;
    }
    TER22 = load_font("Terminal22.pcx", NULL, NULL);
    if (!TER22)
    {
        allegro_message("Failed to install font");
        return false;
    }
    TER28 = load_font("Terminal28.pcx", NULL, NULL);
    if (!TER28)
    {
        allegro_message("Failed to install font");
        return false;
    }

    m_wallpaper = load_bitmap("wallpaper.bmp", nullptr);
    buffer=create_bitmap(SCREEN_W,SCREEN_H);

    show_mouse(screen);

 return true;
}

void allezGros::DeInit()
{
    destroy_bitmap(buffer);
    remove_mouse();
    remove_keyboard();
    allegro_exit();
}

int allezGros::keyGet(int code) const
{
    return key[code];
}

void allezGros::ClearToColor(int color)
{
     clear_to_color(buffer,color);
}

void allezGros::Graphic()
{
    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}

void allezGros::Rectangle(int xBegin, int yBegin, int xEnd, int yEnd, int color, bool remplissage) const
{
    switch (remplissage)
      {
         case true:
            rectfill(buffer,xBegin,yBegin,xEnd,yEnd,color);
            break;
         case false:
            rect(buffer,xBegin,yBegin,xEnd,yEnd,color);
            break;
      }

}

void allezGros::Cercle(int x, int y, int rayon, int color, int remplissage) const
{
    switch (remplissage)
      {
         case true:
            circlefill(buffer, x, y, rayon, color);
            break;
         case false:
            circle(buffer, x, y, rayon, color);
            break;
      }
}

bool allezGros::De4dMouse(int xBegin, int yBegin, int xEnd, int yEnd)
{
    if ( mouse_b&1 && mouse_x>=xBegin && mouse_y>=yBegin && mouse_x<=xEnd && mouse_y<=yEnd)
        return true;
    else
        return false;
}

void allezGros::Texte(int police, std::string txt, int x, int y, int colorFont, int colorBackGround, bool centre)
{
    FONT *myfont;
    switch (police)
      {
         case 1:
            myfont = TER22;
            break;
         case 2:
            myfont = TER28;
            break;
         default:
            myfont = TER28;
      }
      switch (centre)
      {
         case true:
            textout_centre_ex(buffer,myfont,txt.c_str(),x,y,colorFont,colorBackGround);
            break;
         case false:
            textout_ex(buffer,myfont,txt.c_str(),x,y,colorFont,colorBackGround);
            break;
      }

}

void allezGros::Wallapaper() const
{
    draw_sprite(buffer, m_wallpaper, 0, 0);
}

