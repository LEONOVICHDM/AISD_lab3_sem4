#include <iostream>
#include <fstream>
#include<string>

using namespace std;

const int INF = 999999;

template<class T1, class T2>
struct duo {
	T1 data1;
	T2 data2;

	duo(T1 data1, T2 data2) : data1(data1), data2(data2) {};

	friend ostream& operator<<(ostream& out, duo& duo) {
		out << "[" << duo.data1 << " ; " << duo.data2 << "]";
		return out;
	}

	friend istream& operator>>(istream& in, duo& pair) {
		in >> pair.data1;
		in >> pair.data2;
		return in;
	}

	friend bool operator==(duo& p1, duo& p2) {
		return p1.data1 == p2.data1 && p1.data2 == p2.data2;
	}
};

template<class T>
class gleipnir {
private:
	struct item {
		T data;
		item* prev_item;
		item* next_item;

		item(T data, item* prev_item = nullptr, item* next_item = nullptr) :
			data(data), prev_item(prev_item), next_item(next_item) {};


	};

	item* m_head;
	item* m_tail;
	int m_size;

	void remove_solo();

	gleipnir(item*);

	gleipnir(gleipnir<T>*);

public:
	void push_back(T data);

	void push_front(T data);

	void insert(T data, int position);

	T* get();

	T* get_by_index(int position);

	int get_index(T data);

	void remove_back();

	void remove_front();

	void remove(int position);

	bool find(T* data);

	pair<gleipnir, gleipnir> split(int position);

	int size();

	bool empty();

	gleipnir();

	gleipnir(const gleipnir<T>& list);

	~gleipnir();

	friend ostream& operator<<(ostream& out, const gleipnir& list) {
		item* cur_item = list.m_head;
		if (cur_item != nullptr) {
			while (cur_item != list.m_tail && cur_item != nullptr) {
				out << cur_item->data << " ";
				cur_item = cur_item->next_item;
			}
			if (list.m_tail != nullptr)
				out << list.m_tail->data;
		}
		else {
			out << "list is empty!";
		}
		return out;
	}
};

template<class T>
gleipnir<T>::gleipnir() : m_head(nullptr), m_tail(m_head), m_size(0) {};

template<class T>
gleipnir<T>::gleipnir(const gleipnir<T>& list) : m_head(list.m_head), m_tail(list.m_tail), m_size(list.m_size) {};

template<class T>
gleipnir<T>::gleipnir(item* item) :m_size(1) {
	gleipnir<T>::item* cur_item = m_head = item;
	while (cur_item->next_item != nullptr) {
		cur_item = cur_item->next_item;
		m_size++;
	}
	m_tail = cur_item;
}

template<class T>
gleipnir<T>::gleipnir(gleipnir<T>* list) : m_head(list->m_head), m_tail(list->m_tail), m_size(list->m_size) {};

template<class T>
gleipnir<T>::~gleipnir() {
	item* save_item = m_head;
	while (save_item != m_tail && save_item != nullptr) {
		save_item = m_head->next_item;
		m_head = save_item;
	}
}

template<class T>
void gleipnir<T>::push_back(T data) {
	item* new_item = new item(data);
	if (m_head == nullptr) {
		m_head = m_tail = new_item;
	}
	else {
		new_item->prev_item = m_tail;
		m_tail->next_item = new_item;
		m_tail = new_item;
	}
	m_size++;
};

template<class T>
void gleipnir<T>::push_front(T data) {
	item* new_item = new item(data);
	if (m_head == nullptr) {
		m_head = m_tail = new_item;
	}
	else {
		new_item->next_item = m_head;
		m_head->prev_item = new_item;
		m_head = new_item;
	}
	m_size++;
}

template<class T>
void gleipnir<T>::insert(T data, int position) {
	if (position <= m_size - 1) {
		if (position == 0) push_front(data);
		else if (position == m_size) push_back(data);
		else {
			item* cur_item = m_head;
			for (int i = 0; i < position; i++) {
				cur_item = cur_item->next_item;
			}
			item* new_item = new item(data);
			cur_item->prev_item->next_item = new_item;
			new_item->prev_item = cur_item->prev_item;
			new_item->next_item = cur_item;
			cur_item->prev_item = new_item;
		}
		m_size++;
	}
}

template<class T>
int gleipnir<T>::size() { return m_size; }

template<class T>
void gleipnir<T>::remove_solo() {
	delete m_head;
	m_head = m_tail = nullptr;
	m_size--;
}

template<class T>
void gleipnir<T>::remove_back() {
	if (m_size > 1) {
		m_tail = m_tail->prev_item;
		delete m_tail->next_item;
		m_size--;
	}
	else if (m_size == 1)
		remove_solo();
}

template<class T>
void gleipnir<T>::remove_front() {
	if (m_size > 1) {
		m_head = m_head->next_item;
		delete m_head->prev_item;
	}
	else if (m_size == 1)
		remove_solo();
	m_size--;
}

template<class T>
void gleipnir<T>::remove(int position) {
	if (position <= m_size - 1) {
		if (position == 0) remove_front();
		if (position == m_size - 1) remove_back();
		else {
			item* cur_item = m_head;
			for (int i = 0; i < position; i++) {
				cur_item = cur_item->next_item;
			}
			cur_item->prev_item->next_item = cur_item->next_item;
			cur_item->next_item->prev_item = cur_item->prev_item;
			delete cur_item;
		}
		m_size--;
	}
}

template<class T>
pair<gleipnir<T>, gleipnir<T>> gleipnir<T>::split(int position) {
	if (m_size == 2 && position == 0) {
		gleipnir<T> list1, list2;
		list1.push_back(m_head->data);
		list2.push_back(m_tail->data);
		return pair<gleipnir<T>, gleipnir<T>>(list1, list2);
	}
	else if (-1 < position < m_size - 1) {
		item* cur_item = m_head;
		gleipnir<T> list1, list2;
		for (int i = 0; i <= position; i++) {
			list1.push_back(cur_item->data);
			cur_item = cur_item->next_item;
		}
		while (cur_item != nullptr) {
			list2.push_back(cur_item->data);
			cur_item = cur_item->next_item;
		}
		return pair<gleipnir<T>, gleipnir<T>>(list1, list2);
	}
	else {
		return pair<gleipnir<T>, gleipnir<T>>(gleipnir<T>(), gleipnir<T>());
	}
}

template<class T>
bool gleipnir<T>::empty() {
	return (m_head == m_tail == nullptr);
}

template<class T>
bool gleipnir<T>::find(T* data) {
	item* cur_item = m_head;
	while (cur_item != nullptr) {
		if (cur_item->data == *data) return true;
		cur_item = cur_item->next_item;
	}
	return false;
}


template<class T>
T* gleipnir<T>::get() {
	return &m_head->data;
}

template<class T>
T* gleipnir<T>::get_by_index(int position) {

	if (-1 < position < m_size) {
		item* cur_item = m_head;
		for (int i = 0; i < position; i++) {
			cur_item = cur_item->next_item;
		}
		return &cur_item->data;
	}

	return nullptr;
}

template<class T>
int gleipnir<T>::get_index(T data) {
	item* cur_item = m_head;
	unsigned long int index = 0;
	while (cur_item) {
		if (cur_item->data == data)
			return index;
		cur_item = cur_item->next_item;
		index++;
	}
	return -1;
}

gleipnir<pair<char, int>> list_count_symbols(string str) {
	gleipnir<pair<char, int>> list;
	while (!str.empty()) {
		char symbol = str[0];
		str.erase(0, 1);
		int count = 1;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == symbol) {
				str.erase(i, 1);
				i = 0;
				count++;
			}
		}
		list.push_back(pair<char, int>(symbol, count));
	}
	return list;
}

int count_sumbols(string str, char symbol) {
	int count = 0;
	for (int i = 0; i < str.length(); i++)
		if (str[i] == symbol) count++;
	return count;
}

struct adjacency_matrix {
	gleipnir<string>* cities;
	int** matrix;

	friend ostream& operator<<(ostream& out, adjacency_matrix& m) {
		if (m.cities) {
			out << "cities: " << *m.cities << endl << "matrix:\n";
			for (int i = 0; i < m.cities->size(); i++) {
				for (int j = 0; j < m.cities->size(); j++) {
					if (m.matrix[i][j] == INF)
						out << "inf ";
					else
						out << m.matrix[i][j] << " ";
				}
				out << endl;
			}
		}
		else
			out << "no cities!";
	}

	adjacency_matrix() : cities(nullptr), matrix(nullptr) {};
};

string read(ifstream& file) {
	string s = "", str;

	while (!file.eof()) {
		getline(file, s);
		str += s + '\n';
		s = "";
	}
	return str;
}

gleipnir<string> get_cities(string& s) {
	gleipnir<string> cities;
	string city = "";
	for (int i = 0; i < s.length(); i++) {
		if (city != "" && s[i] == ';' && !cities.find(&city)) {
			cities.push_back(city);
			city = "";
		}
		else if (cities.find(&city))
			city = "";
		else if ((s[i] < '0' || s[i] > '9') && s[i] != '\n' && s[i] != ';' && s[i] != '*')
			city += s[i];
	}
	return cities;
}

int road_value_converter(string s) {
	if (s == "*")
		return INF;
	else
		return stoi(s);
}

int** get_road_value(string& s, adjacency_matrix& adj_matrix) {
	string city1 = "", city2 = "", road1 = "", road2 = "";
	int delimiter_count = 0;

	int** matrix = new int* [adj_matrix.cities->size()];
	for (int i = 0; i < adj_matrix.cities->size(); i++)
		matrix[i] = new int[adj_matrix.cities->size()];

	for (int i = 0; i < adj_matrix.cities->size(); i++) {
		for (int j = 0; j < adj_matrix.cities->size(); j++)
			matrix[i][j] = INF;
	}

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ';') {
			delimiter_count++;
			continue;
		}
		if (s[i] == '\n') {
			matrix[adj_matrix.cities->get_index(city1)][adj_matrix.cities->get_index(city2)] = road_value_converter(road1);
			matrix[adj_matrix.cities->get_index(city2)][adj_matrix.cities->get_index(city1)] = road_value_converter(road2);
			city1 = city2 = road1 = road2 = "";
			delimiter_count++;
			continue;
		}
		if (delimiter_count % 4 == 0)
			city1 += s[i];
		else if (delimiter_count % 4 == 1)
			city2 += s[i];
		else if (delimiter_count % 4 == 2)
			road1 += s[i];
		else if (delimiter_count % 4 == 3 && s[i] != '\n')
			road2 += s[i];

	}
	return matrix;
}

void make_adjacency_matrix(ifstream& file, adjacency_matrix& adj_matrix) {
	string s = read(file);
	gleipnir<string> cities = get_cities(s);
	int** matrix = new int* [cities.size()];
	for (int i = 0; i < cities.size(); i++)
		matrix[i] = new int[cities.size()];

	adj_matrix.cities = &cities;
	adj_matrix.matrix = get_road_value(s, adj_matrix);

}

void Floyd_Warshall_alg(adjacency_matrix& adj_matrix) {
	int from, to, weight;
	for (int i = 0; i < adj_matrix.cities->size(); i++) {
		for (int j = 0; j < adj_matrix.cities->size(); j++) {
			if (i == j) continue;
			for (int k = 0; k < adj_matrix.cities->size(); k++) {
				if (j == k) continue;
				if (adj_matrix.matrix[i][j] > adj_matrix.matrix[i][k] + adj_matrix.matrix[k][j])
					adj_matrix.matrix[i][j] = adj_matrix.matrix[i][k] + adj_matrix.matrix[k][j];
			}
		}
	}


	for (int i = 0; i < adj_matrix.cities->size(); i++) {
		for (int j = 0; j < adj_matrix.cities->size(); j++) {
			if (adj_matrix.matrix[i][j] == INF)
				cout << "inf ";
			else
				cout << adj_matrix.matrix[i][j] << " ";
		}
		cout << endl;
	}

}

int get_min_path_value(adjacency_matrix* adj_matrix, string from, string to) {
	return adj_matrix->matrix[adj_matrix->cities->get_index(from)][adj_matrix->cities->get_index(to)];
}

int main() {

	ifstream file("data.txt");

	if (!file.is_open()) {
		cout << "file is broken!\n";
		exit(0);
	}

	adjacency_matrix adj_matrix;
	make_adjacency_matrix(file, adj_matrix);

	Floyd_Warshall_alg(adj_matrix);

	file.close();

	return 0;
}