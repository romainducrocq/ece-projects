#include <iostream>
#include "console.h"

int main()
{
    bool quit = false;
    Console* pConsole = NULL;

    // Alloue la m�moire du pointeur
    pConsole = Console::getInstance();

    // Affichage avec gotoligcol et couleur
    pConsole->gotoLigCol(5, 10);
    pConsole->setColor(COLOR_GREEN);
    std::cout << "Hello World !" << std::endl;
    pConsole->setColor(COLOR_DEFAULT);

    // Boucle �v�nementielle
    while (!quit)
    {
        // Si on a appuy� sur une touche du clavier
        if (pConsole->isKeyboardPressed())
        {
            // R�cup�re le code ASCII de la touche
            int key = pConsole->getInputKey();
            std::cout << "touche = " << key << std::endl;

            if (key == 'a' || key == 27) // 27 = touche escape
            {
                quit = true;
            }
        }
    }

    // Lib�re la m�moire du pointeur !
    Console::deleteInstance();

    return 0;
}
