#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <texture.h>

class ChessPiece {
	public:
		ChessPiece();
		void renderWithCoord(float coord[12]);
		void setType(int id);
		int getCodeId(){return code_id;}
	private:
		static const std::vector<std::string> paths;
		Texture pieceTex;
		float scr_coord[12];
		float tex_coord[8];
		int code_id;
	
		static unsigned short id_num;
};

#endif
