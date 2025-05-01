#include "../include/tabbporo.h"

/****************************
 *
 * TNODOABB
 *
 ****************************/

TNodoABB::TNodoABB() {
    // Constructor por defecto de item se invoca automáticamente
    // Los subárboles iz y de se invocan automáticamente con sus constructores
}

TNodoABB::TNodoABB(const TNodoABB & n) : item(n.item), iz(n.iz), de(n.de) {
    // Copio el item y los subárboles izquierdo y derecho
}

TNodoABB::~TNodoABB() {
    // No necesito hacer nada explícitamente, ya que los destructores 
    // de item, iz, y de se invocarán automáticamente
}

TNodoABB & TNodoABB::operator=(const TNodoABB & n) {
    if(this != &n) {
        item = n.item;
        iz = n.iz;
        de = n.de;
    }
    return *this;
}

/****************************
 *
 * TABBPORO
 *
 ****************************/

TABBPoro::TABBPoro() {
    nodo = NULL;
}

TABBPoro::TABBPoro(const TABBPoro & a) {
    if(a.nodo == NULL)
        nodo = NULL;
    else {
        // Duplico todo el árbol con una copia profunda
        nodo = new TNodoABB(*a.nodo);
    }
}

TABBPoro::~TABBPoro() {
    if(nodo != NULL) {
        delete nodo;
        nodo = NULL;
    }
}

TABBPoro & TABBPoro::operator=(const TABBPoro & a) {
    if(this != &a) {
        // Destruyo el árbol actual
        if(nodo != NULL) {
            delete nodo;
            nodo = NULL;
        }
        
        // Copio el nuevo árbol
        if(a.nodo != NULL)
            nodo = new TNodoABB(*a.nodo);
    }
    return *this;
}

bool TABBPoro::operator==(const TABBPoro & a) const {
    // Dos árboles son iguales si tienen los mismos elementos
    // independientemente de su estructura
    
    // Si ambos están vacíos, son iguales
    if(EsVacio() && a.EsVacio())
        return true;
    
    // Comparo los recorridos en inorden, que contienen los elementos ordenados
    TVectorPoro v1 = Inorden();
    TVectorPoro v2 = a.Inorden();
    
    if(v1.Longitud() != v2.Longitud())
        return false;
    
    // Verifico que todos los elementos sean iguales
    for(int i = 1; i <= v1.Longitud(); i++) {
        if(v1[i] != v2[i])
            return false;
    }
    
    return true;
}

bool TABBPoro::EsVacio() const {
    return nodo == NULL;
}

bool TABBPoro::Insertar(const TPoro & poro) {
    // Si el árbol está vacío, creo un nuevo nodo
    if(EsVacio()) {
        nodo = new TNodoABB();
        nodo->item = poro;
        return true;
    }
    
    // No permitimos duplicados (mismo volumen)
    if(Buscar(poro))
        return false;
    
    // Inserto según el volumen
    if(poro.Volumen() < nodo->item.Volumen())
        return nodo->iz.Insertar(poro);
    else
        return nodo->de.Insertar(poro);
}

bool TABBPoro::Borrar(const TPoro & poro) {
    // Si el árbol está vacío, no puedo borrar
    if(EsVacio())
        return false;
    
    // Voy buscando el nodo a borrar
    if(poro.Volumen() < nodo->item.Volumen())
        return nodo->iz.Borrar(poro);
    else if(poro.Volumen() > nodo->item.Volumen())
        return nodo->de.Borrar(poro);
    else if(nodo->item != poro) // Mismo volumen pero diferente poro
        return false;
    else {
        // He encontrado el poro a borrar
        
        // Caso 1: Nodo hoja (sin hijos)
        if(nodo->iz.EsVacio() && nodo->de.EsVacio()) {
            delete nodo;
            nodo = NULL;
            return true;
        }
        // Caso 2: Solo tiene hijo derecho
        else if(nodo->iz.EsVacio()) {
            TNodoABB *aux = nodo;
            nodo = aux->de.nodo;
            aux->de.nodo = NULL; // Para evitar que borre el subárbol
            delete aux;
            return true;
        }
        // Caso 3: Solo tiene hijo izquierdo
        else if(nodo->de.EsVacio()) {
            TNodoABB *aux = nodo;
            nodo = aux->iz.nodo;
            aux->iz.nodo = NULL; // Para evitar que borre el subárbol
            delete aux;
            return true;
        }
        // Caso 4: Tiene ambos hijos, sustituyo por el mayor de la izquierda
        else {
            // Busco el nodo más a la derecha del subárbol izquierdo
            TABBPoro *mayorIzquierda = &nodo->iz;
            while(!mayorIzquierda->nodo->de.EsVacio())
                mayorIzquierda = &mayorIzquierda->nodo->de;
            
            // Reemplazo el nodo actual por el mayor de la izquierda
            nodo->item = mayorIzquierda->nodo->item;
            
            // Elimino el mayor de la izquierda (ahora duplicado)
            return mayorIzquierda->Borrar(mayorIzquierda->nodo->item);
        }
    }
}

bool TABBPoro::Buscar(const TPoro & poro) const {
    if(EsVacio())
        return false;
    
    // Busco según el volumen
    if(poro.Volumen() < nodo->item.Volumen())
        return nodo->iz.Buscar(poro);
    else if(poro.Volumen() > nodo->item.Volumen())
        return nodo->de.Buscar(poro);
    else // Mismo volumen, verifico si es el mismo poro
        return nodo->item == poro;
}

TPoro TABBPoro::Raiz() const {
    if(EsVacio())
        return TPoro(); // Devuelvo un TPoro vacío
    
    return nodo->item;
}

int TABBPoro::Altura() const {
    if(EsVacio())
        return 0;
    
    // La altura es 1 + el máximo entre las alturas de los subárboles
    int alturaIzq = nodo->iz.Altura();
    int alturaDer = nodo->de.Altura();
    
    return 1 + (alturaIzq > alturaDer ? alturaIzq : alturaDer);
}

int TABBPoro::Nodos() const {
    if(EsVacio())
        return 0;
    
    // Número de nodos = 1 + nodos del subárbol izquierdo + nodos del subárbol derecho
    return 1 + nodo->iz.Nodos() + nodo->de.Nodos();
}

int TABBPoro::NodosHoja() const {
    if(EsVacio())
        return 0;
    
    // Si es un nodo hoja (no tiene hijos)
    if(nodo->iz.EsVacio() && nodo->de.EsVacio())
        return 1;
    
    // Si no es hoja, sumo las hojas de los subárboles
    return nodo->iz.NodosHoja() + nodo->de.NodosHoja();
}

// Métodos auxiliares para los recorridos

void TABBPoro::InordenAux(TVectorPoro & v, int & pos) const {
    if(!EsVacio()) {
        // Recorro subárbol izquierdo
        nodo->iz.InordenAux(v, pos);
        
        // Proceso nodo actual
        v[pos] = nodo->item;
        pos++;
        
        // Recorro subárbol derecho
        nodo->de.InordenAux(v, pos);
    }
}

void TABBPoro::PreordenAux(TVectorPoro & v, int & pos) const {
    if(!EsVacio()) {
        // Proceso nodo actual
        v[pos] = nodo->item;
        pos++;
        
        // Recorro subárbol izquierdo
        nodo->iz.PreordenAux(v, pos);
        
        // Recorro subárbol derecho
        nodo->de.PreordenAux(v, pos);
    }
}

void TABBPoro::PostordenAux(TVectorPoro & v, int & pos) const {
    if(!EsVacio()) {
        // Recorro subárbol izquierdo
        nodo->iz.PostordenAux(v, pos);
        
        // Recorro subárbol derecho
        nodo->de.PostordenAux(v, pos);
        
        // Proceso nodo actual
        v[pos] = nodo->item;
        pos++;
    }
}

// Implementación de los recorridos

TVectorPoro TABBPoro::Inorden() const {
    int numNodos = Nodos();
    TVectorPoro v(numNodos);
    
    if(numNodos > 0) {
        int pos = 1; // Posición en el vector (indexado en 1)
        InordenAux(v, pos);
    }
    
    return v;
}

TVectorPoro TABBPoro::Preorden() const {
    int numNodos = Nodos();
    TVectorPoro v(numNodos);
    
    if(numNodos > 0) {
        int pos = 1; // Posición en el vector (indexado en 1)
        PreordenAux(v, pos);
    }
    
    return v;
}

TVectorPoro TABBPoro::Postorden() const {
    int numNodos = Nodos();
    TVectorPoro v(numNodos);
    
    if(numNodos > 0) {
        int pos = 1; // Posición en el vector (indexado en 1)
        PostordenAux(v, pos);
    }
    
    return v;
}

TVectorPoro TABBPoro::Niveles() const {
    int numNodos = Nodos();
    TVectorPoro v(numNodos);
    
    if(numNodos > 0) {
        // Uso una cola para recorrer el árbol por niveles
        std::queue<const TABBPoro*> cola;
        int pos = 1; // Posición en el vector (indexado en 1)
        
        // Agrego la raíz a la cola
        cola.push(this);
        
        while(!cola.empty()) {
            // Obtengo el primer elemento de la cola
            const TABBPoro* arbol = cola.front();
            cola.pop();
            
            // Proceso el nodo actual
            v[pos] = arbol->nodo->item;
            pos++;
            
            // Agrego hijos a la cola
            if(!arbol->nodo->iz.EsVacio())
                cola.push(&arbol->nodo->iz);
            
            if(!arbol->nodo->de.EsVacio())
                cola.push(&arbol->nodo->de);
        }
    }
    
    return v;
}

TABBPoro TABBPoro::operator+(const TABBPoro & a) const {
    // Hago una copia del árbol izquierdo
    TABBPoro resultado(*this);
    
    // Inserto los elementos del árbol derecho en el resultado
    TVectorPoro vDerecho = a.Inorden();
    
    for(int i = 1; i <= vDerecho.Longitud(); i++) {
        resultado.Insertar(vDerecho[i]);
    }
    
    return resultado;
}

TABBPoro TABBPoro::operator-(const TABBPoro & a) const {
    TABBPoro resultado;
    TVectorPoro vIzquierdo = Inorden();
    
    // Para cada elemento del árbol izquierdo
    for(int i = 1; i <= vIzquierdo.Longitud(); i++) {
        // Si no está en el árbol derecho, lo inserto en el resultado
        if(!a.Buscar(vIzquierdo[i])) {
            resultado.Insertar(vIzquierdo[i]);
        }
    }
    
    return resultado;
}

// Sobrecarga del operador salida
ostream & operator<<(ostream & os, const TABBPoro & a) {
    // Muestro el recorrido por niveles
    os << a.Niveles();
    return os;
}