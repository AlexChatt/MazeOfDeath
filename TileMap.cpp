#include "TileMap.h"

//the fisher-yates shuffle
std::vector<int> TileMap::gettilestoobs(int max, int seed) // randomise our selection of tile to make an obstical
{
	srand(seed);

	std::vector<int> nums;

	for (int i = 0; i < max; i++)
	{
		int edgecheckx = i / height;
		int edgecheckz = i % height;

		if (!(edgecheckx == 0 || edgecheckx == width || edgecheckz == 0 || edgecheckz == height))
		{
			nums.push_back(i);
		}
	}

	for (int i = 0; i < nums.size(); i++)
	{
		int randnum = rand() % nums.size();
		int temphold = nums[i];
		nums[i] = nums[randnum];
		nums[randnum] = temphold;
	}
	return nums;
}
TileMap::TileMap()
{
	listnum = 0;
}


void TileMap::setup(int w, int h, int seed) //setup our map width heigh and the seed we want to use 
{
	width = w;
	height = h;

	tilemap.resize(width);

	for (int i = 0; i < width; i++)
	{
		tilemap[i].resize(height);
	}

	for (int i = 0; i < width; i++)
	{
		int xpos = i - (width / 2);

		for (int j = 0; j < height; j++)
		{
			int zpos = j - (height / 2);
			Tile newtile;
			newtile.position = glm::vec3(xpos + 0.5, 0, zpos + 0.5);
			newtile.x = i;
			newtile.y = j;
			tilemap[i][j] = newtile;

			if (i == 0 || i == width-1 || j == 0 || j == height-1)
			{
				tilemap[i][j].obstucted = true;
			}

		}
	}

	randomtiles = gettilestoobs(width * height, seed);
}

void TileMap::createmap()  //create our map 
{
	int currentobscount = 0;

	std::vector<std::vector<bool>> obs;
	obs.resize(width);
	for (int i = 0; i < width; i++)
	{
		obs[i].resize(height);
	}


	for (int i = 0; i < obsticalammount; i++)
	{
		int tile = gettile();
		int xpos = tile / height;
		int zpos = tile % height;

		currentobscount++;
		obs[xpos][zpos] = true;

		if (tilemap[xpos][zpos].obstucted != true)
		{
			if ((xpos != width / 2 || zpos != height / 2) && canaccess(obs, currentobscount))
			{
				tilemap[xpos][zpos].obstucted = true;
			}
			else if (tilemap[xpos][zpos].obstucted == false)
			{
				currentobscount--;
				obs[xpos][zpos] = false;
				tilemap[xpos][zpos].obstucted = false;
			}
		}

	}



}

bool TileMap::canaccess(std::vector<std::vector<bool>> obs, int currentobscount) //make sure that the tile we want to make an obstical does not block off an area of the map
{
	std::vector<std::vector<bool>> flag;
	flag.resize(width);
	for (int i = 0; i < width; i++)
	{
		flag[i].resize(height);
	}
	flag[width / 2][height / 2] = true;

	std::queue<std::pair<int,int>> queue;
	std::pair<int, int> toadd;
	toadd.first = width / 2;
	toadd.second = height / 2;
	queue.push(toadd);

	int access = 1;

	while (queue.size() > 0)
	{
		std::pair<int, int> start = queue.front();
		queue.pop();

		for (int x = -1; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y++)
			{
				int nextx = start.first + x;
				int nexty = start.second + y;

				if (x == 0 || y == 0)
				{
					if (nextx >= 0 && nexty >= 0 && nextx < width && nexty < height)
					{
						if (!flag[nextx][nexty] && !obs[nextx][nexty])
						{
							flag[nextx][nexty] = true;
							std::pair<int, int> toadd;
							toadd.first = nextx;
							toadd.second = nexty;
							queue.push(toadd);
							access++;
						}
					}
				}
			}
		}

	}

	int target = width * height - currentobscount;
	return target <= access;

}
//refernce to https://www.youtube.com/watch?v=2ycN6ZkWgOo for obstical algothim

int TileMap::gettile()
{
	return randomtiles[listnum++];
}



