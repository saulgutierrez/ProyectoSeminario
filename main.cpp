#include <iostream>
#include <string.h>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <cstring>

#define delimitador ';'
#define finRegistro '|'

using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix)||defined(__unix__)||defined(__unix)||defined(__APPLE__)||defined(__MACH__)
#define CLEAR "clear"
#else
#error "No es posible limpiar pantalla"
#endif

class Indice;

typedef struct {
    int minuto;
    int hora;
}Hora;

typedef struct {
    int dia;
    int mes;
    int anio;
} Fecha;

typedef struct {
    int identificador;
    char remitente[20];
    char destinatario[30];
    char copiaCarbon[15];
    char copiaCarbonCiega[30];
    char asunto[50];
    char contenido[500];
    Fecha fechaCreacion;
    Hora horaCreacion;
} Correo;

void pausa();
int elegirOpcion();
void ingresaCorreo();
void mostrarCorreo();
void eliminarCorreo();
void modificarCorreo();
void imprimirCorreo();
void buscarCorreo();
void exportaraCsv();
void mostrarArchivoSeguridad();
void modificarArchivoSeguridad();
void eliminarArchivoSeguridad();
void consiguehorayfecha();
void imprimirInformacion();
void exportaraDat();
void mostrarArchivoDat();
void imprimirArchivoDat();
void busquedaEnMemoria();
void shellSort(Correo *);
void busquedaPorIndices(string &, int &);
Indice busquedaPorIndices(int&);
void buscarIndice();
void cifradoCesar();
void descifrado();
void leerCifrado();
int pjwHashing(char *clave);

Correo Correo1;
Fecha fecha;
Hora hora;
Correo guardaRegistros[1000];
Correo registrosCifrados;
static int tamanio = 0;

int main() {
	char *clave;
    bool continuarPrograma = true;
    do {
        switch(elegirOpcion()) {
			case 1:
				system(CLEAR);
				ingresaCorreo();
				pausa();
				break;
			case 2:
				system(CLEAR);
				mostrarCorreo();
				pausa();
				break;
			case 3:
				system(CLEAR);
				buscarCorreo();
				pausa();
				break;
			case 4:
				system(CLEAR);
				eliminarCorreo();
				pausa();
				break;
			case 5:
				system(CLEAR);
				modificarCorreo();
				pausa();
				break;
			case 6:
				system(CLEAR);
				exportaraCsv();
				pausa();
				break;
			case 7:
				system(CLEAR);
				mostrarArchivoSeguridad();
				pausa();
				break;
			case 8:
				system(CLEAR);
				modificarArchivoSeguridad();
				pausa();
				break;
			case 9:
				system(CLEAR);
				eliminarArchivoSeguridad();
				pausa();
				break;
			case 10:
				system(CLEAR);
				exportaraDat();
				pausa();
				break;
			case 11:
				system(CLEAR);
				mostrarArchivoDat();
				pausa();
				break;
			case 12:
				system(CLEAR);
				busquedaEnMemoria();
				pausa();
				break;
			case 13:
				system(CLEAR);
				buscarIndice();
				pausa();
				break;
			case 14:
				system(CLEAR);
				cifradoCesar();
				pausa();
				break;
			case 15:
				system(CLEAR);
				descifrado();
				pausa();
				break;
			case 16:
				system(CLEAR);
				leerCifrado();
				pausa();
				break;
			case 17:
				system(CLEAR);
				pjwHashing(clave);
				pausa();
				break;
			case 18:
				continuarPrograma = false;
				break;

			default:
				cout << endl;
				cout << "Opcion Invalida..." << endl;
				cout << "Intentelo de nuevo.";
				cin.get();
				cin.get();
        }
    } while(continuarPrograma);
    return 0;
}

void pausa() {
    cout << "Presiona una tecla para continuar..." << endl;
    cin.ignore();
    getchar();
}

int elegirOpcion() {
    int opcion;
    system(CLEAR);
    cout << "\t\t\tMENU PRINCIPAL" << endl;
    cout << endl;
    cout << "1. Capturar" << endl;
    cout << "2. Mostrar" << endl;
    cout << "3. Buscar" << endl;
    cout << "4. Eliminar" << endl;
    cout << "5. Modificar" << endl;
    cout << "6. Exportar a csv (Copia de seguridad)" << endl;
    cout << "7. Mostrar archivo csv (Copia de seguridad)" << endl;
    cout << "8. Modificar archivo csv (Copia de seguridad)" << endl;
    cout << "9. Eliminar archivo csv (Copia de seguridad)" << endl;
    cout << "10. Exportar a Dat (Fichero de datos)" << endl;
    cout << "11. Mostrar archivo Dat (Fichero de datos)" << endl;
    cout << "12. Busqueda en memoria (Cargar a RAM)" << endl;
    cout << "13. Busqueda por indices (No operativo)" << endl;
    cout << "14. Cifrar" << endl;
    cout << "15. Descifrar" << endl;
    cout << "16. Mostrar archivo cifrado" << endl; 
    cout << "17. Crear tabla Hash (No operativo)" << endl;
    cout << "18. Salir" << endl;
    cout << "Opcion: ";
    cin >> opcion;
    cin.clear();
    return opcion;
}

void ingresaCorreo() {
    ofstream archivo;
    string contenido;
    archivo.open("Correos.txt", ios::out| ios::in | ios::binary);
    if(!archivo.is_open()) {
        archivo.open("Correos.txt", ios::out);
        if(!archivo.good()) {
            cerr << "Error al crear el archivo... abortando" << endl;
            return;
        }
    }
    cout << "Escribe los datos del correo: " << endl << endl;
    cout << "ID: " << endl;
    cin >> Correo1.identificador;
    while(Correo1.identificador <= 0) {
        cout << "ID no valido \n Ingrese un ID valido" << endl;
        cin >> Correo1.identificador;
    }

    cin.ignore();
    cout << "Remitente: " << endl;
    cin.getline(Correo1.remitente, 20);
    cout << "Destinatario: " << endl;
    cin.getline(Correo1.destinatario, 30);
    cout << "CopiaCarbon: " << endl;
    cin.getline(Correo1.copiaCarbon, 15);
    cout << "CopiaCarbonCiega: " << endl;
    cin.getline(Correo1.copiaCarbonCiega, 30);
    cout << "Asunto: " << endl;
    cin.getline(Correo1.asunto, 50);
    cout << "Escriba '|' para teminar la entrada." << endl;
    cout << "Contenido del Correo: " << endl;
    cin.getline(Correo1.contenido, 500, '|');

    consiguehorayfecha();
    consiguehorayfecha();

    archivo.seekp((Correo1.identificador-1)*sizeof(Correo1), ios::beg);
    archivo.write((char *) &Correo1, sizeof(Correo1));
    archivo.close();
    cout << "Correo insertado correctamente. " << endl;
}

void consiguehorayfecha() {
    time_t tiempo = time(0);
    struct tm *tiempoAhora = localtime(&tiempo);
    Correo1.horaCreacion.hora=tiempoAhora->tm_hour;
    Correo1.horaCreacion.minuto=tiempoAhora->tm_min;
    Correo1.fechaCreacion.anio=tiempoAhora->tm_year+1900;
    Correo1.fechaCreacion.mes=tiempoAhora->tm_mon+1;
    Correo1.fechaCreacion.dia=tiempoAhora->tm_mday;
}

void imprimirCorreo() {
    cout << "ID: " << Correo1.identificador << endl;
    cout << "Remitente: " << Correo1.remitente << endl;
    cout << "Destinatario: " << Correo1.destinatario << endl;
    cout << "CopiaCarbon: " << Correo1.copiaCarbon << endl;
    cout << "CopiaCarbonCiega: " << Correo1.copiaCarbonCiega << endl;
    cout << "Asunto: " << Correo1.asunto << endl;
    cout << "Contenido: " << endl << Correo1.contenido << endl;
    cout << "Fecha de creacion: " << Correo1.fechaCreacion.dia << "/"<< Correo1.fechaCreacion.mes<< "/" << Correo1.fechaCreacion.anio << endl;
    cout << "Hora de creacion: " << Correo1.horaCreacion.hora << ":" << Correo1.horaCreacion.minuto << endl;
    cin.ignore();
}

void mostrarCorreo() {
    ifstream Archivo("Correos.txt", ios::in | ios::binary);
    bool encontrado = false;
    if(Archivo.fail()) {
        cerr << "Error en el archivo, no se puede acceder" << endl;
    } else {
        while(!Archivo.eof()) {
            Archivo.read((char*)&Correo1, sizeof(Correo));
            if(Archivo.eof()) {
            	break;
			}
			
            if(Correo1.identificador != 0){
                cout << endl;
                imprimirCorreo();
                encontrado = true;
            }
        }
    }
    Archivo.close();
    
    if(!encontrado) {
        cout << "No Hay elementos" << endl;
    }
}

void buscarCorreo() {
    int opc;
    cout << "\t\t\tMENU" << endl;
    cout << endl;
    cout << "1. Buscar por ID" << endl;
    cout << "2. Buscar por remitente " << endl;
    cout << "3. Atras" << endl;
    cout << "Seleccione opcion: ";
    cin >> opc;
    cin.clear();

    if(opc==1) {
        ifstream Archivo("Correos.txt", ios::in | ios::binary);
        int x;
        cout << "Escribe el ID" << endl;
        cin >> x;
        if(Archivo.is_open()) {
            int buscar = (x-1)*sizeof(Correo);
            Archivo.seekg(buscar);
            Archivo.read((char*) &Correo1,sizeof(Correo));
            if(Correo1.identificador != 0) {
                imprimirCorreo();
            } else {
                cout << "No hay elementos " << endl;
            }
        } else {
            cerr << "Error al abrir el archivo" << endl;
        }
        Archivo.close();
    }
    
    if(opc==2) {
        string remitente;
        bool encontrado = false;
        cin.ignore();
        cout << "Escribe el remitente: " << endl;
        getline(cin,remitente);
        ifstream Archivo("Correos.txt", ios::in | ios::binary);
        if(Archivo.is_open()) {
            while(!Archivo.eof()) {
                Archivo.read((char*) &Correo1, sizeof (Correo));

                if(Archivo.eof()) {
                	break;
				}
                
                if(Correo1.remitente == remitente) {
                    cout << "Correo encontrado: "<< endl;
                    imprimirCorreo();
                    encontrado = true;
                }
            }
            
            if(encontrado==false) {
                cout << "No se encontraron coincidencias " << endl;
            }
        } else {
            cerr << "Error al abrir el archivo" << endl;
        }
        Archivo.close();
    }
    
    if(opc == 3) {
    	main();
	}
}

void modificarCorreo() {
    int id,x;
    bool encontrado = false;
    cout << "\t\t\tMENU" << endl;
    cout << endl;
    cout << "1. Modificar por ID " << endl;
    cout << "2. Modificar por remitente " << endl;
    cout << "3. Atras "  << endl;
    cout << "Seleccione opcion: ";
    cin >> x;
    cin.clear();
    if(x==1) {
        ofstream archivo;
        ifstream Archivo("Correos.txt", ios::in | ios::binary);
        
        if(Archivo.fail()) {
            cerr << "Error al abrir el archivo" << endl;
        }

        archivo.open("Correos.txt", ios::out| ios::in | ios::binary);
        if(!archivo.is_open()) {
            archivo.open("Correos.txt", ios::out);
            if( ! archivo.good()) {
                cerr << "Error al abrir el archivo" << endl;
                return;
            }
        }
        cout << "Ingresa el ID del correo a modificar: " << endl;
        cin >> id;
        while(id <= 0) {
            cerr << "ID no valido \n Ingrese un ID valido" << endl;
            cin >> id;
        }
        
        while (!Archivo.eof()) {
            Archivo.read((char*) &Correo1, sizeof (Correo));
            if (Archivo.eof()) {
            	break;
			}

            if (Correo1.identificador != 0 and Correo1.identificador == id) {
                cout << endl;
                imprimirCorreo();
                encontrado = true;
            }
        }
        if((encontrado = false)) {
            cout << "No se encontraron conincidencias..." << endl;
            return;
        }
        
        cout << "\nCorreo encontrado, escriba los nuevos datos: " << endl;
        Correo1.identificador=id;
        cout << "Remitente: " << endl;
        cin.getline(Correo1.remitente, 20);
        cout << "Destinatario: " << endl;
        cin.getline(Correo1.destinatario, 30);
        cout << "CopiaCarbon: " << endl;
        cin.getline(Correo1.copiaCarbon, 15);
        cout << "CopiaCarbonCiega: " << endl;
        cin.getline(Correo1.copiaCarbonCiega, 30);
        cout << "Asunto: " << endl;
        cin.getline(Correo1.asunto, 50);
        cout << "Escriba '|' para terminar la entrada..." << endl;
        cout << "Contenido del Correo: " << endl;
        cin.getline(Correo1.contenido, 500, '|');

        consiguehorayfecha();

        archivo.seekp((Correo1.identificador-1)*sizeof(Correo1), ios::beg);
        archivo.write((char *) &Correo1, sizeof(Correo1));
        archivo.close();
        Archivo.close();
        cin.ignore();
    }
    if(x==2) {
        int opc;
        string remitente;
        ofstream archivo;
        ifstream Archivo("Correos.txt", ios::in | ios::binary);
        if (Archivo.fail()) {
            cerr << "Error al abrir el archivo" << endl;
        }
        cin.ignore();
        cout << "Ingresa el remitente del correo a modificar: " << endl;
        getline(cin,remitente);
        int z(0);
        while (!Archivo.eof()) {
            Archivo.read((char*) &Correo1, sizeof (Correo));
            z++;

            if (Archivo.eof()){
            	break;
			}
			
            if (Correo1.remitente == remitente) {
                imprimirCorreo();
                cout << "Se encontro una coincidencia " << endl;
                cout << "Quiere modificar este correo? si=1 no =9: " << endl;
                cin >> opc;
                
                if(opc==1) {
                    archivo.open("Correos.txt", ios::out | ios::in | ios::binary);
                    if(!archivo.is_open()) {
                        archivo.open("Correos.txt", ios::out);
                        if(!archivo.good()) {
                            cerr << "Error al abrir el archivo" << endl;
                            return;
                        }
                    }

                    Correo1.identificador=z;
                    cin.ignore();
                    cout << "Remitente: " << endl;
                    cin.getline(Correo1.remitente, 20);
                    cout << "Destinatario: " << endl;
                    cin.getline(Correo1.destinatario, 30);
                    cout << "CopiaCarbon: " << endl;
                    cin.getline(Correo1.copiaCarbon, 15);
                    cout << "CopiaCarbonCiega: " << endl;
                    cin.getline(Correo1.copiaCarbonCiega, 30);
                    cout << "Asunto: " << endl;
                    cin.getline(Correo1.asunto, 50);
                    cout << "Escriba '|' para terminar la entrada" << endl;
                    cout << "Contenido del Correo: " << endl;
                    cin.getline(Correo1.contenido, 500, '|');

                    consiguehorayfecha();


                    archivo.seekp((Correo1.identificador-1)*sizeof(Correo1), ios::beg);
                    archivo.write((char *) &Correo1, sizeof(Correo1));
                    archivo.close();
                    cout << "Correo modificado." << endl;
                    cin.ignore();
                } else {
                    cerr << "Este Correo no se modifico... " << endl;
                    pausa();
                }
            }
        }
        archivo.close();
        Archivo.close();
    }
    if(x == 3) {
    	main();
	}
}

void eliminarCorreo() {
    int op;
    cout << "\t\t\tMENU" << endl;
    cout << endl;
    cout << "1. Eliminar por ID " << endl;
    cout << "2. Eliminar por remitente " << endl;
    cout << "3. Atras" << endl;
    cout << "Seleccione opcion: ";
    cin >> op;
    if(op==1) {
        ofstream archivoaEliminar;
        ifstream Archivo("Correos.txt", ios::in | ios::binary);
        Correo Correo2;
        int x,opc;

        cout << "Escribe el ID correo que quieres eliminar: " << endl;
        cin >> x;

        if(Archivo.is_open()) {
            int buscar = (x-1)*sizeof(Correo);
            Archivo.seekg(buscar);
            Archivo.read((char*) &Correo1,sizeof(Correo));

            if(Correo1.identificador != 0) {
                imprimirCorreo();
                pausa();
                cout << "Estas seguro de que quieres eliminar este correo? si=1 no =9: " << endl;
                cin >> opc;
                
                if(opc==1) {
                    archivoaEliminar.open("Correos.txt", ios::out| ios::in | ios::binary);
                    if(!archivoaEliminar.is_open()) {
                        archivoaEliminar.open("Correos.txt", ios::out);
                        if(!archivoaEliminar.good()){
                            cerr << "Error al abrir el archivo" << endl;
                            return;
                        }
                    }
                    Correo2.identificador=0;
                    archivoaEliminar.seekp((x-1)*sizeof(Correo1), ios::beg);
                    archivoaEliminar.write((char *) &Correo2, sizeof(Correo1));
                    archivoaEliminar.close();
                    cout << "Correo eliminado." << endl;
                } else {
                    cout << "El Correo no se elimino... " << endl;
                    return;
                }
            } else {
                cout << "No hay elementos " << endl;
            }
        } else {
            cerr << "Error al abrir el archivo" << endl;
        }
        Archivo.close();
    }
    
    if(op==2) {
        ofstream archivoaEliminar;
        ifstream Archivo("Correos.txt", ios::in | ios::binary);
        Correo Correo2;
        int opc;
        string remitente;
        cin.ignore();
        cout << "Escribe el remitente del correo a eliminar: " << endl;
        getline(cin,remitente);
        
        if(Archivo.is_open()) {
            int z(0);
            while(!Archivo.eof()) {
                Archivo.read((char*) &Correo1, sizeof (Correo));
                z++;

                if(Archivo.eof()) {
                	break;
				}
				
                if (Correo1.remitente == remitente) {
                    imprimirCorreo();
                    cout << "Se encontro una coincidencia " << endl;
                    cout << "Estas seguro de que quieres eliminar este correo? si=1 no =9: " << endl;
                    cin >> opc;
                    if(opc==1) {
                        archivoaEliminar.open("Correos.txt", ios::out| ios::in | ios::binary);
                        if(!archivoaEliminar.is_open()) {
                            archivoaEliminar.open("Correos.txt", ios::out);
                            if(!archivoaEliminar.good()) {
                                cerr << "Error al abrir el archivo" << endl;
                                return;
                            }
                        }
                        Correo2.identificador = 0;
                        archivoaEliminar.seekp((z-1)*sizeof(Correo1), ios::beg);
                        archivoaEliminar.write((char *) &Correo2, sizeof(Correo1));
                        archivoaEliminar.close();
                        cout << "Correo eliminado." << endl;
                    } else {
                        cout << "Este Correo no se elimino... " << endl;
                        pausa();
                    }
                }
            }
        } else {
            cerr << "Error al abrir el archivo" << endl;
        }
        Archivo.close();
    }
    
    if(op == 3){
    	main();
	}
}

void exportaraCsv() {
    ifstream Archivo("Correos.txt", ios::in | ios::binary);
    string nombreArchivo;
    bool encontrado = false;
    if(!Archivo.good()) {
    	cout << "Error al intentar abrir el archivo base para hacer la copia de seguridad." << endl;
	} else {
        fflush(stdin);
        cout << "Ingresa el Nombre del archivo donde desea gurdar la copia :" << endl;
        getline(cin, nombreArchivo);
        if(nombreArchivo == "") {
            cout << "Se ha presionado enter sin capturar ningun nombre para el archivo." << endl;
            cout << "Se creara un archivo con el nombre 'seguridad.csv'" << endl;
            nombreArchivo = "seguridad";
        }
        nombreArchivo = nombreArchivo+".csv";

        ofstream file(nombreArchivo.c_str(), ios::in | ios::trunc |ios::out);
        if(!file.good()) {
        	cerr << "El archivo para guardar la copia de seguridad no se puede abrir" << endl;
		} else {
            while (!Archivo.eof()) {
                Archivo.read((char*) &Correo1, sizeof (Correo));
                if (Archivo.eof()) {
                    break;
                }
                
                if(Correo1.identificador != 0) {
                    encontrado = true;
                    file << Correo1.identificador << delimitador << Correo1.remitente << delimitador
                         << Correo1.destinatario << delimitador << Correo1.copiaCarbon << delimitador
                         << Correo1.copiaCarbonCiega << delimitador << Correo1.asunto << delimitador
                         << Correo1.contenido << delimitador << Correo1.fechaCreacion.dia << delimitador
                         << Correo1.fechaCreacion.mes << delimitador <<Correo1.fechaCreacion.anio << delimitador
                         << Correo1.horaCreacion.hora << delimitador << Correo1.horaCreacion.minuto << delimitador << endl;
                }
            }
            if(encontrado == false){
            	cout << "No Hay elementos" << endl;
			} else {
            	cout << "Archivo creado con exito" << endl;
			}
        }
        file.close();
    }
    Archivo.close();
}

void mostrarArchivoSeguridad() {
	std::string temp;
	bool elementos = false;
	string nombreArchivo;

	cout << "Ingrese el nombre del archivo que desea leer: ";
	cin.clear();
	cin.ignore();
	getline(cin,nombreArchivo);
	nombreArchivo = nombreArchivo + ".csv";
	ifstream Archivo(nombreArchivo.c_str());
	
	if(Archivo.fail()) {
		cerr << "No existe tal archivo, o ha sido movido de la carpeta del .csv" << endl;
	} else {
	    cout << "Mostrando archvo de seguridad: " << endl;
		while(!Archivo.eof()) {
			getline(Archivo, temp, ';');
			if(Archivo.eof()){
				break;
			}
			Correo1.identificador = stoi(temp);

			getline(Archivo, temp, ';');

			int n = temp.length();
			char a[n+1];
			strcpy(a, temp.c_str());
			strcpy(Correo1.remitente, a);

			getline(Archivo, temp, ';');
			strcpy(a, temp.c_str());
			strcpy(Correo1.destinatario, a);

			getline(Archivo, temp, ';');
			strcpy(a, temp.c_str());
			strcpy(Correo1.copiaCarbon, a);
			getline(Archivo, temp, ';');

			strcpy(a, temp.c_str());
			strcpy(Correo1.copiaCarbonCiega, a);

			getline(Archivo, temp, ';');
			strcpy(a, temp.c_str());
			strcpy(Correo1.asunto, a);

			getline(Archivo, temp, ';');
			strcpy(a, temp.c_str());
			strcpy(Correo1.contenido, a);

			getline(Archivo, temp, ';');
			fecha.dia = stoi(temp);

			getline(Archivo, temp, ';');
			fecha.mes = stoi(temp);

			getline(Archivo, temp, ';');
			fecha.anio= stoi(temp);

			getline(Archivo, temp, ';');
			hora.hora= stoi(temp);

			getline(Archivo, temp, ';');
			hora.minuto= stoi(temp);

			if(Correo1.identificador != 0) {
				imprimirInformacion();
				elementos = true;
			}
		}
	}
	if(elementos == false) {
		cout << "No hay elementos" << endl;
	}
	Archivo.close();
}

void imprimirInformacion() {
	cout << "Identificador: " << Correo1.identificador << endl;
	cout << "Remitente: " << Correo1.remitente << endl;
	cout << "Destinatario: " << Correo1.destinatario << endl;
	cout << "Copia Carbon: " << Correo1.copiaCarbon << endl;
	cout << "Copia Carbon Ciega: " << Correo1.copiaCarbonCiega << endl;
	cout << "Asunto: " << Correo1.asunto << endl;
	cout << "Contenido: " << Correo1.contenido << endl;
	cout << "Dia: " << fecha.dia << endl;
	cout << "Mes: " << fecha.mes << endl;
	cout << "Anio: " << fecha.anio << endl;
	cout << "Hora: " << hora.hora << endl;
	cout << "Minuto: " << hora.minuto << endl;
	cout << "\n";
}

void modificarArchivoSeguridad() {
	int idModificar;
	string ID, temp;
	string nombreArchivo;
	// UBNUTU
	cin.ignore();
	cin.clear();
	fflush(stdin);
	cout << "Ingrese el nombre del archivo donde desea modificar un registro: ";
	getline(cin,nombreArchivo);
	nombreArchivo = nombreArchivo + ".csv";
	ofstream Temp("temp.csv",ios::out);
	ifstream Archivo(nombreArchivo.c_str(), ios::in);
	if(!Archivo.good()) {
		cerr << "Error al intentar abrir el archivo base para hacer la copia de seguridad." << endl;
	} else {
		if(!Archivo.good()){
			cerr << "El archivo para guardar la copia de seguridad no se puede abrir" << endl;
		} else {
			cout << "Ingrese ID asociado a registro a modificar: ";
			cin >> idModificar;

			// Obtener datos del usuario.
			string REMITENTE;
			string DESTINATARIO;
			string COPIACARBON;
			string COPIACARBONCIEGA;
			string ASUNTO;
			string CONTENIDO;

			cout << "Remitente: " << endl;
			fflush(stdin);
			cin.ignore();
			cin.clear();
			getline(cin, REMITENTE);
			cout << "Destinatario: " << endl;
			getline(cin, DESTINATARIO);
			cout << "CopiaCarbon: " << endl;
			getline(cin, COPIACARBON);
			cout << "CopiaCarbonCiega: " << endl;
			getline(cin, COPIACARBONCIEGA);
			cout << "Asunto: " << endl;
			getline(cin, ASUNTO);
			cout << "Escriba '|' para teminar la entrada." << endl;
			cout << "Contenido del Correo: " << endl;
			getline(cin, CONTENIDO, '|');

			consiguehorayfecha();
			consiguehorayfecha();

			while(!Archivo.eof()) {
				getline(Archivo, ID, ';');

				if(Archivo.eof()) {
					break;
				}

				Correo1.identificador = stoi(ID);

				getline(Archivo, temp, ';');
				int n = temp.length();
				char a[n+1];
				strcpy(a, temp.c_str());
				strcpy(Correo1.remitente, a);

				getline(Archivo, temp, ';');
				strcpy(a, temp.c_str());
				strcpy(Correo1.destinatario, a);

				getline(Archivo, temp, ';');
				strcpy(a, temp.c_str());
				strcpy(Correo1.copiaCarbon, a);
				getline(Archivo, temp, ';');

				strcpy(a, temp.c_str());
				strcpy(Correo1.copiaCarbonCiega, a);

				getline(Archivo, temp, ';');
				strcpy(a, temp.c_str());
				strcpy(Correo1.asunto, a);

				getline(Archivo, temp, ';');
				strcpy(a, temp.c_str());
				strcpy(Correo1.contenido, a);

				getline(Archivo, temp, ';');
				fecha.dia = stoi(temp);

				getline(Archivo, temp, ';');
				fecha.mes = stoi(temp);

				getline(Archivo, temp, ';');
				fecha.anio= stoi(temp);

				getline(Archivo, temp, ';');
				hora.hora= stoi(temp);

				getline(Archivo, temp, ';');
				hora.minuto= stoi(temp);

				// MODIFICAR
				if(idModificar == stoi(ID)) {
					Temp << ID << delimitador << REMITENTE<< delimitador
						 << DESTINATARIO << delimitador << COPIACARBON << delimitador
						 << COPIACARBONCIEGA << delimitador <<  ASUNTO<< delimitador
						 << CONTENIDO << delimitador << Correo1.fechaCreacion.dia << delimitador
						 << Correo1.fechaCreacion.mes << delimitador <<Correo1.fechaCreacion.anio << delimitador
						 << Correo1.horaCreacion.hora << delimitador << Correo1.horaCreacion.minuto << delimitador << endl;
				}
				else {
					Temp << Correo1.identificador << delimitador << Correo1.remitente << delimitador
						 << Correo1.destinatario << delimitador << Correo1.copiaCarbon << delimitador
						 << Correo1.copiaCarbonCiega << delimitador << Correo1.asunto << delimitador
						 << Correo1.contenido << delimitador << Correo1.fechaCreacion.dia << delimitador
						 << Correo1.fechaCreacion.mes << delimitador <<Correo1.fechaCreacion.anio << delimitador
						 << Correo1.horaCreacion.hora << delimitador << Correo1.horaCreacion.minuto << delimitador << endl;
				}
			}
		}
		Temp.close();
	}
	Archivo.close();
	remove(nombreArchivo.c_str());
	rename("temp.csv", nombreArchivo.c_str());
}

void eliminarArchivoSeguridad() {
	string temp;
	string ID;
	int idEliminar;
	string nombreArchivo;
	fflush(stdin);
	cin.ignore();
	cin.clear();
	cout << "Ingrese el nombre del archivo donde desea eliminar un registro: ";
	getline(cin,nombreArchivo);
	nombreArchivo = nombreArchivo + ".csv";
	ofstream Temp("temp.csv", std::ios_base::out);
	ifstream Archivo(nombreArchivo.c_str(), std::ios_base::in);
	if(!Archivo.good()) {
		cerr << "Error al intentar abrir el archivo base para hacer la copia de seguridad." << endl;
	} else {
		if(!Archivo.good()) {
			cerr << "El archivo para guardar la copia de seguridad no se puede abrir" << endl;
		} else {
			cout << "Ingrese ID asociado a registro a eliminar: ";
			cin >> idEliminar;

			while(!Archivo.eof()) {
				getline(Archivo, ID, ';');

				if(Archivo.eof()) {
					break;
				}

				Correo1.identificador = stoi(ID);

				getline(Archivo, temp, ';');
				int n = temp.length();
				char a[n+1];
				strcpy(a, temp.c_str());
				strcpy(Correo1.remitente, a);

				getline(Archivo, temp, ';');
				strcpy(a, temp.c_str());
				strcpy(Correo1.destinatario, a);

				getline(Archivo, temp, ';');
				strcpy(a, temp.c_str());
				strcpy(Correo1.copiaCarbon, a);
				getline(Archivo, temp, ';');

				strcpy(a, temp.c_str());
				strcpy(Correo1.copiaCarbonCiega, a);

				getline(Archivo, temp, ';');
				strcpy(a, temp.c_str());
				strcpy(Correo1.asunto, a);

				getline(Archivo, temp, ';');
				strcpy(a, temp.c_str());
				strcpy(Correo1.contenido, a);

				getline(Archivo, temp, ';');
				fecha.dia = stoi(temp);

				getline(Archivo, temp, ';');
				fecha.mes = stoi(temp);

				getline(Archivo, temp, ';');
				fecha.anio= stoi(temp);

				getline(Archivo, temp, ';');
				hora.hora= stoi(temp);

				getline(Archivo, temp, ';');
				hora.minuto= stoi(temp);

				// ELIMINAR
				if(idEliminar != stoi(ID)) {
					Temp << Correo1.identificador << delimitador << Correo1.remitente << delimitador
						 << Correo1.destinatario << delimitador << Correo1.copiaCarbon << delimitador
						 << Correo1.copiaCarbonCiega << delimitador << Correo1.asunto << delimitador
						 << Correo1.contenido << delimitador << Correo1.fechaCreacion.dia << delimitador
						 << Correo1.fechaCreacion.mes << delimitador <<Correo1.fechaCreacion.anio << delimitador
						 //<< Correo1.horaCreacion.hora << delimitador << Correo1.horaCreacion.minuto << finRegistro << endl;
						 << Correo1.horaCreacion.hora << delimitador << Correo1.horaCreacion.minuto << delimitador << endl;
				}
			}
		}
		Temp.close();
	}
	Archivo.close();
	remove(nombreArchivo.c_str());
	rename("temp.csv", nombreArchivo.c_str());
}

void exportaraDat() {
    string nombreArchivo;
    Correo Correo1;
    cout << "Ingrese el nombre del archivo de datos: ";
    cin.clear();
    cin.ignore();
    getline(cin,nombreArchivo);
    nombreArchivo = nombreArchivo + ".dat";
    ifstream Archivo;
    ofstream Copia;
    Copia.open(nombreArchivo.c_str(), ios::out | ios::binary);
    if(Copia.is_open()) {
        Archivo.open("Correos.txt",ios::in | ios::binary);
        if(Archivo.good()) {
            while(!Archivo.eof()) {
                if(Archivo.eof()) {
                    break;
                }
                Archivo.read((char *)&Correo1, sizeof(Correo));
                Copia.write((char *)&Correo1, sizeof(Correo));
            }
            cout << "Correo expotado correctamente." << endl;
        } else {
            cerr << "Error al abrir el archivo de correos." << endl;
        }
    } else {
        cerr << "Error al abir el archivo de datos." << endl;
    }
    Archivo.close();
    Copia.close();
}

void mostrarArchivoDat() {
    ifstream Copia;
    string nombreArchivo;
    bool encontrado = false;
    cout << "Digite el nombre del archivo que desea leer: ";
    cin.clear();
    cin.ignore();
    getline(cin,nombreArchivo);
    nombreArchivo = nombreArchivo + ".dat";
    Copia.open(nombreArchivo.c_str(), ios::in | ios::binary);
    if(Copia.fail()) {
        cerr << "Error al abir el archivo de datos." << endl;
    } else {
        cout << "Mostrando archivo de datos..." << endl;
        while(!Copia.eof()) {
            Copia.read((char *)&Correo1, sizeof(Correo));
            if(Copia.eof()) {
                break;
            }
            if(Correo1.identificador != 0) {
                cout << endl;
                imprimirArchivoDat();
                encontrado = true;
            }
        }
    }
    Copia.close();
    if(!encontrado) {
        cout << "No Hay elementos" << endl;
    }
    Copia.close();
}

void imprimirArchivoDat() {
    cout << "ID: " << Correo1.identificador << endl;
    cout << "Remitente: " << Correo1.remitente << endl;
    cout << "Destinatario: " << Correo1.destinatario << endl;
    cout << "Copia Carbon: " << Correo1.copiaCarbon << endl;
    cout << "Copia Carbon Ciega: " << Correo1.copiaCarbonCiega << endl;
    cout << "Asunto: " << Correo1.asunto << endl;
    cout << "Contenido: " << endl << Correo1.contenido << endl;
    cout << "Fecha de creacion: " << Correo1.fechaCreacion.dia << "/" << Correo1.fechaCreacion.mes << "/" << Correo1.fechaCreacion.anio << endl;
    cout << "Hora de creacion: " << Correo1.horaCreacion.hora << ":" << Correo1.horaCreacion.minuto << endl;
    cin.get();
    cin.get();
    cin.ignore();
}

void busquedaEnMemoria() {
	Correo Correo1;
	Correo guardaRegistros[1000];
	int i = 0;
	int contador = 1;
	string nombreArchivo;
	cout << "Ingrese el nombre del archivo que desea cargar a memoria: ";
	cin.clear();
	cin.ignore();
	getline(cin, nombreArchivo);
	ifstream Archivo;
	nombreArchivo = nombreArchivo + ".txt";
	Archivo.open(nombreArchivo.c_str(), ios_base::in | ios_base::binary);

	if(Archivo.fail()) {
		throw "Error al leer el archivo";
		Archivo.close();
	} else if(Archivo.is_open()) {
		while(!Archivo.eof()) {
			Archivo.seekg((contador - 1) * sizeof(Correo1), std::ios_base::beg);
			Archivo.read((char *)&Correo1, sizeof(Correo1));

			if(Correo1.identificador == 0) {
				contador++;
				continue;
			}

			guardaRegistros[i] = Correo1;

			tamanio = i;
			i++;
			contador++;
		}
	}
	cout << "Mostrando registros en memoria: " << endl;
	for(int i(0); i < tamanio; i++) {
		cout << "ID: " << guardaRegistros[i].identificador << endl;
		cout << "Remitente: " << guardaRegistros[i].remitente << endl;
		cout << "Destinatario: " << guardaRegistros[i].destinatario << endl;
		cout << "Copia Carbon: " << guardaRegistros[i].copiaCarbon << endl;
		cout << "Copia Carbon Ciega: " << guardaRegistros[i].copiaCarbonCiega << endl;
		cout << "Asunto: " << guardaRegistros[i].asunto << endl;
		cout << "Contenido: " << guardaRegistros[i].contenido << endl;
		cout << endl;
	}
	pausa();

	cout << "Ordenando por remitente..." << endl;
	pausa();
	shellSort(guardaRegistros);
	cout << "Mostrando registros ordenados por remitente: " << endl;
	for(int i(0); i < tamanio; i++) {
		cout << "ID: " << guardaRegistros[i].identificador << endl;
		cout << "Remitente: " << guardaRegistros[i].remitente << endl;
		cout << "Destinatario: " << guardaRegistros[i].destinatario << endl;
		cout << "Copia Carbon: " << guardaRegistros[i].copiaCarbon << endl;
		cout << "Copia Carbon Ciega: " << guardaRegistros[i].copiaCarbonCiega << endl;
		cout << "Asunto: " << guardaRegistros[i].asunto << endl;
		cout << "Contenido: " << guardaRegistros[i].contenido << endl;
		cout << endl;
	}
	cin.get();
	cin.get();
	system(CLEAR);
	char opcion;
	string str;
	cout << "Desea realizar una busqueda(s/n) ? ";
	cin >> opcion;
	string remitenteABuscar;
	if(opcion == 's' or opcion == 'S') {
        cout << "Ingrese el nombre del remitente a buscar: ";
        cin.clear();
        cin.ignore();
        getline(cin, remitenteABuscar);
        i = 0;
        bool encontrado = false;
        while((encontrado == false) and (i < tamanio)) {
			if(guardaRegistros[i].remitente == remitenteABuscar) {
				encontrado = true;
			}
			i++;
		}
		if(encontrado == false) {
			cerr << "Registro no encontrado." << endl;
		} else {
			cout << "Registro encontrado" << endl;
			cout << "Mostrando..." << endl;
			cout << "ID: " << guardaRegistros[i-1].identificador << endl;
			cout << "Remitente: " << guardaRegistros[i-1].remitente << endl;
			cout << "Destinatario: " << guardaRegistros[i-1].destinatario << endl;
			cout << "Copia Carbon: " << guardaRegistros[i-1].copiaCarbon << endl;
			cout << "Copia Carbon Ciega: " << guardaRegistros[i-1].copiaCarbonCiega << endl;
			cout << "Asunto: " << guardaRegistros[i-1].asunto << endl;
			cout << "Contenido: " << guardaRegistros[i-1].contenido << endl;
		}
	} else if(opcion == 'N' or opcion == 'n') {
        cout << "Volviendo al menu principal" << endl;
        cin.get();
        cin.get();
        elegirOpcion();
	} else {
        cerr << "No introdujo una opcion correcta." << endl;
        cout << "Volviendo al menu principal" << endl;
        cin.get();
        cin.get();
        elegirOpcion();
	}
Archivo.close();
}

void shellSort(Correo *guardaRegistros) {
	std::string str1;
	std::string str2;
	Correo aux;
	for(int gap = tamanio / 2; gap > 0; gap /= 2) {
		for(int i = gap; i < tamanio; i += 1) {
			for(int j = i-gap; j >= 0; j = j-gap) {
				str1 = guardaRegistros[j].remitente;
				str2 = guardaRegistros[j + gap].remitente;

				if(str1 <= str2) {
					//if(guardaRegistros[j].contenido >= guardaRegistros[j + gap].email){
						break;
				} else{
					aux = guardaRegistros[j];
					guardaRegistros[j] = guardaRegistros[j + gap];
					guardaRegistros[j + gap] = aux;
				}
			}
		}
	}
}

void cifradoCesar() {
	Correo Correo1;
	ifstream Archivo;
	ofstream Encriptacion;
	std::string nombreArchivo;
	int i = 0;
	int contador = 1;
	char alfabeto[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	cout << "Digite el nombre del archivo a cifrar: ";
	cin.clear();
	cin.ignore();
	getline(cin, nombreArchivo);
	nombreArchivo = nombreArchivo + ".txt";
	Archivo.open(nombreArchivo.c_str(), ios::in | ios::binary);
	if(Archivo.is_open()) {
		Encriptacion.open("Cifrado.txt", ios::out | ios::binary);
		if(Encriptacion.good()) {
			while(!Archivo.eof()) {
				Archivo.seekg((contador - 1) * sizeof(Correo1), std::ios_base::beg);
				Archivo.read((char *)&Correo1, sizeof(Correo1));
				
				if(Correo1.identificador == 0) {
					contador++;
					continue;
				}
				
				// Guardamos los registros en memoria
				guardaRegistros[i] = Correo1;
				
				tamanio = i;
				i++;
				contador++;
			}
			
			cout << "Vaciando registros a memoria principal..." << endl;
			cout << "Mostrando registros en memoria..." << endl;
			for(int i(0); i < tamanio; i++) {
				cout << "ID: " << guardaRegistros[i].identificador << endl;
				cout << "Remitente: " << guardaRegistros[i].remitente << endl;
				cout << "Destinatario: " << guardaRegistros[i].destinatario << endl;
				cout << "Copia Carbon: " << guardaRegistros[i].copiaCarbon << endl;
				cout << "Copia Carbon Ciega: " << guardaRegistros[i].copiaCarbonCiega << endl;
				cout << "Asunto: " << guardaRegistros[i].asunto << endl;
				cout << "Contenido: " << guardaRegistros[i].contenido << endl;
				cout << endl;
			}
			pausa();
			for(int i = 0; i < tamanio; i++) {
				
				// Cifrar remitente
				for(int j = 0; j < strlen(guardaRegistros[i].remitente); j++) {
					if(guardaRegistros[i].remitente[j] != 32) {
						for(int k = 0; k < strlen(alfabeto); k++) {
							if(guardaRegistros[i].remitente[j] == alfabeto[k]) {
								int aux = (k + 3) % 26;
								guardaRegistros[i].remitente[j] = alfabeto[aux];
								break;
							}
						}
					}
				}
				
				// Cifrar destinatario
				for(int j = 0; j < strlen(guardaRegistros[i].destinatario); j++) {
					if(guardaRegistros[i].destinatario[j] != 32) {
						for(int k = 0; k < strlen(alfabeto); k++) {
							if(guardaRegistros[i].destinatario[j] == alfabeto[k]) {
								int aux = (k + 3) % 26;
								guardaRegistros[i].destinatario[j] = alfabeto[aux];
								break;
							}
						}
					}
				}
				
				// Cifrar copiaCarbon
				for(int j = 0; j < strlen(guardaRegistros[i].copiaCarbon); j++) {
					if(guardaRegistros[i].copiaCarbon[j] != 32) {
						for(int k = 0; k < strlen(alfabeto); k++) {
							if(guardaRegistros[i].copiaCarbon[j] == alfabeto[k]) {
								int aux = (k + 3) % 26;
								guardaRegistros[i].copiaCarbon[j] = alfabeto[aux];
								break;
							}
						}
					}
				}
				
				// Cifrar copiaCarbonCiega
				for(int j = 0; j < strlen(guardaRegistros[i].copiaCarbonCiega); j++) {
					if(guardaRegistros[i].copiaCarbonCiega[j] != 32) {
						for(int k = 0; k < strlen(alfabeto); k++) {
							if(guardaRegistros[i].copiaCarbonCiega[j] == alfabeto[k]) {
								int aux = (k + 3) % 26;
								guardaRegistros[i].copiaCarbonCiega[j] = alfabeto[aux];
								break;
							}
						}
					}
				}
				
				// Cifrar asunto
				for(int j = 0; j < strlen(guardaRegistros[i].asunto); j++) {
					if(guardaRegistros[i].asunto[j] != 32) {
						for(int k = 0; k < strlen(alfabeto); k++) {
							if(guardaRegistros[i].asunto[j] == alfabeto[k]) {
								int aux = (k + 3) % 26;
								guardaRegistros[i].asunto[j] = alfabeto[aux];
								break;
							}
						}
					}
				}
				
				// Cifrar contenido
				for(int j = 0; j < strlen(guardaRegistros[i].contenido); j++) {
					if(guardaRegistros[i].contenido[j] != 32) {
						for(int k = 0; k < strlen(alfabeto); k++) {
							if(guardaRegistros[i].contenido[j] == alfabeto[k]) {
								int aux = (k + 3) % 26;
								guardaRegistros[i].contenido[j] = alfabeto[aux];
								break;
							}
						}
					}
				}
			}
			
			cout << "Los correos electronicos han sido cifrados correctamente..." << endl;
			cout << "Mostrando..." << endl;
			for(int i(0); i < tamanio; i++) {
				cout << "Identificador: " << guardaRegistros[i].identificador << endl;
				cout << "Remitente: " << guardaRegistros[i].remitente << endl;
				cout << "Destinatario: " << guardaRegistros[i].destinatario << endl;
				cout << "Copia Carbon: " << guardaRegistros[i].copiaCarbon << endl;
				cout << "Copia carbon Ciega: " << guardaRegistros[i].copiaCarbonCiega << endl;
				cout << "Asunto: " << guardaRegistros[i].asunto << endl;
				cout << "Contenido: " << guardaRegistros[i].contenido << endl;
				cout << endl;
			}
			
			cout << "Generando archivo de cifrado..." << endl;
			cout << "Copiando registros a archivo de cifrado..." << endl;
			pausa();
			for(int i = 0; i < tamanio; i++) {
				Encriptacion.write((char *)&guardaRegistros[i], sizeof(Correo));
			}
			cout << "Se ha creado un fichero llamado \"Cifrado.txt\" en el directorio raiz de este ejecutable. " << endl;
			cout << "Registros guardados con exito" << endl;
			cin.get();
			cin.get();
			Archivo.close();
			Encriptacion.close();
		} else {
			cerr << "Error  al abrir el archivo de cifrado." << endl;
			Archivo.close();
			Encriptacion.close();
		}
	} else {
		cerr << "Error al abrir archivo a cifrar." << endl;
		Archivo.close();
		Encriptacion.close();
	}
}

void leerCifrado() {
	ifstream leerEncriptado;
	string nombreArchivo;
	Correo guardaCifrado[1000];
	bool encontrado = false;
	cout << "Digite el nombre del archivo encriptado a leer: ";
	cin.clear();
	cin.ignore();
	getline(cin, nombreArchivo);
	nombreArchivo = nombreArchivo + ".txt";
	leerEncriptado.open(nombreArchivo.c_str(), ios::in | ios::binary);
	if(leerEncriptado.is_open()) {
		for(int i = 0; i < tamanio; i++) {
			leerEncriptado.read((char *)&guardaCifrado[i], sizeof(Correo));
			cout << "ID: " << guardaCifrado[i].identificador << endl;
			cout << "Remitente: " << guardaCifrado[i].remitente << endl;
			cout << "Destinatario: " << guardaCifrado[i].destinatario << endl;
			cout << "Copia Carbon: " << guardaCifrado[i].copiaCarbon << endl;
			cout << "Copia Carbon Ciega: " << guardaCifrado[i].copiaCarbonCiega << endl;
			cout << "Asunto: " << guardaCifrado[i].asunto << endl;
			cout << "Contenido: " << guardaCifrado[i].contenido << endl;
			cin.ignore();
		}
	} else {
		cerr << "Error al abrir el archivo de encriptacion." << endl;
		return;
	}
	
	if(!encontrado) {
		cout << "No hay elementos" << endl;
	}
	leerEncriptado.close();
}

void descifrado() {
	ifstream Encriptacion;
	std::string nombreArchivo;
	int i = 0;
	int contador = 1;
	Correo guardaCifrado[1000] = {'\0'};
	char alfabeto[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	cout << "Digite el nombre del archivo a descifrar: ";
	cin.clear();
	cin.ignore();
	getline(cin, nombreArchivo);
	nombreArchivo = nombreArchivo + ".txt";
	Encriptacion.open(nombreArchivo.c_str(), ios::in | ios::binary);
	if(Encriptacion.fail()) {
		cerr << "Error al abrir el archivo de encriptacion. " << endl;
		return;
	} else {
		cout << "Archivo encontrado! " << endl;
		cout << "Mostrando contenido..." << endl;
		for(int i = 0; i < tamanio; i++){
			Encriptacion.read((char *)&guardaCifrado[i], sizeof(Correo));
			cout << "ID: " << guardaCifrado[i].identificador << endl;
			cout << "Remitente: " << guardaCifrado[i].remitente << endl;
			cout << "Destinatario: " << guardaCifrado[i].destinatario << endl;
			cout << "Copia Carbon: " << guardaCifrado[i].copiaCarbon << endl;
			cout << "Copia Carbon Ciega: " << guardaCifrado[i].copiaCarbonCiega << endl;
			cout << "Asunto: " << guardaCifrado[i]. asunto << endl;
			cout << "Contenido: " << guardaRegistros[i].contenido << endl;
			cout << endl;
		}
		pausa();
		for(int i = 0; i < tamanio; i++) {
			
			// Descifrar remitente
			for(int j = 0; j < strlen(guardaCifrado[i].remitente); j++) {
				if(guardaCifrado[i].remitente[j] != 32) {
					for(int k = 0; k < strlen(alfabeto); k++) {
						if(guardaCifrado[i].remitente[j] == alfabeto[k]) {
							int aux;
							if((k - 3) < 0) {
								aux = 26 + (k - 3);
							} else {
								aux = (k - 3) % 26;
							}
							guardaCifrado[i].remitente[j] = alfabeto[aux];
							break;
						}
					}
				}
			}
			
			// Descifrar destinatario
			for(int j = 0; j < strlen(guardaCifrado[i].destinatario); j++) {
				if(guardaCifrado[i].destinatario[j] != 32) {
					for(int k = 0; k < strlen(alfabeto); k++) {
						if(guardaCifrado[i].destinatario[j] == alfabeto[k]) {
							int aux;
							if((k - 3) < 0) {
								aux = 26 + (k - 3);
							} else {
								aux = (k - 3) % 26;
							}
							guardaCifrado[i].destinatario[j] = alfabeto[aux];
							break;
						}
					}
				}
			}
			
			// Descifrar copiaCarbon
			for(int j = 0; j < strlen(guardaCifrado[i].copiaCarbon); j++) {
				if(guardaCifrado[i].copiaCarbon[j] != 32) {
					for(int k = 0; k < strlen(alfabeto); k++) {
						if(guardaCifrado[i].copiaCarbon[j] == alfabeto[k]) {
							int aux;
							if((k - 3) < 0) {
								aux = 26 + (k - 3);
							} else {
								aux = (k - 3) % 26;	
							}
							guardaCifrado[i].copiaCarbon[j] = alfabeto[aux];
							break;
						}
					}
				}
			}
			
			// Descifrar copiaCarbonCiega
			for(int j = 0; j < strlen(guardaCifrado[i].copiaCarbonCiega); j++) {
				if(guardaCifrado[i].copiaCarbonCiega[j] != 32) {
					for(int k = 0; k < strlen(alfabeto); k++) {
						if(guardaCifrado[i].copiaCarbonCiega[j] == alfabeto[k]) {
							int aux;
							if((k - 3) < 0) {
								aux = 26 + (k - 3);
							} else {
								aux = (k - 3) % 26;
							}
							guardaCifrado[i].copiaCarbonCiega[j] = alfabeto[aux];
							break;
						}
					}
				}
			}
			
			// Descifrar asunto
			for(int j = 0; j < strlen(guardaCifrado[i].asunto); j++) {
				if(guardaCifrado[i].asunto[j] != 32) {
					for(int k = 0; k < strlen(alfabeto); k++) {
						if(guardaCifrado[i].asunto[j] == alfabeto[k]) {
							int aux;
							if((k - 3) < 0) {
								aux = 26 + (k - 3);
							} else {
								aux = (k - 3) % 26;
							}
							guardaCifrado[i].asunto[j] = alfabeto[aux];
							break;
						}
					}
				}
			}
			
			// Descifrar contenido
			for(int j = 0; j < strlen(guardaCifrado[i].contenido); j++) {
				if(guardaCifrado[i].contenido[j] != 32) {
					for(int k = 0; k < strlen(alfabeto); k++) {
						if(guardaCifrado[i].contenido[j] == alfabeto[k]) {
							int aux;
							if((k - 3) < 0) {
								aux = 26 + (k - 3);
							} else {
								aux = (k - 3) % 26;
							}
							guardaCifrado[i].contenido[j] = alfabeto[aux];
							break;
						}
					}
				}
			}
		}
		
		cout << "Los correos han sido descifrado correctamente..." << endl;
		cout << "Mostrando..." << endl;
		for(int i(0); i < tamanio; i++) {
			cout << "Identificador: " << guardaCifrado[i].identificador << endl;
			cout << "Remitente: " << guardaCifrado[i].remitente << endl;
			cout << "Destinatario: " << guardaCifrado[i].destinatario << endl;
			cout << "Copia Carbon: " << guardaCifrado[i].copiaCarbon << endl;
			cout << "Copia Carbon Ciega: " << guardaCifrado[i].copiaCarbonCiega << endl;
			cout << "Asunto: " << guardaCifrado[i].asunto << endl;
			cout << "Contenido: " << guardaCifrado[i].contenido << endl;
			cout << endl;
		}
	}
}

// HASH - NO OPERATIVO
int pjwHashing(char *clave) {
	#define PRIMO 211
	char *p;
	unsigned int h = 0, g;
	for(p = clave; *p != '\0'; p++) {
		h = (h << 4) + (*p);
		h = h&0xF0000000;
		if(g > 1) {
			h = h^(g << 24);
			h = h^g;
		}
	}
	return (h % PRIMO);
}

////////////////// BUSQUEDA POR INDICES PRIMARIOS ---- NO OPERATIVO /////////////////////////////////////////
////////////////// AVL SEARCH TREE //////////////////////////////////////////////////////////////////////////

class AvlTreeException : public std::exception{
    private:
        std::string msg;

    public:
        explicit AvlTreeException(const char* message) : msg(message) { }

        explicit AvlTreeException(const std::string& message) : msg(message) { }

        virtual ~AvlTreeException() throw() { }

        virtual const char* what() const throw (){
            return msg.c_str();
        }

};

class NodeException : public std::exception {
    private:
        std::string msg;

    public:
        explicit NodeException(const char* message) : msg(message) { }

        explicit NodeException(const std::string& message) : msg(message) { }

        virtual ~NodeException() throw() { }

        virtual const char* what() const throw () {
            return msg.c_str();
        }

};

template <class T>
class Node {
    private:
        T* dataPtr;
        Node<T>* right;
        Node<T>* left;
    public:
        Node();
        //Constructor parametrizado
        Node(const T&);
        ~Node();

        T& getData() const;
        T* getDataPtr() const;
        Node<T>*& getRight();
        Node<T>*& getLeft();

        void setData(T);
        void setDataPtr(T*);
        void setRight(Node<T>*&);
        void setLeft(Node<T>*&);

        //std::string toString();
};

template <class T>
Node<T>::Node() : dataPtr(nullptr), right(nullptr), left(nullptr) {}

template <class T>
Node<T>::Node(const T& e) : right(nullptr), left(nullptr) {
    dataPtr = new T(e);
    if(dataPtr == nullptr) {
        throw NodeException ("Memoria no disponible, creando nodo");
    }
}

template <class T>
Node<T>:: ~Node() {
    delete dataPtr;
}

template <class T>
T& Node<T>::getData() const {
    if(dataPtr == nullptr) {
        throw NodeException("Dato no disponible en memoria, getData");
    }
    return *dataPtr;
}

template <class T>
T* Node<T>::getDataPtr() const {
    return dataPtr;
}

template <class T>
Node<T>*& Node<T>::getRight() {
    return right;
}

template <class T>
Node<T>*& Node<T>::getLeft() {
    return left;
}

template <class T>
void Node<T>::setData(T e) {
    if(dataPtr == nullptr) {
        dataPtr = new T;
        if(dataPtr == nullptr) {
            throw NodeException ("Memoria no disponible, setData");
        }
    }
    *dataPtr = e;
}

template <class T>
void Node<T>::setDataPtr(T* p) {
    dataPtr = p;
}

template <class T>
void Node<T>::setRight(Node<T>*& p) {
    right = p;
}

template <class T>
void Node<T>::setLeft(Node<T>*& p) {
    left = p;
}

//template <class T>
//std::string Node<T>::toString()
//{
//    std::string result;

//    result = dataPtr;

//    return result;
//}

template <class T>
class AvlTree {
    private:
        Node<T>* root;

        void copyAll(const AvlTree<T>&);
        void insertData(Node<T>*&, T&);
        Node<T>*& findData(T&, Node<T>*&);
        Node<T>*& deleteData(Node<T>*&, T&);
        T& retrieve(Node<T>*&, Node<T>*&);

        Node<T>*& getLowest(Node<T>*&); //Cambiar a Lowest
        Node<T>*& getBiggest(Node<T>*&); //Cambiar a Biggest

        void parsePostOrderToDelete(Node<T>*&);

        void parsePreOrder(Node<T>*&);
        void parseInOrder(Node<T>*&);
        void parsePostOrder(Node<T>*&);

        T& retrieveInOrder(Node<T>*&, T&, int&);
        void deleteTheMinInOrder(Node<T>*&);
        void decreaseIndexInOrder(Node<T>*&, T&, int&);
        void replaceInOrder(Node<T>*&, T&, T&, int&);

        void writeParseInOrder(Node<T>*&, std::fstream&);

        unsigned getHeight(Node<T>*&);

        int getBalanceFact(Node<T>*&);

        void simpleLeftRot(Node<T>*&);
        void simpleRightRot(Node<T>*&);
        void doubleLeftRot(Node<T>*&);
        void doubleRightRot(Node<T>*&);

        void doBalancing(Node<T>*&);

    public:
        AvlTree();
        AvlTree(const AvlTree&);
        ~AvlTree();

        bool isEmpty();
        void insertData(T&);
        void deleteData(T&);

        Node<T>*& findData(T&);

        T& retrieve(Node<T>*&);

        bool isLeaf(Node<T>*&);

        void parsePreOrder();
        void parseInOrder();
        void parsePostOrder();

        T& retrieveInOrder(T&, int&); //Se le pasa la signal del mainwindow
        void deleteTheMinInOrder();
        void decreaseIndexInOrder(T&, int&);
        void replaceInOrder(T&, T&, int&);

        void writeParseInOrder(std::fstream&);


        unsigned getHeight();
        long unsigned int getHeightLeft();
        long unsigned int getHeightRight();

        void deleteAll();
        AvlTree& operator = (const AvlTree&);

};

///Implementación
template <class T>
void AvlTree<T>::copyAll(const AvlTree<T>&) {

}

template <class T>
void AvlTree<T>::insertData(Node<T>*& r, T& e) {
    if(r == nullptr) { ///Inserta como hoja (está balanceada)
        if((r = new Node<T>(e)) == nullptr) {
            throw AvlTreeException("Memoria no disponible, insertData");
        }
    } else {   ///Busca subárbol para insertar
        if(e < r->getData()) {
            insertData(r->getLeft(), e);
        } else {
            insertData(r->getRight(), e);
        }
        ///Aquí sale de la recursividad (ruta de inserción, de regreso)
        doBalancing(r);
    }
}

template <class T>
Node<T>*& AvlTree<T>::findData(T& e, Node<T>*& r) {
    if(r == nullptr) {
        throw AvlTreeException("No existe el dato, findData");
    }

    if(e == r->getData()) {
        return r;
    }

    if(e < r->getData()) {
        return findData(e, r->getLeft());
    } else {
        return findData(e, r->getRight());
    }
}

template <class T>
Node<T>*& AvlTree<T>::deleteData(Node<T>*& r, T &e) {
    if(r == nullptr) {
        return r;
    } else if(e < r->getData()) {
        r->setLeft(deleteData(r->getLeft(), e));
    } else if(e > r->getData()) {
        r->setRight(deleteData(r->getRight(), e));
    } else {
        //Case 1: No child
        if(isLeaf(r)) {
            delete r;
            r = nullptr;
        } else if (r->getLeft() == nullptr) { //Case 2: One child
            Node<T> *temp = r;
            r = r->getRight();
            delete temp;
        } else if(r->getRight() == nullptr) {
            Node<T> *temp = r;
            r = r->getLeft();
            delete temp;
        } else { //Case 3: two children
            Node<T> *temp = getLowest(r->getRight());
            r->setData(temp->getData());
            r->setRight(deleteData(r->getRight(), temp->getData()));
        }
    }
    return r;
}

template <class T>
T& AvlTree<T>::retrieve(Node<T>*& p, Node<T>*& r) {
    if(r == nullptr or p == nullptr) {
        throw AvlTreeException("Insuficiencia de datos, retrieve");
    }
    return p->getData();
}

template <class T>
Node<T>*& AvlTree<T>::getLowest(Node<T>*& r) {
    if(r == nullptr) {
        return r;
    }

    if(r->getLeft() == nullptr) {
        return r;
    } else {
        return getLowest(r->getLeft());
    }
}

template <class T>
Node<T>*& AvlTree<T>::getBiggest(Node<T>*& r) {
    if(r == nullptr) {
        return r;
    }

    if(r->getRight() == nullptr) {
        return r;
    } else {
        return getBiggest(r->getRight());
    }
}

template <class T>
void AvlTree<T>::parsePostOrderToDelete(Node<T>*& r) {
    if(r == nullptr) {
        return;
    }
    parsePostOrderToDelete(r->getLeft());
    parsePostOrderToDelete(r->getRight());
    delete r;
}


template <class T>
void AvlTree<T>::parsePreOrder(Node<T>*& r) {
    if(r == nullptr) {
        return;
    }
    std::cout << r->getData().toString() << ", ";
    parsePreOrder(r->getLeft());
    parsePreOrder(r->getRight());
}

template <class T>
void AvlTree<T>::parseInOrder(Node<T>*& r) {
    if(r==nullptr) {
        return;
    }
    parseInOrder(r->getLeft());
    std::cout << r->getData().toString() << ", ";
    parseInOrder(r->getRight());
}

template <class T>
void AvlTree<T>::parsePostOrder(Node<T>*& r ){
    if(r == nullptr) {
        return;
    }
    parsePostOrder(r->getLeft());
    parsePostOrder(r->getRight());
    std::cout << r->getData().toString() << ", ";
}

template <class T>
T& AvlTree<T>::retrieveInOrder(Node<T>*& r, T& e, int &s) {
    if(r == nullptr) {
        return e;
    }
    retrieveInOrder(r->getLeft(), e, s);
    //Para nuevo correo
    if(s == 4) {
        if(r->getData().getDireccion() == 0) {
            return r->getData();
        }
    } else if(s == 1 || s == 9 || s == 10) {
        if(r->getData().getClave() == e.getClave()) {
            return r->getData();
        }
    }
    retrieveInOrder(r->getRight(), e, s);
}

template <class T>
void AvlTree<T>::deleteTheMinInOrder(Node<T>*& r) {
    deleteTheMinInOrder(r->getLeft());
    if(r->getData().getDireccion() == 0) {
        deleteData(r->getData());
    }
    deleteTheMinInOrder(r->getRight());
}

template <class T>
void AvlTree<T>::decreaseIndexInOrder(Node<T>*& r, T &e, int &s) {
    int p, k;
    T data;
    if(r == nullptr) {
        return;
    }
    decreaseIndexInOrder(r->getLeft(), e, s);
    if(s == 4) {
        if(r->getData().getDireccion() > 0) {
            p = r->getData().getDireccion() - 1;
            r->getData().setDireccion(p);
        }
    } else if(s == 1 || s == 9 || s == 10) {
        std::cout << r->getData().toString() << " " << e.toString() << std::endl;
        if(r->getData().getDireccion() > e.getDireccion()) {
            k = r->getData().getClave();
            p = r->getData().getDireccion() - 1;
            data.setClave(k);
            data.setDireccion(p);
            std::cout << "mmm" << std::endl;
            r->setData(data);
        } else {
            std::cout << "no" << std::endl;
        }
    }
    decreaseIndexInOrder(r->getRight(), e, s);
}

template <class T>
void AvlTree<T>::replaceInOrder(Node<T>*& r, T &e, T& newE, int &s) {
    int p(9), new_e(newE.getClave());
    if(r == nullptr) {
        return;
    }
    replaceInOrder(r->getLeft(), e, newE, s);
    if(s == 1 || s == 10) {
        if(r->getData().getClave() == e.getClave()) {
            r->getData().setDireccion(p);
        }
    } else if(s == 4 || s == 9) {
        if(r->getData().getClave() == e.getClave()) {
            r->getData().setClave(new_e);
            r->getData().setDireccion(p);
        }
    }
    replaceInOrder(r->getRight(), e, newE, s);
}

template <class T>
void AvlTree<T>::writeParseInOrder(Node<T>*& r, std::fstream &filePath) {
    if(r==nullptr) {
        return;
    }
    writeParseInOrder(r->getLeft(), filePath);
    std::cout << "wpio:" << r->getData().toString() << ", ";
    filePath.write((char*)&r->getData(), sizeof(r->getData()));
    writeParseInOrder(r->getRight(), filePath);
}

template <class T>
unsigned AvlTree<T>::getHeight(Node<T>*& r) {
    if(r == nullptr) {
        return 0;
    }
    unsigned lH(getHeight(r->getLeft()));
    unsigned rH(getHeight(r->getRight()));

    /*if(lH > rH) {
        return lH+1;
    } else{
        return rH+1;
    }*/

    return(lH > rH ? lH : rH) + 1;
}

template <class T>
AvlTree<T>::AvlTree() : root(nullptr) {
}

template <class T>
AvlTree<T>::AvlTree(const AvlTree<T>& t) : AvlTree() {
    copyAll(t);
}

template <class T>
AvlTree<T>::~AvlTree() {
    deleteAll();
}

template <class T>
bool AvlTree<T>::isEmpty() {
    return root == nullptr;
}

template <class T>
void AvlTree<T>::insertData(T& e) {
    insertData(root, e);
}

template <class T>
void AvlTree<T>::deleteData(T &e) {
    deleteData(root, e);
}

template <class T>
Node<T>*& AvlTree<T>::findData(T& e) {
    findData(e, root);
}

template <class T>
T& AvlTree<T>::retrieve(Node<T>*& p) {
    retrieve(p, root);
}

template <class T>
bool AvlTree<T>::isLeaf(Node<T>*& r) {
    if(r == nullptr){
        return false;
    }
    return r->getLeft() == nullptr and r->getRight() == nullptr;
    //return r != nullptr and r->getLeft() == r->getRight();
}

template <class T>
void AvlTree<T>::parsePreOrder() {
    parsePreOrder(root);
}

template <class T>
void AvlTree<T>::parseInOrder() {
    parseInOrder(root);
}

template <class T>
void AvlTree<T>::parsePostOrder() {
    parsePostOrder(root);
}

template <class T>
T& AvlTree<T>::retrieveInOrder(T &e, int &s) {
    retrieveInOrder(root, e, s);
}

template <class T>
void AvlTree<T>::deleteTheMinInOrder() {
    deleteTheMinInOrder(root);
}

template <class T>
void AvlTree<T>::decreaseIndexInOrder(T &e, int &s) {
    decreaseIndexInOrder(root, e, s);
}

template <class T>
void AvlTree<T>::replaceInOrder(T &e, T &newE, int &s) {
    replaceInOrder(root, e, newE, s);
}

template <class T>
void AvlTree<T>::writeParseInOrder(std::fstream &filePath) {
    writeParseInOrder(root, filePath);
}


template <class T>
unsigned AvlTree<T>::getHeight() {
    return getHeight(root);
}

template <class T>
long unsigned int AvlTree<T>::getHeightLeft() {
    return getHeight(root->getLeft());
}

template <class T>
long unsigned int AvlTree<T>::getHeightRight() {
    return getHeight(root->getRight());
}

template <class T>
void AvlTree<T>::deleteAll() {
    parsePostOrderToDelete(root);
}

template <class T>
AvlTree<T>& AvlTree<T>::operator=(const AvlTree& t) {
    deleteAll();
    copyAll(t);
    return *this;
}

//AVL

template< class T>
int AvlTree<T>::getBalanceFact(Node<T>*& r) {
    return getHeight(r->getRight()) - getHeight(r->getLeft());
}

template<class T>
void AvlTree<T>::simpleLeftRot(Node<T>*& r) {
    Node<T>* aux1(r->getRight());
    Node<T>* aux2(aux1->getLeft());

    r->setRight(aux2);
    aux1->setLeft(r);
    r = aux1;
}

template<class T>
void AvlTree<T>::simpleRightRot(Node<T>*& r) {
    Node<T>* aux1(r->getLeft());
    Node<T>* aux2(aux1->getRight());

    r->setLeft(aux2);
    aux1->setRight(r);
    r = aux1;
}

template<class T>
void AvlTree<T>::doubleLeftRot(Node<T>*& r) {
    simpleRightRot(r->getRight());
    simpleLeftRot(r);
}

template<class T>
void AvlTree<T>::doubleRightRot(Node<T>*& r) {
    simpleLeftRot(r->getLeft());
    simpleRightRot(r);
}

template<class T>
void AvlTree<T>::doBalancing(Node<T>*& r) {
    switch(getBalanceFact(r)) {
	case 2: ///Aplicar rotación a la izquierda
		if(getBalanceFact(r->getRight()) == 1) { //Signo coincide aplicar rotacion simple
			//std::cout << "RSI: " << r->getData() << std::endl;
			simpleLeftRot(r);
		} else { ///Signo distinto aplicar rotación doble
			//std::cout << "RDI: " << r->getData() << std::endl;
			doubleLeftRot(r);
		}
		break;
	case -2: ///Aplicar rotación a la derecha
		if(getBalanceFact(r->getLeft()) == -1) { //Signo coincide aplicar rotacion simple
			//std::cout << "RSD: " << r->getData() << std::endl;
			simpleRightRot(r);
		} else { ///Signo distinto aplicar rotación doble
			//std::cout << "RDD: " << r->getData() << std::endl;
			doubleRightRot(r);
		}
		break;
    }
}

class Indice {
private:
    int direccion;

public:
	int clave;
    Indice() {
        clave = 0;
        direccion = 0;
    }

    int getClave() {
        return clave;
    }

    int getDireccion() {
        return direccion;
    }

    void setClave(int& key) {
        clave = key;
    }

    void setDireccion(const int& dir) {
        direccion = dir;
    }

    bool operator != (const Indice& index) {
        return clave != index.clave;
    }

    bool operator == (const Indice& index) {
        return clave == index.clave;
    }

    bool operator < (const Indice& index) {
        return clave < index.clave;
    }

    bool operator > (const Indice& index) {
        return clave > index.clave;
    }

    Indice& operator = (const Indice& index) {
        clave = index.clave;
        direccion = index.direccion;
        return *this;
    }

    std::string toString() {
        std::string str;

        str = std::to_string(clave);
        str += "|";
        str += std::to_string(direccion);

        return str;
    }
};

void buscarIndice() {
	int id;
	string nombreArchivo;
	std::cout << "Creando archivo de indices..." << endl;
	std::cin.get();
	std::cin.get();
	cout << "Archivo creado exitosamente." << endl;
	std::cin.get();
	std::cin.get();
	std::cout << "Escriba el identificador del correo que desea buscar: ";
	std::cin >> id;
	busquedaPorIndices(nombreArchivo, id);
}

// Crear archivo de Indices y escribir sobre el
void busquedaPorIndices(string &nombreArchivo, int &id) {
	Indice index;
	Indice auxIndex;
	AvlTree <Indice> indexTree;
	AvlTree <Indice> indexAvlTree;
	Correo auxCorreo;
	string infoCorreo;
	string str;
	string temp;
	ifstream Copia;
	int llave;
	try {
		Copia.open("indices.dat", ios_base::in | ios_base::binary);
		if(Copia.fail()) {
			cerr << "Error al crear el archivo de indices" << endl;
			exit(1);
		}
		auxIndex.clave = id;
		if(indexAvlTree.isEmpty()) {
			cout << "Vacio" << endl;
		} else {
			cout << "Lleno" << endl;
		}
		
		cout << "PRUEBA" << endl;
		indexAvlTree.parseInOrder();
		
		try {
			llave = indexAvlTree.retrieve(indexAvlTree.findData(auxIndex)).clave;
			cout << "Llave: " << llave << endl;
			
			Copia.seekg((llave-1)*sizeof(Correo), ios_base::beg);
			Copia.read((char *)&auxCorreo, sizeof(auxCorreo));
			cout << "Identificador: " << auxCorreo.identificador << endl;
			cout << "Asunto: " << auxCorreo.asunto << endl;
			cout << "Fecha: " << auxCorreo.fechaCreacion.dia << "/" << auxCorreo.fechaCreacion.mes << "/" << auxCorreo.fechaCreacion.anio << endl;
			cout << "Hora: " << auxCorreo.horaCreacion.hora << ":" << auxCorreo.horaCreacion.minuto << endl;
		} catch(exception ex) {
			cout << "El dato no existe en el arbol primario.";
		}
		
	} catch(Correo *e){
		throw "Error al abrir el archivo de indices.";
		Copia.close();
	}
}

// Leer desde el archivo de Indices
Indice busquedaPorIndices(int &id) {
	Indice index;
	string nombreArchivo = "indices.dat";
	ifstream leer(nombreArchivo, ios_base::in | ios_base::binary);
	int totalRegistros;
	int tamArchivo;
	int contador(1);
	
	leer.seekg(0, ios_base::end);
	tamArchivo = leer.tellg();
	leer.seekg(0, ios_base::beg);
	
	totalRegistros = tamArchivo/sizeof(Indice);
	
	if(leer.fail()) {
		cerr << "Error al abrir el archivo." << endl;	
	} else {
		while(contador <= totalRegistros) {
			leer.seekg((contador-1) * sizeof(Indice), ios_base::beg);
			leer.read((char *)&index, sizeof(index));
			
			if(index.clave == id) {
				cout << index.clave << endl;
				return index;
			}
			contador++;
		}
		return index;
	}
}
