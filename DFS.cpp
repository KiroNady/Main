#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int> > DFS(vector<vector<int > > g);
void DFSnode(vector<vector<int> > *g, int index, vector<bool> *visited, int *time , vector <vector <int> > *times);
void TopologicalSort(vector<vector<int> > g);
vector<vector<int > > Transpose(vector<vector<int > > *g);

int main(){

	vector< vector <int> > g(6);
	g[0].push_back(1);
	g[0].push_back(3);

	g[1].push_back(4);

	g[2].push_back(4);
	g[2].push_back(5);
	
	g[3].push_back(1);

	g[4].push_back(3);
	g[5].push_back(5);

	//DFS(g);
	//TopologicalSort(g);
	vector <vector < int > > gT(Transpose(&g));

	for (int i = 0 ; i < gT.size() ; i++){
		cout << i << " : ";
		for (int j = 0; j < gT[i].size() ; j++){
			cout << gT[i][j] << " ";
		}
		cout << endl;
	}
	

}

vector<vector<int> > DFS(vector<vector<int > > g){
	vector<bool> visited(6);
	for (int i =0; i < 6; i++){
		visited[i]=false;
	}
	vector <vector <int> > times(6);
	int time = 0;
	for (int i =0; i<g.size(); i++){
		if (!visited[i]){
			visited[i] = true;
			DFSnode(&g , i , &visited , &time , &times);
		}
	}
	return times;
}

void DFSnode(vector<vector<int> > *g, int index, vector<bool> *visited, int *time , vector <vector <int> > *times){
	(*time)++;
	cout << "begin " << index << " : " << *time << endl;
	(*times)[index].push_back(*time);
	for (int i = 0; i< (*g)[index].size(); i++){
		int node = (*g)[index][i];
		if (!((*visited)[node])){
			(*visited)[node] = 1;
			DFSnode(&(*g) , (*g)[index][i] , &(*visited) , &(*time) , &(*times));
		}
	}
	(*time)++;
	cout << "end " << index << " : " << *time << endl;
	(*times)[index].push_back(*time);
	return;
}

bool sortcol(vector<int> v1 , vector<int> v2){
	return v1[1] < v2[1];
}

void TopologicalSort(vector<vector<int> > g){

	vector <vector<int> > tp(DFS(g));
	for(int i = 0; i < tp.size() ; i++){
		cout << tp[i][0] << " " << tp[i][1] << endl;
	}
	sort(tp.begin() , tp.end(), sortcol);
	cout << "sorted " << endl;
	for(int i = 0; i < tp.size() ; i++){
		cout << tp[i][0] << " " << tp[i][1] << endl;
	}
}


vector<vector<int > > Transpose(vector<vector<int > > *g){
	vector<vector<int> > gT((*g).size());

	for (int i = 0 ; i < (*g).size() ; i++){
		for (int j = 0; j < (*g)[i].size() ; j++){
			gT[(*g)[i][j]].push_back(i);
		}
	}
	return gT;
}

