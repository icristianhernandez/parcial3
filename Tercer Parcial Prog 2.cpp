/*
Este programa simula el trabajo de 3 bombas que llevan etileno de una empresa a otra, tomado como inputs el tiempo de rotación y el estado de las válvulas y mostrando en pantalla los galones, etc

Alumnos: Aron Pernia 32.070.898, Cristian Hernandez 28.481.734.

Fecha: 12/12/2023

cantidad de revisiones: 10
*/
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct {                                   // estado de las bombas
    bool b1 = true, b2 = true, b3 = true;  // bombas
    bool s1 = true, s2 = true, s3 = true;  // bombas dañadas
    bool p1 = false, p2 = false, p3 = false;  // controladores de arranque de presion
} bomba;

string line;                                          // variable para conocer la linea del dato
string temp;                                          // variable para conocer a que dato hace referencia
bool v101, v102, v103, v201, v202, v203;              // booleana de las valvulas
char V101, V102, V103, V201, V202, V203, p1, p2, p3;  // ingreso desde el archivo de texto
int Rotacion = 30;                                    // rango de rotacion
int presion1, presion2, presion3;                     // presion de cada bomba
double cant = 0;                                      // material traspasado
int cantidad;                                         // cantidad hasta la cual se puede llenar
char opcion;                                          // opcion para verificar si desea un limite de llenado
bool Opcion;                                          // opcion en booleano
float i = 0;                                          // variable de iteracion
int j = 1;                                            // variable de iteracion
int k = 0;                                            // variable de iteracion
float precio = 0;                                     // precio del material
char opcion2;                                         // verificador de si el programa utiliza precios o no
float valor;                                          // el valor del material expedido
bool Opcion2;                                         // Booleano de opcion2

bool fromCharSymbolToBool(char symbol) {
    if (symbol == '+') {
        return true;
    } else {
        return false;
    }
}

// funciones de krol de presion de cada bomba
bool p101(bool v101, bool v201) {  // bomba 1
    if (v101 == true and v201 == true and presion1 > 33) {
        presion1--;
    } else if (v101 == true and v201 == true and presion1 < 33) {
        presion1++;
    } else if (v101 == true and v201 == true and presion1 == 33) {
        presion1 = presion1;
    } else if (v101 == true and v201 == false) {
        if (presion1 <= 50) {
            presion1 ++;
        } else {
            presion1 = 50;
        }
    } else if (v101 == false and v101 == false) {
        if (presion1 >= 0) {
            presion1 --;
        } else {
            presion1 = 0;
        }
    }

    return true;
}

bool p102(bool v102, bool v202) {  // bomba 2

    if (v102 == true and v202 == true and presion2 > 33) {
        presion2--;
    } else if (v102 == true and v202 == true and presion2 < 33) {
        presion2++;
    } else if (v102 == true and v202 == true and presion2 == 33) {
        presion2 = presion2;
    } else if (v102 == true and v202 == false) {
        if (presion2 <= 50) {
            presion2++;
        } else {
            presion2 = 50;
        }
    } else if (v101 == false and v101 == false) {
        if (presion2 >= 0) {
            presion2 --;
        } else {
            presion2 = 0;
        }
    }
    return true;
}

bool p103(bool v103, bool v203) {  // bomba 3

    if (v103 == true and v203 == true and presion3 > 33) {
        presion3--;
    } else if (v103 == true and v203 == true and presion3 < 33) {
        presion3++;
    } else if (v103 == true and v203 == true and presion3 == 33) {
        presion3 = presion3;
    } else if (v103 == true and v203 == false) {
        if (presion3 <= 50) {
            presion3 ++;
        } else {
            presion3 = 50;
        }
    } else if (v103 == false and v103 == false) {
        if (presion3 >= 0) {
            presion3 --;
        } else {
            presion3 = 0;
        }
    }
    return true;
}

int main() {
    // verificacion
    while (true) {
        ifstream file("datos.txt");  // Abre el archiVo

        while (getline(file, line)) {  // Lee cada línea del archiVo
            istringstream ss(line);
            ss >> temp;  // Ignora la parte no numérica
            if (temp == "V101:") {
                ss >> V101;
                if (V101 != '+' and V101 != '-') {
                    cout << "Caracter invalido en V101: " << V101 << endl;
                }

            } else if (temp == "V102:") {
                ss >> V102;
                if (V102 != '+' and V102 != '-') {
                    cout << "Caracter invalido en V102: " << V102 << endl;
                }

            } else if (temp == "V103:") {
                ss >> V103;
                if (V103 != '+' and V103 != '-') {
                    cout << "Caracter invalido en V103: " << V103 << endl;
                }
            } else if (temp == "V201:") {
                ss >> V201;
                if (V201 != '+' and V201 != '-') {
                    cout << "Caracter invalido en V201: " << V201 << endl;
                }
            } else if (temp == "V202:") {
                ss >> V202;
                if (V202 != '+' and V202 != '-') {
                    cout << "Caracter invalido en V202: " << V202 << endl;
                }
            } else if (temp == "V203:") {
                ss >> V203;
                if (V203 != '+' and V203 != '-') {
                    cout << "Caracter invalido en V203: " << V203 << endl;
                }
            } else if (temp == "Rotacion:") {
                ss >> Rotacion;
                if (Rotacion <= 0) {
                    cout << "Caracter invalido en Rotacion: " << Rotacion << endl;
                }
            } else if (temp == "p101:") {
                ss >> p1;
                if (p1 != '+' and p1 != '-') {
                    cout << "Caracter invalido en p101: " << V203 << endl;
                }
            } else if (temp == "p102:") {
                ss >> p2;
                if (p2 != '+' and p2 != '-') {
                    cout << "Caracter invalido en p102: " << p102 << endl;
                }
            } else if (temp == "p103:") {
                ss >> p3;
                if (p3 != '+' and p3 != '-') {
                    cout << "Caracter invalido en p103: " << V203 << endl;
                }
            } else if (temp == "=:") {
                ss >> opcion;
                if (opcion != '+' and opcion != '-') {
                    cout << "Caracter invalido en =: : " << V203 << endl;
                }
            } else if (temp == "cantidad:" and opcion == '+') {
                ss >> cantidad;
                if (cantidad <= 0) {
                    cout << "Caracter invalido en cantidad: " << cantidad << endl;
                }
            } else if (temp == "Precio:" and opcion2 == '+') {
                ss >> precio;
                if (precio <= 0) {
                    cout << "Caracter invalido en precio: " << precio << endl;
                }
            } else if (temp == ":=") {
                ss >> opcion2;
                if (opcion2 != '+' and opcion2 != '-') {
                    cout << "Caracter invalido en =: " << opcion2 << endl;
                }
        }}

        file.close();  // cerrar el archivo

        // cambio de char a booleano
        v101 = fromCharSymbolToBool(V101);
        v102 = fromCharSymbolToBool(V102);
        v103 = fromCharSymbolToBool(V103);
        v201 = fromCharSymbolToBool(V201);
        v202 = fromCharSymbolToBool(V202);
        v203 = fromCharSymbolToBool(V203);
        bomba.s1 = fromCharSymbolToBool(p1);
        bomba.s2 = fromCharSymbolToBool(p2);
        bomba.s3 = fromCharSymbolToBool(p3);
        Opcion = fromCharSymbolToBool(opcion);
        Opcion2 = fromCharSymbolToBool(opcion2);

        // condiciones de bombas
        if (bomba.s1 == true and bomba.s2 == true and bomba.s3 == true and v101 == true and v102 == true and v103 == true and v201 == true and v202 == true and v203 == true) {
            if (j == 1) {  // sistema sin bomba 1
            
                bomba.b1 = false;
                bomba.p1 = false;
                
                if (presion2 < 20){
                	bomba.p2 = true;
				}
                if (v102 == true and presion2 < 50 and bomba.s2 == true and bomba.p2 == true) {  // bomba 2
                	bomba.b2 = true;
                    p102(v102, v202);
                } else {
                    bomba.b2 = false;
                    bomba.p2 = false;
                    presion2 --;
                    if (presion2 < 0) {
                        presion2 = 0;
                    }
                }
				
				if (presion3 < 20){
					bomba.p3 = true;
				}
                if (v103 == true and presion3 < 50 and bomba.s3 == true and bomba.p3 == true) {  // bomba 3
                    bomba.b3 = true;
                    p103(v103, v203);
                } else {
                    bomba.b3 = false;
                    bomba.p3 = false;
                    presion3 --;
                    if (presion3 < 0) {
                        presion3 = 0;
                    }
                }
                
                k++; // rotacion
                if (k >= Rotacion) {
                    k = 0;
                    j = 2;
                }
                if (presion1 > 0) {
                    presion1--;
                    if (presion1 <= 0) {
                        presion1 = 0;
                    }
                }
            }

            else if (j == 2) { // sistema sin bomba 2
                bomba.b2 = false;
                bomba.p2 = false;
                if (presion1 < 20){
                	bomba.p1 = true;
				}
                if (v101 == true and presion1 < 50 and bomba.s1 == true and bomba.p1 == true) {  // bomba 1
                    bomba.b1 = true;
                    p101(v101, v201);
                } else {
                    bomba.b1 = false;
                    bomba.p1 = false;
                    presion1 --;
                    if (presion1 < 0) {
                        presion1 = 0;
                    }
                }
                if (presion3 < 20){
                	bomba.p3 = true;
				}
                if (v103 == true and presion3 < 50 and bomba.s3 == true and  bomba.p3 == true) {  // bomba 3
                    bomba.b3 = true;
                    p103(v103, v203);
                } else {
                    bomba.b3 = false;
                    bomba.p3 = false;
                    presion3 --;
                    if (presion3 < 0) {
                        presion3 = 0;
                    }
                }
                
                k++; // rotacion
                if (k >= Rotacion) {
                    k = 0;
                    j = 3;
                }
                if (presion2 > 0) {
                    presion2--;
                    if (presion2 <= 0) {
                        presion2 = 0;
                    }
                }
            } else if (j == 3) {
                // sistema sin bomba 3
                bomba.b3 = false;
                bomba.p3 = false;
                if (presion1 <= 20){
                	bomba.p1 = true;
				}
                if (v101 == true and presion1 < 50 and bomba.s1 == true and bomba.p1 == true) {  // bomba 1
                    bomba.b1 = true;
                    p101(v101, v201);
                } else {
                    bomba.b1 = false;
                    bomba.p1 = true;
                    presion1 --;
                    if (presion1 < 0) {
                        presion1 = 0;
                    }
                }
                
                if (presion2 <= 20){
                	bomba.p2 = true;
				}
                if (v102 == true and presion2 < 50 and bomba.s2 == true) {  // bomba 2
                    bomba.b2 = true;
                    p102(v102, v202);
                } else {
                    bomba.b2 = false;
                    bomba.p2 = false;
                    presion2 --;
                    if (presion2 < 0) {
                        presion2 = 0;
                    }
                }
                
                k++; // rotacion
                if (k >= Rotacion) {
                    k = 0;
                    j = 1;
                }
                if (presion3 > 0) {
                    presion3--;
                    if (presion3 <= 0) {
                        presion3 = 0;
                    }
                }
            }
        } else {  // funcion sin rotacion
			
			if (presion1 <= 20){
				bomba.p1 = true;
			}
            if (v101 == true and presion1 < 50 and bomba.s1 == true and bomba.p1 == true) {  // bomba 1
                bomba.b1 = true;
                p101(v101, v201);
            } else {
                bomba.b1 = false;
                bomba.p1 = false;
                presion1 --;
                if (presion1 < 0) {
                    presion1 = 0;
                }
            }
			
			if (presion2 <= 20){
				bomba.p2 = true;
			}
            if (v102 == true and presion2 < 50 and bomba.s2 == true and bomba.p2 == true) {  // bomba 2
                bomba.b2 = true;
                p102(v102, v202);
            } else {
                bomba.b2 = false;
                bomba.p2 = false;
                presion2 --;
                if (presion2 < 0) {
                    presion2 = 0;
                }
            }
			
			if (presion3 <= 20){
				bomba.p3 = true;
			}
            if (v103 == true and presion3 < 50 and bomba.s3 == true) {  // bomba 3
                bomba.b3 = true;
                p103(v103, v203);
            } else {
                bomba.b3 = false;
                bomba.p3 = false;
                presion3 --;
                if (presion3 < 0) {
                    presion3 = 0;
                }
            }
        }

        // cantidad emitida
        if (bomba.b1 == true and v201 == true) {
            cant += (40.00 / 60.00);
        }
        if (bomba.b2 == true and v202 == true) {
            cant += (40.00 / 60.00);
        }
        if (bomba.b3 == true and v203 == true) {
            cant += (40.00 / 60.00);
        }
        
        valor = cant * precio;

        // colocar en pantalla
        cout << fixed;
        cout.precision(4);
        cout << "presion de la bomba 1: " << presion1 << endl;
        cout << "presion de la bomba 2: " << presion2 << endl;
        cout << "presion de la bomba 3: " << presion3 << endl;
        cout << "Material: " << cant << " galones." << endl << endl;

        cout << "La bomba 1 esta: ";
        if (bomba.b1 == true) {
            cout << "encendida." << endl;
        } else {
            cout << "apagada." << endl;
        }

        cout << "La bomba 2 esta: ";
        if (bomba.b2 == true) {
            cout << "encendida." << endl;
        } else {
            cout << "apagada." << endl;
        }

        cout << "La bomba 3 esta: ";
        if (bomba.b3 == true) {
            cout << "encendida." << endl;
        } else {
            cout << "apagada." << endl;
        }
        
        if (Opcion2 == true){
        	cout<<"El valor del material expedido es: "<<valor<<endl;
		}

        if (Opcion == true and i <= cantidad) {
            i = (cant * 100) / cantidad;
            cout << "El tanque se ha llenado en un: " << i << "%.";
            if (i >= 100) {
                break;
            }
        }

        if (Opcion == true and i <= 100 and i >= 0) {
            cout << endl;
            cout << "|";
            for (int j = 1; j <= i; j++) {
                cout << "*";
            }
            cout << "|" << endl;
        }

        // descanso y cambio de pantalla
        Sleep(1000);
        system("cls");
    }

    return 0;
}
