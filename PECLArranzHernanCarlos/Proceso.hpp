#ifndef PROCESO_HPP
#define PROCESO_HPP

#include <string>
#include <iostream>

using namespace std;

class Proceso {
private:
    int pid;
    string usuario;
    bool estado; 
    int prioridad;
    bool tiempoReal; 
public:
    Proceso(int pid, string usuario, bool tiempoReal);
    ~Proceso();
    int getPID() const;
    string getUsuario() const;
    bool mostrar_proceso() const;
    int getPrioridad() const;
    bool esTiempoReal() const;
    void setEjecucion(bool estado);
    void setPrioridad(int nuevaPrioridad);
    void mostrar() const;
};
#endif // PROCESO_HPP

