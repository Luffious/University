#include <iostream>
#include <string>
#include <ctime>
#include <map>

using namespace std;

class Visitor
{
private:
    int _appearence_probability;
    int _duration_of_visit;
    int _pre_entry_probability;
protected:
    Visitor(int _appearence_probability, int _duration_of_visit, int _pre_entry_probability) :
        _appearence_probability(_appearence_probability),
        _duration_of_visit(_duration_of_visit),
        _pre_entry_probability(_pre_entry_probability)
    {}
public:
    int getDurationOfVisit() {
        return _duration_of_visit;
    }
};

class Child : public Visitor 
{
public:
    Child(int _appearence_probability, int _duration_of_visit, int _pre_entry_probability) :
        Visitor(_appearence_probability, _duration_of_visit, _pre_entry_probability)
    {}
};

class Adult : public Visitor 
{
public:
    Adult(int _appearence_probability, int _duration_of_visit, int _pre_entry_probability) :
        Visitor(_appearence_probability, _duration_of_visit, _pre_entry_probability)
    {}
};

class OldMan : public Visitor
{
public:
    OldMan(int _appearence_probability, int _duration_of_visit, int _pre_entry_probability) :
        Visitor(_appearence_probability, _duration_of_visit, _pre_entry_probability)
    {}
};

class Null : public Visitor
{
public:
    Null(int _appearence_probability, int _duration_of_visit, int _pre_entry_probability) :
        Visitor(_appearence_probability, _duration_of_visit, _pre_entry_probability)
    {}
};

class Queue
{
private:
    int _amount_of_visitors = 0;
    Visitor** _p_visitor;
    map <int, string> _queue_type;
    map <int, string> :: iterator _queue_iterator;
    int _time = 0;
    int _temp_time = 0;
    int _visitors_total_amount = 0;
    int _visitors_in_amount = 0;
    void _department() {
        _queue_type = generateQueue();
        int _temp_i = 0;
        while (_time + _p_visitor[_temp_i]->getDurationOfVisit() <= 540) {
            _queue_iterator = _queue_type.begin();
            for (int i = 0; i < _amount_of_visitors; i++) {
                if (_queue_iterator->second == "pre entry") {
                    int _temp = _p_visitor[i]->getDurationOfVisit();
                    if (_time + _temp <= 540) {
                        _time += _temp;
                        _temp_time += _temp;
                        if (_temp != 0) {
                            cout << "Время: " << _time << endl;
                            _visitors_in_amount++;
                        }
                    }
                    else
                    {
                        _temp_i = i;
                        i = 10;
                        break;
                    }
                }
                advance(_queue_iterator, 1);
                if (_temp_time >= 10 && _time + _p_visitor[_temp_i]->getDurationOfVisit() <= 540) {
                    _queue_type = generateQueue();
                    _temp_time = 0;
                }
            }
            _queue_iterator = _queue_type.begin();
            for (int i = 0; i < _amount_of_visitors; i++) {
                if (_queue_iterator->second == "live") {
                    int _temp = _p_visitor[i]->getDurationOfVisit();
                    if (_time + _temp <= 540) {
                        _time += _temp;
                        _temp_time += _temp;
                        if (_temp != 0) {
                            cout << "Время: " << _time << endl;
                            _visitors_in_amount++;
                        }
                    }
                    else
                    {
                        _temp_i = i;
                        i = 10;
                        break;
                    }
                }
                advance(_queue_iterator, 1);
                if (_temp_time >= 10 && _time + _p_visitor[_temp_i]->getDurationOfVisit() <= 540) {
                    _queue_type = generateQueue();
                    _temp_time = 0;
                }
            }
        }
    }
    void _statistics() {
        cout << "Посетителей всего: " << _visitors_total_amount << ", из них прошло: " << _visitors_in_amount << "." << endl;
    }
public:
    map <int, string> generateQueue() {
        map <int, string> queue_type;
        for (int i = 0; i < _amount_of_visitors; i++) {
            int child_queue_randomizer = 1 + rand() % 100;
            int adult_queue_randomizer = 1 + rand() % 100;
            int old_man_queue_randomizer = 1 + rand() % 100;
            if (child_queue_randomizer <= 5) {
                adult_queue_randomizer = 100;
                old_man_queue_randomizer = 100;
                _p_visitor[i] = new Child(5, 5 + rand() % 6, 10);
                int queue_type_randomizer = 1 + rand() % 100;
                if (queue_type_randomizer <= 10) {
                    queue_type.insert(pair <int, string>(i, "pre entry"));
                    cout << "Появился ребёнок с длительностью визита " << _p_visitor[i]->getDurationOfVisit() 
                         << " минут, попавший в очередь по записи." << endl;
                }
                else {
                    queue_type.insert(pair <int, string>(i, "live"));
                    cout << "Появился ребёнок с длительностью визита " << _p_visitor[i]->getDurationOfVisit()
                        << " минут, попавший в живую очередь." << endl;
                }
                _visitors_total_amount++;
            }
            if (adult_queue_randomizer <= 30) {
                old_man_queue_randomizer = 100;
                _p_visitor[i] = new OldMan(30, 7 + rand() % 3, 5);
                int queue_type_randomizer = 1 + rand() % 100;
                if (queue_type_randomizer <= 5) {
                    queue_type.insert(pair <int, string>(i, "pre entry"));
                    cout << "Появился старик с длительностью визита " << _p_visitor[i]->getDurationOfVisit()
                        << " минут, попавший в очередь по записи." << endl;
                }
                else {
                    queue_type.insert(pair <int, string>(i, "live"));
                    cout << "Появился старик с длительностью визита " << _p_visitor[i]->getDurationOfVisit()
                        << " минут, попавший в живую очередь." << endl;
                }
                _visitors_total_amount++;
            }
            if (old_man_queue_randomizer <= 40) {
                _p_visitor[i] = new Adult(40, 2 + rand() % 4, 70);
                int queue_type_randomizer = 1 + rand() % 100;
                if (queue_type_randomizer <= 70) {
                    queue_type.insert(pair <int, string>(i, "pre entry"));
                    cout << "Появился взрослый с длительностью визита " << _p_visitor[i]->getDurationOfVisit();
                    if (_p_visitor[i]->getDurationOfVisit() <= 4) {
                        cout << " минуты, попавший в очередь по записи." << endl;
                    }
                    else {
                        cout << " минут, попавший в очередь по записи." << endl;
                    }
                }
                else {
                    queue_type.insert(pair <int, string>(i, "live"));
                    cout << "Появился взрослый с длительностью визита " << _p_visitor[i]->getDurationOfVisit();
                    if (_p_visitor[i]->getDurationOfVisit() <= 4) {
                        cout << " минуты, попавший в живую очередь." << endl;
                    }
                    else {
                        cout << " минут, попавший в живую очередь." << endl;
                    }
                }
                _visitors_total_amount++;
            }
            if (child_queue_randomizer > 5 && adult_queue_randomizer > 30 && old_man_queue_randomizer > 40) {
                _p_visitor[i] = new Null(0, 0, 0);
                queue_type.insert(pair <int, string>(i, "null"));
            }
        }
        return queue_type;
    }
    Queue(int _amount_of_visitors)    
    {
        this->_amount_of_visitors = _amount_of_visitors;
        _p_visitor = new Visitor * [_amount_of_visitors];
        _department();
        _statistics();
    }
};

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    Queue Queue(10);
}
