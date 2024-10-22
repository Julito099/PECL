#include "Gestor.hpp"

void Gestor::genera12Procesos() {
    static int pidCounter = 300;
    static int usuarioCounter = 0;

    for (int i = 0; i < 12; i++) {
        int pid = pidCounter++;
        std::string usuario = "usuario" + std::to_string(usuarioCounter++);
        bool tiempoReal = rand() % 2;
        Proceso* proceso = new Proceso(pid, usuario, tiempoReal);
        pila.insertar(proceso);
    }
}

void Gestor::muestraProcesos() const {
    pnodoPila actual = pila.ultimo;
    while (actual != nullptr) {
        Proceso* proceso = actual->proceso;
        std::cout << "El proceso cuyo PID es " << proceso->getPID() 
                  << " es de tipo " << (proceso->esTiempoReal() ? "en tiempo real" : "normal") << std::endl;
        actual = actual->siguiente;
    }
}


void Gestor::borraProcesosPila(){
	while (!pila.estaVacia()) {
        pila.extraer();
    }
}

while (!pila.estaVacia()) {
	Proceso* proceso = pila.extraer();
	proceso->setEjecucion(false);
	if (proceso->esTiempoReal()) {
		proceso->setPrioridad(rand() % 100);
	} else {
		proceso->setPrioridad(120 + (rand() % 39) - 19);
	}
	int indiceCola = 0;
	if (proceso->esTiempoReal()) {
		indiceCola = (colas[2].getLongitud() <= colas[3].getLongitud()) ? 2 : 3;
	} else {
		indiceCola = (colas[0].getLongitud() <= colas[1].getLongitud()) ? 0 : 1;
	}
	colas[indiceCola].insertar(proceso);
}


void Gestor::muestraProcesosGPUs0y1() const{
	std::cout << "GPU 0:" << std::endl;
	colas[0].mostrar();
	std::cout << "GPU 1:" << std::endl;
	colas[1].mostrar();
}

void Gestor::muestraProcesosGPUs2y3() const{
	std::cout << "GPU 2:" << std::endl;
	colas[2].mostrar();
	std::cout << "GPU 3:" << std::endl;
	colas[3].mostrar();
}
	std::cout << "GPU 2:" << std::endl;
	colas[2].mostrar();
	std::cout << "GPU 3:" << std::endl;
	colas[3].mostrar();
}
void Gestor::borraProcesosColas() {
    for (int i = 0; i < 4; i++) {
        while (!colas[i].estaVacia()) {
            colas[i].eliminar();
        }
    }
}

void Gestor::moverProcesosAListas() {
    for (int i = 0; i < 4; i++) {
        while (!colas[i].estaVacia()) {
            Proceso* proceso = colas[i].desencolar();
            proceso->setEjecucion(true);
            if (i < 2) {
                listaNormal.insertar(proceso);
            } else {
                listaTiempoReal.insertar(proceso);
            }
        }
    }
}

void Gestor::muestraProcesosNormal() const {
    std::cout << "Lista Normal:" << std::endl;
    listaNormal.mostrar();
}

void Gestor::muestraProcesosTiempoReal() const {
    std::cout << "Lista Tiempo Real:" << std::endl;
    listaTiempoReal.mostrar();
}

void Gestor::buscarProcesos() const {
    Proceso* menorPrioridadNormal = nullptr;
    Proceso* mayorPrioridadTiempoReal = nullptr;

    // Buscar proceso normal de menor prioridad
    NodoLista* actual = listaNormal.cabeza;
    while (actual != nullptr) {
        if (menorPrioridadNormal == nullptr || actual->proceso->getPrioridad() < menorPrioridadNormal->getPrioridad()) {
            menorPrioridadNormal = actual->proceso;
        }
        actual = actual->siguiente;
    }

    // Buscar proceso en tiempo real de mayor prioridad
    actual = listaTiempoReal.cabeza;
    while (actual != nullptr) {
        if (mayorPrioridadTiempoReal == nullptr || actual->proceso->getPrioridad() > mayorPrioridadTiempoReal->getPrioridad()) {
            mayorPrioridadTiempoReal = actual->proceso;
        }
        actual = actual->siguiente;
    }

    std::cout << "Proceso Normal de menor prioridad:" << std::endl;
    if (menorPrioridadNormal != nullptr) {
        menorPrioridadNormal->mostrar();
    } else {
        std::cout << "No hay procesos normales en la lista." << std::endl;
    }

    std::cout << "Proceso en Tiempo Real de mayor prioridad:" << std::endl;
    if (mayorPrioridadTiempoReal != nullptr) {
        mayorPrioridadTiempoReal->mostrar();
    } else {
        std::cout << "No hay procesos en tiempo real en la lista." << std::endl;
    }
}

void Gestor::buscarProcesoPorNombreUsuario() const {
    std::string nombreUsuario;
    std::cout << "Ingrese el nombre de usuario: ";
    std::cin >> nombreUsuario;

    bool encontrado = false;

    // Buscar en la lista normal
    NodoLista* actual = listaNormal.cabeza;
    while (actual != nullptr) {
        if (actual->proceso->getUsuario() == nombreUsuario) {
            actual->proceso->mostrar();
            encontrado = true;
        }
        actual = actual->siguiente;
    }

    // Buscar en la lista de tiempo real
    actual = listaTiempoReal.cabeza;
    while (actual != nullptr) {
        if (actual->proceso->getUsuario() == nombreUsuario) {
            actual->proceso->mostrar();
            encontrado = true;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        std::cout << "No se encontraron procesos para el usuario: " << nombreUsuario << std::endl;
    }
}


void Gestor::eliminarProcesoPorPID() {
    int pid;
    std::cout << "Ingrese el PID del proceso a eliminar: ";
    std::cin >> pid;

    Proceso* proceso = listaNormal.buscarPorPID(pid);
    if (proceso == nullptr) {
        proceso = listaTiempoReal.buscarPorPID(pid);
    }

    if (proceso != nullptr) {
		std::cout << "PID\tUSUARIO\tESTADO\tPRIORIDAD\tTIPO" << std::endl;
        std::cout << proceso->getPID() << "\t" 
                  << proceso->getUsuario() << "\t" 
                  << (proceso->mostrar_proceso() ? "Ejecución" : "Parado") << "\t" 
                  << proceso->getPrioridad() << "\t\t" 
                  << (proceso->esTiempoReal() ? "Tiempo Real" : "Normal") << std::endl;
        std::cout << "El proceso cuyo PID es " << proceso->getPID()
                  << " es de tipo " << (proceso->esTiempoReal() ? "en tiempo real" : "normal")
                  << ", su estado es " << (proceso->mostrar_proceso() ? "ejecución" : "parado")
                  << " y su prioridad es: " << proceso->getPrioridad() << std::endl;

        listaNormal.eliminarPorPID(pid);
        listaTiempoReal.eliminarPorPID(pid);
    } else {
        std::cout << "No se encontró un proceso con el PID " << pid << std::endl;
    }
}

void Gestor::cambiarPrioridadProcesoPorPID() {
    int pid, nuevaPrioridad;
    std::cout << "Ingrese el PID del proceso al que desea cambiar la prioridad: ";
    std::cin >> pid;

    Proceso* proceso = listaNormal.buscarPorPID(pid);
    if (proceso == nullptr) {
        proceso = listaTiempoReal.buscarPorPID(pid);
    }

    if (proceso != nullptr) {
        // Mostrar datos del proceso antes de cambiar la prioridad
        std::cout << "PID\tUSUARIO\tESTADO\tPRIORIDAD\tTIPO" << std::endl;
        std::cout << proceso->getPID() << "\t" 
                  << proceso->getUsuario() << "\t" 
                  << (proceso->mostrar_proceso() ? "Ejecución" : "Parado") << "\t" 
                  << proceso->getPrioridad() << "\t\t" 
                  << (proceso->esTiempoReal() ? "Tiempo Real" : "Normal") << std::endl;

        std::cout << "Ingrese la nueva prioridad para el proceso: ";
        std::cin >> nuevaPrioridad;

        // Cambiar la prioridad del proceso
        proceso->setPrioridad(nuevaPrioridad);

        // Mostrar datos del proceso después de cambiar la prioridad
        std::cout << "PID\tUSUARIO\tESTADO\tPRIORIDAD\tTIPO" << std::endl;
        std::cout << proceso->getPID() << "\t" 
                  << proceso->getUsuario() << "\t" 
                  << (proceso->mostrar_proceso() ? "Ejecución" : "Parado") << "\t" 
                  << proceso->getPrioridad() << "\t\t" 
                  << (proceso->esTiempoReal() ? "Tiempo Real" : "Normal") << std::endl;
    } else {
        std::cout << "No se encontró un proceso con el PID " << pid << std::endl;
    }
}


void Gestor::reiniciar() {
    borraProcesosPila();
    borraProcesosColas();
    listaNormal.~Lista();
    listaTiempoReal.~Lista();
}

// Métodos adicionales para adaptarse al main
int Gestor::ProcesosEnPila() const {
    return pila.getLongitud();
}

int Gestor::ProcesosEnGPU0() const {
    return colas[0].getLongitud();
}

int Gestor::ProcesosEnGPU1() const {
    return colas[1].getLongitud();
}

int Gestor::ProcesosEnGPU2() const {
    return colas[2].getLongitud();
}

int Gestor::ProcesosEnGPU3() const {
    return colas[3].getLongitud();
}

int Gestor::ProcesosEnListaNormal() const {
    return listaNormal.getLongitud();
}

int Gestor::ProcesosEnListaTiempoReal() const {
    return listaTiempoReal.getLongitud();
}

int Gestor::ProcesosEnArbol() const {
    // Implementar si se añade la funcionalidad del árbol
    return 0;
}

