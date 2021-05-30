#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

// Сидоров Сергей - 5 вариант

// Структура для хранения узлов
struct GraphVertex
{
    int value, len;
    GraphVertex* adj;
};
 
// Структура для хранения ребра графа (взвешенного)
struct EdgeWithWeight {
    int from_v, to_v, length;
};

// Структура для хранения ребра графа (не взвешенного)
struct EdgeWithoutWeight {
    int from_v, to_v;
};

class DiffGraph
{
    // Метод для выделения нового узла списка смежности (взвешенного)
    GraphVertex* adjListForVertex(int valueue, int length, GraphVertex* heading)
    {
        GraphVertex* newNode = new GraphVertex;
        newNode->value = valueue;
        newNode->len = length;

        // Новый узел должен указывать на текущее направление
        newNode->adj = heading;
 
        return newNode;
    }
    
    // Метод для выделения нового узла списка смежности (не взвешенного)
    GraphVertex* adjListForVertex(int valueue, GraphVertex* heading)
    {
        GraphVertex* newNode = new GraphVertex;
        newNode->value = valueue;
        newNode->len = -1;

        // Новый узел должен указывать на текущее направление
        newNode->adj = heading;
 
        return newNode;
    }
    
    int N;  // Общее кол-во узлов в графе
    int N_EDGES = 0;  // Общее кол-во ребер
    bool* visited;
    vector<vector<int>> adjLists;

public:
    
    bool directed;  // Направленный ли граф
    bool weighted;  // Взвешенный ли граф
    GraphVertex** heading;  // Массив указателей на узлы, для представления списка смежности
    
    EdgeWithoutWeight* edges_no_lengt = nullptr;  // Указатель на массив не взвешенных ребер
    EdgeWithWeight* edges_lengt = nullptr;  // Указатель на массив взвешенных ребер
    
    // Конструктор (для взвешенного)
    DiffGraph(vector<EdgeWithWeight> edges, int n, int N, bool directed)
    {   
        visited = new bool[N];

        edges_lengt = new EdgeWithWeight[n];
        for(int i = 0; i < n; i++){
            edges_lengt[i] = edges[i];
        }
        // Выставляем то, что граф взвешен
        this->weighted = true;

        // Выставляем тип графа
        this->directed = directed;

        // Выделяем память
        heading = new GraphVertex*[N]();
        this->N = N;
        
        // Инициализируем указатели на направления для всех вершин
        for (int i = 0; i < N; i++) {
            heading[i] = nullptr;
        }
 
        // Добавляем ребра направленному графу
        for (unsigned i = 0; i < n; i++)
        {
            int from_v = edges[i].from_v;
            int to_v = edges[i].to_v;
            int length = edges[i].length;
 
            // Вставка в начало
            GraphVertex* newNode = adjListForVertex(to_v, length, heading[from_v]);

            // Указатели направления должны указывать на новый узел
            heading[from_v] = newNode;
            this->N_EDGES++;

            // Если граф не направленный, то каждому направлению создаем ещё и обратное
            if(!this->directed){

                newNode = adjListForVertex(from_v, length, heading[to_v]);

                // Меняем направление, чтобы оно вело на новый узел
                heading[to_v] = newNode;
            }
        }
        if(!this->directed){
            reverseEdges();
        }
        adjLists = adjacencyMat();
    }
    
    // Конструктор (для не взвешенного)
    DiffGraph(vector<EdgeWithoutWeight> edges, int n, int N, bool directed)
    {
        edges_no_lengt = new EdgeWithoutWeight[n];
        for(int i = 0; i < n; i++){
            edges_no_lengt[i] = edges[i];
        }

        // Выставляем то, что граф не взвешен
        this->weighted = false;

        // Выставляем тип графа
        this->directed = directed;

        // Выделяем память
        heading = new GraphVertex*[N]();
        this->N = N;

        // Инициализируем указатели на направления для всех вершин
        for (int i = 0; i < N; i++) {
            heading[i] = nullptr;
        }

        
        // Добавляем ребра направленному графу
        for (unsigned i = 0; i < n; i++)
        {
            int from_v = edges[i].from_v;
            int to_v = edges[i].to_v;
 
            // Вставка в начало
            GraphVertex* newNode = adjListForVertex(to_v, heading[from_v]);

            // Указатели направления должны указывать на новый узел
            heading[from_v] = newNode;

            this->N_EDGES++;

            // Если граф не направленный, то каждому направлению создаем ещё и обратное
            if(!this->directed){

                newNode = adjListForVertex(from_v, heading[to_v]);

                // Меняем направление, чтобы оно вело на новый узел
                heading[to_v] = newNode;
            }
        }
        if(!this->directed){
            reverseEdges();
        }
        adjLists = adjacencyMat();
    }

    // Деструктор
    ~DiffGraph() {
        for (int i = 0; i < N; i++) {
            delete[] heading[i];
        }
        delete[] edges_lengt;
        delete[] edges_no_lengt;
        delete[] heading;
    }

    // Метод для создания обратных направлений неориентированному графу
    void reverseEdges(){
        if(this->weighted){
            vector<EdgeWithWeight> tmp_edges(this->N_EDGES);
            for(int i = 0; i < this->N_EDGES; i++){
                tmp_edges[i] = this->edges_lengt[i];
            }

            // Ищем
            for(int i = 0; i < this->N_EDGES; i++){
                EdgeWithWeight tmp_el = tmp_edges[i];
                for( auto iter = tmp_edges.begin(); iter != tmp_edges.end() - 1; iter++ ){
                    if(( iter->from_v == tmp_el.to_v) && (iter->to_v == tmp_el.from_v)){
                        tmp_edges.erase(iter);
                        break;
                    }
                        
                }
                cout << i;
            }
            
            int tmp_size = tmp_edges.size();
            for(int i = 0; i < tmp_size; i++){
                tmp_edges.push_back({tmp_edges[i].to_v, tmp_edges[i].from_v, tmp_edges[i].length});
            }

            delete[] edges_lengt;
            edges_lengt = new EdgeWithWeight[tmp_edges.size()];
            for(int i = 0; i < tmp_edges.size(); i++){
                edges_lengt[i] = tmp_edges[i];
            }
            this->N_EDGES = tmp_edges.size();

        }else{
            vector<EdgeWithoutWeight> tmp_edges(this->N_EDGES);
            for(int i = 0; i < this->N_EDGES; i++){
                tmp_edges[i] = this->edges_no_lengt[i];
            }

            // Ищем
            for(int i = 0; i < this->N_EDGES; i++){
                EdgeWithoutWeight tmp_el = tmp_edges[i];
                for( auto iter = tmp_edges.begin(); iter != tmp_edges.end() - 1; iter++ ){
                    if(( iter->from_v == tmp_el.to_v) && (iter->to_v == tmp_el.from_v)){
                        tmp_edges.erase(iter);
                        break;
                    }
                        
                }
            }

            int tmp_size = tmp_edges.size();
            for(int i = 0; i < tmp_size; i++){
                tmp_edges.push_back({tmp_edges[i].to_v, tmp_edges[i].from_v});
            }

            delete[] edges_no_lengt;
            edges_no_lengt = new EdgeWithoutWeight[tmp_edges.size()];
            for(int i = 0; i < tmp_edges.size(); i++){
                edges_no_lengt[i] = tmp_edges[i];
            }
            this->N_EDGES = tmp_edges.size();
        }
    }

    // Метод выдачи матрицы смежности
    vector<vector<int>> adjacencyMat(){

        // Создаем двумерный вектор размера NxN (кол-во узлов)
        vector<vector<int>> main_matrix (this->N, vector<int>(this->N, 0));

        // Заполняем матрицу смежности
        if(this->weighted){
            for(int i = 0; i < N; i++){
                GraphVertex* current_node = heading[i];
                while (current_node != nullptr){
                    main_matrix[i][current_node->value] = current_node->len;
                    current_node = current_node->adj;
                }
            }
        }else{
            for(int i = 0; i < N; i++){
                GraphVertex* current_node = heading[i];
                while (current_node != nullptr){
                    main_matrix[i][current_node->value] = 1;
                    current_node = current_node->adj;
                }
            }
        }

        return main_matrix;
    }

    vector<vector<int>> incidenceMat(){
        // Создаем двумерный вектор размера NxM (кол-во узлов x кол-во ребер)
        vector<vector<int>> main_matrix (this->N, vector<int>(this->N_EDGES, 0));

        if(this->weighted){
            for(int i = 0; i < this->N; i++){
                for(int j = 0; j < this->N_EDGES; j++){
                    if(i == edges_lengt[j].from_v){
                        main_matrix[i][j] = 1;
                    }
                    if(i == edges_lengt[j].to_v){
                        main_matrix[i][j] = -1;
                    }
                }
            }
        }else{
            for(int i = 0; i < this->N; i++){
                for(int j = 0; j < this->N_EDGES; j++){
                    if(i == edges_no_lengt[j].from_v){
                        main_matrix[i][j] = 1;
                    }
                    if(i == edges_no_lengt[j].to_v){
                        main_matrix[i][j] = -1;
                    }
                }
            }
        }
        

        return main_matrix;
    }

    // Метод выдачи списка смежности
    vector<vector<int>> adjacencyList(){
        vector<vector<int>> main_matrix (this->N, vector<int>(0));

        if(weighted){
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N_EDGES; j++){
                    if(edges_lengt[j].from_v == i){
                        main_matrix[i].push_back(edges_lengt[j].to_v);
                    }else if(edges_lengt[j].to_v == i){
                        main_matrix[i].push_back(edges_lengt[j].from_v);
                    }
                }
                sort(main_matrix[i].begin(), main_matrix[i].end());
                main_matrix[i].erase(unique(main_matrix[i].begin(), main_matrix[i].end()), main_matrix[i].end());
            }
        }else{
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N_EDGES; j++){
                    if(edges_no_lengt[j].from_v == i){
                        main_matrix[i].push_back(edges_no_lengt[j].to_v);
                    }else if(edges_no_lengt[j].to_v == i){
                        main_matrix[i].push_back(edges_no_lengt[j].from_v);
                    }
                }
                sort(main_matrix[i].begin(), main_matrix[i].end());
                main_matrix[i].erase(unique(main_matrix[i].begin(), main_matrix[i].end()), main_matrix[i].end());
            }
        }
        
        return main_matrix;
    }

    // Метод выдачи списка ребер
    vector<vector<int>> edgesList(){

        int edges_amount = N_EDGES;
        if(!directed){
            edges_amount = N_EDGES / 2;
        }
        vector<vector<int>> main_matrix (edges_amount, vector<int>(2));

        if(weighted){
            for(int i = 0; i < edges_amount; i++){
                main_matrix[i][0] = edges_lengt[i].from_v;
                main_matrix[i][1] = edges_lengt[i].to_v;
            }
        }else{
            for(int i = 0; i < edges_amount; i++){
                main_matrix[i][0] = edges_no_lengt[i].from_v;
                main_matrix[i][1] = edges_no_lengt[i].to_v;
            }
        }

        return main_matrix;
        
    }

    // Метод поиска в глубина (DFS)
    void DFS(int vertex, int& current_length, vector<EdgeWithWeight>& vertexes_graph){
        visited[vertex] = true;
        vector<int> adjList = adjLists[vertex];
    
        for(int i = 0; i < N; i++)
            if(!visited[i] && adjList[i] != 0){
                current_length += adjList[i];
                vertexes_graph.push_back({vertex, i, adjList[i]});
                DFS(i, current_length, vertexes_graph);
            }
    }

    // Метод поиска длиннейшего пути из вершины
    vector<EdgeWithWeight> searchLongestRootForOneVertex(int vertex){
        vector<EdgeWithWeight> vertexes_graph;
        int sum_root = 0;
        DFS(vertex, sum_root, vertexes_graph);
        for(int i = 0; i < N; i++){
            visited[i] = false;
        }
        return vertexes_graph;
    }

    // Метод поиска длиннейшего пути в графе
    vector<EdgeWithWeight> findLongestRoot(){
        vector<vector<EdgeWithWeight>> tmp_vect (N, vector<EdgeWithWeight>());

        int max_len = -1;
        int sum = 0;
        int longest_i = 0;
        for(int i = 0; i < N; i++){
            tmp_vect[i] = searchLongestRootForOneVertex(i);
        }

        for(int i = 0; i < N; i++){
            sum = 0;
            for(int j = 0; j < tmp_vect[i].size(); j++){
                sum += tmp_vect[i][j].length;
            }
            if(sum > max_len){
                max_len = sum;
                longest_i = i;
            }
        }

        return tmp_vect[longest_i];

    } 

    
};

class DiffGraphGenerator{
    private:
        int max_vertexes = 10;
        int min_vertexes = 5;

        int max_edges = 9;
        int min_edges = 3;

        int max_edges_for_vertex = 3;

        bool directed = true;

        int max_incoming_edges = 5;
        int max_outcoming_edges = 5;

        bool is_lengthed = true;

        int max_length = 10;
        int min_length = 1;

        bool is_legal_islands = false;

        DiffGraph* result_graph = nullptr;

    public:
        DiffGraphGenerator(){};

        void setMaxVertexes(int value){
            this->max_vertexes = value;
        }

        void setMinVertexes(int value){
            this->min_vertexes = value;
        }

        void setMaxEdges(int value){
            this->max_edges = value;
        }

        void setMinEdges(int value){
            this->min_edges = value;
        }

        void setMaxEdgesForVertex(int value){
            this->max_edges_for_vertex = value;
        }

        void setIsDirected(bool value){
            this->directed = value;
        }

        void setMaxIncomingEdges(int value){
            this->max_incoming_edges = value;
        }

        void setMaxOutcomingEdges(int value){
            this->max_outcoming_edges = value;
        }

        void setIsWeighted(bool value){
            this->is_lengthed = value;
        }

        void setMaxWeight(int value){
            this->max_length = value;
        }

        void SetMinWeight(int value){
            this->min_length = value;
        }

        void setIsLegalIslands(bool value){
            this->is_legal_islands = value;
        }

        DiffGraph* generateRandomGraph(){
            
            int vertexes_amount = this->min_vertexes + rand() % (this->max_vertexes - this->min_vertexes + 1);
            int edges_amount = this->min_edges + rand() % (this->max_edges - this->min_edges + 1);

            int* vertex_edges = new int[vertexes_amount];
            int* vertex_outcoming_edges = new int[vertexes_amount];
            int* vertex_incoming_edges = new int[vertexes_amount];
            bool* vertex_empty = new bool[vertexes_amount];

            for(int i = 0; i < vertexes_amount; i++){
                vertex_edges[i] = 0;
                vertex_outcoming_edges[i] = 0;
                vertex_incoming_edges[i] = 0;
                vertex_empty[i] = 1;
            }

            vector<EdgeWithWeight> edges_lengt(edges_amount);
            vector<EdgeWithoutWeight> edges_no_lengt(edges_amount);

            if(this->is_lengthed){
                for(int i = 0; i < edges_amount; i++){
                    edges_lengt[i] = {rand() % (edges_amount + 1), rand() % (edges_amount + 1), this->min_length + rand() % (this->max_length - this->min_length + 1)};

                    while((edges_lengt[i].to_v == edges_lengt[i].from_v) || (vertex_edges[edges_lengt[i].to_v] > this->max_edges_for_vertex) || (vertex_edges[edges_lengt[i].from_v] > this->max_edges_for_vertex)){
                        edges_lengt[i].to_v = rand() % (edges_amount + 1);
                        if(vertex_edges[edges_lengt[i].from_v] > this->max_edges_for_vertex){
                            edges_lengt[i].from_v = rand() % (edges_amount + 1);
                        }
                    }

                    while((vertex_outcoming_edges[edges_lengt[i].from_v] >= this->max_outcoming_edges) || (vertex_incoming_edges[edges_lengt[i].to_v] >= this->max_incoming_edges)){
                        if(vertex_edges[edges_lengt[i].from_v] >= this->max_edges_for_vertex){
                            edges_lengt[i].from_v = rand() % (edges_amount + 1);
                        }else{
                            edges_lengt[i].to_v = rand() % (edges_amount + 1);
                        }
                    }

                    vertex_empty[edges_lengt[i].from_v] = 0;
                    vertex_empty[edges_lengt[i].to_v] = 0;
                    vertex_edges[edges_lengt[i].from_v]++;
                    vertex_edges[edges_lengt[i].to_v]++;
                    vertex_incoming_edges[edges_lengt[i].to_v]++;
                    vertex_outcoming_edges[edges_lengt[i].from_v]++;
                }

                if(!this->is_legal_islands){
                    int vertexes_empty_num = 0;
                    for(int i = 0; i < vertexes_amount; i++){
                        if(vertex_empty[i]){
                            vertexes_empty_num++;
                            if(i != 0){
                                for(int j = 0; j< edges_amount; j++){
                                    if(edges_lengt[j].to_v == i){
                                        edges_lengt[j].to_v--;
                                    }else if(edges_lengt[j].from_v == i){
                                        edges_lengt[j].from_v--;
                                    }
                                }
                            }else{
                                for(int j = 0; j< edges_amount; j++){
                                    if(edges_lengt[j].to_v == i){
                                        edges_lengt[j].to_v++;
                                    }else if(edges_lengt[j].from_v == i){
                                        edges_lengt[j].from_v++;
                                    }
                                }
                            }

                        }
                    }
                    vertexes_amount -= vertexes_empty_num;
                }

                delete[] vertex_edges;
                delete[] vertex_outcoming_edges;
                delete[] vertex_incoming_edges;

                this->result_graph = new DiffGraph(edges_lengt, edges_amount, vertexes_amount, this->directed);
                
                return result_graph;

            }else{
                for(int i = 0; i < edges_amount; i++){
                    edges_no_lengt[i] = {rand() % (edges_amount + 1), rand() % (edges_amount + 1)};

                    while((edges_no_lengt[i].to_v == edges_no_lengt[i].from_v) || (vertex_edges[edges_no_lengt[i].to_v] > this->max_edges_for_vertex) || (vertex_edges[edges_no_lengt[i].from_v] > this->max_edges_for_vertex)){
                        edges_no_lengt[i].to_v = rand() % (edges_amount + 1);
                        if(vertex_edges[edges_no_lengt[i].from_v] > this->max_edges_for_vertex){
                            edges_no_lengt[i].from_v = rand() % (edges_amount + 1);
                        }
                    }

                    while((vertex_outcoming_edges[edges_no_lengt[i].from_v] >= this->max_outcoming_edges) || (vertex_incoming_edges[edges_no_lengt[i].to_v] >= this->max_incoming_edges)){
                        if(vertex_edges[edges_no_lengt[i].from_v] >= this->max_edges_for_vertex){
                            edges_no_lengt[i].from_v = rand() % (edges_amount + 1);
                        }else{
                            edges_no_lengt[i].to_v = rand() % (edges_amount + 1);
                        }
                    }

                    vertex_empty[edges_no_lengt[i].from_v] = 0;
                    vertex_empty[edges_no_lengt[i].to_v] = 0;
                    vertex_edges[edges_no_lengt[i].from_v]++;
                    vertex_edges[edges_no_lengt[i].to_v]++;
                    vertex_incoming_edges[edges_no_lengt[i].to_v]++;
                    vertex_outcoming_edges[edges_no_lengt[i].from_v]++;
                }

                if(!this->is_legal_islands){
                    int vertexes_empty_num = 0;
                    for(int i = 0; i < vertexes_amount; i++){
                        if(vertex_empty[i]){
                            vertexes_empty_num++;
                            if(i != 0){
                                for(int j = 0; j< edges_amount; j++){
                                    if(edges_no_lengt[j].to_v == i){
                                        edges_no_lengt[j].to_v--;
                                    }else if(edges_no_lengt[j].from_v == i){
                                        edges_no_lengt[j].from_v--;
                                    }
                                }
                            }else{
                                for(int j = 0; j< edges_amount; j++){
                                    if(edges_no_lengt[j].to_v == i){
                                        edges_no_lengt[j].to_v++;
                                    }else if(edges_no_lengt[j].from_v == i){
                                        edges_no_lengt[j].from_v++;
                                    }
                                }
                            }

                        }
                    }
                    vertexes_amount -= vertexes_empty_num;
                }

                delete[] vertex_edges;
                delete[] vertex_outcoming_edges;
                delete[] vertex_incoming_edges;

                this->result_graph = new DiffGraph(edges_no_lengt, edges_amount, vertexes_amount, this->directed);
                return result_graph;
            }


            
        }

        ~DiffGraphGenerator(){
            delete result_graph;


        }

};

int main()
{
    vector<EdgeWithWeight> edges = {
        // `(x, y, w)` —> ребро из `x` в `y` с весом `w`
        { 0, 1, 6 }, { 1, 2, 7 }, { 2, 0, 5 }, { 2, 1, 4 },
        { 3, 2, 10 }, { 4, 5, 1 }, { 5, 4, 3 }
    };

    // vector<EdgeWithoutWeight> edges[] =
    // {
    //     // `(x, y, w)` —> ребро из `x` в `y` с весом `w`
    //     { 0, 1 }, { 1, 2 }, { 2, 0 }, { 2, 1 },
    //     { 3, 2 }, { 4, 5 }, { 5, 4 }
    // };

    // кол-во узлов
    int N = 6;
 
    // кол-во ребер
    int n = edges.size();
 
    // создаем граф
    DiffGraph graph(edges, n, N, 1);

    cout << "Матрица смежности" << endl;
    vector<vector<int>> test = graph.adjacencyMat();
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << test[i][j] << "\t";
        }
        cout << endl;
    }
    
    cout << "Матрица инциндентности" << endl;
    vector<vector<int>> test_1 = graph.incidenceMat();
    for(int i = 0; i < N; i++){
        for(int j = 0; j < test_1[i].size(); j++){
            cout << test_1[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "Список смежности" << endl;
    vector<vector<int>> test_2 = graph.adjacencyList();
    for(int i = 0; i < N; i++){
        cout << i << ": ";
        for(int j = 0; j < test_2[i].size(); j++){
            cout << test_2[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "Список ребер" << endl;
    vector<vector<int>> test_3 = graph.edgesList();
    for(int i = 0; i < test_3.size(); i++){
        cout << i << ": ";
        for(int j = 0; j < test_3[i].size(); j++){
            cout << test_3[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "Поиск наидлиннейшего маршрута в графе" << endl;
    vector<EdgeWithWeight> res_longest = graph.findLongestRoot();
    for(int i = 0; i < res_longest.size(); i++){
        cout << res_longest[i].from_v << " -> " << res_longest[i].to_v << " : " << res_longest[i].length;
        cout << endl;
    }
    

    DiffGraphGenerator new_graph;
    DiffGraph* res = new_graph.generateRandomGraph();
    
    cout << "Матрица смежности" << endl;
    vector<vector<int>> res_test = res->adjacencyMat();
    for(int i = 0; i < res_test.size(); i++){
        for(int j = 0; j < res_test[i].size(); j++){
            cout << res_test[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "Матрица инциндентности" << endl;
    vector<vector<int>> res_test_1 = res->incidenceMat();
    for(int i = 0; i < res_test_1.size(); i++){
        for(int j = 0; j < res_test_1[i].size(); j++){
            cout << res_test_1[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "Список смежности" << endl;
    vector<vector<int>> res_test_2 = res->adjacencyList();
    for(int i = 0; i < res_test_2.size(); i++){
        cout << i << ": ";
        for(int j = 0; j < res_test_2[i].size(); j++){
            cout << res_test_2[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "Список ребер" << endl;
    vector<vector<int>> res_test_3 = res->edgesList();
    for(int i = 0; i < res_test_3.size(); i++){
        cout << i << ": ";
        for(int j = 0; j < res_test_3[i].size(); j++){
            cout << res_test_3[i][j] << "\t";
        }
        cout << endl;
    }
}