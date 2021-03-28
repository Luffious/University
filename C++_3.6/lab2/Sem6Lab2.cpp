#include <iostream>
#include <stack>
#include <sstream>
#include <ctime>

using namespace std;

void sumAvMinMax() {
	stack <int> st;
	int amount = 1000;
	int sum = 0;
	int avg = 0;
	int stBoundaries[2];
	stBoundaries[0] = -1000;
	stBoundaries[1] = 1000;
	int max = stBoundaries[0] - 1;
	int min = stBoundaries[1] + 1;
	for (int i = 0; i < amount; i++) {
		st.emplace(stBoundaries[0] + rand() % (stBoundaries[1] - stBoundaries[0] + 1));
		int i_st = st.top();
		sum += i_st;
		if (i_st < min) {
			min = i_st;
		}
		if (i_st > max) {
			max = i_st;
		}
	}
	avg = sum / amount;
	cout << "Первый тест: сумма всех элементов стека = " << sum << ", среднее значение элемента стека = " << avg << ", минимальное значение элемента\n стека = " 
		<< min << ", максимальное значение элемента стека = " << max << "." << endl;
}

void pushPop() {
	stack <string> st;
	int amount = 10;
	cout << "Второй тест: проверка стека st.empty() - ";
	if (st.empty()) {
		cout << "стек пуст. ";
	}
	cout << "Теперь вставляем 10 элементов в стек и выводим его\nс разделителем \";\":" << endl;
	for (int i = 0; i < amount; i++) {
		std::stringstream out;
		out << i + 1;
		st.emplace("Строка " + out.str());
		if (i != amount - 1) {
			cout << st.top() << " ; ";
		}
		else {
			cout << st.top() << endl;
		}
	}
	cout << "Вытаскиваем 5 строк из стека и выведем верхний элемент стека - \"";
	for (int i = 0; i < 5; i++) {
		st.pop();
	}
	cout << st.top() << "\"." << endl;
}

void search() {
	struct People {
		string name;
		string surname;
		string patronymic;
		int day = 0;
		int month = 0;
		int year = 0;
	};
	stack <struct People> st;
	stack <struct People> search_st;
	const int amount = 100;
	const int nsp_amount = 27;
	int wrong_elem = 0;
	People people[amount] = {};
	string names[nsp_amount] = { "Harry", 
		"Bruce", "Cook",
		"Carolyn", "Morgan",
		"Albert", "Walker",
		"Randy", "Reed",
		"Larry", "Barnes",
		"Lois", "Wilson",
		"Jesse", "Campbell",
		"Ernest", "Rogers",
		"Theresa", "Patterson",
		"Henry", "Simmons",
		"Michelle", "Perry",
		"Frank", "Butler",
		"Shirley", "Ross" };
	string surnames[nsp_amount] = { "Brooks",
		"Rachel", "Edwards",
		"Christopher", "Perez",
		"Thomas", "Baker",
		"Sara", "Moore",
		"Chris", "Bailey",
		"Roger", "Johnson",
		"Marilyn", "Thompson",
		"Anthony", "Evans",
		"Julie", "Hall",
		"Paula", "Phillips",
		"Annie", "Hernandez",
		"Dorothy", "Murphy",
		"Alice", "Howard" };
	string pantronymics[nsp_amount] = { "Ruth", 
		"Debra", "Allen",
		"Gerald", "Harris",
		"Raymond", "Carter",
		"Jacqueline", "Torres",
		"Joseph", "Nelson",
		"Carlos", "Sanchez",
		"Ralph", "Clark",
		"Jean", "Alexander",
		"Stephen", "Roberts",
		"Eric", "Long",
		"Amanda", "Scott",
		"Teresa", "Diaz",
		"Wanda", "Thomas" };
	for (int i = 0; i < amount; i++) {
		people[i].month = 1 + rand() % 12;
		people[i].year = 1980 + rand() % (2020 - 1980 + 1);
		if ((people[i].month == 1) or (people[i].month == 3) or (people[i].month == 5) or (people[i].month == 7) or (people[i].month == 8) 
		or (people[i].month == 10) or (people[i].month == 12)) {
			people[i].day = 1 + rand() % 31;
		}
		else if (people[i].month != 2) {
			people[i].day = 1 + rand() % 30;
		}
		else if (people[i].year % 4 == 0) {
			people[i].day = 1 + rand() % 29;
		}
		else {
			people[i].day = 1 + rand() % 28;
		}
		people[i].name = names[rand() % nsp_amount];
		people[i].surname = surnames[rand() % nsp_amount];
		people[i].patronymic = pantronymics[rand() % nsp_amount];
		/*if (people[i].day < 10) {
			cout << people[i].name << " " << people[i].surname << " " << people[i].patronymic << " 0" << people[i].day << "." << people[i].month << "." 
			<< people[i].year << endl;
		}
		else {
			cout << people[i].name << " " << people[i].surname << " " << people[i].patronymic << " " << people[i].day << "." << people[i].month << "." 
			<< people[i].year << endl;
		}*/
		st.emplace(people[i]);
	}
	struct tm cur_time;
	time_t tt = time(NULL);
	errno_t tim;
	tim = localtime_s(&cur_time, &tt);
	while (!st.empty()) {
		People temp = st.top();
		if (((1900 + cur_time.tm_year) - temp.year <= 19) or ((1900 + cur_time.tm_year) - temp.year > 31)) {
			search_st.emplace(st.top());
			st.pop();
		}
		else if ((1900 + cur_time.tm_year) - temp.year == 20) {
			if ((cur_time.tm_mon + 1) < temp.month) {
				search_st.emplace(st.top());
				st.pop();
			}
			else if ((cur_time.tm_mon + 1) == temp.month) {
				if (cur_time.tm_mday < temp.day) {
					search_st.emplace(st.top());
					st.pop();
				}
				else {
					wrong_elem++;
					st.pop();
				}
			}
			else if ((cur_time.tm_mon + 1) > temp.month) {
				wrong_elem++;
				st.pop();
			}
		}
		else if ((1900 + cur_time.tm_year) - temp.year == 31) {
			if ((cur_time.tm_mon + 1) < temp.month) {
				wrong_elem++;
				st.pop();
			}
			else if ((cur_time.tm_mon + 1) == temp.month) {
				if (cur_time.tm_mday < temp.day) {
					wrong_elem++;
					st.pop();
				}
				else {
					search_st.emplace(st.top());
					st.pop();
				}
			}
			else if ((cur_time.tm_mon + 1) > temp.month) {
				search_st.emplace(st.top());
				st.pop();
			}
		}
		else {
			wrong_elem++;
			st.pop();
		}
	}
	cout << "Третий тест: проверка правильности - количество элементов, не подходящих под условие " << wrong_elem 
	<< ", а количество элементов в новом \nотфильтрованном стеке " << search_st.size() << ", что в сумме даёт количество элементов исходного стека." << endl;
}

void sortCheck() {
	cout << "Четвёртый тест: проверяем правильность, сверяя отсортированный стек и отсортированный массив, при этом при совпадении\nзначения элементов "
		<< "прибавляем счётчику 1. В итоге счётчик должен достигнуть количества элементов." << endl;
	stack <int> st;
	const int amount = 1000;
	int stack_to_ar[amount];
	int stBoundaries[2];
	stBoundaries[0] = -1000;
	stBoundaries[1] = 1000;
	for (int i = 0; i < amount; i++) {
		st.emplace(stBoundaries[0] + rand() % (stBoundaries[1] - stBoundaries[0] + 1));
		stack_to_ar[i] = st.top();
	}
	for (int i = 0; i < amount - 1; i++) {
		for (int j = 0; j < amount - i - 1; j++) {
			if (stack_to_ar[j] > stack_to_ar[j + 1]) {
				int temp = stack_to_ar[j];
				stack_to_ar[j] = stack_to_ar[j + 1];
				stack_to_ar[j + 1] = temp;
			}
		}
	}
	stack<int> temp_st;
	while (!st.empty())
	{
		int temp = st.top();
		st.pop();
		while (!temp_st.empty() && temp_st.top() > temp)
		{
			st.push(temp_st.top());
			temp_st.pop();
		}
		temp_st.push(temp);
	}
	st = temp_st;
	int count = 0;
	for (int i = amount - 1; i >= 0; i--) {
		if (temp_st.top() == stack_to_ar[i]) {
			temp_st.pop();
			count++;
		}
	}
	cout << "Счётчик - " << count << ", количество элементов - " << amount << "." << endl;
}

void inversion() {
	stack <int> st;
	stack <int> temp;
	const int amount = 1000;
	int arr[amount];
	int arrBoundaries[2];
	arrBoundaries[0] = -1000;
	arrBoundaries[1] = 1000;
	cout << "Пятый тест: инверсия отсортированного по возрастанию стека без использования итераторов, только push и pop. Сверяем\nпроверкой верхнего" 
		<< " элемента стека до и после инверсии.";
	for (int i = 0; i < amount; i++) {
		arr[i] = arrBoundaries[0] + rand() % (arrBoundaries[1] - arrBoundaries[0] + 1);
	}
	for (int i = 0; i < amount - 1; i++) {
		for (int j = 0; j < amount - i - 1; j++) {
			if (arr[j] < arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < amount; i++) {
		st.push(arr[i]);
	}
	cout << " До инверсии: " << st.top() << ", ";
	for (int i = 0; i < amount; i++) {
		temp.push(st.top());
		st.pop();
	}
	st = temp;
	cout << "после инверсии: " << st.top() << "." << endl;
}

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "rus");
	sumAvMinMax();
	cout << endl;
	pushPop();
	cout << endl;
	search();
	cout << endl;
	sortCheck();
	cout << endl;
	inversion();
	cout << endl;
}