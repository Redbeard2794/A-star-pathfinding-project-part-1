#ifndef ASTARINFOSTORAGE
#define ASTARINFOSTORAGE

#include <string>

using namespace std;

class aStarInfoStorage
{
public:
	aStarInfoStorage();

	aStarInfoStorage(string n, float c, float h);

	~aStarInfoStorage();

	string getNodeName();

	float getHeuristicValue();

	float getCostSoFar();

	void setNodeName(string na);

	void setHeuristicValue(float he);

	void setCostSoFar(float co);
private:
	string nodeName;
	float heuristicValue;
	float costSoFar;
};

aStarInfoStorage::aStarInfoStorage()
{
}


aStarInfoStorage::aStarInfoStorage(string n, float c, float h) : nodeName(n), costSoFar(c), heuristicValue(h)
{
}

aStarInfoStorage::~aStarInfoStorage(){}

#pragma region Gets
string aStarInfoStorage::getNodeName(){ return nodeName; }

float aStarInfoStorage::getHeuristicValue(){ return heuristicValue; }

float aStarInfoStorage::getCostSoFar(){ return costSoFar; }
#pragma endregion

#pragma region Sets
void aStarInfoStorage::setNodeName(string na){ nodeName = na; }

void aStarInfoStorage::setHeuristicValue(float he){ heuristicValue = he; }

void aStarInfoStorage::setCostSoFar(float co) { costSoFar = co; }
#pragma endregion







#endif