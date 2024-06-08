#include <iostream>
#include <conio.h>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>
using namespace std;
struct medicamentoComprado {
    string nombre;
    int precio;
    int cantidad;
    string estado;
};

struct interfazAdmin {
    string nombre;
    string constraseña;
};
struct medicamento {
    string nombre;
    int precio;
    int cantidad;
    string descripcion;
    string fechaV;
};

void verificarAperturaArchivo(ofstream &archivo);
void restringirEntradaOpcion(int & n );
void restringirEntradaNumero(int & n);
void restringirEntradaString(string & s);
void agregarAdministrador(interfazAdmin & Admin);
void identificacionUsuario(interfazAdmin & Admin);
void imprimirMenu(int &  opcion);


void imprimirListaMedicamentos();
void añadirMedicamento();
void modificarMedicamento();
void eliminarMedicamento();
void observarCompras();
void observarEstadoCompas();


void reiniciarProceso(string & respuestaIterativa);
void reiniciarProcesoMin(string & respuestaIterativa);
int main() {
    cout << "Diesel Aponte - Trabajo Final " << endl;
    //Inicialización de variables:
    string respuestaIterativa;
    interfazAdmin Administrador;
    int opcion;
    ofstream archivoA ("ListaMedicamentos.txt",ios::app);
    ifstream archivoL ("ListaMedicamentos.txt",ios::app);
    //Procesos:
    verificarAperturaArchivo(archivoA); //Verificación de la información del archivo
    agregarAdministrador(Administrador); //Agregando un usaurio
    identificacionUsuario(Administrador); //Identificación del usuario
    do {
        imprimirMenu(opcion);
        switch (opcion) {
            case 1: //Imprimir lista de medicamentos
                imprimirListaMedicamentos();
                break;
            case 2: //Añadir medicamento
                añadirMedicamento();
                break;
            case 3: //Modificar medicamento

                break;
            case 4: //Eliminar medicamento

                break;
            case 5: //Ver ultimas compras de medicamentos

                break;
            case 6: //Observar estado de envio de los medicamentos vendidos

                break;
            default:
                cout << "Dato ingresado no valido ... " << endl;
            break;
        }
        reiniciarProceso(respuestaIterativa);
        reiniciarProcesoMin(respuestaIterativa);
        //Restringir Respuesta a un si o no
    }while(respuestaIterativa == "si" || respuestaIterativa == "s");

    cout << "Pulse cualquier tecla para continuar: " << endl;
    getch();
    return 0;
}
void restringirEntradaOpcion(int & n) {
    cin >> n;
    while(cin.fail() || n > 6) {
        cout << "Dato ingresado no valido ... " << endl;
        cout << "Ingrese un numero: " << endl;
        cin.clear();
        cin.ignore(10000,'\n');
        cin >> n;
    }
}
void restringirEntradaNumero(int & n) {
    cin >> n;
    while(cin.fail()) {
        cout << "Dato ingresado no valido ... " << endl;
        cout << "Ingrese un numero: " << endl;
        cin.clear();
        cin.ignore(10000,'\n');
        cin >> n;
    }
}

void restringirEntradaString(string & s) {
    cin >> s;
    while(cin.fail()) {
        cout << "Dato ingresado no valido ... " << endl;
        cout << "Ingrese una palabra: " << endl;
        cin.clear();
        cin.ignore(10000,'\n');
        cin >> s;
    }
}

void verificarAperturaArchivo(ofstream &archivo) {
    if(!archivo.is_open()) {
        cout << "El archivo no se abrio correctamente" << endl;
    } else {
        cout << "El archivo se abrio correctamente " << endl;
        cout << "Informacion procesada correctamente ... " << endl;
    }
    cout << endl;
}

void agregarAdministrador(interfazAdmin & Admin) {
    cout << "-----------------------------------------" << endl;
    cout << "Creando interfaz administrador ..." << endl;
    cout << "Ingrese el nombre de usuario: " << endl;
    restringirEntradaString(Admin.nombre);
    cout << "Ingrese una nueva contrasena para su cuenta: " << endl;
    restringirEntradaString(Admin.constraseña);
    cout << "Administrador agregado satisfactoriamente ..." << endl;
    cout << "-----------------------------------------" << endl;
    cout << endl;
}

void identificacionUsuario(interfazAdmin & Admin) {
    string respuestaName;
    string respuestaPassword;
    cout << "-----------------------------------------" << endl;
    cout << "Ingrese su usuario de administrador: " << endl;
    restringirEntradaString(respuestaName);
    while(respuestaName != Admin.nombre) {
        cout << "El nombre ingresado no pertenece a ningun usuario ..." << endl;
        cout << "Ingrese otra vez el nombre de usuario: " << endl;
        restringirEntradaString(respuestaName);
    }
    cout << "Ingrese la contrasena: " << endl;
    restringirEntradaString(respuestaPassword);
    while(respuestaPassword != Admin.constraseña) {
        cout << "La contraseña ingresada no es correcta ... " << endl;
        cout << "Ingrese la contrasena: " << endl;
        restringirEntradaString(respuestaPassword);
    }
    cout << "-----------------------------------------" << endl;
    cout << "ACCEDIENDO PERFIL ..." << endl;
    cout << endl;
}

void imprimirMenu(int & opcion) {
    cout << "-----------------Gestion de Medicamentos-----------------" << endl;
    cout << "1.-Ver Lista medicamentos " << endl;
    cout << "2.-Añadir Medicamento." << endl;
    cout << "3.-Modificar caracteristicas del medicamento." << endl;
    cout << "4.-Eliminar medicamento." << endl;
    cout << "5.-Observar ultimas compras." << endl;
    cout << "6.-Observar estado de medicamentos. " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << endl;
    cout << "Ingrese una opcion: " << endl;
    restringirEntradaNumero(opcion);
}


void imprimirListaMedicamentos() {
    //Abriendo el archivo en lectura
    ifstream archivo("ListaMedicamentos.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    // Contar el número de líneas para determinar el tamaño del arreglo
    int size = 0;
    string linea;
    while (getline(archivo, linea)) {
        size++;
    }

    // Reposicionando la lectura
    archivo.clear();
    archivo.seekg(0, ios::beg);

    // Creando arreglo dinamico
    medicamento* MedicamentosDisponibles;
    MedicamentosDisponibles = new medicamento [size];

    // Creando la lista de medicamentos
    int  numOrden= 0;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string elementosMedicamento;
        int elementosNumericosMedicamento;
        getline(ss, elementosMedicamento, '/');
        MedicamentosDisponibles[numOrden].nombre = elementosMedicamento;

        getline(ss, elementosMedicamento, '/');
        elementosNumericosMedicamento = stoi(elementosMedicamento);
        MedicamentosDisponibles[numOrden].cantidad = elementosNumericosMedicamento;

        getline(ss, elementosMedicamento, '/');
        elementosNumericosMedicamento = stoi(elementosMedicamento);
        MedicamentosDisponibles[numOrden].precio = elementosNumericosMedicamento;

        getline(ss, elementosMedicamento, '/');
        MedicamentosDisponibles[numOrden].descripcion = elementosMedicamento;

        numOrden++;
    }
    archivo.close();

    // Imprimiendo los datos del arreglo
    for (int i = 0; i < size; i++) {
        cout << "Medicamento (" << (i + 1) << ")"<< endl;
        cout << "Nombre: " << MedicamentosDisponibles[i].nombre << endl;
        cout << "Cantidad: " << MedicamentosDisponibles[i].cantidad << endl;
        cout << "Precio: " << MedicamentosDisponibles[i].precio << endl;
        cout << "Descripcion: " << MedicamentosDisponibles[i].descripcion << endl;
        cout << "------------------------------------" << endl;
    }

    // Liberando memoria del arr[]
    delete[] MedicamentosDisponibles;
}

void añadirMedicamento() {
    // Leer medicamentos existentes
    ifstream archivo("ListaMedicamentos.txt");
    if (!archivo.is_open()) { //Falla a la hora de abrir el archivo
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    // Contar el número de líneas para determinar el tamaño del arreglo
    int size = 0;
    string linea;
    while (getline(archivo, linea)) {
        size++;
    }

    // Reposicionando la lectura del archivo al principio del txt
    archivo.clear();
    archivo.seekg(0, ios::beg);

    // Creando arreglo dinamico
    medicamento* MedicamentosDisponibles = new medicamento[size];

    // Inicializando el numero de Orden del medicamento
    int numOrden = 0;
    while (getline(archivo, linea)) { //Mientras hayan lineas que obtener en el archivo
        stringstream ss(linea); //Inicialización de un stringstream en la linea act
        string elementosMedicamento; //Variable para almacenar cada aspecto del medicamento
        int elementosNumericosMedicamento;
        getline(ss, elementosMedicamento, '/'); //Leyendo cada linea hasta encontrar el delimitador
        MedicamentosDisponibles[numOrden].nombre = elementosMedicamento;

        getline(ss, elementosMedicamento, '/');
        elementosNumericosMedicamento = stoi(elementosMedicamento);
        MedicamentosDisponibles[numOrden].cantidad = elementosNumericosMedicamento;

        getline(ss, elementosMedicamento, '/');
        elementosNumericosMedicamento = stoi(elementosMedicamento);
        MedicamentosDisponibles[numOrden].precio = elementosNumericosMedicamento;

        getline(ss, elementosMedicamento, '/');
        MedicamentosDisponibles[numOrden].descripcion = elementosMedicamento;

        numOrden++;
    }
    archivo.close();

    // Llenando los campos del medicamento
    medicamento nuevoMedicamento;
    cout << "Ingrese el nombre del medicamento: " << endl;
    restringirEntradaString(nuevoMedicamento.nombre);
    cout << "Ingrese la cantidad del medicamento: " << endl;
    restringirEntradaNumero(nuevoMedicamento.cantidad);
    cout << "Ingrese el precio del medicamento: " << endl;
    restringirEntradaNumero(nuevoMedicamento.precio);
    cout << "Ingrese una descripcion del medicamento: " << endl;
    restringirEntradaString(nuevoMedicamento.descripcion);
    //Escribiendo en el archivo
    ofstream archivoSalida("ListaMedicamentos.txt", ios::app);
    if (!archivoSalida.is_open()) {
        cout << "No se pudo abrir el archivo para escritura." << endl;
        return;
    }

    // Escribir el nuevo medicamento en el archivo
    archivoSalida << nuevoMedicamento.nombre << '/'<< nuevoMedicamento.cantidad << '/'<< nuevoMedicamento.precio << '/'<< nuevoMedicamento.descripcion << '\n';

    archivoSalida.close();

    // Liberando memoria
    delete[] MedicamentosDisponibles;
}
void modificarMedicamento() {
    //Abriendo el archivo en lectura
    ifstream archivo("ListaMedicamentos.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    // Contar el número de líneas para determinar el tamaño del arreglo
    int sizearr = 0;
    string linea;
    while (getline(archivo, linea)) {
        sizearr++;
    }

    // Reposicionando la lectura
    archivo.clear();
    archivo.seekg(0, ios::beg);

    // Creando arreglo dinamico
    medicamento* MedicamentosDisponibles;
    MedicamentosDisponibles = new medicamento [sizearr];

    // Creando la lista de medicamentos
    int  numOrden= 0;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string elementosMedicamento;
        int elementosNumericosMedicamento;
        getline(ss, elementosMedicamento, '/');
        MedicamentosDisponibles[numOrden].nombre = elementosMedicamento;

        getline(ss, elementosMedicamento, '/');
        elementosNumericosMedicamento = stoi(elementosMedicamento);
        MedicamentosDisponibles[numOrden].cantidad = elementosNumericosMedicamento;

        getline(ss, elementosMedicamento, '/');
        elementosNumericosMedicamento = stoi(elementosMedicamento);
        MedicamentosDisponibles[numOrden].precio = elementosNumericosMedicamento;

        getline(ss, elementosMedicamento, '/');
        MedicamentosDisponibles[numOrden].descripcion = elementosMedicamento;

        numOrden++;
    }
    archivo.close();
    int i = 0;
    string nombreMedicamentoBuscado;
    cout << "Ingrese el nombre del medicamento que quiere modificar: " << endl;
    restringirEntradaString(nombreMedicamentoBuscado);
    for(i; i < sizearr; i++) {
        if (nombreMedicamentoBuscado == MedicamentosDisponibles[i].nombre) {
            cout << "Medicamento Encontrado ..." << endl;
            cout << "Medicamento (" << (i + 1) << ")"<< endl;
            cout << "Nombre: " << MedicamentosDisponibles[i].nombre << endl;
            cout << "Cantidad: " << MedicamentosDisponibles[i].cantidad << endl;
            cout << "Precio: " << MedicamentosDisponibles[i].precio << endl;
            cout << "Descripcion: " << MedicamentosDisponibles[i].descripcion << endl;
            cout << "------------------------------------" << endl;
            cout << endl;
            cout << "Que caracteristica del medicamento quier modificar: " << endl;
            break;
        }
    }
    if(nombreMedicamentoBuscado != MedicamentosDisponibles[i].nombre) {
        cout << "Medicamento no Encontrado..." << endl;
        modificarMedicamento();
    }
}
void eliminarMedicamento();


void observarCompras();
void observarEstadoCompas();

void reiniciarProceso(string &respuestaIterativa) {
    cout << "Quiere realizar alguna otra diligencia? (Si/No)" << endl;
    restringirEntradaString(respuestaIterativa);
}

void reiniciarProcesoMin(string & respuestaIterativa) {
    for (int i = 0; i < respuestaIterativa.length(); i++) {
        // Cambiar cada letra por su representación
        // minúscula
        respuestaIterativa[i] = tolower(respuestaIterativa[i]);
    }
}
