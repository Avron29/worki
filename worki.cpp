#include "worki.h"
#include <vector>
#include <iostream>

static std::vector<przedmiot*> g_przedmioty;
static worek* g_biurko = new worek;
static std::vector<worek*> g_worki = {g_biurko};

przedmiot* nowy_przedmiot(){
    static int id = 0;
    przedmiot* p = new przedmiot;
    g_przedmioty.push_back(p);
    p->id = id;
    id++;
    p->nadworek = g_biurko->index;
    return p;
}

worek* nowy_worek(){
    static int id = 0;
    worek* w = new worek;
    w->index = static_cast<int>(g_worki.size());
    g_worki.push_back(w);
    w->id = id;
    id++;
    w->nadworek = g_biurko->index;
    return w;
}

void wloz(przedmiot* co, worek *gdzie){
    g_worki[co->nadworek]->liczbaElementow--;
    co->nadworek = gdzie->index;
    gdzie->liczbaElementow++;
}

void wloz(worek* co, worek* gdzie){
    g_worki[co->nadworek]->liczbaElementow -= co->liczbaElementow;
    co->nadworek = gdzie->index;
    gdzie->liczbaElementow += co->liczbaElementow;
}

void wyjmij(przedmiot* p){
    wloz(p, g_biurko);
}

void wyjmij(worek* w){
    wloz(w, g_biurko);
}

int w_ktorym_worku(przedmiot* p){
    return g_worki[p->nadworek]->id; 
}

int w_ktorym_worku(worek* w){
    return g_worki[w->nadworek]->id; 
}

int ile_przedmiotow(worek* w){
    return w->liczbaElementow;
}

void na_odwrot(worek* w){
    std::swap(g_worki[g_biurko->index], g_worki[w->index]);
    std::swap(g_biurko->index, w->index);
    w->nadworek = g_biurko->index;
    w->liczbaElementow = static_cast<int>(g_przedmioty.size()) - w->liczbaElementow;
}

void gotowe(){
    for (przedmiot* p : g_przedmioty) delete p;
    for (worek* w : g_worki) delete w;
}