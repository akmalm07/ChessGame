#include "pch.h"
#include "Game.h"



//
//Game::Game()
//{
//	GraphicsHandlerAPI::InitalizeAPIS();
//
//	InitalizeCommon(); 
//
//	textures.clear();
//
//}


Game::Game(unsigned int windowHeight, unsigned int windowWidth)  
{
	Initalize(); 

	RunGame(windowWidth, windowHeight);

}


void Game::CreateWindow(unsigned int height, unsigned int width, const std::string& name)
{
	auto [data , outcomeBool] = windows.emplace(name, Window(width, height, name)); 

	if (!outcomeBool) 
	{
		fprintf(stderr, "Error Creating window ( Game : CreateWindow )");
		EndGame();
		return;
	}

	bool error = data->second.CreateWindow(); 

	if (!error) 
	{
		fprintf(stderr, "Error Creating window ( Game : CreateWindow )");
		EndGame();
		return;
	}

	printf("Window official is created with the name %s", name.c_str());

}



void Game::InitalizeBoardWindowButtons(const std::string& windowName)
{
	if (windows.find(windowName) == windows.end())
	{
		fprintf(stderr, "Entered invalid window name ( Game.cpp : InitalizeWindowButtons )");
		return;
	}

	Window& window = windows.at(windowName); 
	

	board.SetWindowButtonsInChessFormat(window);
}




void Game::InitalizeBoard(unsigned int winWidth, unsigned int winHeight, const std::string& name)
{
	printf("\n Board Intialized!\n");

	float brightnessFactor = 0.85f;// Brightness

	glm::vec4 lightGreen = glm::vec4(0.5647f, 0.9294f, 0.5647f, 1.0f);

	glm::vec4 white = glm::vec4(1.0f, 1.0f, 0.9412f, 1.0f);

	lightGreen *= brightnessFactor;
	white *= brightnessFactor;

	board.SetAllValues(winWidth, winHeight ,
		lightGreen.r, lightGreen.g, lightGreen.b, lightGreen.a,
		white.r, white.g, white.b, white.a);

	InitalizeMeshes();

	AddPieces(); 

	InitalizeBoardWindowButtons(name);

}


void Game::InitalizeMeshes()
{ 

	printf("\nMeshes Intialized!\n");
	
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			std::unique_ptr<Mesh> squares = std::make_unique<Mesh>(); 
			if (!squares)
			{
				fprintf(stderr, "ASSERT ERROR");
			}
			auto vertices = board.GetSquareVerticies(i, j);
			auto indices = board.GetSquareIndicies();

			squares->Initalize(vertices, indices, true, false);  
			meshesSquares[i * 8 + j] = std::move(squares); 

		}
	}
}



void Game::RenderBoard(GLuint squareColorUniform, GLuint textureUniform, glm::mat4& modelMatrix)
{
	std::string str = "bRook";

	shaders->LinkModelMatrix(modelMatrix); 

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			board.UseSquareColor(squareColorUniform, ((i + j) % 2) == 0); 

			UseTextures(textureUniform, i, j); 

			if (meshesSquares[i * 8 + j]) 
			{
				meshesSquares[i * 8 + j]->RenderMesh(); 
			}
			else
			{
				fprintf(stderr, "Rendering the Mesh of Squares in board is nullptr! (RenderBoard : Game.cpp)");
			}
		}
	}



	return;
}




void Game::AddPieces() 
{
	printf("\n Pieces Intialized and added!\n");

	for (size_t i = 0; i < 8; i++)
	{
		std::unique_ptr<Pawn> pawnBlack = std::make_unique<Pawn>(Colors::BLACK, i);
		board.AddPiece<Pawn>(std::move(pawnBlack));

		std::unique_ptr<Pawn> pawnWhite = std::make_unique<Pawn>(Colors::WHITE, i);
		board.AddPiece<Pawn>(std::move(pawnWhite));
	}

	for (size_t i = 0; i < 2; i++) 
	{
		Colors color = (i == 0 ? Colors::BLACK : Colors::WHITE);

		for (size_t j = 0; j < 2; j++) 
		{
			bool boolean = static_cast<bool>(j);

			std::unique_ptr<Rook> rook = std::make_unique<Rook>(color, boolean);
			board.AddPiece<Rook>(std::move(rook));

			std::unique_ptr<Knight> knight = std::make_unique<Knight>(color, boolean); 
			board.AddPiece<Knight>(std::move(knight));

			std::unique_ptr<Bishop> bishop = std::make_unique<Bishop>(color, boolean);
			board.AddPiece<Bishop>(std::move(bishop));
		}

		std::unique_ptr<Queen> queen = std::make_unique<Queen>(color);
		board.AddPiece<Queen>(std::move(queen));  

		std::unique_ptr<King> king = std::make_unique<King>(color);
		board.AddPiece<King>(std::move(king));   
	}

	board.AssignValuesForPosition();
}



void Game::LoadTextures()
{

	printf("\nLoaded Textures!\n");

	//Texture darkSquare("Textures/darkSquare.png");
	//textures[0] = darkSquare;

	//Texture lightSquare("Textures/lightSquare.png");
	//textures[1] = lightSquare;


	std::string textureNames[] = 
	{
	"wPawn", "wRook", "wKnight", "wBishop", "wQueen", "wKing", 
	"bPawn", "bRook", "bKnight", "bBishop", "bQueen", "bKing"
	};

	for (const auto& name : textureNames) 
	{ 
		Texture texture("../Textures/" + name + ".png");
		texture.LoadTexture();
		if (!texture.IsLoaded())
		{
			fprintf(stderr, " \nFailed to load texture %s \n", name.c_str());
			continue;
		}
		textures[name] = std::move(texture); 
	}

}


void Game::UseTextures(GLuint textureLocation, unsigned int posX, unsigned int posY)
{
	Colors color = BoardLayout::GetCurrentStateColors(posX, posY);
	

	GLuint location = shaders->IsTexValidLocation();
	if (color != Colors::EMPTY)
	{

		std::string str = "";
		Pieces piece = BoardLayout::GetCurrentStatePieces(posX, posY);

		switch (color)
		{
		case Colors::BLACK:
			str = "b";
			break;
		case Colors::WHITE:
			str = "w";
			break;
		}

		switch (piece)
		{
		case Pieces::PAWN:
			str += "Pawn";
			break;
		case Pieces::ROOK:
			str += "Rook";
			break;
		case Pieces::KNIGHT:
			str += "Knight";
			break;
		case Pieces::BISHOP:
			str += "Bishop";
			break;
		case Pieces::QUEEN:
			str += "Queen";
			break;
		case Pieces::KING:
			str += "King";
			break;
		}

		if (textures.find(str) == textures.end())
		{
			return;
		}
		Texture& texture = textures.at(str);
		texture.UseTexture(GL_TEXTURE0, textureLocation); 
		board.UseIsTexValid(location, GL_TRUE);
	}
	else
	{
		board.UseIsTexValid(location, GL_FALSE);
	}

	return;
}



void Game::CreateShaders(const std::string& vertShader, const std::string& fragShader)
{
	shaders = std::make_unique<Shader>();
	shaders->CreateFromFiles(vertShader, fragShader); 
}



void Game::RunGame(unsigned int windowWidth, unsigned int windowHeight)
{
	std::string windowName = "Main Run";
	CreateWindow(windowHeight, windowWidth, windowName);  


	InitalizeBoard(windowWidth, windowHeight, windowName);


	if (windows.find(windowName) == windows.end()) 
	{
		fprintf(stderr, "Entered invalid window name ( Game.cpp : RunGame) "); 
		return;
	}

	Window& window = windows.at(windowName); 

	CreateShaders(vertFile, fragFile);
	



	glm::mat4 projection = glm::ortho(window.GetLeftOrtho(), window.GetRightOrtho(), window.GetTopOrtho(), window.GetBottomOrtho());

	//GLuint modelUniform, projectionUniform; 
	GLuint squareColorUniform, textureUniform;

	//GLboolean isBlackSquare;

	window.AddKeyCombonation(GLFW_KEY_ESCAPE, [&window]()
		{
			printf("Window Closed by Escape Key");
			glfwSetWindowShouldClose(window.GetWindow(), GLFW_TRUE);

		});
	
	window.AddKeyCombonation(GLFW_KEY_Z, Mods::CONTROL
		, [&window]()
		{
			window.SetWhichTimePressed(false);

		});


	LoadTextures(); 

	while (!window.GetShouldClose())
	{
		/*std::this_thread::sleep_for(std::chrono::seconds(1));
		printf("I was in the main window loop");*/
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  

		glfwPollEvents();

		glClearColor(1.0f, 0.5f, 0.0f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glm::mat4 model(1.0f);

		shaders->UseShader();  
		shaders->LinkModelMatrix(model);  
		shaders->LinkProjectionMatrix(projection);

		textureUniform = shaders->GetTex0Location(); 
		squareColorUniform = shaders->GetSquareColorLocation(); 


		RenderBoard(squareColorUniform, textureUniform, model);   



		window.SwapBuffers();
	}




}





void Game::EndGame()  
{
	Delete(); 

	GraphicsHandlerAPI::ShutdownAPIS();  
}


Game::~Game()
{
	EndGame();
}




void Game::Delete()
{

	shaders.reset();

	posX = 0;
	posY = 0;

	textures.clear();

	windows.clear();

	for (auto& mesh : meshesSquares)
	{
		mesh.reset();
	}

	for (auto& mesh : meshesPieces)
	{
		mesh.reset(); 
	}

	for (size_t i = 0; i < players.size(); i++)
	{
		players[i].color = Colors::EMPTY;
		players[i].turn = false;
	}
}


void Game::Clear()
{

	shaders = nullptr;


	posX = 0;
	posY = 0;

	for (auto& [key, texture] : textures)
		texture.ClearTexture();
	textures.clear();

	for (auto& [key, window] : windows)
		window.ClearWindow();
	windows.clear();


	for (const auto& mesh : meshesSquares)
		if (mesh != nullptr)
			mesh->ClearMesh();


	for (const auto& mesh : meshesPieces)
		if (mesh != nullptr)
			mesh->ClearMesh(); 
	meshesPieces.clear();

	for (size_t i = 0; i < players.size(); i++)
	{
		players[i].color = Colors::EMPTY;
		players[i].turn = false;
	}
}


void Game::Initalize()
{
	Clear();
	bool success = GraphicsHandlerAPI::InitalizeAPIS(); 
	if (success == false)
	{
		fprintf(stderr, "Failed to Initialize the APIS (Game.cpp : Initialize())");
	}
}

//
//
//void Game::Switch(Piece::Pieces instruction, std::function<void(int)> Func, unsigned int addFactor) 
//{
//	switch (instruction)
//	{
//
//	case Pieces::wPawn: 
//		Func(0 + addFactor);
//		break;
//
//	case Pieces::wRook:
//		Func(1 + addFactor);
//		break;
//
//	case Pieces::wKnight:
//		Func(2 + addFactor);
//		break;
//
//	case Pieces::wBishop:
//		Func(3 + addFactor);
//		break;
//
//	case Pieces::wQueen:
//		Func(4 + addFactor);
//		break;
//
//	case Pieces::wKing:
//		Func(5 + addFactor);
//		break;
//
//	case Pieces::bPawn:
//		Func(6 + addFactor);
//		break;
//
//	case Pieces::bRook:
//		Func(7 + addFactor);
//		break;
//
//	case Pieces::bKnight:
//		Func(8 + addFactor);
//		break;
//
//	case Pieces::bBishop:
//		Func(9 + addFactor);
//		break;
//
//	case Pieces::bQueen:
//		Func(10 + addFactor);
//		break;
//
//	case Pieces::bKing:
//		Func(11 + addFactor);
//		break;
//	}
//}
//
//
//void Game::Switch(Piece::Pieces instruction, std::function<void()> Func1, std::function<void()> Func2, std::function<void()> Func3, std::function<void()> Func4, std::function<void()> Func5, std::function<void()> Func6)
//{
//
//	switch (instruction)
//	{
//
//	case Pieces::wPawn:
//	case Pieces::bPawn:
//		Func1();
//		break;
//
//	case Pieces::wRook:
//	case Pieces::bRook:
//		Func2();
//		break;
//
//	case Pieces::wKnight:
//	case Pieces::bKnight:
//		Func3();
//		break;
//
//	case Pieces::wBishop:
//	case Pieces::bBishop:
//		Func4();
//		break;
//
//	case Pieces::wQueen:
//	case Pieces::bQueen:
//		Func5();
//		break;
//
//	case Pieces::wKing:
//	case Pieces::bKing:
//		Func6();
//		break;
//
//	}
//}
//
//
//
//void Game::CreatePieces()
//{
//	bool color = true;
//	bool first = true;
//	int k = 0;
//	size_t idx = 0;
//
//
//	for (size_t i = 0; i < 2; i++)
//	{
//		Player player(color);
//		playerList[i] = player;
//
//		Queen queen(color);
//		queenList[i] = queen;
//
//		King king(color);
//		kingList[i] = king;
//
//		if (i == 1)
//		{
//			color = !color;
//		}
//	}
//
//	color = true;
//
//	for (size_t i = 0; i < 4; i++)
//	{
//
//		Rook rook(color, first);
//		rookList[i] = rook;
//
//		Knight knight(color, first);
//		knightList[i] = knight;
//
//		Bishop bishop(color, first);
//		bishopList[i] = bishop;
//
//		first = !first;
//
//		if (i == 1)
//		{
//			color = !color;
//		}
//	}
//
//	color = true;
//
//	for (size_t i = 0; i < 16; i++)
//	{
//		Pawn pawn(color, i + 1);
//		pawnList[i] = pawn;
//
//		if (i == 7)
//		{
//			color = !color;
//		}
//
//	}
//
//	idx = 0;
//	for (size_t j = 0; j < 8; j++) {
//		Mesh piece;
//		piece.Initalise(pieces.GetPieceVerticies(j, 1).data(), pieces.GetPieceIndicies().data(), 16, 6, true, false);
//		meshListPieces[idx++] = piece;
//	}
//
//	for (size_t j = 0; j < 8; j++) {
//		Mesh piece;
//		piece.Initalise(pieces.GetPieceVerticies(j, 0).data(), pieces.GetPieceIndicies().data(), 16, 6, true, false);
//		meshListPieces[idx++] = piece;
//	}
//
//	for (size_t j = 0; j < 8; j++) {
//		Mesh piece;
//		piece.Initalise(pieces.GetPieceVerticies(j, 6).data(), pieces.GetPieceIndicies().data(), 16, 6, true, false);
//		meshListPieces[idx++] = piece;
//	}
//
//	for (size_t j = 0; j < 8; j++) {
//		Mesh piece;
//		piece.Initalise(pieces.GetPieceVerticies(j, 7).data(), pieces.GetPieceIndicies().data(), 16, 6, true, false);
//		meshListPieces[idx++] = piece;
//	}
//
//
//	pieces.setMove();
//}

		//if (!mainWindow.GetIsLeftButtonPressed())
		//{

		//	xS = mainWindow.GetMouseXS();
		//	yS = mainWindow.GetMouseYS();

		//	pieceIDS = pieces.CheckPieceID(xS, yS);

		//	index = pieces.ConvertIDtoNum(pieceIDS);

		//	if (pieceIDS != 0)
		//	{
		//		Switch(
		//			Piece::ConvertIDtoEnum(pieceIDS),  
		//			[this]() {
		//				basePtr = &pawnList[index]; 
		//				available = basePtr->FindAvailableMoves();
		//			},
		//			[this]() {
		//				basePtr = &rookList[index]; 
		//				available = basePtr->FindAvailableMoves();
		//			}, 
		//			[this]() {
		//				basePtr = &knightList[index];
		//				available = basePtr->FindAvailableMoves();
		//			},
		//			[this]() {
		//				basePtr = &bishopList[index];
		//				available = basePtr->FindAvailableMoves();
		//			},
		//			[this]() {
		//				basePtr = &queenList[index];
		//				available = basePtr->FindAvailableMoves();
		//			},
		//			[this]() {
		//				basePtr = &kingList[index];
		//				available = basePtr->FindAvailableMoves();
		//			}
		//		);

		//	}
		//	
		//}
		//else
		//{
		//	xE = mainWindow.GetMouseXE();
		//	yE = mainWindow.GetMouseYE();

		//	pieceIDE = pieces.CheckPieceID(xE, yE);

		//	if (available[xE][yE] and pieces.CanMove(xE, yE) and playerList[0].GetTurn())
		//	{
		//		id = basePtr->MoveToSquare(xE, yE);

		//		if (id != 0)
		//		{
		//			Switch(
		//				pieces.ConvertIDtoEnum(id),

		//				[this]() {
		//					pawnList[pieces.ConvertIDtoNum(id)].Clear();  
		//				},
		//				[this]() { 
		//					rookList[pieces.ConvertIDtoNum(id)].Clear(); 
		//				},
		//				[this]() {
		//					knightList[pieces.ConvertIDtoNum(id)].Clear(); 
		//				},
		//				[this]() {
		//					bishopList[pieces.ConvertIDtoNum(id)].Clear(); 
		//				},
		//				[this]() {
		//					queenList[pieces.ConvertIDtoNum(id)].Clear(); 
		//				},
		//				[this]() {
		//					kingList[pieces.ConvertIDtoNum(id)].Clear();
		//				}
		//			);
		//		}

		//		pieces.SwitchTurns();

		//		players[0].SwitchTurn();
		//	}
		//	else if (available[xE][yE] and pieces.CanMove(xE, yE) and playerList[1].GetTurn())
		//	{
		//		basePtr->MoveToSquare(xE, yE);

		//		pieces.SwitchTurns();

		//		playerList[1].SwitchTurn();
		//	}


		//}