#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;

struct Estudiante {
    int id_estudiante;
    string nombres;
    string apellidos;
    int edad;
    string carrera;
    string direccion;
    string email;
    string telefono;
    int nota_primer_bimestre;
    int nota_segundo_semestre;
};

struct Docente {
    int id_docente;
    string nombre;
    string apellido;
    int edad;
    string tipo_contrato;
    string email;
    string telefono;
    string departamento;
};

struct Materia {
    int id_materia;
    string nombre;
    int creditos;
    string departamento;
    int semestre;
    string tipo;
    string horario;
    string aula;
};

struct Investigacion {
    int id_investigacion;
    string titulo;
    string area_estudio;
    string apellidos_estudiante_autor;
    string apellidos_docente_autor;
    float presupuesto;
    string resultados;
    string estado;
};

void crearArchivoCSVConEncabezado(const string& nombreArchivo, const string& encabezado) {
    ofstream archivo(nombreArchivo.c_str(), ios::out | ios::app);
    
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << ". " << strerror(errno) << endl;
    } else {
        // Mover el puntero al inicio del archivo para verificar si está vacío
        archivo.seekp(0, ios::end);
        size_t size = archivo.tellp();
        
        // Si el archivo está vacío, escribir el encabezado
        if (size == 0) {
            archivo << encabezado << endl;
        }
        
        archivo.close();
        cout << "Archivo creado o verificado: " << nombreArchivo << endl;
    }
}

void menuPrincipal();
void submenu(const string& tipo);
void ingresoDeEstudiante();
void ingresoDeDocente();
void ingresoDeMateria();
void ingresoDeInvestigacion();
void editar(const string& tipo);
void eliminar(const string& tipo);
void mostrarEl(const string& tipo);

// Funciones para guardar registros en archivos .csv
void guardarEstudianteCSV(const Estudiante& estudiante);
void guardarDocenteCSV(const Docente& docente);
void guardarMateriaCSV(const Materia& materia);
void guardarInvestigacionCSV(const Investigacion& investigacion);

void guardarEstudianteCSV(const Estudiante& estudiante) {
    ofstream archivo("estudiantes.csv", ios::app);
    archivo << estudiante.id_estudiante << ","
            << estudiante.nombres << ","
            << estudiante.apellidos << ","
            << estudiante.edad << ","
            << estudiante.carrera << ","
            << estudiante.direccion << ","
            << estudiante.email << ","
            << estudiante.telefono << ","
            << estudiante.nota_primer_bimestre << ","
            << estudiante.nota_segundo_semestre << endl;
    archivo.close();
}

void guardarDocenteCSV(const Docente& docente) {
    ofstream archivo("docentes.csv", ios::app);
    archivo << docente.id_docente << ","
            << docente.nombre << ","
            << docente.apellido << ","
            << docente.edad << ","
            << docente.tipo_contrato << ","
            << docente.email << ","
            << docente.telefono << ","
            << docente.departamento << endl;
    archivo.close();
}

void guardarMateriaCSV(const Materia& materia) {
    ofstream archivo("materias.csv", ios::app);
    archivo << materia.id_materia << ","
            << materia.nombre << ","
            << materia.creditos << ","
            << materia.departamento << ","
            << materia.semestre << ","
            << materia.tipo << ","
            << materia.horario << ","
            << materia.aula << endl;
    archivo.close();
}

void guardarInvestigacionCSV(const Investigacion& investigacion) {
    ofstream archivo("investigaciones.csv", ios::app);
    archivo << investigacion.id_investigacion << ","
            << investigacion.titulo << ","
            << investigacion.area_estudio << ","
            << investigacion.apellidos_estudiante_autor << ","
            << investigacion.apellidos_docente_autor << ","
            << investigacion.presupuesto << ","
            << investigacion.resultados << ","
            << investigacion.estado << endl;
    archivo.close();
}

void mostrarEl(const string& tipo) {
    ifstream archivo;
    string linea;

    if (tipo == "Estudiante") {
        archivo.open("estudiantes.csv");
        cout << "\n--- Lista de Estudiantes ---" << endl;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
    } else if (tipo == "Docente") {
        archivo.open("docentes.csv");
        cout << "\n--- Lista de Docentes ---" << endl;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
    } else if (tipo == "Materia") {
        archivo.open("materias.csv");
        cout << "\n--- Lista de Materias ---" << endl;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
    } else if (tipo == "Investigación") {
        archivo.open("investigaciones.csv");
        cout << "\n--- Lista de Investigaciones ---" << endl;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
    }

    archivo.close();
}

// Funciones para editar y eliminar registros en archivos .csv
void editarEstudianteCSV(int id);
void eliminarEstudianteCSV(int id);
void editarDocenteCSV(int id);
void eliminarDocenteCSV(int id);
void editarMateriaCSV(int id);
void eliminarMateriaCSV(int id);
void editarInvestigacionCSV(int id);
void eliminarInvestigacionCSV(int id);



int main() {
	setlocale(LC_ALL,"spanish");
	crearArchivoCSVConEncabezado("estudiantes.csv", "ID, Nombres, Apellidos, Edad, Carrera, Dirección, Email, Teléfono, Nota Primer Bimestre, Nota Segundo Semestre");
    crearArchivoCSVConEncabezado("docentes.csv", "ID, Nombre, Apellido, Edad, Tipo de Contrato, Email, Teléfono, Departamento");
    crearArchivoCSVConEncabezado("materias.csv", "ID, Nombre, Créditos, Departamento, Semestre, Tipo, Horario, Aula");
    crearArchivoCSVConEncabezado("investigaciones.csv", "ID, Título, Área de Estudio, Apellidos Estudiante Autor, Apellidos Docente Autor, Presupuesto, Resultados, Estado");
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    int opcion;
    do {
        cout << "\n--- Menú Principal ---" << endl;
        cout << "1. Estudiante" << endl;
        cout << "2. Docente" << endl;
        cout << "3. Materia" << endl;
        cout << "4. Investigación" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: submenu("Estudiante"); break;
            case 2: submenu("Docente"); break;
            case 3: submenu("Materia"); break;
            case 4: submenu("Investigación"); break;
            case 5: cout << "Saliendo del programa..." << endl; break;
            default: cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while(opcion != 5);
}

void submenu(const string& tipo) {
    int opcion;
    do {
        cout << "\n--- Submenú " << tipo << " ---" << endl;
        cout << "1. Ingreso" << endl;
        cout << "2. Editar" << endl;
        cout << "3. Eliminar" << endl;
        cout << "4. Mostrar" << endl;
        cout << "5. Volver al Menú Principal" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (tipo == "Estudiante") {
            switch(opcion) {
                case 1: ingresoDeEstudiante(); break;
                case 2: editar(tipo); break;
                case 3: eliminar(tipo); break;
                case 4: mostrarEl(tipo); break;
                case 5: break;
                default: cout << "Opción no válida. Intente de nuevo." << endl;
            }
        } else if (tipo == "Docente") {
            switch(opcion) {
                case 1: ingresoDeDocente(); break;
                case 2: editar(tipo); break;
                case 3: eliminar(tipo); break;
                case 4: mostrarEl(tipo); break;
                case 5: break;
                default: cout << "Opción no válida. Intente de nuevo." << endl;
            }
        } else if (tipo == "Materia") {
            switch(opcion) {
                case 1: ingresoDeMateria(); break;
                case 2: editar(tipo); break;
                case 3: eliminar(tipo); break;
                case 4: mostrarEl(tipo); break;
                case 5: break;
                default: cout << "Opción no válida. Intente de nuevo." << endl;
            }
        } else if (tipo == "Investigación") {
            switch(opcion) {
                case 1: ingresoDeInvestigacion(); break;
                case 2: editar(tipo); break;
                case 3: eliminar(tipo); break;
                case 4: mostrarEl(tipo); break;
                case 5: break;
                default: cout << "Opción no válida. Intente de nuevo." << endl;
            }
        }
    } while(opcion != 5);
}

void ingresoDeEstudiante() {
    Estudiante estudiante;
    cout << "Ingresando nuevo estudiante..." << endl;
    cout << "ID Estudiante: "; cin >> estudiante.id_estudiante;
    cout << "Nombres: "; cin.ignore(); getline(cin, estudiante.nombres);
    cout << "Apellidos: "; getline(cin, estudiante.apellidos);
    cout << "Edad: "; cin >> estudiante.edad;
    cout << "Carrera: "; cin.ignore(); getline(cin, estudiante.carrera);
    cout << "Dirección: "; getline(cin, estudiante.direccion);
    cout << "Email: "; getline(cin, estudiante.email);
    cout << "Teléfono: "; getline(cin, estudiante.telefono);
    cout << "Nota Primer Bimestre: "; cin >> estudiante.nota_primer_bimestre;
    cout << "Nota Segundo Semestre: "; cin >> estudiante.nota_segundo_semestre;
    guardarEstudianteCSV(estudiante); // Guardar en archivo .csv
}

// Función para editar un estudiante en el archivo .csv
void editarEstudianteCSV(int id) {
    ifstream archivo("estudiantes.csv");
    ofstream archivoTemp("temp.csv");
    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;
        vector<string> datos;

        while (getline(ss, dato, ',')) {
            datos.push_back(dato);
        }

        if (datos[0] == to_string(id)) {
                        encontrado = true;
            Estudiante estudiante;
            estudiante.id_estudiante = id;
            estudiante.nombres = datos[1];
            estudiante.apellidos = datos[2];
            estudiante.edad = stoi(datos[3]);
            estudiante.carrera = datos[4];
            estudiante.direccion = datos[5];
            estudiante.email = datos[6];
            estudiante.telefono = datos[7];
            estudiante.nota_primer_bimestre = stoi(datos[8]);
            estudiante.nota_segundo_semestre = stoi(datos[9]);

            int opcion;
            cout << "Seleccione el campo que desea editar:" << endl;
            cout << "1. Nombres" << endl;
            cout << "2. Apellidos" << endl;
            cout << "3. Edad" << endl;
            cout << "4. Carrera" << endl;
            cout << "5. Dirección" << endl;
            cout << "6. Email" << endl;
            cout << "7. Teléfono" << endl;
            cout << "8. Nota Primer Bimestre" << endl;
            cout << "9. Nota Segundo Semestre" << endl;
            cout << "Ingrese su opción: ";
            cin >> opcion;

            switch(opcion) {
                case 1: cout << "Nuevos Nombres: "; cin.ignore(); getline(cin, estudiante.nombres); break;
                case 2: cout << "Nuevos Apellidos: "; getline(cin, estudiante.apellidos); break;
                case 3: cout << "Nueva Edad: "; cin >> estudiante.edad; break;
                case 4: cout << "Nueva Carrera: "; cin.ignore(); getline(cin, estudiante.carrera); break;
                case 5: cout << "Nueva Dirección: "; getline(cin, estudiante.direccion); break;
                case 6: cout << "Nuevo Email: "; getline(cin, estudiante.email); break;
                case 7: cout << "Nuevo Teléfono: "; getline(cin, estudiante.telefono); break;
                case 8: cout << "Nueva Nota Primer Bimestre: "; cin >> estudiante.nota_primer_bimestre; break;
                case 9: cout << "Nueva Nota Segundo Semestre: "; cin >> estudiante.nota_segundo_semestre; break;
                default: cout << "Opción no válida." << endl; return;
            }

            archivoTemp << estudiante.id_estudiante << "," << estudiante.nombres << "," << estudiante.apellidos << "," << estudiante.edad << "," << estudiante.carrera << "," << estudiante.direccion << "," << estudiante.email << "," << estudiante.telefono << "," << estudiante.nota_primer_bimestre << "," << estudiante.nota_segundo_semestre << endl;
        } else {
            archivoTemp << linea << endl;
        }
    }

    archivo.close();
    archivoTemp.close();
    remove("estudiantes.csv");
    rename("temp.csv", "estudiantes.csv");

    if (!encontrado) {
        cout << "Estudiante no encontrado." << endl;
    }
}

// Función para eliminar un estudiante en el archivo .csv
void eliminarEstudianteCSV(int id) {
    ifstream archivo("estudiantes.csv");
    ofstream archivoTemp("temp.csv");
    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;
        vector<string> datos;

        while (getline(ss, dato, ',')) {
            datos.push_back(dato);
        }

        if (datos[0] == to_string(id)) {
            encontrado = true;
        } else {
            archivoTemp << linea << endl;
        }
    }

    archivo.close();
    archivoTemp.close();
    remove("estudiantes.csv");
    rename("temp.csv", "estudiantes.csv");

    if (encontrado) {
        cout << "Estudiante eliminado." << endl;
    } else {
        cout << "Estudiante no encontrado." << endl;
    }
}

void ingresoDeDocente() {
    Docente docente;
    cout << "Ingresando nuevo docente..." << endl;
    cout << "ID Docente: "; cin >> docente.id_docente;
    cout << "Nombre: "; cin.ignore(); getline(cin, docente.nombre);
    cout << "Apellido: "; getline(cin, docente.apellido);
    cout << "Edad: "; cin >> docente.edad;
    cout << "Tipo de Contrato: "; cin.ignore(); getline(cin, docente.tipo_contrato);
    cout << "Email: "; getline(cin, docente.email);
    cout << "Teléfono: "; getline(cin, docente.telefono);
    cout << "Departamento: "; getline(cin, docente.departamento);
    guardarDocenteCSV(docente); // Guardar en archivo .csv
}

// Función para editar un docente en el archivo .csv
void editarDocenteCSV(int id) {
    ifstream archivo("docentes.csv");
    ofstream archivoTemp("temp.csv");
    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;
        vector<string> datos;

        while (getline(ss, dato, ',')) {
            datos.push_back(dato);
        }

        if (datos[0] == to_string(id)) {
            encontrado = true;
            Docente docente;
            docente.id_docente = id;
            docente.nombre = datos[1];
            docente.apellido = datos[2];
            docente.edad = stoi(datos[3]);
            docente.tipo_contrato = datos[4];
            docente.email = datos[5];
            docente.telefono = datos[6];
            docente.departamento = datos[7];

            int opcion;
            cout << "Seleccione el campo que desea editar:" << endl;
            cout << "1. Nombre" << endl;
            cout << "2. Apellido" << endl;
            cout << "3. Edad" << endl;
            cout << "4. Tipo de Contrato" << endl;
            cout << "5. Email" << endl;
            cout << "6. Teléfono" << endl;
            cout << "7. Departamento" << endl;
            cout << "Ingrese su opción: ";
            cin >> opcion;

            switch(opcion) {
                case 1: cout << "Nuevo Nombre: "; cin.ignore(); getline(cin, docente.nombre); break;
                case 2: cout << "Nuevo Apellido: "; getline(cin, docente.apellido); break;
                case 3: cout << "Nueva Edad: "; cin >> docente.edad; break;
                case 4: cout << "Nuevo Tipo de Contrato: "; cin.ignore(); getline(cin, docente.tipo_contrato); break;
                case 5: cout << "Nuevo Email: "; getline(cin, docente.email); break;
                case 6: cout << "Nuevo Teléfono: "; getline(cin, docente.telefono); break;
                case 7: cout << "Nuevo Departamento: "; getline(cin, docente.departamento); break;
                default: cout << "Opción no válida." << endl; return;
            }

            archivoTemp << docente.id_docente << "," << docente.nombre << "," << docente.apellido << "," << docente.edad << "," << docente.tipo_contrato << "," << docente.email << "," << docente.telefono << "," << docente.departamento << endl;
        } else {
            archivoTemp << linea << endl;
        }
    }

    archivo.close();
    archivoTemp.close();
    remove("docentes.csv");
    rename("temp.csv", "docentes.csv");

    if (!encontrado) {
        cout << "Docente no encontrado." << endl;
    }
}

// Función para eliminar un docente en el archivo .csv
void eliminarDocenteCSV(int id) {
    ifstream archivo("docentes.csv");
    ofstream archivoTemp("temp.csv");
    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;
        vector<string> datos;

        while (getline(ss, dato, ',')) {
            datos.push_back(dato);
        }

        if (datos[0] == to_string(id)) {
            encontrado = true;
        } else {
            archivoTemp << linea << endl;
        }
    }

    archivo.close();
    archivoTemp.close();
    remove("docentes.csv");
    rename("temp.csv", "docentes.csv");

    if (encontrado) {
        cout << "Docente eliminado." << endl;
    } else {
        cout << "Docente no encontrado." << endl;
    }
}


void ingresoDeMateria() {
    Materia materia;
    cout << "Ingresando nueva materia..." << endl;
    cout << "ID Materia: "; cin >> materia.id_materia;
    cout << "Nombre: "; cin.ignore(); getline(cin, materia.nombre);
    cout << "Créditos: "; cin >> materia.creditos;
    cout << "Departamento: "; cin.ignore(); getline(cin, materia.departamento);
    cout << "Semestre: "; cin >> materia.semestre;
    cout << "Tipo (Obligatoria, Electiva): "; cin.ignore(); getline(cin, materia.tipo);
    cout << "Horario: "; getline(cin, materia.horario);
    cout << "Aula: "; getline(cin, materia.aula);
    guardarMateriaCSV(materia); // Guardar en archivo .csv
}

// Función para editar campos específicos de una materia en el archivo .csv
void editarMateriaCSV(int id) {
    ifstream archivo("materias.csv");
    ofstream archivoTemp("temp.csv");
    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;
        vector<string> datos;

        while (getline(ss, dato, ',')) {
            datos.push_back(dato);
        }

        if (datos[0] == to_string(id)) {
            encontrado = true;
            Materia materia;
            materia.id_materia = id;
            materia.nombre = datos[1];
            materia.creditos = stoi(datos[2]);
            materia.departamento = datos[3];
            materia.semestre = stoi(datos[4]);
            materia.tipo = datos[5];
            materia.horario = datos[6];
            materia.aula = datos[7];

            int opcion;
            cout << "Seleccione el campo que desea editar:" << endl;
            cout << "1. Nombre" << endl;
            cout << "2. Créditos" << endl;
            cout << "3. Departamento" << endl;
            cout << "4. Semestre" << endl;
            cout << "5. Tipo" << endl;
            cout << "6. Horario" << endl;
            cout << "7. Aula" << endl;
            cout << "Ingrese su opción: ";
            cin >> opcion;

            switch(opcion) {
                case 1: cout << "Nuevo Nombre: "; cin.ignore(); getline(cin, materia.nombre); break;
                case 2: cout << "Nuevos Créditos: "; cin >> materia.creditos; break;
                case 3: cout << "Nuevo Departamento: "; cin.ignore(); getline(cin, materia.departamento); break;
                case 4: cout << "Nuevo Semestre: "; cin >> materia.semestre; break;
                case 5: cout << "Nuevo Tipo: "; cin.ignore(); getline(cin, materia.tipo); break;
                case 6: cout << "Nuevo Horario: "; getline(cin, materia.horario); break;
                case 7: cout << "Nueva Aula: "; getline(cin, materia.aula); break;
                default: cout << "Opción no válida." << endl; return;
            }

            archivoTemp << materia.id_materia << "," << materia.nombre << "," << materia.creditos << "," << materia.departamento << "," << materia.semestre << "," << materia.tipo << "," << materia.horario << "," << materia.aula << endl;
        } else {
            archivoTemp << linea << endl;
        }
    }

    archivo.close();
    archivoTemp.close();
    remove("materias.csv");
    rename("temp.csv", "materias.csv");

    if (!encontrado) {
        cout << "Materia no encontrada." << endl;
    }
}

// Función para eliminar una materia en el archivo .csv
void eliminarMateriaCSV(int id) {
    ifstream archivo("materias.csv");
    ofstream archivoTemp("temp.csv");
    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;
        vector<string> datos;

        while (getline(ss, dato, ',')) {
            datos.push_back(dato);
        }

        if (datos[0] == to_string(id)) {
            encontrado = true;
            // No escribir esta línea en el archivo temporal, efectivamente eliminándola
        } else {
            archivoTemp << linea << endl;
        }
    }

    archivo.close();
    archivoTemp.close();
    remove("materias.csv");
    rename("temp.csv", "materias.csv");

    if (encontrado) {
        cout << "Materia eliminada." << endl;
    } else {
        cout << "Materia no encontrada." << endl;
    }
}


void ingresoDeInvestigacion() {
    Investigacion investigacion;
    cout << "Ingresando nueva investigación..." << endl;
    cout << "ID Investigación: "; cin >> investigacion.id_investigacion;
    cout << "Título: "; cin.ignore(); getline(cin, investigacion.titulo);
    cout << "Área de Estudio: "; getline(cin, investigacion.area_estudio);
    cout << "Apellidos Estudiante Autor (Escribir 'Ninguno' si no aplica): "; getline(cin, investigacion.apellidos_estudiante_autor);
    cout << "Apellidos Docente Autor (Escribir 'Ninguno' si no aplica): "; getline(cin, investigacion.apellidos_docente_autor);
    cout << "Presupuesto: "; cin >> investigacion.presupuesto;
    cout << "Resultados: "; cin.ignore(); getline(cin, investigacion.resultados);
    cout << "Estado (En Proceso, Finalizado): "; getline(cin, investigacion.estado);
    guardarInvestigacionCSV(investigacion); // Guardar en archivo .csv
}

// Función para editar una investigación en el archivo .csv
void editarInvestigacionCSV(int id) {
    ifstream archivo("investigaciones.csv");
    ofstream archivoTemp("temp.csv");
    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;
        vector<string> datos;

        while (getline(ss, dato, ',')) {
            datos.push_back(dato);
        }

        if (datos[0] == to_string(id)) {
            encontrado = true;
            Investigacion investigacion;
            investigacion.id_investigacion = id;
            cout << "Título: "; cin.ignore(); getline(cin, investigacion.titulo);
            cout << "Área de Estudio: "; getline(cin, investigacion.area_estudio);
            cout << "Apellidos Estudiante Autor (Escribir 'Ninguno' si no aplica): "; getline(cin, investigacion.apellidos_estudiante_autor);
            cout << "Apellidos Docente Autor (Escribir 'Ninguno' si no aplica): "; getline(cin, investigacion.apellidos_docente_autor);
            cout << "Presupuesto: "; cin >> investigacion.presupuesto;
            cout << "Resultados: "; cin.ignore(); getline(cin, investigacion.resultados);
            cout << "Estado (En Proceso, Finalizado): "; getline(cin, investigacion.estado);
            archivoTemp << investigacion.id_investigacion << "," << investigacion.titulo << "," << investigacion.area_estudio << "," << investigacion.apellidos_estudiante_autor << "," << investigacion.apellidos_docente_autor << "," << investigacion.presupuesto << "," << investigacion.resultados << "," << investigacion.estado << endl;
        } else {
            archivoTemp << linea << endl;
        }
    }

    archivo.close();
    archivoTemp.close();
    remove("investigaciones.csv");
    rename("temp.csv", "investigaciones.csv");

    if (!encontrado) {
        cout << "Investigación no encontrada." << endl;
    }
}

// Función para eliminar una investigación en el archivo .csv
void eliminarInvestigacionCSV(int id) {
    ifstream archivo("investigaciones.csv");
    ofstream archivoTemp("temp.csv");
    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;
        vector<string> datos;

        while (getline(ss, dato, ',')) {
            datos.push_back(dato);
        }

        if (datos[0] == to_string(id)) {
            encontrado = true;
        } else {
            archivoTemp << linea << endl;
        }
    }

    archivo.close();
    archivoTemp.close();
    remove("investigaciones.csv");
    rename("temp.csv", "investigaciones.csv");

    if (encontrado) {
        cout << "Investigación eliminada." << endl;
    } else {
        cout << "Investigación no encontrada." << endl;
    }
}


void editar(const string& tipo) {
    int id;
    cout << "Ingrese el ID del " << tipo << " a editar: ";
    cin >> id;

    if (tipo == "Estudiante") {
        editarEstudianteCSV(id);
    } else if (tipo == "Docente") {
        editarDocenteCSV(id);
    } else if (tipo == "Materia") {
        editarMateriaCSV(id);
    } else if (tipo == "Investigación") {
        editarInvestigacionCSV(id);
    }
}

void eliminar(const string& tipo) {
    int id;
    cout << "Ingrese el ID del " << tipo << " a eliminar: ";
    cin >> id;

    if (tipo == "Estudiante") {
        eliminarEstudianteCSV(id);
    } else if (tipo == "Docente") {
        eliminarDocenteCSV(id);
    } else if (tipo == "Materia") {
        eliminarMateriaCSV(id);
    } else if (tipo == "Investigación") {
        eliminarInvestigacionCSV(id);
    }
}
