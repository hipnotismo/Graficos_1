#include "TileMap.h"

TileMap::TileMap() {

}

const Tile& TileMap::tile(unsigned int uiId) {
	Tile* NoTile = nullptr;

	for (int i = 0; i < tiles.size(); i++) {
		if (uiId == tiles[i].getId()) {
			return tiles[i];
		}
	}

	return *NoTile;
}
//================================================
void TileMap::setMapTileId(int layer, unsigned int uiCol, unsigned int uiRow, unsigned int uiId) {
	_tileMapGrid[layer][uiCol][uiRow] = tile(uiId);
}
//================================================
void TileMap::setTile(const Tile& rkTile) {
	tiles.push_back(rkTile);
}
//================================================
void TileMap::setTileDimensions(float tileWidth, float tileHeight) {
	_tileWidth = tileWidth;
	_tileHeight = tileHeight;
}
//================================================
void TileMap::setDimensions(float width, float height) {
	_width = width;
	_height = height;

	//creo la grilla bidimensional para guardar la posicion de cada tile igual que en el editor
	Tile** tileMap;
	tileMap = new Tile * [_height];
	for (int i = 0; i < _height; i++) {
		tileMap[i] = new Tile[_width];
	}
	_tileMapGrid.push_back(tileMap);
}
//================================================
void TileMap::setTexture(const TextureData& rkTexture) {
	map = rkTexture;
}
//================================================
void TileMap::draw() {

	float mapWidth = -(_width * _tileWidth) / 2;
	float mapHeight = (_height * _tileHeight) / 2;

	for (int i = 0; i < _tileMapGrid.size(); i++) {
		for (int y = 0; y < _height; y++) {
			for (int x = 0; x < _width; x++) {
				if (_tileMapGrid[i][y][x].getId() != NULL) {
					_tileMapGrid[i][y][x].setPosX(mapWidth + (_tileWidth * x));
					_tileMapGrid[i][y][x].setPosY(mapHeight - (_tileHeight * y));
					_tileMapGrid[i][y][x].Draw();
				}
			}
		}
	}

}

bool TileMap::importTileMap(std::string filePath) {
	tinyxml2::XMLDocument doc; //guarda el documento
	tinyxml2::XMLError errorHandler; //guarda el resultado de las funciones

	errorHandler = doc.LoadFile(filePath.c_str()); //carga el archivo XML
	if (errorHandler == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED) return false;

	// Loading Map element and save Map width, heigth in tiles and width, heigth of Tiles in pixels
	tinyxml2::XMLElement * mapNode = doc.FirstChildElement("map");
	if (mapNode == nullptr)
		return false;
	setDimensions(mapNode->FloatAttribute("width"), mapNode->FloatAttribute("height"));				// Get width and heigth for
	setTileDimensions(mapNode->FloatAttribute("tilewidth"), mapNode->FloatAttribute("tileheight")); // the map and the tiles

	// Loading Tilset element
	tinyxml2::XMLElement * pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset == NULL)
		return false;

	int tileCount = pTileset->IntAttribute("tilecount"); // Number of Tiles in the Tileset
	int columns = pTileset->IntAttribute("columns");  // Columns of Tiles in the Tileset
	int rows = tileCount / columns;

	//_imagePath += pTileset->FirstChildElement("image")->Attribute("source");			// Loading Textures
	//setTexture(rkRenderer.loadTexture(_imagePath.c_str(), D3DCOLOR_XRGB(255, 255, 255))); //
	map = TextureImporter::ImportTexture("Res/Sprites/map.png");

	// Save the Tiles in the TileMap
	_imageWidth = pTileset->FirstChildElement("image")->IntAttribute("width");
	_imageHeight = pTileset->FirstChildElement("image")->IntAttribute("height");
	float tileX = 0.0f, tileY = 0.0f;
	int _id = 1;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			Tile newTile;

			newTile.setId(_id);
			newTile.SetTextureData(map);
			newTile.Scale(_tileWidth, _tileHeight, 1.0f);

			newTile.SetTextureCoordinate(tileX / _imageWidth, tileY / _imageHeight,
				(tileX + _tileWidth) / _imageWidth, tileY / _imageHeight,
				tileX / _imageWidth, (tileY + _tileHeight) / _imageHeight,
				(tileX + _tileWidth) / _imageWidth, (tileY + _tileHeight) / _imageHeight);

			tileX += _tileWidth;
			setTile(newTile);
			_id++;
		}
		tileX = 0;
		tileY += _tileHeight;
	}

	tinyxml2::XMLElement * pTile = pTileset->FirstChildElement("tile");

	while (pTile) {
		unsigned int id = pTile->IntAttribute("id");
		tinyxml2::XMLElement* pProperty = pTile->FirstChildElement("properties")->FirstChildElement("property");
		std::string propertyName = pProperty->Attribute("value");
		if (propertyName == "false")
			tiles[id].walkability(false);
		else
			tiles[id].walkability(true);

		pTile = pTile->NextSiblingElement("tile");
	}

	// Loading Layer element
	tinyxml2::XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer == NULL)
		return false;

	int layerCount = 0;
	while (pLayer) {
		// Loading Data element
		tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
		if (pData == NULL)
			return false;

		if (layerCount > 0) {
			Tile** tileMap;
			tileMap = new Tile * [_height];
			for (int i = 0; i < _height; i++) {
				tileMap[i] = new Tile[_width];
			}
			_tileMapGrid.push_back(tileMap);
		}

		while (pData) {
			std::vector<int> tileGids;
			for (tinyxml2::XMLElement* pTile = pData->FirstChildElement("tile");
				pTile != NULL;
				pTile = pTile->NextSiblingElement("tile"))
			{
				unsigned int gid = std::atoi(pTile->Attribute("gid")); // tile's id is saved
				tileGids.push_back(gid);
			}

			int gid = 0;
			for (int y = 0; y < _height; y++) {
				for (int x = 0; x < _width; x++) {
					if (tileGids[gid] != 0)
						setMapTileId(layerCount, y, x, tileGids[gid]);
					gid++;
				}
			}

			pData = pData->NextSiblingElement("data");
		}
		layerCount++;
		pLayer = pLayer->NextSiblingElement("layer");
	}

	return true;
}

TileMap::TileMap(std::string filePath)
{
	/*data = TextureImporter::ImportTexture(filePath);
	if (data.nrChannels == 4)
		alpha = true;*/

	tinyxml2::XMLDocument doc; //guarda el documento
	tinyxml2::XMLError errorHandler; //guarda el resultado de las funciones

	errorHandler = doc.LoadFile(filePath.c_str()); //carga el archivo XML
	if (errorHandler == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED) {
		std::cout << "ERROR::TILEMAP::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	// Loading Map element and save Map width, heigth in tiles and width, heigth of Tiles in pixels
	tinyxml2::XMLElement * mapNode = doc.FirstChildElement("map");
	if (mapNode == nullptr)
		std::cout << "ERROR::TILEMAP::FILE_NOT_SUCCESFULLY_MAP" << std::endl;

	//_tileWidth = mapNode->FloatAttribute("tilewidth");
	//std::cout << mapNode->FloatAttribute("tilewidth") << std::endl;

}

void TileMap::checkCollision(Entity2D& object) {

	convertedPosX = object.GetPositionX() + (_width / 2) * _tileWidth;
	convertedPosY = object.GetPositionY() - (_height / 2) * _tileHeight;

	int left_tile = convertedPosX / _tileWidth;
	int right_tile = (convertedPosX + object.GetScaleX()) / _tileWidth;

	int top_tile = (convertedPosY / _tileHeight) * -1;
	int bottom_tile = ((convertedPosY - object.GetScaleY()) / _tileHeight) * -1; // Se resta porque el eje Y crece hacia arriba

	if (left_tile < 0)
		left_tile = 0;

	if (right_tile >= _width)
		right_tile = _width - 1;

	if (top_tile < 0)
		top_tile = 0;

	if (bottom_tile >= _height)
		bottom_tile = _height - 1;

	/*
	cout << "converted X: " << convertedPosX << endl;
	cout << "converted Y: " << convertedPosY << endl;

	cout << "left: " <<left_tile << endl;
	cout << "right: "<<right_tile << endl;
	cout << "top: " << top_tile << endl;
	cout << "bottom: "<<bottom_tile << endl;
	*/

	for (int i = left_tile; i <= right_tile; i++) {

		for (int j = top_tile; j <= bottom_tile; j++) {

			for (int k = 0; k < _tileMapGrid.size(); k++) {
				//cout << "caminable " << "[" << k << "]" << "[" << j << "]" << "[" << i << "] : "<< _tileMapGrid[k][j][i].isWalkable() << endl; // true == 1  ; false == 0
				//cout << true << endl;
				if (!_tileMapGrid[k][j][i].isWalkable()) {

					if (_tileMapGrid[k][j][i].checkCollision(object) == CollisionHorizontalRight ||
						_tileMapGrid[k][j][i].checkCollision(object) == CollisionHorizontalLeft)
						object.returnToPreviusPosH();

					if (_tileMapGrid[k][j][i].checkCollision(object) == CollisionVerticalUp)
						object.returnToPreviusPos(object.GetPositionX(), object.previusPosY() + 0.2);

					else if (_tileMapGrid[k][j][i].checkCollision(object) == CollisionVerticalDown)
						object.returnToPreviusPos(object.GetPositionX(), object.previusPosY() - 0.2);
				}
			}
		}
	}
}

TileMap::TileMap(const char* MapTiles, const char* filePath, int width)
{
	map = TextureImporter::ImportTexture(filePath);
	if (map.nrChannels == 4)
		alpha = true;
	int counter = 0;

	widthReference = width;
	heightReference = strlen(MapTiles) / width;

	float tileXW = 0.0f, tileYW = -100.0f, _tileWidthW = 43, _tileHeightW = 43;
	int _imageWidthW = 763, _imageHeightW = 349;

	float tileX = 200.0f, tileY = -100.0f, _tileWidth = 43, _tileHeight = 43;
	int _imageWidth = 763, _imageHeight = 349;

	for (int y = 0; y < heightReference; y++)
	{
		for (int x = 0; x < widthReference; x++)
		{
			char tileType = MapTiles[counter];

			Sprite newSpite;
			newSpite.SetPosition(x, y, -1.0f);
			newSpite.SetTextureData(map);
			switch (tileType)
			{
			case 'W':
				
				newSpite.SetTextureCoordinate(tileXW / _imageWidthW, tileYW / _imageHeightW,
					(tileXW + _tileWidthW) / _imageWidthW, tileYW / _imageHeightW,
					tileXW / _imageWidthW, (tileYW + _tileHeightW) / _imageHeightW,
					(tileXW + _tileWidthW) / _imageWidthW, (tileYW + _tileHeightW) / _imageHeightW);	
				newSpite.weight = 90;
				ColisionTiles.push_back(newSpite);

				break;
			case 'G':
				

				newSpite.SetTextureCoordinate(tileX / _imageWidth, tileY / _imageHeight,
					(tileX + _tileWidth) / _imageWidth, tileY / _imageHeight,
					tileX / _imageWidth, (tileY + _tileHeight) / _imageHeight,
					(tileX + _tileWidth) / _imageWidth, (tileY + _tileHeight) / _imageHeight);

				break;
			default:
				break;
			}
			counter++;
			tiled.push_back(newSpite);
		}
	}

}

TileMap::~TileMap() {

}

void TileMap::draw() {
	for (int i = 0; i < tiled.size(); i++) {
		tiled[i].Draw();
	}
}

void  TileMap::CollisionTileMap(Entity2D& vs) {

	for (int i = 0; i < ColisionTiles.size(); i++) {

		ColisionTiles[i].CheckCollisionAABB(vs);
	}
}

std::vector<Sprite> TileMap::ReturnCollisions() {

	return ColisionTiles;
}
