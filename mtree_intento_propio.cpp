#include "m_tree.h"
int main(){
    cout<<"_____________________________________________________________________________"<<endl;
    m_tree arbol_m;
    string llenar_nombre[20] = {"Peru", "Bulgaria", "Bosnia_and_Herzegovina", "Montenegro", "North_Macedonia"
    , "Hungary", "Czechia", "Georgia", "Romania", "Gibraltar","Brazil","San_Marino","Croatia", "Slovakia"
    , "Argentina", "Armenia", "Lithuania", "Slovenia","Colombia","USA"};
    float llenar_x[20] = {66477,101106,84584,250528,103485,114600,200245,212561,93390,215221,102912,175688
    ,149455,124480,116439,113938,176235,202419,98156,148104};
    float llenar_y[20] = {5983,4139,3870,3673,3639,3586,3080,3030,2966,2910,2863,2733,2678,2639,2547,2547
    ,2525,2512,2489,2406};
    for (int i = 0; i < 20; i++){
        punto *a = new punto();
        llenar(a,llenar_nombre[i],llenar_x[i],llenar_y[i]);
        arbol_m.anadir(a);
        delete a;
        if(i == 4 || i == 9){
            cout<<arbol_m;
            cout<<"_____________________________________________________________________________"<<endl;
        }
    }
    cout<<arbol_m;
    cout<<"_____________________________________________________________________________"<<endl;
    punto *a = new punto();
    llenar(a,llenar_nombre[0],llenar_x[0],llenar_y[0]);
    arbol_m.vecinos_mas_cercanos(a,37000);
    cout<<"_____________________________________________________________________________"<<endl;
    llenar(a,llenar_nombre[5],llenar_x[5],llenar_y[5]);
    arbol_m.vecinos_mas_cercanos(a);
/*---------------------------------------------------------------------------------------------------------------------------------*/
    cout<<"_____________________________________________________________________________"<<endl;
    m_tree arbol_n;
    string llenar_nombre2[20] = {"USA","Slovenia","Slovakia","San_Marino","Romania","Peru", "North_Macedonia","Montenegro"
    ,"Lithuania","Hungary","Gibraltar","Georgia","Czechia","Croatia","Colombia","Bulgaria","Brazil","Bosnia_and_Herzegovina"
    ,"Armenia","Argentina"};
    float llenar_x2[20] = {148104,202419,124480,175688,93390,66477,103485,250528,176235,114600,215221
    ,212561,200245,149455,98156,101106,102912,84584,113938,116439};
    float llenar_y2[20] = {2406,2512,2639,2733,2966,5983,3639,3673,2525,3586,2910,3030,3080,2678,2489
    ,4139,2863,3870,2547,2547};
    for (int i = 0; i < 20; i++){
        punto *a = new punto();
        llenar(a,llenar_nombre2[i],llenar_x2[i],llenar_y2[i]);
        arbol_n.anadir(a);
        delete a;
        if(i == 4 || i == 9){
            cout<<arbol_n;
            cout<<"_____________________________________________________________________________"<<endl;
        }
    }
    cout<<arbol_n;
    cout<<"_____________________________________________________________________________"<<endl;
    punto *b = new punto();
    llenar(b,llenar_nombre[5],llenar_x[5],llenar_y[5]);
    arbol_m.vecinos_mas_cercanos(b,37000);
    cout<<"_____________________________________________________________________________"<<endl;
    llenar(b,llenar_nombre[9],llenar_x[9],llenar_y[9]);
    arbol_m.vecinos_mas_cercanos(b);
    return 0;
}