/*
    FontSystem.h - Copyright (C)EdzUp
    Programmed by Ed 'EdzUp' Upton
*/

#include "ETexture.h"

class FontSystem {
    private:
    ETexture        FontImage;

    public:
    void LoadFont( std::string filename, int width, int height, int amount ) {

    }
    /*
		GameFont.LoadFont( "EdzUpFont.png", 14, 15, 92 )
		GameFont.SetFont(  "!`#$% '()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~~" )
		GameFont.SetChar( 2, 34 )		'set the char to "
		GameFont.ChangeFontSize( 12, 15 )
		GameFont.LowerCase = True
		*/
};
