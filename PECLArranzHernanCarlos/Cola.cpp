#include "Cola.hpp"

Cola::Cola()
{
	primero = NULL;
	ultimo = NULL;
	longitud = 0;
}

void Cola::insertar(Proceso* p)
{
	pnodoCola nuevo;
	nuevo = new NodoCola(p, ultimo);
	if(ultimo){
		ultimo->siguiente = nuevo;
	}
	ultimo = nuevo;
	
	if(!primero){
		primero = nuevo;
	}
	longitud++;
}

void Cola::mostrar() const
{
	pnodoCola aux = primero;
	cout << "\tEl contenido de la cola es: ";
	while(aux) {
		cout <<"-> " << aux->proceso;
		aux = aux->siguiente;
	}
	cout << endl;
}

Proceso* Cola::eliminar()
{
	if (!primero) return nullptr;
    pnodoCola nodo = primero;
    Proceso* p = nodo->proceso;
    primero = nodo->siguiente;
    if (!primero) {
        ultimo = nullptr;
    }
    delete nodo;
    longitud--;
    return p;
}

Proceso* Cola ::verPrimero() const{
	return primero->proceso;
}

bool Cola::estaVacia() const {
    return primero == nullptr;
}

int Cola::getLongitud() const {
    return longitud;
}

Cola::~Cola()
{
	while(primero)
		eliminar();
}
