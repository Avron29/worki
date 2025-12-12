#include "worki.h"
#include <list>
#include <iostream>

// Musimy gdzies przechowywac przedmioty zeby potem moc je wszystkie zwolnic
// By osiagnoc operacje w rzeczywistym czasie stalym uzywamy listy
static std::list<przedmiot*> g_przedmioty;
static std::list<worek*> g_worki;
static worek* g_biurko = nullptr;

static void initBiurko(){
    g_biurko = new worek;
    g_biurko->id = -1;
    g_worki.push_back(g_biurko);
    g_biurko->selfpointer = &g_worki.back();
    g_biurko->nadworek = &g_worki.back(); 
}

przedmiot* nowy_przedmiot(){
    static int id = 0;
    if (g_biurko == nullptr) initBiurko();
    przedmiot* p = new przedmiot;
    p->id = id;
    id++;
    g_przedmioty.push_back(p);
    p->nadworek = g_biurko->selfpointer;
    return p;
}

worek* nowy_worek(){
    static int id = 0;
    if (g_biurko == nullptr) initBiurko();
    worek* w = new worek;
    w->id = id;
    id++;
    g_worki.push_back(w);
    w->selfpointer = &g_worki.back();
    w->nadworek = g_biurko->selfpointer;
    return w;
}

void wloz(przedmiot* co, worek *gdzie){
    (*co->nadworek)->liczbaElementow--;
    co->nadworek = gdzie->selfpointer;
    gdzie->liczbaElementow++;
}

void wloz(worek* co, worek* gdzie){
    (*co->nadworek)->liczbaElementow -= co->liczbaElementow;
    co->nadworek = gdzie->selfpointer;
    gdzie->liczbaElementow += co->liczbaElementow;
}

void wyjmij(przedmiot* p){
    wloz(p, g_biurko);
}

void wyjmij(worek* w){
    wloz(w, g_biurko);
}

int w_ktorym_worku(przedmiot* p){
    return (*p->nadworek)->id; 
}

int w_ktorym_worku(worek* w){
    return (*w->nadworek)->id; 
}

int ile_przedmiotow(worek* w){
    return w->liczbaElementow;
}

void na_odwrot(worek* w){
    std::swap(*w->selfpointer, *g_biurko->selfpointer);
    std::swap(w->selfpointer, g_biurko->selfpointer);
    w->nadworek = g_biurko->selfpointer;
    w->liczbaElementow = static_cast<int>(g_przedmioty.size()) - w->liczbaElementow;
}

void gotowe(){
    for (przedmiot* p : g_przedmioty) delete p;
    for (worek* w : g_worki) delete w;
}
