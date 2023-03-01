#ifndef TILEMAP_H
#define TILEMAP_H
#include "export.h"
#include "Utility.h"
#include "TextureImporter.h"
#include "tinyxml2.h"
#include "Tile.h"

#include <iostream>
#include <vector>

class ENGINE_API TileMap 
{
public:
	TileMap();
	TileMap(std::string filePath);
	TileMap(const char* MapTiles, const char* filePath, int width);
	void setTileDimensions(float tileWidth, float tileHeight);
	void setDimensions(float width, float height);
	void draw();
	void CollisionTileMap(Entity2D& vs);
	std::vector<Sprite> ReturnCollisions();
	~TileMap();
	bool alpha = false;

	 const Tile& tile(unsigned int uiId);
	 void setTile(const Tile& rkTile);
	 void setMapTileId(int layer, unsigned int uiCol, unsigned int uiRow, unsigned int uiId);

	 void setTexture(const TextureData& rkTexture);
	 void draw(Renderer& rkRenderer);

	 bool importTileMap(std::string filePath);

	 bool importTileMap(std::string filePath, Renderer& rkRenderer);
	 void checkCollision(Entity2D& object);

	//std::vector<Frame> myFrames;
	/*void Update();
	int currentFrame;
	float currentTime;*/
private:
	std::vector<Tile> tiles;
	std::vector<Tile**> _tileMapGrid;

	std::vector<Sprite> tiled;
	std::vector<Sprite> ColisionTiles;

	unsigned int _width;
	unsigned int _height;

	float _tileWidth;
	float _tileHeight;

	TextureData map;

	float _imageWidth;
	float _imageHeight;

	float convertedPosX;
	float convertedPosY;

	int widthReference, heightReference;
	char _imagePath;
	//float length = 0;
	//const float lengthMultiply = 1000;

};
#endif
