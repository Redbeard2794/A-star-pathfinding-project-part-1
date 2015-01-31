
#include <iostream>
#include <fstream>

#include "Graph.h"
#include "aStarInfoStorage.h"
#include <utility>
#include <string>
#include <map>
using std::pair;

using namespace std;


typedef GraphArc<aStarInfoStorage, int> Arc;//<char,int> info at each arc and weight info 
typedef GraphNode<aStarInfoStorage, int> Node;

void visit( Node * pNode ) {
	//cout << "Visiting: " << pNode->data().first << " " << pNode->data().second << endl;
	cout << "Visit has been called" << endl;
}
void visitAstar(Node * pNode) {
	//cout << "Visiting: " << pNode->data().first << " " << pNode->data().second << endl;
	cout << "A* is visiting a node" << endl;
}

int main(int argc, char *argv[]) {
   
	/*Graph<pair<string, int>, int> graph(6);*///create the graph(9=number of vertices) 
	Graph<aStarInfoStorage, int> graph(30);//Need a third bit of info instead of a pair....

	string c; 
	int i = 0;
	ifstream myfile;
	myfile.open ("Nodes.txt");

	while ( myfile >> c ) {
		//graph.addNode(make_pair(c, INT_MAX), FLT_MAX, i++);
		graph.addNode(aStarInfoStorage(c, INT_MAX, INT_MAX), i++);
	}

	myfile.close();
	myfile.open("newArcs.txt");

	int from, to;
	int weight;
	int ifrom, ito;
	while ( myfile >> from >> to >> weight ) {
		ifrom = from;// from.at(0);// -'A';
		ito = to;// .at(0);// -'A';
		graph.addArc(ifrom, ito, weight);
	}
    myfile.close();

#pragma region breadthFirst
	// Now traverse the graph.
	//graph.breadthFirst( graph.nodeArray()[0], visit );//vertex to start at, function pointer(address of a function to be used)  
#pragma endregion


#pragma region adaptedBreadthFirst
	//graph.adaptedBreadthFirst(graph.nodeArray()[0], visit, graph.nodeArray()[15]);
	//Node* target = graph.nodeArray()[15];
	//while(target->getPrevNode()!=NULL)
	//{
	//	cout << target->data() << endl;
	//	target = target->getPrevNode();
	//}  
#pragma endregion

#pragma region UCS for start to destination
	//cout << "Here is the path" << endl;
	//std::vector<Node*> path;
	//graph.UCS(graph.nodeArray()[0], graph.nodeArray()[5], visit, path);
	//for (int i = 0; i < path.size(); i++)
	//{
	//	cout << path.at(i)->data().first << endl;//" " << path.at(i)->data().second << endl;
	//}
	//Node *finall = graph.nodeArray()[5];  
	//cout << finall->data().second << endl;
#pragma endregion


#pragma region Precomputing UCS for all possible routes from each node

	//std::map<string, vector<pair<string, int>>> routeMap;//list is essentially the path. Each element is pair of city name and its cost
	//
	////put each element from path (pair(first,second)) into the list of map 
	//string allKeys = "";
	//for (int index = 0; index < 5; index++)
	//{
	//	for (int i = index+1; i < graph.getCount(); i++)
	//	{
	//		vector<pair<string, int>> value;
	//		vector<Node*> path;

	//		//key is for putting into the map
	//		string key = graph.nodeArray()[index]->data().first + "->" + graph.nodeArray()[i]->data().first;


	//		//call UCS
	//		graph.UCS(graph.nodeArray()[index], graph.nodeArray()[i], visit, path);

	//		for (int h = 0; h < path.size(); h++)
	//			value.push_back(path.at(h)->data());
	//		//dont put duplicates into the map
	//		
	//		allKeys.append(key);

	//		//if (allKeys.compare(key) == 0)
	//			routeMap[key] = value;
	//		//clean up
	//		graph.clearMarks();
	//		path.clear();
	//		cout << endl;
	//	}
	//	
	//	cout << endl;
	//}
	//
	//cout << "Here are all possible routes to all nodes from all nodes" << endl;
	////outputting data in map
	//for (std::map<string, vector<pair<string, int>>>::iterator it = routeMap.begin(); it != routeMap.end(); ++it){
	//	cout << "*route* = " << it->first << endl;
	//	for (int i = 0; i < it->second.size(); i++)
	//	{
	//		cout << it->second.at(i).first << " "<<it->second.at(i).second << endl;
	//	}
	//}


	////output how many entries are in the map
	//cout << "The map has " << routeMap.size() << " entries" << endl;
#pragma endregion

	//A*
	string allKeys = "";
	for (int index = 0; index < 29; index++)
	{
		for (int i = index+1; i < graph.getCount(); i++)
		{
			vector<Node*> path;

			//call UCS
			graph.generateHeuristics(graph.nodeArray()[index], graph.nodeArray()[i], visit, path);
			
			allKeys.append(graph.key);

			graph.pathCosts[graph.key] = graph.value;
			//clean up
			graph.clearMarks();
			path.clear();
			cout << endl;
		}
		
		
	}
	cout << "** All paths computed **" << endl << endl;

	vector<Node*> bestPath;
	graph.aStar(graph.nodeArray()[9], graph.nodeArray()[28], visitAstar, bestPath);

	cout << endl;
	cout << "Here is the path: " << endl;

	graph.outputPath(bestPath);
	cout << endl;

	cout << "End of program" << endl;

	system("PAUSE");
	
}
