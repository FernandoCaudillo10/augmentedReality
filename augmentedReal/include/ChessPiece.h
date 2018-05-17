#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <texture.h>

class ChessPiece {
	public:
		ChessPiece();
		void renderWithCoord(float coord[12]);
		
	private:
		Texture pieceTex;
		float scr_coord[12];
		float tex_coord[8];
		int code_id;
};

#endif
