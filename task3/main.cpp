#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "header.h"

using namespace std;

enum Airplanes { //перечислимый тип, ввод с консоли числа
	CREATE_PLANE = 1,  
	PLANES_FOR_TOWN,
	TOWNS_FOR_PLANE,
	PLANES,
	EXIT
};

int main(){
    system("chcp 65001");
    cout <<	"1 - Создание самолета" << endl;
	cout << "2 - Вывод самолетов, которые пролетают через определенный город" << endl;
	cout <<	"3 - Вывод всех городов, которые пролетает определенный самолет" << endl;
	cout <<	"4 - Отображение всех самолетов и их маршрутов" << endl;
	cout <<	"5 - Завершение работы программы" << endl;
    vector<string> towns; //вектор городов
	vector<string> planes; //вектор самолетов
	map <string, vector <string>> route; //вектор остановок 
    int command;
    while(true){
        cout << "Введите комманду: ";
        
        cin >> command;
        if (command == Airplanes::CREATE_PLANE){
            createPlane(towns, planes, route);
        } else if(command == Airplanes::PLANES_FOR_TOWN){
            planesForTown(route);
        } else if(command == Airplanes::TOWNS_FOR_PLANE){
            townsForPlane(route);
        } else if(command == Airplanes::PLANES){
            if(!route.empty()){
                displayPlanes(planes, route);
            } else{
                cout << "Вы не добавили ни одного самолета" << endl;
            }
            
        } else if(command == Airplanes::EXIT){
            break;
        } else {
            cout << "Неизвестная команда, попробуйте еще раз!" << endl;
            cin >> command;
        }
    }
}