#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <texture.h>

class ChessPiece {
	public:
		ChessPiece();
		void renderWithCoord(float coord[12]);
		void setCodeId(int id){code_id = id;}
		int getCodeId(){return code_id;}
	private:
		Texture pieceTex;
		float scr_coord[12];
		float tex_coord[8];
		int code_id;
	
		static unsigned short id_num;
};

#endif
