#define M_TREE_NODO_H
#ifdef M_TREE_NODO_H
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
    void anadir(float, float, int);
    float distancia(float, float, m_tree_nodo*);
    void particion(m_tree_nodo*,m_tree_nodo*,m_tree_nodo*);
    void division(m_tree_nodo*,int);
    void actualizar(m_tree_nodo*,m_tree_nodo*);
    vector<pair<int,int>> dist_min_into(m_tree_nodo*);
    ~m_tree_nodo();
};

m_tree_nodo::m_tree_nodo()
{
    centro=nullptr;
    radio = 0;
    raiz = nullptr;
    padre = nullptr;
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
        this->actualizar(nuevo,nullptr);
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
    if(N->hijos.empty()){
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
        N_1->padre = N_raiz;
        N_2->padre = N_raiz;
        N_raiz->hijos.push_back(N_1);
        N_raiz->actualizar(N_raiz,N_1);
        N_raiz->hijos.push_back(N_2);
        N_raiz->actualizar(N_raiz,N_2);
    }
    else{
        m_tree_nodo* morir;
        morir = N;
        N = N_1;
        delete morir;
        N_1->padre = N_padre;
        this->actualizar(N_padre,N_1);
        N_padre->hijos.push_back(N_2);
        N_2->padre = N_padre;
        if(N->hijos.size() > n_maximo){
            this->division(N_padre, n_maximo);
        }
        else{
            this->actualizar(N_padre,N_2);
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
void m_tree_nodo::actualizar(m_tree_nodo*N,m_tree_nodo*P = nullptr){
    while (1){
        if(N->centro == nullptr){
            N->centro = new float[2];
            N->centro[0] = N->valores[0].first;
            N->centro[1] = N->valores[0].second;
        }
        if(P==nullptr){
            auto j = N->valores.end();
            j--;
            float dist = this->distancia(j->first,j->second,N);
            if(dist > N->radio){
                float nuevo_diametro = dist + N->radio;
                float dis_y = N->centro[1] - j->second;
                float dis_x = N->centro[0] - j->first;
                float dis_x_rad = dis_x*nuevo_diametro/dist;
                float dis_y_rad = dis_y*nuevo_diametro/dist;
                N->centro[0]-= (dis_x_rad - dis_x);
                N->centro[1]-= (dis_y_rad - dis_y);
                N->radio = nuevo_diametro/2;
            }
            return;
        }
        else{
            float dist = this->distancia(P->centro[0],P->centro[1],N);
            if((dist + P->radio) > N->radio){
                float nuevo_diametro = dist + P->radio + N->radio;
                float dis_y = N->centro[1] - P->centro[1];
                float dis_x = N->centro[0] - P->centro[0];
                float dis_x_rad = dis_x * N->radio/dist;
                float dis_y_rad = dis_y * N->radio/dist;
                float x4 = dis_x_rad + N->centro[0];
                float y4 = dis_y_rad + N->centro[1];
                dis_x_rad = dis_x * (dist + P->radio)/dist;
                dis_y_rad = dis_y * (dist + P->radio)/dist;
                float x3 = dis_x_rad - N->centro[0];
                float y3 = dis_y_rad - N->centro[1];
                N->centro[0] = (x4 - x3)/2;
                N->centro[1] = (y4 - y3)/2;
                N->radio = nuevo_diametro/2;
            }
        }
        if(N->padre != nullptr)
            this->actualizar(N->padre,N);
    }
}
m_tree_nodo::~m_tree_nodo()
{
}
#endif