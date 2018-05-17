#include <ChessPiece.h>

unsigned short ChessPiece::id_num = 0;
const std::vector<std::string> ChessPiece::paths({
	"media/towerBlack.jpg",
	"media/horseBlack.jpg",
	"media/bishopBlack.jpg",
	"media/kingBlack.jpg",
	"media/queenBlack.jpg",
	"media/pawnBlack.jpg",
	"media/towerWhite.jpg",
	"media/horseWhite.jpg",
	"media/bishopWhite.jpg",
	"media/kingWhite.jpg",
	"media/queenWhite.jpg",
	"media/pawnWhite.jpg",
	});

ChessPiece::ChessPiece() {
	code_id = id_num++;

	float tempvert[32] = {
                        // positions          // colors           // texture coords
                          0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
                          0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
                         -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
                         -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
                };
	unsigned int tempin[6] = {
					0, 1, 3, // first triangle
					1, 2, 3  // second triangle
			};
	float tempfl[8] = {
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
		};
 
	pieceTex.setasGraphic();

	pieceTex.setVertices(tempvert);
	pieceTex.setTexCoordinate(tempfl);
	pieceTex.setIndices(tempin);
	pieceTex.setBuffers();

	pieceTex.setImage("smile.png");
	pieceTex.bind();
	pieceTex.renderTexbyIm();
}
void ChessPiece::renderWithCoord(float coord[12]) {
	pieceTex.render();

	for (unsigned int i=0; i < 12; ++i) {
		scr_coord[i] = coord[i];
	}
	
	pieceTex.updateCoordinate(scr_coord);
	pieceTex.draw();
}
void ChessPiece::setType(int id){
	code_id = id;
	
	pieceTex.setImage(paths[id].c_str());
	pieceTex.bind();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	pieceTex.renderTexbyIm();
}
