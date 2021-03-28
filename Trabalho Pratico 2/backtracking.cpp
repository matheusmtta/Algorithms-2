#include <bits/stdc++.h>

//Set an arbitrarily large number as infinity
#define INF (double)0x3f3f3f3f

using namespace std;

int n; double C;
vector <double> val, wgt;

double solve(int idx, double cap){
	//Se o peso carregado for maior que a capacidade total
	//retorna um valor arbitrariamente pequeno -INF que será
	//descartado na recursão.
	if (cap < 0) return -INF;
	//Se não existem mais itens para serem verificados
	//retorna um valor nulo que não irá influenciar no resultado 
	if (idx == n) return 0;
	//Retorna o máximo entre NÃO PEGAR o item atual e PEGAR o item atual
	//adicionando o valor do item no resultado do ramo
	return max(solve(idx+1, cap), solve(idx+1, cap - wgt[idx]) + val[idx]);
}

int main(){
	//./exe < testcase
	//Lê a entrada a partir n itens C capacidade
	cin >> n >> C;

	//Lê o valor e o peso de cada item da entrada
	for (int i = 0; i < n; i++){
		double v, w; cin >> v >> w;
		val.push_back(v), wgt.push_back(w);
	} 

	//Salva o tempo inicial em que o algoritmo de backtracking irá iniciar
	auto initialExeTime = chrono::high_resolution_clock::now();

	//Chama a função de backtracking para o primeiro
	//elemento 0 com capacidade total C na mochila
	double ans = solve(0, C);

	//Salva o tempo final de execução do algoritmo de backtracking
	//computa o tempo de execução total em segundos
	auto finalExeTime = chrono::high_resolution_clock::now();
	double exeTime = chrono::duration_cast<chrono::microseconds>(finalExeTime - initialExeTime).count()*1e-6;

	cout << "Maximum value: " << setprecision(15) << ans << endl;
	cout << "Execution time: " << setprecision(15) << exeTime << endl;
}