#include <bits/stdc++.h>

using namespace std;

//Cada container irá representar um item, com valores relativos
//ao seu valor, peso e proporção de valor por peso
struct Container {
	double val, wgt, ratio;
	Container(double val, double wgt) : val(val), wgt(wgt){
		ratio = val/wgt; 
	}
};

//Retorna verdadeiro se a proporção de lucro por peso do item lhs for maior que a do item rhs
//utilizaremos essa função para ordenar nosso vetor
bool comp(const Container &lhs, const Container &rhs){ return lhs.ratio > rhs.ratio; }

//Cada nó irá armazenar informações acerca de cada vértice na busca, i.e, 
//profundidade do nó na árvore e o lucro/peso atual sendo obtidos/carregados 
struct Node {
	int depth = 0;
	double profit = 0, weight = 0;
	
	//Checa o um bound de resultado para o nó atual, tomando o lucro corrente e o
	//valor que pode ser agregado a ele em um caso ótimo (talvez impossível)
	double getBound(const double &C, const int &n, const vector<Container> &itens){
		return profit + ((C - weight)*(depth == n ? 0 : itens[depth].ratio));		
	}
	
	Node(int depth, double profit, double weight) :  depth(depth), profit(profit), weight(weight){}
};

//Redefine o operador de < para ordenar os elementos da fila de prioridades
//dando preferência aos nós com maior lucro, e em caso de empate, aqueles com
//o menor peso total
bool operator < (const Node &lhs, const Node &rhs){
	if (lhs.profit == rhs.profit)
		return lhs.weight > rhs.weight;
	return lhs.profit < rhs.profit;
}	

int main(){
	//./exe < testcase
	//Lê a entrada a partir n itens C capacidade
	int n; double C;
	cin >> n >> C;

	vector <Container> itens; 

	//Lê o valor e o peso de cada item da entrada
	for (int i = 0; i < n; i++){
		double v, w; cin >> v >> w;
		Container tmp(v, w);
		itens.push_back(tmp);
	}

	double ans = 0;

	//Salva o tempo inicial em que o algoritmo de backtracking irá iniciar
	auto initialExeTime = chrono::high_resolution_clock::now();

	//Ordena os itens de acordo com a razão entre
	//valor e peso de cada um individualmente
	sort(itens.begin(), itens.end(), comp);

	//Define uma fila de prioridades que prioriza
	//o nó da árvore de branch & bound com maior lucro atual
	priority_queue <Node> q;

	//Inicializa a busca com um nó no nível 0, lucro 0 e peso 0
	Node src(0, 0, 0);
	q.push(src);

	while (!q.empty()){
		//Toma o nó de maior lucro atual na árvore de pesquisa
		Node v = q.top(); q.pop();

		//Verifica se o nó é um nó válido, i.e, profundidade < n-1
		//(número total de itens) e peso inferior a capacidade total da mochila
		if (v.depth == n || v.weight > C) continue;

		//Cria nós de busca relativos a pegar o item atual ou não pegá-lo
		Node nxtPick(v.depth+1, v.profit + itens[v.depth].val, v.weight + itens[v.depth].wgt);
		Node nxtLeft(v.depth+1, v.profit, v.weight);

		//Verificamos se o nó que pego o elemento atual é válido, i.e,
		//peso acumulado é menor que a capacidade da mochila C, e checamos
		//se o lucro corrente é maior que o da resposta global ótima.
		//Se sim, atualizamos nossa resposta final
		if (nxtPick.weight <= C && nxtPick.profit > ans)
			ans = nxtPick.profit;

		//Checamos quais nós tem potencial para serem uma resposta
		//ótima, e os adicionamos à fila de prioridades
		if (nxtPick.getBound(C, n, itens) > ans) q.push(nxtPick);
		if (nxtLeft.getBound(C, n, itens) > ans) q.push(nxtLeft);
	}

	//Salva o tempo final de execução do algoritmo de backtracking
	//computa o tempo de execução total em segundos
	auto finalExeTime = chrono::high_resolution_clock::now();
	double exeTime = chrono::duration_cast<chrono::microseconds>(finalExeTime - initialExeTime).count()*1e-6;

	cout << "Maximum value: " << setprecision(15) << ans << endl;
	cout << "Execution time: " << setprecision(15) << exeTime << endl;

	return 0;
}