#include <iostream>
#include <conio.h>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

struct medicamentoComprado {
 string nombre;
 double precio;
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
void iniciarPrograma();
void verificarAperturaArchivo(ofstream &archivo);
void restringirEntradaOpcion(int & n );
void restringirEntradaNumero(int & n);
void restringirEntradaNumeroFloat(float &n);
void restringirEntradaString(string & s);
void agregarAdministrador(interfazAdmin & Admin);
void identificacionUsuario(interfazAdmin & Admin);
void imprimirMenu(int & opcion);
void imprimirListaMedicamentos();
void añadirMedicamento();
void modificarMedicamento();
void eliminarMedicamento();
void observarCompras();
void reiniciarProceso(string & respuestaIterativa);
int main() {
 cout << "Diesel Aponte - Trabajo Final " << endl;
 iniciarPrograma();
 system("pause");
 return 0;
}
void iniciarPrograma() {
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
 modificarMedicamento();
 break;
 case 4: //Eliminar medicamento
 eliminarMedicamento();
 break;
 case 5: //Ver ultimas compras de medicamentos
 observarCompras();
 break;
 case 6:
 cout << "Saliendo del programa ..." << endl;
 respuestaIterativa = "-1";
 break;
 default:
 cout << "Dato ingresado no valido ... " << endl;
 break;
 }
 if(respuestaIterativa != "-1") {
 reiniciarProceso(respuestaIterativa);
 //Restringir Respuesta a un si o no
 }
 }while(respuestaIterativa == "si" || respuestaIterativa == "s");
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
void restringirEntradaNumeroFloat(float & n) {
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
 cout << "2.-Agregar Medicamento." << endl;
 cout << "3.-Modificar caracteristicas del medicamento." << endl;
 cout << "4.-Eliminar medicamento." << endl;
 cout << "5.-Observar ultimas compras." << endl;
 cout << "6.-Salir del programa." << endl;
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
 int numOrden= 0;
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
 string elementosMedicamento; //Variable para almacenar cada aspecto del
 int elementosNumericosMedicamento;
 getline(ss, elementosMedicamento, '/'); //Leyendo cada linea hasta encontrar el

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
 archivoSalida << nuevoMedicamento.nombre << '/'<< nuevoMedicamento.cantidad <<'/'<< nuevoMedicamento.precio << '/'<< nuevoMedicamento.descripcion << '\n';
 archivoSalida.close();
 // Liberando memoria
 delete[] MedicamentosDisponibles;
}
void modificarMedicamento() {
 // Abriendo el archivo en lectura
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
 MedicamentosDisponibles = new medicamento[sizearr];
 // Creando la lista de medicamentos
 int numOrden = 0;
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
 // Imprimiendo los medicamentos disponibles
 for (int i = 0; i < sizearr; i++) {
 cout << "Medicamento (" << (i + 1) << ")" << endl;
 cout << "Nombre: " << MedicamentosDisponibles[i].nombre << endl;
 cout << "Cantidad: " << MedicamentosDisponibles[i].cantidad << endl;
 cout << "Precio: " << MedicamentosDisponibles[i].precio << endl;
 cout << "Descripcion: " << MedicamentosDisponibles[i].descripcion << endl;
 cout << "------------------------------------" << endl;
 }
 // Solicitar el número de orden del medicamento a modificar
 int numeroOrdenMed;
 cout << "Ingrese el numero de orden del medicamento que quiere modificar: " << endl;
 restringirEntradaNumero(numeroOrdenMed);
 // Verificar que el número de orden sea válido
 if (numeroOrdenMed < 1 || numeroOrdenMed > sizearr) {
 cout << "Número de orden no válido." << endl;
 delete[] MedicamentosDisponibles;
 return;
 }
 // Permitir al usuario modificar los campos del medicamento
 medicamento& med = MedicamentosDisponibles[numeroOrdenMed - 1];
 cout << "Modificando el medicamento: " << med.nombre << endl;
 cout << "Ingrese el nuevo nombre del medicamento (actual: " << med.nombre << "): " <<
endl;;
 restringirEntradaString(med.nombre);
 cout << "Ingrese la nueva cantidad del medicamento (actual: " << med.cantidad << "): "
<< endl;
 restringirEntradaNumero(med.cantidad);
 cout << "Ingrese el nuevo precio del medicamento (actual: s/" << med.precio << "): " <<
endl;
 restringirEntradaNumero(med.precio);
 cout << "Ingrese la nueva descripcion del medicamento: " << endl;
 restringirEntradaString(med.descripcion);
 // Guardar los cambios en el archivo
 ofstream archivoSalida("ListaMedicamentos.txt");
 if (!archivoSalida.is_open()) {
 cout << "No se pudo abrir el archivo para escritura." << endl;
 delete[] MedicamentosDisponibles;
 return;
 }
 for (int i = 0; i < sizearr; i++) {
 archivoSalida << MedicamentosDisponibles[i].nombre << '/'
 << MedicamentosDisponibles[i].cantidad << '/'
 << MedicamentosDisponibles[i].precio << '/'
 << MedicamentosDisponibles[i].descripcion << '\n';
 }
 archivoSalida.close();
 // Confirmar los cambios realizados
 cout << "Se realizaron cambios en el medicamento " << med.nombre << " (" <<
numeroOrdenMed << ") con exito." << endl;
 // Liberando memoria del arreglo dinámico
 delete[] MedicamentosDisponibles;
}
void eliminarMedicamento() {
 ifstream archivo("ListaMedicamentos.txt");
 if (!archivo.is_open()) {
 cout << "No se pudo abrir el archivo." << endl;
 return;
 }
 // Leer el archivo y contar el número de medicamentos
 int sizearr = 0;
 string linea;
 while (getline(archivo, linea)) {
 sizearr++;
 }
 archivo.clear();
 archivo.seekg(0, ios::beg);
 // Almacenar los medicamentos en arreglos dinámicos
 medicamento* MedicamentosDisponibles = new medicamento[sizearr];
 int numOrden = 0;
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
 // Imprimir los medicamentos disponibles
 for (int i = 0; i < sizearr; i++) {
 cout << "Medicamento (" << (i + 1) << ")" << endl;
 cout << "Nombre: " << MedicamentosDisponibles[i].nombre << endl;
 cout << "Cantidad: " << MedicamentosDisponibles[i].cantidad << endl;
 cout << "Precio: " << MedicamentosDisponibles[i].precio << endl;
 cout << "Descripcion: " << MedicamentosDisponibles[i].descripcion << endl;
 cout << "------------------------------------" << endl;
 }
 // Solicitar al usuario el número de orden del medicamento a eliminar
 int numeroOrdenMed;
 cout << "Ingrese el numero de orden del medicamento que quiere eliminar: " << endl;
 restringirEntradaNumero(numeroOrdenMed);
 // Verificar que el número de orden sea válido
 if (numeroOrdenMed < 1 || numeroOrdenMed > sizearr) {
 cout << "Numero de orden no valido." << endl;
 delete[] MedicamentosDisponibles;
 return;
 }
 string nombreMed = MedicamentosDisponibles[numeroOrdenMed - 1].nombre;
 // Reescribir el archivo sin el medicamento eliminado
 ofstream archivoSalida("ListaMedicamentos.txt");
 if (!archivoSalida.is_open()) {
 cout << "No se pudo abrir el archivo para escritura." << endl;
 delete[] MedicamentosDisponibles;
 return;
 }
 for (int i = 0; i < sizearr; i++) {
 if (i != numeroOrdenMed - 1) {
 archivoSalida << MedicamentosDisponibles[i].nombre << '/'
 << MedicamentosDisponibles[i].cantidad << '/'
 << MedicamentosDisponibles[i].precio << '/'
 << MedicamentosDisponibles[i].descripcion << '\n';
 }
 }
 archivoSalida.close();
 delete[] MedicamentosDisponibles;
 // Mensaje de confirmación
 cout << "El medicamento " << nombreMed << " fue eliminado satisfactoriamente." <<
endl;
}
void observarCompras() {
 ifstream archivo("ListaMedicamentos.txt");
 if (!archivo.is_open()) {
 cout << "No se pudo abrir el archivo." << endl;
 return;
 }
 // Leer el archivo y contar el número de medicamentos
 int sizearr = 0;
 string linea;
 while (getline(archivo, linea)) {
 sizearr++;
 }
 archivo.clear();
 archivo.seekg(0, ios::beg);
 // Almacenar los medicamentos en arreglos dinámicos
 medicamento* MedicamentosDisponibles = new medicamento[sizearr];
 int numOrden = 0;
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
 // Imprimir los medicamentos disponibles
 for (int i = 0; i < sizearr; i++) {
 cout << "Medicamento (" << (i + 1) << ")" << endl;
 cout << "Nombre: " << MedicamentosDisponibles[i].nombre << endl;
 cout << "Cantidad: " << MedicamentosDisponibles[i].cantidad << endl;
 cout << "Precio: " << MedicamentosDisponibles[i].precio << endl;
 cout << "Descripcion: " << MedicamentosDisponibles[i].descripcion << endl;
 cout << "------------------------------------" << endl;
 }
 // Solicitar el número de orden o nombre del medicamento
 cout << "Ingrese el numero de orden o el nombre del medicamento que quiere comprar: "
<< endl;
 string entrada;
 restringirEntradaString(entrada);
 int numeroOrdenMed = -1;
 string nombreMedicamento;
 bool medicamentoEncontrado = false;
 for (int i = 0; i < sizearr; i++) {
 if (to_string(i + 1) == entrada || MedicamentosDisponibles[i].nombre == entrada) {
 numeroOrdenMed = i;
 nombreMedicamento = MedicamentosDisponibles[i].nombre;
 medicamentoEncontrado = true;
 break;
 }
 }
 if (!medicamentoEncontrado) {
 cout << "Medicamento no encontrado ..." << endl;
 delete[] MedicamentosDisponibles;
 observarCompras(); // Volver a preguntar
 return;
 }
 // Solicitar la cantidad a comprar
 cout << "Que cantidad desea comprar? (-1 / Cancelar compra) " << endl;
 int cantidadComprar;
 restringirEntradaNumero(cantidadComprar);
 if (cantidadComprar == -1) {
 cout << "Compra cancelada ..." << endl;
 delete[] MedicamentosDisponibles;
 return;
 }
 if (cantidadComprar > MedicamentosDisponibles[numeroOrdenMed].cantidad) {
 cout << "No hay suficiente cantidad disponible. Solo hay " <<
MedicamentosDisponibles[numeroOrdenMed].cantidad << " disponibles." << endl;
 delete[] MedicamentosDisponibles;
 return;
 }
 // Mostrar el monto de pago
 int montoPago = cantidadComprar * MedicamentosDisponibles[numeroOrdenMed].precio;
 cout << "Cantidad a pagar: " << montoPago << endl;
 cout << "Aceptar (1) Cancelar (-1)" << endl;
 int decision;
 restringirEntradaNumero(decision);
 if (decision == -1) {
 cout << "Compra cancelada ..." << endl;
 delete[] MedicamentosDisponibles;
 return;
 }
 // Realizar el pago
 cout << "Realizando pagos ..." << endl;
 this_thread::sleep_for(chrono::seconds(4));
 cout << "Compra realizada con exito!" << endl;
 // Actualizar la cantidad de medicamento en el archivo
 MedicamentosDisponibles[numeroOrdenMed].cantidad -= cantidadComprar;
 ofstream archivoSalida("ListaMedicamentos.txt");
 if (!archivoSalida.is_open()) {
 cout << "No se pudo abrir el archivo para escritura." << endl;
 delete[] MedicamentosDisponibles;
 return;
 }
 for (int i = 0; i < sizearr; i++) {
 archivoSalida << MedicamentosDisponibles[i].nombre << '/'
 << MedicamentosDisponibles[i].cantidad << '/'
 << MedicamentosDisponibles[i].precio << '/'
 << MedicamentosDisponibles[i].descripcion << '\n';
 }
 archivoSalida.close();
 delete[] MedicamentosDisponibles;
}
void reiniciarProceso(string & respuestaIterativa) {
 cout << "Quiere realizar alguna otra diligencia? (Si/No)" << endl;
 restringirEntradaString(respuestaIterativa);
 // Convertir a minúsculas para asegurar la comparación
 for (char &c : respuestaIterativa) {
 c = tolower(c);
 }
 // Validar la respuesta del usuario
 while (respuestaIterativa != "si" && respuestaIterativa != "s" && respuestaIterativa != "no"
&& respuestaIterativa != "n") {
 cout << "Respuesta no válida. Ingrese una de las opciones (Si/No): " << endl;
 restringirEntradaString(respuestaIterativa);
 // Convertir a minúsculas de nuevo después de obtener nueva entrada
 for (char &c : respuestaIterativa) {
 c = tolower(c);
 }
 }
}