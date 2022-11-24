#define M_TREE_H
#ifdef M_TREE_H
#include "m_tree_nodo.h"
class m_tree{
private:
    m_tree_nodo *raiz;
    int maximos_hijos;
public:
    m_tree(int);
    ~m_tree();
};
m_tree::m_tree(int hijos_maximo = 4){
    raiz = new m_tree_nodo();
    maximos_hijos = hijos_maximo;
}
m_tree::~m_tree()
{
}
#endif