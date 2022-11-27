#define M_TREE_H
#ifdef M_TREE_H
#include "m_tree_nodo.h"
class m_tree{
private:
    m_tree_nodo *raiz;
    int tamano;
    int maximos_hijos;
public:
    m_tree(int);
    void anadir(punto*);
    friend ostream& operator << (ostream &o,const m_tree &p);
    void vecinos_mas_cercanos(punto*, float, int);
    ~m_tree();
};
m_tree::m_tree(int hijos_maximo = 4){
    raiz = new m_tree_nodo();
    maximos_hijos = hijos_maximo;
}
void m_tree::anadir(punto*nuevo){
    raiz->anadir(nuevo,maximos_hijos);
}
ostream& operator << (ostream &o,const m_tree &p)
{
    o << *(p.raiz);
    return o;
}
void m_tree::vecinos_mas_cercanos(punto*buscado, float distancia = 0, int cantidad = 1){
    raiz->vecinos_mas_cercanos(buscado,distancia,cantidad);
}
m_tree::~m_tree()
{
}
#endif