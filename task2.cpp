#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

struct client {
    string ticket;
    int duration;
};

class Queue {
private:
    int NumberOfWindows;
    vector<queue<client>> windows;
    vector<client> visitors;

public:
    Queue(int numWindows): NumberOfWindows(numWindows), windows(numWindows) {}

    void enqueue(int duration, int ticketNumber) {
        string ticket = "T" + to_string(ticketNumber);
        visitors.push_back({ticket, duration});
        cout << ticket << endl;
    }

    void distribute() {
        vector<int> load(NumberOfWindows, 0);

        // Сортировка посетителей по убыванию продолжительности для оптимизации распределения максимальной нагрузки
        sort(visitors.begin(), visitors.end(), [](client &a, client &b) {
            return a.duration > b.duration;
        });

        for (client &v : visitors) {
            int minWindow = distance(load.begin(), min_element(load.begin(), load.end()));
            load[minWindow] += v.duration;
            windows[minWindow].push(v);
        }

        for (int i = 0; i < NumberOfWindows; ++i) {
            cout << "Окно " << i + 1 << " (";
            int time = 0;
            bool NotPrinted = true;
            while (!windows[i].empty()) {
                if (NotPrinted == false){
                    cout << ", ";
                }
                NotPrinted = false;
                client v = windows[i].front(); 
                windows[i].pop();
                cout << v.ticket;
                time += v.duration;
            }
            cout << ") " << time << " минут" << endl;
        }
    }
};

int main() {
    system("chcp 65001");
    int NumberOfWindows;
    cout << "Введите кол-во окон: ";
    cin >> NumberOfWindows;
    Queue queue(NumberOfWindows);

    string command;
    int ticketNumber = 1;
    while (true) {
        cin >> command;
        if (command == "ENQUEUE") {
            int duration;
            cin >> duration;
            queue.enqueue(duration, ticketNumber);
            ticketNumber++;
        } else if (command == "DISTRIBUTE") {
            if (ticketNumber != 1) {
                queue.distribute();
                break;
            } else{
                cout << "Ошибка! Вы не добавили никого в очередь!" << endl;
                break;
            }
        } else if (command == "exit"){
            return 0;
        }
    }
    return 0;
}
