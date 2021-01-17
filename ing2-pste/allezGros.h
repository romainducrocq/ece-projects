#ifndef ALLEZGROS_H_INCLUDED
#define ALLEZGROS_H_INCLUDED

#include <allegro.h>
#include <string>
#include <iostream>

#define WHITE     makecol(255,255,255)
#define BLACK     makecol(0,0,0)
#define RED       makecol(255,0,0)
#define GREEN     makecol(0,255,0)
#define BLUE      makecol(0,0,255)
#define YELLOW    makecol(255,255,0)
#define CYAN      makecol(0,255,255)
#define ROSE      makecol(244,194,194)



class allezGros
{
    private:
    BITMAP *buffer;
    FONT *TER22, *TER28;
    int m_resX, m_resY, m_depth;
    BITMAP* m_wallpaper;

    public:
        allezGros(int resX, int resY, int depth);
        ~allezGros();

        bool Init();
        void DeInit();
        int keyGet(int code) const;
        void ClearToColor(int color);
        void Graphic();
        void Rectangle(int xBegin, int yBegin, int xEnd, int yEnd, int color, bool remplissage) const;
        void Cercle(int x, int y, int rayon, int color, int remplissage) const;
        bool De4dMouse(int xBegin, int yBegin, int xEnd, int yEnd);
        void Texte(int police, std::string txt, int x, int y, int colorFont, int colorBackGround, bool centre);
        void Wallapaper() const;
};

#endif // ALLEZGROS_H_INCLUDED
