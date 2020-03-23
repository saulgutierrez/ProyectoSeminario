#include <iostream>
#include <string.h>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <vector>
#include <ctime>

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

Correo Correo1;

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
            continuarPrograma = false;
            break;

        default:
            cout << "Opcion Invalida..." << endl;
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
    cout << "10. Salir" << endl;
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
            cout << "Error al crear el archivo... abortando" << endl;
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
        cout << "Error en el archivo, no se puede acceder" << endl;
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
            cout << "Error al abrir el archivo" << endl;
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
            cout << "Error al abrir el archivo" << endl;
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
            cout << "Error al abrir el archivo" << endl;
        }

        archivo.open("Correos.txt", ios::out| ios::in | ios::binary);
        if(!archivo.is_open() )
        {
            archivo.open("Correos.txt", ios::out);
            if( ! archivo.good() )
            {
                cout << "Error al abrir el archivo" << endl;
                return;
            }
        }
        cout << "Ingresa el ID del correo a modificar: " << endl;
        cin >> id;
        while(id <= 0)
        {
            cout << "ID no valido \n Ingrese un ID valido" << endl;
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
            cout << "Error al abrir el archivo" << endl;
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
                            cout << "Error al abrir el archivo" << endl;
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
                    cout << "Este Correo no se modifico... " << endl;
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
                            cout << "Error al abrir el archivo" << endl;
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
            cout << "Error al abrir el archivo" << endl;
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
                                cout << "Error al abrir el archivo" << endl;
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
            cout << "Error al abrir el archivo" << endl;
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
        	cout << "El archivo para guardar la copia de seguridad no se puede abrir" << endl;
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
                         << Correo1.horaCreacion.hora << delimitador << Correo1.horaCreacion.minuto << finRegistro << endl;
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
	string nombreArchivo;
    fflush(stdin);
    cout << "Ingresa el Nombre del archivo que desea leer :" << endl;
    getline(cin, nombreArchivo);
    if (nombreArchivo == "")
    {
        cout << "Se ha presionado enter sin capturar ningun nombre para el archivo." << endl;
        cout << "Se intentara leer un archivo con el nombre 'seguridad.csv'" << endl;
        nombreArchivo = "seguridad";
    }
    nombreArchivo = nombreArchivo+".csv";
    ifstream Archivo(nombreArchivo.c_str());
    string line = "";
    vector <string> datos_csv;
    while(getline(Archivo,line)){
    	stringstream strstr(line);
    	string word = "";
    	while(getline(strstr,word, ';')){
    		datos_csv.push_back(word);
		}
	}
	cout << "Elemento encontrado" << endl;
	cout << "Mostrando..." << endl;
	for(int i = 0; i < datos_csv.size(); i++){
		cout << datos_csv.at(i) << endl;
	}
}

void modificarArchivoSeguridad()
{	
	int idModificar;
	bool encontrado = false;
	int idEliminar;
	string nombreArchivo;
	fflush(stdin);
	cout << "Ingrese el nombre del archivo donde desea modificar un registro: ";
	getline(cin,nombreArchivo);
	nombreArchivo = nombreArchivo + ".csv";
	fstream Temp("temp.csv",ios::out | ios::in | ios::trunc);
	fstream Archivo(nombreArchivo.c_str(), ios::in | ios::trunc | ios::out);
	if(!Archivo.good()){
		cerr << "Error al intentar abrir el archivo base para hacer la copia de seguridad." << endl;
	}
	else
	{
		if(!Archivo.good()){
			cout << "El archivo para guardar la copia de seguridad no se puede abrir" << endl;
		}
		else
		{
			cout << "Ingrese ID asociado a registro a modificar: ";
			cin >> idModificar;
			int buscar = (idModificar-1)*sizeof(Correo);
            Archivo.seekg(buscar);
            Archivo.read((char*)&Correo1,sizeof(Correo));
			if(Correo1.identificador != 0)
			{
				encontrado = true;
				
				Temp.write((char *)&Correo1, sizeof(Correo));
				
				cout << "Registro encontrado !! " << endl;
				cout << "Ingrese nuevos datos: " << endl;
				cout << "Remitente: " << endl;
				cin.clear();
				cin.ignore();
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
				
				Temp.write((char *)&Correo1, sizeof(Correo));
			}
			if(encontrado == false){
				cout << "Elemento no encontrado" << endl;
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
	int idEliminar;
	string nombreArchivo;
	bool encontrado = false;
	fflush(stdin);
	cout << "Ingrese el nombre del archivo donde desea eliminar un registro: ";
	getline(cin,nombreArchivo);
	nombreArchivo = nombreArchivo + ".csv";
	fstream Temp("temp.csv",ios::out | ios::in | ios::trunc);
	fstream Archivo(nombreArchivo.c_str(), ios::in | ios::trunc | ios::out);
	if(!Archivo.good()){
		cerr << "Error al intentar abrir el archivo base para hacer la copia de seguridad." << endl;
	}
	else
	{
		if(!Archivo.good()){
			cout << "El archivo para guardar la copia de seguridad no se puede abrir" << endl;
		}
		else
		{
			cout << "Ingrese ID asociado a registro a eliminar: ";
			cin >> idEliminar;
			int buscar = (idEliminar-1)*sizeof(Correo);
            Archivo.seekg(buscar);
            Archivo.read((char*)&Correo1,sizeof(Correo));
			if(Correo1.identificador != 0)
			{
				encontrado = true;
				Temp.write((char *)&Correo1, sizeof(Correo));
			}
			if(encontrado == false){
				cout << "Elemento no encontrado" << endl;
			}
			else{
				cout << "Registro modificado exitosamente." << endl;
			}
		}
		Temp.close();
	}
	Archivo.close();
	remove(nombreArchivo.c_str());
	rename("temp.csv", nombreArchivo.c_str());
}
