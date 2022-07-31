#include<iostream>
#include<cstdlib>
#define INFINITO 999
using namespace std ;

// costos[][] sera la matriz de costos del grafo a evaluar
int V, E, costos[100][100], origen; 

// Este tiene el conjunto de las distancias de los caminos mínimos desde el vértice de origen a todas los vertices del grafo
// distancia[i] --> es la minima distancia de src (vertice de origen) hacia un vertice i
int distancia[100];

// Indica que vertices ya tienen un camino minimo, desde el origen hasta i, con un true y cuales no con un false
// visitados[i] --> indica que el vertice i-esimo ya fue analizado 
// y ya existe un camino minimo desde el vertice de origen hasta el vertice i-ésimo
bool visitados[100];

// Tiene los padres de cada vertice que conforma un camino de longitud minima
// desde el vertice origen hasta el final
// --> verticePadre[childIndex] = parentIndex
int verticePadre[100];

void inicializacion();
int getCercano();
void dijkstra();
void mostrar();

int main() {
	cout<<"--------------------------CONSTRUCCION DEL GRAFO--------------------------"<<endl; 
    do {
		cout<<"Digite el numero de vertices: ";cin>>V;
	} while (V < 0);
    do {
		cout<<"Digite el numero de aristas: ";cin>>E;
	} while (E < 0);
	cout<<endl;
    
    // Inicializamos la matriz de costos con infinitos y ceros en la Traz(A)
    // costos[i][j] = indica el costo de la arista que va de i a j
    for(int i=0; i<V; i++){
    	for(int j=0; j<V; j++){
    		if(i==j){
    			costos[i][j] = 0;
			}else{
				costos[i][j] = INFINITO;
			}
		}
	}
	// Infinito indica que la arista de i a j en el grafo, no existe
    
    // Pedimos al usuario que brinde los datos
    // para crear las aristas del grafo, aristas que van del vértice "a" a "b"
	// y llenar la matriz de adyacencia ya inicializada con sus valores de costo
    int originIndex, finalIndex, costo;
	for(int i=0; i<E; i++){
		do {
			cout<<"Digite el indice del vertice de origen, puede ser de 0 a "<<V-1<<": ";cin>>originIndex;
		} while (0 > originIndex || originIndex >= V);
		
		do {
			cout<<"Digite el indice del vertice final, puede ser de 0 a "<<V-1<<": ";cin>>finalIndex;
		} while (0 > finalIndex || finalIndex >= V);
		
		cout<<"Costo de esta arista: ";cin>>costo;
		// Llenamos la matriz de costos simetricamente
		costos[originIndex][finalIndex] = costo;
		costos[finalIndex][originIndex] = costo;
		
		cout<<endl;
	}
	// Se pide que vértice sera el de origen
	cout<<"\nDesde que vertice inicia el recorrido: ";cin>>origen;
	inicializacion();
	dijkstra();
	mostrar();
	
	cout<<endl;
	system("pause");
	return 0;
}

void inicializacion(){
	// De momentos llenaremos de infinitos el vector de distancias de 
	// los caminos de menor longitud desde el origen hasta los vertices del grafo
	for(int i=0;i<V;i++){
		// Inicializamos el vector verticePadre
		verticePadre[i] = i;
		// De momentos no se sabe la distancia desde el origen hacia el vertice i-esimo
		distancia[i] = INFINITO;
		visitados[i] = false;
	}
	// Se declara que la distancia del origen al origen es 0
	distancia[origen] = 0;
}

void dijkstra(){
	for(int i=0; i<V; i++){
		// Obtiene el índice del vertice final del mínimo elemento del
		// conjunto de las distancias de los caminos mínimos del origen hasta los demás vértices
		int cercano = getCercano();
		// Indica que el vertice ya ha sido visitado
		visitados[cercano] = true;
		
		// Aqui actualizamos el vector distancia[]
		// Analisis por columnas en "j", recorriendo todos los vertices del grafo para ver qué vertices son vecinos y analizar distancias
		for(int j = 0; j<V; j++){
			if(costos[cercano][j] != INFINITO && distancia[j] > distancia[cercano] + costos[cercano][j]){ 
			// Si se cumple la condicion:
				// * Se actualizan las posibles distancias de los caminos mínimos
				// (distancia mínima del vertice de origen a cercano) + (costo de arista que va de cercano a un vertice vecino)
				distancia[j] = distancia[cercano] + costos[cercano][j];
				// * Se actualiza el vector de padres de cada vertice
				verticePadre[j] = cercano;
				// j: vertice vecino del vertice "cercano"
			}
		}
	}
}

int getCercano(){
	int min = INFINITO; 
	int minVertice = 0;
	// Funcion devuelve el indice del menor valor (vértice) del array distancia (de los vértices aun no analizados)
	for(int i=0; i<V; i++){
		// El camino corto no puede pasar por una misma arista
		// más de una vez, verificamos
		if(!visitados[i] && distancia[i] < min){ 
			min = distancia[i]; 
			minVertice = i;
		}
	} 
	return minVertice; 
}

void mostrar(){
	//Mostramos las rutas de costo minimo
	cout<<"\n------------------------------------------------------------------------------"<<endl<<endl;
	cout<<"Vertices Destino: \t\t\tCosto Minimo : \t\t\tRuta: "<<endl;
	
	for(int i=0; i<V; i++){
		cout<<i<<"\t\t\t\t\t"<<distancia[i]<<"\t\t\t\t"<<" ";
		cout<<i<<" ";
		// Obtenemos el padre de dicho vertice
		int verticeRuta = verticePadre[i];
		// Aca obtenemos los padres que conforman el camino mas corto
		// desde el origen hasta el vértice i-ésimo del grafo
		while(verticeRuta != origen){
			cout<<" <-- "<<verticeRuta<<" ";
			verticeRuta = verticePadre[verticeRuta];
		}
		cout<<" <-- "<<origen;
		cout<<endl;
	}
}
