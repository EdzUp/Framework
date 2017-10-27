/*
    Convert.h - Copyright (C)EdzUp
    Programmed by Ed 'EdzUp' Upton
*/

#ifndef FWCONVERT
    #define FWCONVERT

    long ConvertRGBA[ 4 ];

    class ConversionClass{
    public:
        std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace) {
            size_t pos = 0;
            while ((pos = subject.find(search, pos)) != std::string::npos) {
                subject.replace(pos, search.length(), replace);
                pos += replace.length();
            }
            return( subject );
        }

        void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace) {
            size_t pos = 0;
            while ((pos = subject.find(search, pos)) != std::string::npos) {
                subject.replace(pos, search.length(), replace);
                pos += replace.length();
            }
        }

        char WrapChar( long Value, long Adjustment ) {
            char Temp;

            Temp = Value +Adjustment;

            if ( Temp>255 ) return( Temp -256 );
            if ( Temp<0 ) return( Temp +256 );

            return( Temp );
        }

        std::string ToUpper( std::string &s ) {
            std::string ns;

            ns = s;
            for(unsigned int l = 0; l < s.length(); l++) {
                ns[l] = toupper(s[l]);
            }

            return( ns );
        }

        std::string Chr( long value ) {
            char* newchar;

            newchar = (char*)value;
            return( (std::string)newchar );
        }

        std::string Left( std::string str, long n ) {
            if ( n>(long)str.size() ) n=str.size();

            return( str.substr( 0, n ) );
        }

        std::string Right( std::string str, long n ) {
            if ( n>(long)str.size() ) n=str.size();

            return( str.substr( n, str.size()-n ) );
        }

        std::string Set( long n, std::string chr ) {
            std::string Temp;

            for ( int i =1; i<n; i++ ) {
                Temp += chr;
            }
            return( Temp );
        }

        std::string Mid( std::string str, long pos, long length =-1 ) {
            if ( length == -1 ) return( str.substr( pos, str.size() ) );

            return( str.substr( pos, pos +length ) );
        }
/*
	Function FormatNumeric:String(value:Float)
		Local i:Int,s:String,ns:String,k:Int
		Local os:String
		s=String(value)
		os=s
		Local pos:Int=s.Length()
		If s.Find(".")>0 pos=s.Find(".") Else os=""
		For i=pos To 1 Step -1
			If k>2 ns+="." k=0
			k+=1
			ns=ns+Mid(s,i,1)
		Next
		s=""
		For i= ns.Length() To 1 Step -1
			s+=Mid(ns,i,1)
		Next
		If os<>"" s=s+","+os[pos+1..]
		Return s
	End Function
End
*/
    };
#endif // FWCONVERT

/*
Class ConvertClass
	Function HexToRGBA( InHex:String )
		If InHex.Length=8
			ConvertRGBA[ 0 ] = HexToDec( InHex[ 0..2 ] )
			ConvertRGBA[ 1 ] = HexToDec( InHex[ 2..4 ] )
			ConvertRGBA[ 2 ] = HexToDec( InHex[ 4..6 ] )
			ConvertRGBA[ 3 ] = HexToDec( InHex[ 6..8 ] )

			Print "RGBA ["+InHex+"]:"+ConvertRGBA[ 0 ]+"  "+ConvertRGBA[ 1 ]+"  "+ConvertRGBA[ 2 ]+"  "+ConvertRGBA[ 3 ]
		Else
			Error "Wrong string length"
		Endif
	End

	Function HexToDec:Int( Hex:String )
		Local Value:Int = 0
		Local Char:Int =0

		If Hex.Length() <8
			'add 0's to beginning of thing so FF becomes 000000FF
			Local TempHex:String = ""
			For Char =Hex.Length() To 7
				TempHex += "0"
			Next
			TempHex += Hex
			Hex = TempHex
		Endif

		Local Conversion:Int = 1		'starts at 1 then 16, 256, 4096,
		'now the characters are 'eight bytes' now begin conversion
		For Char=7 To 0 Step -1
			If Hex[ Char ]<58
				Value += ( ( Hex[ Char ] -48 ) *Conversion )
			Else
				Value += ( ( Hex[ Char ] -55 ) *Conversion )
			Endif
			Conversion *= 16	'multiply conversion by 16 for next byte
		Next

		Return Value
	End

*/
