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

typedef struct
{
    int minuto;
    int hora;

} Hora;

typedef struct
{

    int dia;
    int mes;
    int anio;

} Fecha;

typedef struct
{

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
void shellSort(Correo *, int);

Correo Correo1;
Fecha fecha;
Hora hora;

int main()
{

    bool continuarPrograma = true;
    do
    {
        switch(elegirOpcion())
        {
        case 1:
            system("CLS");
            ingresaCorreo();
            pausa();
            break;
        case 2:
            system("CLS");
            mostrarCorreo();
            pausa();
            break;
        case 3:
            system("CLS");
            buscarCorreo();
            pausa();
            break;
        case 4:
            system("CLS");
            eliminarCorreo();
            pausa();
            break;
        case 5:
            system("CLS");
            modificarCorreo();
            pausa();
            break;
        case 6:
            system("CLS");
            exportaraCsv();
            pausa();
            break;
        case 7:
            system("CLS");
            mostrarArchivoSeguridad();
            pausa();
            break;
        case 8:
        	system("CLS");
        	modificarArchivoSeguridad();
        	pausa();
        	break;
        case 9:
        	system("CLS");
        	eliminarArchivoSeguridad();
        	pausa();
        	break;
        case 10:
            system("CLS");
            exportaraDat();
            pausa();
            break;
        case 11:
            system("CLS");
            mostrarArchivoDat();
            pausa();
            break;
        case 12:
			system("CLS");
			busquedaEnMemoria();
			pausa();
			break;
        case 13:
            continuarPrograma = false;
            break;

        default:
            cout << endl;
            cout << "Opcion Invalida..." << endl;
            cout << "Intentelo de nuevo.";
            cin.get();
            cin.get();
        }
    }
    while(continuarPrograma);
    return 0;
}

void pausa()
{

    cout << "Presiona una tecla para continuar..." << endl;
    cin.ignore();
    getchar();
}

int elegirOpcion()
{
    int opcion;
    system("CLS");
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
    cout << "13. Salir" << endl;
    cout << "Opcion: ";
    cin >> opcion;
    cin.clear();
    return opcion;
}

void ingresaCorreo()
{
    ofstream archivo;
    string contenido;
    archivo.open("Correos.txt", ios::out| ios::in | ios::binary);
    if(!archivo.is_open() )
    {
        archivo.open("Correos.txt", ios::out);
        if( ! archivo.good() )
        {
            cerr << "Error al crear el archivo... abortando" << endl;
            return;
        }
    }
    cout << "Escribe los datos del correo: " << endl << endl;
    cout << "ID: " << endl;
    cin >> Correo1.identificador;
    while(Correo1.identificador <= 0)
    {
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

void consiguehorayfecha()
{
    time_t tiempo = time(0);
    struct tm *tiempoAhora = localtime(&tiempo);
    Correo1.horaCreacion.hora=tiempoAhora->tm_hour;
    Correo1.horaCreacion.minuto=tiempoAhora->tm_min;
    Correo1.fechaCreacion.anio=tiempoAhora->tm_year+1900;
    Correo1.fechaCreacion.mes=tiempoAhora->tm_mon+1;
    Correo1.fechaCreacion.dia=tiempoAhora->tm_mday;
}

void imprimirCorreo()
{
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

void mostrarCorreo()
{
    ifstream Archivo("Correos.txt", ios::in | ios::binary);
    bool encontrado = false;
    if (Archivo.fail())
    {
        cerr << "Error en el archivo, no se puede acceder" << endl;
    }
    else
    {
        while (!Archivo.eof())
        {
            Archivo.read((char*) &Correo1, sizeof (Correo));
            if (Archivo.eof()){
            	break;
			}
            if (Correo1.identificador != 0)
            {
                cout << endl;
                imprimirCorreo();
                encontrado = true;
            }
        }

    }
    Archivo.close();
    if (!encontrado)
    {
        cout << "No Hay elementos" << endl;
    }
}

void buscarCorreo()
{
    int opc;
    cout << "\t\t\tMENU" << endl;
    cout << endl;
    cout << "1. Buscar por ID" << endl;
    cout << "2. Buscar por remitente " << endl;
    cout << "3. Atras" << endl;
    cout << "Seleccione opcion: ";
    cin >> opc;
    cin.clear();

    if(opc==1)
    {
        ifstream Archivo("Correos.txt", ios::in | ios::binary);
        int x;
        cout << "Escribe el ID" << endl;
        cin >> x;
        if(Archivo.is_open())
        {
            int buscar = (x-1)*sizeof(Correo);
            Archivo.seekg(buscar);
            Archivo.read((char*) &Correo1,sizeof(Correo));
            if(Correo1.identificador != 0)
            {
                imprimirCorreo();
            }
            else
            {
                cout << "No hay elementos " << endl;
            }

        }
        else
        {
            cerr << "Error al abrir el archivo" << endl;
        }
        Archivo.close();
    }
    if(opc==2)
    {
        string remitente;
        bool encontrado = false;
        cin.ignore();
        cout << "Escribe el remitente: " << endl;
        getline(cin,remitente);
        ifstream Archivo("Correos.txt", ios::in | ios::binary);
        if(Archivo.is_open())
        {
            while (!Archivo.eof())
            {
                Archivo.read((char*) &Correo1, sizeof (Correo));

                if (Archivo.eof()){
                	break;
				}
                if (Correo1.remitente == remitente)
                {
                    cout << "Correo encontrado: "<< endl;
                    imprimirCorreo();
                    encontrado = true;
                }
            }
            if(encontrado==false)
            {
                cout << "No se encontraron coincidencias " << endl;
            }
        }

        else
        {
            cerr << "Error al abrir el archivo" << endl;
        }
        Archivo.close();
    }
    if(opc == 3){
    	main();
	}
}

void modificarCorreo()
{
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
    if(x==1)
    {
        ofstream archivo;
        ifstream Archivo("Correos.txt", ios::in | ios::binary);
        if (Archivo.fail())
        {
            cerr << "Error al abrir el archivo" << endl;
        }

        archivo.open("Correos.txt", ios::out| ios::in | ios::binary);
        if(!archivo.is_open() )
        {
            archivo.open("Correos.txt", ios::out);
            if( ! archivo.good() )
            {
                cerr << "Error al abrir el archivo" << endl;
                return;
            }
        }
        cout << "Ingresa el ID del correo a modificar: " << endl;
        cin >> id;
        while(id <= 0)
        {
            cerr << "ID no valido \n Ingrese un ID valido" << endl;
            cin >> id;
        }
        while (!Archivo.eof())
        {
            Archivo.read((char*) &Correo1, sizeof (Correo));
            if (Archivo.eof()){
            	break;
			}

            if (Correo1.identificador != 0 and Correo1.identificador == id)
            {
                cout << endl;
                imprimirCorreo();
                encontrado = true;

            }
        }
        if((encontrado = false))
        {
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
    if(x==2)
    {
        int opc;
        string remitente;
        ofstream archivo;
        ifstream Archivo("Correos.txt", ios::in | ios::binary);
        if (Archivo.fail())
        {
            cerr << "Error al abrir el archivo" << endl;
        }
        cin.ignore();
        cout << "Ingresa el remitente del correo a modificar: " << endl;
        getline(cin,remitente);
        int z(0);
        while (!Archivo.eof())
        {
            Archivo.read((char*) &Correo1, sizeof (Correo));
            z++;

            if (Archivo.eof()){
            	break;
			}
            if (Correo1.remitente == remitente)
            {
                imprimirCorreo();
                cout << "Se encontro una coincidencia " << endl;
                cout << "Quiere modificar este correo? si=1 no =9: " << endl;
                cin >> opc;
                if(opc==1)
                {
                    archivo.open("Correos.txt", ios::out | ios::in | ios::binary);
                    if(!archivo.is_open() )
                    {
                        archivo.open("Correos.txt", ios::out);
                        if( ! archivo.good() )
                        {
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
                }
                else
                {
                    cerr << "Este Correo no se modifico... " << endl;
                    pausa();
                }
            }
        }
        archivo.close();
        Archivo.close();
    }
    if(x == 3){
    	main();
	}
}

void eliminarCorreo()
{
    int op;
    cout << "\t\t\tMENU" << endl;
    cout << endl;
    cout << "1. Eliminar por ID " << endl;
    cout << "2. Eliminar por remitente " << endl;
    cout << "3. Atras" << endl;
    cout << "Seleccione opcion: ";
    cin >> op;
    if(op==1)
    {
        ofstream archivoaEliminar;
        ifstream Archivo("Correos.txt", ios::in | ios::binary);
        Correo Correo2;
        int x,opc;

        cout << "Escribe el ID correo que quieres eliminar: " << endl;
        cin >> x;
        if(Archivo.is_open())
        {
            int buscar = (x-1)*sizeof(Correo);
            Archivo.seekg(buscar);
            Archivo.read((char*) &Correo1,sizeof(Correo));
            if(Correo1.identificador != 0)
            {
                imprimirCorreo();
                pausa();
                cout << "Estas seguro de que quieres eliminar este correo? si=1 no =9: " << endl;
                cin >> opc;
                if(opc==1)
                {
                    archivoaEliminar.open("Correos.txt", ios::out| ios::in | ios::binary);
                    if(!archivoaEliminar.is_open() )
                    {
                        archivoaEliminar.open("Correos.txt", ios::out);
                        if( ! archivoaEliminar.good() )
                        {
                            cerr << "Error al abrir el archivo" << endl;
                            return;
                        }
                    }
                    Correo2.identificador=0;
                    archivoaEliminar.seekp((x-1)*sizeof(Correo1), ios::beg);
                    archivoaEliminar.write((char *) &Correo2, sizeof(Correo1));
                    archivoaEliminar.close();
                    cout << "Correo eliminado." << endl;
                }
                else
                {
                    cout << "El Correo no se elimino... " << endl;

                    return;
                }
            }
            else
            {
                cout << "No hay elementos " << endl;
            }
        }
        else
        {
            cerr << "Error al abrir el archivo" << endl;
        }
        Archivo.close();
    }
    if(op==2)
    {
        ofstream archivoaEliminar;
        ifstream Archivo("Correos.txt", ios::in | ios::binary);
        Correo Correo2;
        int opc;
        string remitente;
        cin.ignore();
        cout << "Escribe el remitente del correo a eliminar: " << endl;
        getline(cin,remitente);
        if(Archivo.is_open())
        {
            int z(0);
            while (!Archivo.eof())
            {
                Archivo.read((char*) &Correo1, sizeof (Correo));
                z++;

                if (Archivo.eof()){
                	break;
				}
                if (Correo1.remitente == remitente)
                {
                    imprimirCorreo();
                    cout << "Se encontro una coincidencia " << endl;
                    cout << "Estas seguro de que quieres eliminar este correo? si=1 no =9: " << endl;
                    cin >> opc;
                    if(opc==1)
                    {
                        archivoaEliminar.open("Correos.txt", ios::out| ios::in | ios::binary);
                        if(!archivoaEliminar.is_open() )
                        {
                            archivoaEliminar.open("Correos.txt", ios::out);
                            if( ! archivoaEliminar.good() )
                            {
                                cerr << "Error al abrir el archivo" << endl;
                                return;
                            }
                        }
                        Correo2.identificador=0;
                        archivoaEliminar.seekp((z-1)*sizeof(Correo1), ios::beg);
                        archivoaEliminar.write((char *) &Correo2, sizeof(Correo1));
                        archivoaEliminar.close();
                        cout << "Correo eliminado." << endl;
                    }
                    else
                    {
                        cout << "Este Correo no se elimino... " << endl;
                        pausa();
                    }
                }
            }
        }
        else
        {
            cerr << "Error al abrir el archivo" << endl;
        }
        Archivo.close();
    }
    if(op == 3){
    	main();
	}
}

void exportaraCsv()
{
    ifstream Archivo("Correos.txt", ios::in | ios::binary);
    string nombreArchivo;
    bool encontrado = false;
    if (!Archivo.good()){
    	cout << "Error al intentar abrir el archivo base para hacer la copia de seguridad." << endl;
	}
    else
    {
        fflush(stdin);
        cout << "Ingresa el Nombre del archivo donde desea gurdar la copia :" << endl;
        getline(cin, nombreArchivo);
        if (nombreArchivo == "")
        {
            cout << "Se ha presionado enter sin capturar ningun nombre para el archivo." << endl;
            cout << "Se creara un archivo con el nombre 'seguridad.csv'" << endl;
            nombreArchivo = "seguridad";
        }
        nombreArchivo = nombreArchivo+".csv";

        ofstream file(nombreArchivo.c_str(), ios::in | ios::trunc |ios::out);
        if (!file.good()){
        	cerr << "El archivo para guardar la copia de seguridad no se puede abrir" << endl;
		}
        else
        {
            while (!Archivo.eof())
            {
                Archivo.read((char*) &Correo1, sizeof (Correo));
                if (Archivo.eof())
                    break;
                if (Correo1.identificador != 0)
                {
                    encontrado = true;

                    file << Correo1.identificador << delimitador << Correo1.remitente << delimitador
                         << Correo1.destinatario << delimitador << Correo1.copiaCarbon << delimitador
                         << Correo1.copiaCarbonCiega << delimitador << Correo1.asunto << delimitador
                         << Correo1.contenido << delimitador << Correo1.fechaCreacion.dia << delimitador
                         << Correo1.fechaCreacion.mes << delimitador <<Correo1.fechaCreacion.anio << delimitador
                         << Correo1.horaCreacion.hora << delimitador << Correo1.horaCreacion.minuto << delimitador << endl;
                }

            }
            if (encontrado == false){
            	cout << "No Hay elementos" << endl;
			}
            else{
            	cout << "Archivo creado con exito" << endl;
			}
        }
        file.close();
    }
    Archivo.close();
}

void mostrarArchivoSeguridad()
{
	std::string temp;
	bool elementos = false;
	string nombreArchivo;

	cout << "Ingrese el nombre del archivo que desea leer: ";
	cin.clear();
	cin.ignore();
	getline(cin,nombreArchivo);
	nombreArchivo = nombreArchivo + ".csv";
	ifstream Archivo(nombreArchivo.c_str());
	if(Archivo.fail()){
		cerr << "No existe tal archivo, o ha sido movido de la carpeta del .csv" << endl;
	}
	else
	{
	    cout << "Mostrando archvo de seguridad: " << endl;
		while(!Archivo.eof())
		{

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

			if(Correo1.identificador != 0)
			{
				imprimirInformacion();
				elementos = true;
			}
		}
	}
	if(elementos == false)
		cout << "No hay elementos" << endl;

	Archivo.close();
}

void imprimirInformacion()
{
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

void modificarArchivoSeguridad()
{
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
	if(!Archivo.good()){
		cerr << "Error al intentar abrir el archivo base para hacer la copia de seguridad." << endl;
	}
	else
	{
		if(!Archivo.good()){
			cerr << "El archivo para guardar la copia de seguridad no se puede abrir" << endl;
		}
		else
		{
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

			while(!Archivo.eof())
            {
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
				if(idModificar == stoi(ID))
                {
					Temp << ID << delimitador << REMITENTE<< delimitador
						 << DESTINATARIO << delimitador << COPIACARBON << delimitador
						 << COPIACARBONCIEGA << delimitador <<  ASUNTO<< delimitador
						 << CONTENIDO << delimitador << Correo1.fechaCreacion.dia << delimitador
						 << Correo1.fechaCreacion.mes << delimitador <<Correo1.fechaCreacion.anio << delimitador
						 << Correo1.horaCreacion.hora << delimitador << Correo1.horaCreacion.minuto << delimitador << endl;
				}
				else
				{
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

void eliminarArchivoSeguridad()
{

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
	if(!Archivo.good()){
		cerr << "Error al intentar abrir el archivo base para hacer la copia de seguridad." << endl;
	}
	else
	{
		if(!Archivo.good()){
			cerr << "El archivo para guardar la copia de seguridad no se puede abrir" << endl;
		}
		else
		{
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

void exportaraDat()
{
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
    if(Copia.is_open()){
        Archivo.open("Correos.txt",ios::in | ios::binary);
        if(Archivo.good()){
            while(!Archivo.eof()){
                if(Archivo.eof()){
                    break;
                }
                Archivo.read((char *)&Correo1, sizeof(Correo));
                Copia.write((char *)&Correo1, sizeof(Correo));
            }
            cout << "Correo expotado correctamente." << endl;
        }
        else{
            cerr << "Error al abrir el archivo de correos." << endl;
        }
    }
    else{
        cerr << "Error al abir el archivo de datos." << endl;
    }
}

void mostrarArchivoDat()
{
    ifstream Copia;
    string nombreArchivo;
    bool encontrado = false;
    cout << "Digite el nombre del archivo que desea leer: ";
    cin.clear();
    cin.ignore();
    getline(cin,nombreArchivo);
    nombreArchivo = nombreArchivo + ".dat";
    Copia.open(nombreArchivo.c_str(), ios::in | ios::binary);
    if(Copia.fail()){
        cerr << "Error al abir el archivo de datos." << endl;
    }
    else{
        cout << "Mostrando archivo de datos..." << endl;
        while(!Copia.eof()){
            Copia.read((char *)&Correo1, sizeof(Correo));
            if(Copia.eof()){
                break;
            }
            if(Correo1.identificador != 0)
            {
                cout << endl;
                imprimirArchivoDat();
                encontrado = true;
            }
        }
    }
    Copia.close();
    if(!encontrado)
    {
        cout << "No Hay elementos" << endl;
    }
}

void imprimirArchivoDat()
{
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

void busquedaEnMemoria()
{
	Correo Correo1;
	Correo guardaRegistros[1000];
	int i = 0;
	int contador = 1;
	int tamanio;
	string nombreArchivo;
	cout << "Ingrese el nombre del archivo que desea cargar a memoria: ";
	cin.clear();
	cin.ignore();
	getline(cin, nombreArchivo);
	ifstream Archivo;
	nombreArchivo = nombreArchivo + ".txt";
	Archivo.open(nombreArchivo.c_str(), ios_base::in | ios_base::binary);

	if(Archivo.fail()){
		throw "Error al leer el archivo";
		Archivo.close();
	}
	else if(Archivo.is_open()){
		while(!Archivo.eof()){
			Archivo.seekg((contador - 1) * sizeof(Correo1), std::ios_base::beg);
			Archivo.read((char *)&Correo1, sizeof(Correo1));

			if(Correo1.identificador == 0){
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
	for(int i(0); i < tamanio; i++){
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
	shellSort(guardaRegistros, tamanio);
	cout << "Mostrando registros ordenados por remitente: " << endl;
	for(int i(0); i < tamanio; i++){
		cout << "ID: " << guardaRegistros[i].identificador << endl;
		cout << "Remitente: " << guardaRegistros[i].remitente << endl;
		cout << "Destinatario: " << guardaRegistros[i].destinatario << endl;
		cout << "Copia Carbon: " << guardaRegistros[i].copiaCarbon << endl;
		cout << "Copia Carbon Ciega: " << guardaRegistros[i].copiaCarbonCiega << endl;
		cout << "Asunto: " << guardaRegistros[i].asunto << endl;
		cout << "Contenido: " << guardaRegistros[i].contenido << endl;
		cout << endl;
	}

Archivo.close();
}

void shellSort(Correo *guardaRegistros, int tamanio)
{
	std::string str1;
	std::string str2;
	Correo aux;
	for(int gap = tamanio / 2; gap > 0; gap /= 2)
	{
		for(int i = gap; i < tamanio; i += 1)
		{
			for(int j = i-gap; j >= 0; j = j-gap)
			{
				str1 = guardaRegistros[j].remitente;
				str2 = guardaRegistros[j + gap].remitente;

				if(str1 <= str2){
					//if(guardaRegistros[j].contenido >= guardaRegistros[j + gap].email){
						break;
				}
				else{
					aux = guardaRegistros[j];
					guardaRegistros[j] = guardaRegistros[j + gap];
					guardaRegistros[j + gap] = aux;
				}
			}
		}
	}
}
