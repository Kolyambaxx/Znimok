#include <iostream>
#include <string>

class Memento;  // Попереднє оголошення для використання у класі Originator

// Об'єкт, для якого буде створюватися знімок
class Originator {
public:
    Originator(const std::string& state) : state(state) {}

    void setState(const std::string& newState) {
        state = newState;
        std::cout << "State set to: " << state << std::endl;
    }

    // Створення знімка поточного стану
    Memento createMemento() const;

    // Відновлення стану знімка
    void restoreMemento(const Memento& memento);

    void showState() const {
        std::cout << "Current state: " << state << std::endl;
    }

private:
    std::string state;
};

// Знімок стану
class Memento {
public:
    friend class Originator;

private:
    Memento(const std::string& state) : state(state) {}

    std::string getState() const {
        return state;
    }

    void setState(const std::string& newState) {
        state = newState;
    }

private:
    std::string state;
};

// Опікун (Caretaker) - зберігає та відновлює знімки станів об'єкта Originator
class Caretaker {
public:
    Caretaker() : memento(nullptr) {}

    ~Caretaker() {
        delete memento;
    }

    void saveState(const Memento& memento);
    Memento* retrieveState();

private:
    Memento* memento;
};

// Реалізація методів класу Originator
Memento Originator::createMemento() const {
    return Memento(state);
}

void Originator::restoreMemento(const Memento& memento) {
    state = memento.getState();
    std::cout << "State restored to: " << state << std::endl;
}

// Реалізація методів класу Caretaker
void Caretaker::saveState(const Memento& memento) {
    delete this->memento;  // Звільнення попереднього знімка, якщо він існує
    this->memento = new Memento(memento);
}

Memento* Caretaker::retrieveState() {
    return memento;
}

int main() {
    Originator originator("Initial State");
    originator.showState();

    Caretaker caretaker;
    caretaker.saveState(originator.createMemento());

    originator.setState("New State");
    originator.showState();

    Memento* savedState = caretaker.retrieveState();
    originator.restoreMemento(*savedState);
    originator.showState();

    delete savedState;

    return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
