#include <iostream>
#include <limits.h>
#include <algorithm>
#include <vector>
using namespace std;

class m_tree_nodo
{
private:
    float *centro;
    float radio;
    m_tree_nodo *padre;
    m_tree_nodo *raiz;
    vector<pair<float,float>> valores;
    vector<m_tree_nodo*> hijos;
public:
    m_tree_nodo();
    void anadir(float, float, m_tree_nodo*);
    float distancia(float, float, m_tree_nodo*);
    void particion(m_tree_nodo*,m_tree_nodo*,m_tree_nodo*);
    void division(m_tree_nodo*,int);
    vector<pair<int,int>> dist_min_into(m_tree_nodo*);
    ~m_tree_nodo();
};

m_tree_nodo::m_tree_nodo()
{
    centro=nullptr;
    radio = 0;
    raiz = nullptr;
    padre = nullptr;
    hijos = nullptr;
}
void m_tree_nodo::anadir(float x_new, float y_new, int n_maximo){
    m_tree_nodo * nuevo = this->raiz;
    if(this->raiz == nullptr)
        nuevo = this;
    while (!nuevo->hijos.empty()){
        vector<pair<int,int>> valores;
        vector<pair<int,int>> valores_2;
        for (int i = 0; i < nuevo->hijos.size(); i++){
            float dist = this->distancia(x_new,y_new,nuevo->hijos[i]);
            if(nuevo->hijos[i]->radio >= dist){
                valores.push_back({dist, i});
            }
            valores_2.push_back({dist - nuevo->hijos[i]->radio, i});
        }
        if(!valores.empty()){
            sort(valores.begin(),valores.end());
            int indice = valores[0].second;
            nuevo = nuevo->hijos[indice];
        }
        else{
            sort(valores_2.begin(),valores_2.end());
            int indice = valores_2[0].second;
            nuevo = nuevo->hijos[indice];
        }
    }
    nuevo->valores.push_back({x_new,y_new});
    if(nuevo->valores.size() > n_maximo){
        this->division(nuevo,n_maximo);
    }
    else{
        this->actualizar(nuevo);
    }
}
float m_tree_nodo::distancia(float x, float y, m_tree_nodo*N){
    float dis_x = (N->centro[0] - x);
    float dis_y = (N->centro[1] - y);
    return  (dis_x * dis_x + dis_y * dis_y);
}
void m_tree_nodo::particion(m_tree_nodo*N,m_tree_nodo*N_1,m_tree_nodo*N_2){
    N_1 = new m_tree_nodo();
    N_2 = new m_tree_nodo();
    if(!N->hijos.empty()){
        
    }
    else{
        vector<pair<int,int>> menor_dist = this->dist_min_into(N);
        bool visitado[N->hijos.size()]{false};
        int medio = N->hijos.size() /2;
        int cont = 0;
        for (auto i:menor_dist){
            if(cont<medio){
                if(!visitado[i.first]){
                    N_1->valores.push_back(i.first);
                }
                if(!visitado[i.second]){
                    N_1->valores.push_back(i.second);
                }
            }
            else{
                if(!visitado[i.first]){
                    N_2->valores.push_back(i.first);
                }
                if(!visitado[i.second]){
                    N_2->valores.push_back(i.second);
                }
            }
            cont++;
        }
    }
}
void m_tree_nodo::division(m_tree_nodo*N, int n_maximo){
    m_tree_nodo* N_padre;
    if(N != this->raiz){
        N_padre = N->padre;
    }
    m_tree_nodo* N_1;
    m_tree_nodo* N_2;
    particion(N,N_1,N_2);
    if(N == this->raiz){
        m_tree_nodo* N_raiz = new m_tree_nodo();
        this->raiz = N_raiz;
        N_2->padre = N_raiz;
        N_1->padre = N_raiz;
        N_raiz->hijos.push_back(N_1,N_2);
    }
    else{
        m_tree_nodo* morir;
        morir = N;
        N = N_1;
        delete morir;
        N_padre->hijos.push_back(N_2);
        N_1->padre = N_padre;
        N_2->padre = N_padre;
        if(N->hijos.size() > n_maximo){
            this->division(N_padre, n_maximo);
        }
    }
}
vector<pair<int,int>> m_tree_nodo::dist_min_into(m_tree_nodo*N){
    vector<pair<int,int>> resul;
    vector<pair<int,pair<int,int>>> resul_2;
    for (int i = 0; i < N->valores.size(); i++){
        for (int j = i+1; j < N->valores.size(); j++){
            float dis_x = (N->valores[i].first - N->valores[j].first);
            float dis_y = (N->valores[i].second - N->valores[j].second);
            float resul = (dis_x * dis_x + dis_y * dis_y);
            resul_2.push_back({resul,{i,j}});
        }
    }
    sort(resul_2.begin(),resul_2.end());
    for (auto i:resul_2){
        resul.push_back(i.second);
    }
    return resul;
}
m_tree_nodo::~m_tree_nodo()
{
}

int main(){
    return 0;
}