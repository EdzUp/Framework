/*
    TextSystem.h - Copyright (C)EdzUp
    Programmed by Ed 'EdzUp' Upton
*/

#ifndef _TEXTSYSTEMCLASS_
    #define _TEXTSYSTEMCLASS_
    #include <string>

    class TextSystemClass {
        public:
            long Len( std::string st ) {
                return( st.length() );
            }
    };
#endif // _TEXTSYSTEMCLASS_

