#define M_TREE_NODO_H
#ifdef M_TREE_NODO_H
#include <iostream>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
struct punto{
    string nombre;
    int x;
    int y;
};
void llenar(punto*media, string n_1, int x_1, int y_1){
    media->nombre = n_1;
    media->x = x_1;
    media->y = y_1;
}
bool comparar(const pair<float,punto> &a, const pair<float,punto> &b){
    return a.first < b.first;
}
class m_tree_nodo
{
private:
    punto*centro;
    float radio;
    int letra;
    m_tree_nodo *padre;
    vector<punto> valores;
    vector<m_tree_nodo*> hijos;
public:
    m_tree_nodo();
    float distancia(punto*, punto*);
    float distancia(vector<punto*>, vector<punto*>);
    void anadir(punto*, int);
    void actualizar(m_tree_nodo*,m_tree_nodo*);
    void division(m_tree_nodo*,int);
    void particion(m_tree_nodo*,m_tree_nodo*,m_tree_nodo*);
    void vecinos_mas_cercanos(punto*, float, int);
    friend ostream& operator << (ostream &o,const m_tree_nodo &p);
    ~m_tree_nodo();
};
m_tree_nodo::m_tree_nodo()
{
    centro = nullptr;
    radio = 0;
    letra = 0;
    padre = nullptr;
}
float m_tree_nodo::distancia(punto* a, punto* b){
    float dis_x = (a->x - b->x);
    float dis_y = (a->y - b->y);
    return  (dis_x * dis_x + dis_y * dis_y);
}
float m_tree_nodo::distancia(vector<punto*> a, vector<punto*> b){
    int i_1=0;
    int j_1=0;
    float maxima_distancia = -1;
    if(a.size() > 1){
        for(int i=0; i< a.size(); i++){
            for (int j = i+1; j < a.size(); j++){
                float dist = this->distancia((a[i]),(a[j]));
                if(maxima_distancia == -1 || dist > maxima_distancia){
                    maxima_distancia = dist;
                    i_1 = i;
                    j_1 = j;
                }
            }
        }
    }
    int i_2=0;
    int j_2=0;
    if(b.size() > 1){
        maxima_distancia = -1;
        for(int i=0; i< a.size(); i++){
            for (int j = i+1; j < a.size(); j++){
                float dist = this->distancia((a[i]),(a[j]));
                if(maxima_distancia == -1 || dist > maxima_distancia){
                    maxima_distancia = dist;
                    i_2 = i;
                    j_2 = j;
                }
            }
        }
    }
    float dis_x = (((a[i_1]->x + a[j_1]->x)/2) - ((a[i_2]->x + a[j_2]->x)/2));
    float dis_y = (((a[i_1]->y + a[j_1]->y)/2) - ((a[i_2]->y + a[j_2]->y)/2));
    return  (dis_x * dis_x + dis_y * dis_y);
}
void m_tree_nodo::anadir(punto* nuevo_punto, int n_maximo){
    m_tree_nodo * nuevo = this;
    while (!nuevo->hijos.empty()){
        int minima_distancia = -1;
        int minimo_indice = -1;
        for (int i = 0; i < nuevo->hijos.size(); i++){
            float dist = this->distancia(nuevo_punto,nuevo->hijos[i]->centro);
            if(minimo_indice == -1 || dist < minima_distancia){
                minima_distancia = dist;
                minimo_indice = i;
            }
        }
        nuevo = nuevo->hijos[minimo_indice];
    }
    nuevo->valores.push_back(*nuevo_punto);
    if(nuevo->valores.size() <= n_maximo){
        this->actualizar(nuevo,nullptr);
    }
    else{
        this->division(nuevo,n_maximo);
    }
}
void m_tree_nodo::actualizar(m_tree_nodo*nuevo, m_tree_nodo*hijo){
    m_tree_nodo * base = nuevo;
    while (base!=nullptr){
        if(hijo == nullptr){
            int ultimo = base->valores.size() - 1;
            if(base->centro == nullptr){
                base->centro = new punto();
                base->centro->nombre = char(this->letra + 65);
                this->letra++;
                base->centro->x = base->valores[ultimo].x;
                base->centro->y = base->valores[ultimo].y;
                break;
            }
            float dist = this->distancia(&(base->valores[ultimo]),base->centro);
            if(dist > base->radio){
                float nuevo_diametro = dist + base->radio;
                float nuevo_radio = nuevo_diametro/2;
                float dist_x = base->centro->x - base->valores[ultimo].x;
                float dist_y = base->centro->x - base->valores[ultimo].y;
                float rad_limit_x = nuevo_diametro*dist/dist_x;
                float rad_limit_y = nuevo_diametro*dist/dist_y;
                float x_rad = base->valores[ultimo].x + rad_limit_x;
                float y_rad = base->valores[ultimo].y + rad_limit_y;
                base->centro->x = (x_rad + base->valores[ultimo].x)/2;
                base->centro->y = (y_rad + base->valores[ultimo].y)/2;
                base->radio = nuevo_diametro/2;
                hijo = base;
                base = base->padre;
            }
            else{
                break;
            }
        }
        else{
            if(base->centro == nullptr){
                base->centro = new punto();
                base->centro->nombre = char(this->letra + 65);
                this->letra++;
                base->centro->x = hijo->centro->x;
                base->centro->y = hijo->centro->y;
                base->radio = hijo->radio;
                break;
            }
            float dist = this->distancia(hijo->centro,base->centro);
            if((dist + hijo->radio) > base->radio){
                float nuevo_diametro_1 = dist + base->radio;
                float dist_x = base->centro->x - hijo->centro->x;
                float dist_y = base->centro->x - hijo->centro->y;
                float rad_limit_x = nuevo_diametro_1*dist/dist_x;
                float rad_limit_y = nuevo_diametro_1*dist/dist_y;
                float x_rad_1 = hijo->centro->x + rad_limit_x;
                float y_rad_1 = hijo->centro->y + rad_limit_y;

                float nuevo_diametro_2 = dist + hijo->radio;
                dist_x = hijo->centro->x - base->centro->x;
                dist_y = hijo->centro->x - base->centro->y;
                rad_limit_x = nuevo_diametro_2*dist/dist_x;
                rad_limit_y = nuevo_diametro_2*dist/dist_y;
                float x_rad_2 = base->centro->x + rad_limit_x;
                float y_rad_2 = base->centro->y + rad_limit_y;

                base->centro->x = (x_rad_1 + x_rad_2)/2;
                base->centro->y = (y_rad_1 + y_rad_2)/2;
                base->radio = (dist + hijo->radio + base->radio)/2;
                hijo = base;
                base = base->padre;
            }
            else{
                break;
            }
        }
    }
}
void m_tree_nodo::division(m_tree_nodo*nuevo, int n_maximo){
    m_tree_nodo * dividido = nuevo;
    while(dividido != nullptr){
        m_tree_nodo* part1;
        m_tree_nodo* part2;
        part1 = new m_tree_nodo();
        part2 = new m_tree_nodo();
        this->particion(dividido,part1,part2);
        if(dividido->padre == nullptr){
            delete dividido->centro;
            dividido->centro = nullptr;
            if(dividido->hijos.empty()){
                dividido->valores.clear();
            }
            else{
                dividido->hijos.clear();
            }
            dividido->hijos.push_back(part1);
            part1->padre = dividido;
            this->actualizar(dividido,part1);
            dividido->hijos.push_back(part2);
            part2->padre = dividido;
            this->actualizar(dividido,part2);
            break;
        }
        else{
            m_tree_nodo* pad = dividido->padre;
            for (int i = 0; i < pad->hijos.size(); i++){
                if(pad->hijos[i] == dividido){
                    pad->hijos.erase(pad->hijos.begin()+i);
                    break;
                }
            }
            delete dividido;
            pad->hijos.push_back(part1);
            part1->padre = pad;
            this->actualizar(pad,part1);
            pad->hijos.push_back(part2);
            if(pad->hijos.size() <= n_maximo){
                part2->padre = pad;
                this->actualizar(pad,part2);
                dividido = nullptr;
            }
            else{
                dividido = pad;
            }
        }
    }
}
void m_tree_nodo::particion(m_tree_nodo*dividido,m_tree_nodo*part1,m_tree_nodo*part2){
    vector<vector<punto*>> grupos;
    if(dividido->hijos.empty()){
        for (int i = 0; i < dividido->valores.size(); i++){
            vector<punto*> m;
            m.push_back(&dividido->valores[i]);
            grupos.push_back(m);
        }
        int medidor = 0;
        while (grupos.size() > 2){
            float minima_distancia = -1;
            int i_1;
            int j_1;
            for (int i = 0; i < grupos.size(); i++){
                for (int j = i+1; j < grupos.size(); j++){
                    float dist = this->distancia(grupos[i],grupos[j]);
                    if(minima_distancia == -1 || dist < minima_distancia){
                        minima_distancia = dist;
                        i_1 = i;
                        j_1 = j;
                    }
                }
            }
            for (int k = 0; k < grupos[j_1].size(); k++){
                grupos[i_1].push_back(grupos[j_1][k]);
            }
            grupos.erase(grupos.begin()+j_1);
        }
        for (auto i:grupos[0]){
            part1->valores.push_back(*i);
            this->actualizar(part1,nullptr);
        }
        for (auto i:grupos[1]){
            part2->valores.push_back(*i);
            this->actualizar(part2,nullptr);
        }
    }
    else{
        vector<vector<int>> grupos_indice;
        int indic = 0;
        for (auto i:dividido->hijos){
            vector<punto*> m;
            vector<int> n;
            m.push_back(i->centro);
            n.push_back(indic);
            grupos.push_back(m);
            grupos_indice.push_back(n);
            indic++;
        }
        while (grupos.size() > 2){
            float minima_distancia = -1;
            int i_1;
            int j_1;
            for (int i = 0; i < grupos.size(); i++){
                for (int j = i+1; j < grupos.size(); j++){
                    float dist = this->distancia(grupos[i],grupos[j]);
                    if(minima_distancia == -1 || dist < minima_distancia){
                        minima_distancia = dist;
                        i_1 = i;
                        j_1 = j;
                    }
                }
            }
            for (int k = 0; k < grupos[j_1].size(); k++){
                grupos[i_1].push_back(grupos[j_1][k]);
                grupos_indice[i_1].push_back(grupos_indice[j_1][k]);
            }
            grupos.erase(grupos.begin()+j_1);
            grupos_indice.erase(grupos_indice.begin()+j_1);
        }
        for (auto i:grupos_indice[0]){
            part1->hijos.push_back(dividido->hijos[i]);
            dividido->hijos[i]->padre = part1;
            this->actualizar(part1,dividido->hijos[i]);
        }
        for (auto i:grupos_indice[1]){
            part2->hijos.push_back(dividido->hijos[i]);
            dividido->hijos[i]->padre = part2;
            this->actualizar(part2,dividido->hijos[i]);
        }
    }
}
ostream& operator << (ostream &o,const m_tree_nodo &p)
{
    if(p.hijos.empty()){
        for (auto i:p.valores){
            o << p.centro->nombre << " -> " << i.nombre <<";\n";
        }
    }
    else{
        for (auto i:p.hijos){
            o << p.centro->nombre << " -> " << i->centro->nombre <<";\n";
        }
        for (auto i:p.hijos){
            if(i!=nullptr)
                o << (*i);
        }
    }
    return o;
}
void m_tree_nodo::vecinos_mas_cercanos(punto* buscado, float distancia, int cantidad){
    queue<m_tree_nodo*> buscadores;
    vector<pair<float,punto>> respuestas;
    buscadores.push(this);
    while (!buscadores.empty()){
        m_tree_nodo* analizador = buscadores.front();
        buscadores.pop();
        if(!analizador->hijos.empty()){
            vector<m_tree_nodo*> dentro;
            vector<m_tree_nodo*> fuera;
            for (auto i:analizador->hijos){
                float dist = this->distancia(i->centro,buscado);
                dist = dist - i->radio;
                if(distancia > 0){
                    if(distancia >= dist){
                        dentro.push_back(i);
                    }
                    else{
                        fuera.push_back(i);
                    }
                }
                else if(dist <= 0){
                    dentro.push_back(i);
                }
                else{
                    fuera.push_back(i);
                }
            }
            if(!dentro.empty()){
                for (auto i:dentro)
                    buscadores.push(i);
            }
            else{
                for (auto i:fuera)
                    buscadores.push(i);
            }
        }
        else{
            for (auto i:analizador->valores){
                if(buscado->nombre != i.nombre){
                    float dist = this->distancia(&i,buscado);
                    if(distancia > 0){
                        if(distancia >= dist)
                            respuestas.push_back({dist,i});
                    }
                    else{
                        respuestas.push_back({dist,i});
                    }
                }
            }
        }
    }
    if(respuestas.empty()){
        cout<<"No hay vecino cercano en dicho rango"<<endl;
    }
    else{
        sort(respuestas.begin(),respuestas.end(),comparar);
        for (int i = 0; i < cantidad; i++){
            cout<<respuestas[i].second.nombre<<endl;
        }
    }
}
m_tree_nodo::~m_tree_nodo()
{
}
#endif