#include<bits/stdc++.h>
using namespace std;


/////////////////////////
struct Lecture {
    string day;
    int min_inicio;
    int min_fin;
};

bool operator <(const Lecture& x, const Lecture& y) {
    return x.day < y.day;
}

struct Course {
    string name;
    char section;
    set<Lecture> lecture_set;
};

bool operator <(const Course& x, const Course& y) {
    if(x.name < y.name) {
        return true;
    } else if(x.name == y.name) {
        if(x.section <  y.section) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}


//////////////
set<Course> allCourses;
map<int, Course> intToCourse;
map<Course, int> courseToInt;
/////////////
vector<string> split(string s) {
    vector<string> splited;
    int last_comma = -1;
    for(int i = 0; i < s.size(); i++) {
        if(i == s.size()-1) {
            splited.push_back(s.substr(last_comma+1, i-last_comma));
        }
        else if(s[i] == ',') {
            splited.push_back(s.substr(last_comma+1, i-last_comma-1));
            last_comma = i;
        }
    }
    return splited;
}

void imprimirClase(Lecture lecture) {
    cout << "Dia: " << lecture.day << endl;
    cout << "Minuto Inicio: " << lecture.min_inicio << endl;
    cout << "Minuto Fin: " << lecture.min_fin << endl;
}

void imprimirConjuntoClases(set<Lecture> lectures) {
    for (auto it = lectures.begin(); it != lectures.end(); ++it) {
        imprimirClase(*it);
    }
}
void imprimirCurso(Course course) {
    cout << "Nombre del curso: " << course.name << endl;
    cout << "Seccion: " << course.section << endl;
    cout << "Clases: " << endl;
    imprimirConjuntoClases(course.lecture_set);
} 
void imprimirConjuntoCursos(set<Course> courses) {
    for (auto it = courses.begin(); it != courses.end(); ++it) {
        imprimirCurso(*it);
        cout << "\n****************\n";
    }
}
void llenarCursos() {
    vector<string> list_lectures;
    string myText;
    ifstream MyReadFile("cursos.txt");

    while (getline (MyReadFile, myText)) {
        list_lectures.push_back(myText);
    }

    MyReadFile.close();

    //////////////////////
    Lecture tmp_lecture;
    Course tmp_course;
    set<Lecture> tmp_set_courses;
    string tmp_name;
    char tmp_section;
    for(auto elm : list_lectures) {
        vector<string> splited = split(elm);
        if(elm == "#"){
            tmp_course.name = tmp_name;
            tmp_course.section = tmp_section;
            tmp_course.lecture_set = tmp_set_courses;
            allCourses.insert(tmp_course);
            tmp_set_courses.clear();
        }
         else {
            tmp_section = splited[1][0];
            tmp_name = splited[0];
            tmp_lecture.day = splited[2];
            tmp_lecture.min_inicio = stoi(splited[3]);
            tmp_lecture.min_fin = stoi(splited[4]);
            tmp_set_courses.insert(tmp_lecture);
        }
    }
}

/////////////////
struct Edge {
    int src, dest;
};

class Graph {
public:
    vector<vector<int>> adj;
 
    Graph(vector<Edge> const &edges, int N)
    {
        adj.resize(N);
 
        for (Edge edge: edges)
        {
            int src = edge.src;
            int dest = edge.dest;
 
            adj[src].push_back(dest);
            adj[dest].push_back(src);
        }
    }
};
 
string COLORS[] = {"", "BLUE", "GREEN", "RED", "YELLOW", "ORANGE", "PINK", "BLACK", "BROWN", "WHITE", "PURPLE"
,"c11", "c12", "c13", "c14", "c15", "c16", "c17", "c18", "c19", "c20"};

// **********************
map<int, set<int>>  colorToSameColorSet;  // mapeo color -> vertices del mismo color
set<set<int>> setOfSameColorVertices; // contains vertices of the same color
set<set<set<int>>> setOfAllSets; 
// ********************

//******************* UTIL **********************
bool isSafe(Graph const &graph, vector<int> color, int v, int c)
{
    for (int u: graph.adj[v]) {
        if (color[u] == c) {
            return false;
        }
    }
 
    return true;
}

void showVerticesOfEachColor(){
    for (auto const& x : colorToSameColorSet) {
        cout << COLORS[x.first] << ": ";
        for (auto it = x.second.begin(); it != x.second.end(); ++it) cout << ' ' << intToCourse[(*it)].name << '-' << intToCourse[(*it)].section << " ";
        cout << endl;
    }
}

void printSummary() {
    ofstream myfile ("Resumen.txt");
    if (myfile.is_open()) {
        for(auto const& elm : setOfAllSets) {
            myfile << "***************\n";
            for(auto const& xx : elm) {
                myfile << "POSIBLE HORARIO: ";
                for(auto it = xx.begin(); it != xx.end(); ++it) {
                    myfile << ' ' << intToCourse[(*it)].name << '-' << intToCourse[(*it)].section << endl;
                }
                myfile << endl;
            }
            myfile << "***************\n";
        }
    } else {
        cout << "Unable to open file";
    }
    
}

void fileManipulation() {
    ofstream myfile ("horarios.txt");
    if (myfile.is_open()) {
        for(auto const& elm : setOfAllSets) {
            for(auto const& xx : elm) {
                for(auto it = xx.begin(); it != xx.end(); ++it) {
                    myfile << (*it)<< ' ';
                }
                myfile << endl;
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";
}
//******************* UTIL **********************

// MAIN ALGORITHM
void kColorable(Graph const &graph, vector<int> &color, int k, int v, int N)
{
    if (v == N)
    {
        colorToSameColorSet.clear();
        for (int v = 0; v < N; v++) {
            //cout << intToCourse[v].name << "-" << intToCourse[v].section << ": " << setw(8) << left << COLORS[color[v]];
            colorToSameColorSet[color[v]].insert(v);
        }
        //cout << endl;
        //showVerticesOfEachColor();
        setOfSameColorVertices.clear();
        for (auto const& x : colorToSameColorSet) {
            setOfSameColorVertices.insert(x.second);
        }
        setOfAllSets.insert(setOfSameColorVertices);
        
        return;
    }

    for (int c = 1; c <= k; c++)
    {
        if (isSafe(graph, color, v, c))
        {
            color[v] = c;
 
            kColorable(graph, color, k, v + 1, N);
 
            color[v] = 0;
        }
    }
}


void llenarMapeos() {
    int index = 0;
    for (auto it = allCourses.begin(); it != allCourses.end(); ++it) {
        intToCourse[index] = *it;
        courseToInt[*it] = index;
        index++;
    }
}

bool intervalo_cruze(int l1, int u1, int l2, int u2) {
    return l1 < u2 && l2 < u1;
}

bool cruze(Course course1, Course course2) {
    for (auto it1 = course1.lecture_set.begin(); it1 != course1.lecture_set.end(); ++it1) {
        for (auto it2 = course2.lecture_set.begin(); it2 != course2.lecture_set.end(); ++it2) {
            if((*it1).day == (*it2).day) {
                if(intervalo_cruze((*it1).min_inicio, (*it1).min_fin, (*it2).min_inicio, (*it2).min_fin)) {
                    return true;
                } 
            } 
        }
    }
    return false;
}

vector<Edge> createEdges() {
    vector<Edge> edges;
    for (auto course1 = allCourses.begin(); course1 != allCourses.end(); ++course1) {
        for (auto course2 = course1; course2 != allCourses.end(); ++course2) {
            if(course1 == course2) {
                continue;
            } else{
                if((*course1).name == (*course2).name) {
                    edges.push_back({courseToInt[*course1], courseToInt[*course2]});
                } else if(cruze(*course1, *course2)){
                    edges.push_back({courseToInt[*course1], courseToInt[*course2]});
                }
            }
        }
    }
    return edges;
}
void fileMapping() {
    ofstream myfile ("mapeo_numero_curso.txt");
    if (myfile.is_open()) {
        for(auto const& elm : intToCourse) {
            myfile << elm.first << "," << elm.second.name << "-" << elm.second.section << endl;
        }
        myfile.close();
    }
    else cout << "Unable to open file";
}
int main() {
    llenarCursos();
    llenarMapeos();
    fileMapping();
    int N = allCourses.size();
    // number of colors
    int k = 4;
    vector<Edge> edges = createEdges();
    // Shows the graph edges
    for(auto elm : edges) {
        cout << "{" << elm.dest << ',' << elm.src << "}, ";
    }
    // {
    //     {0, 1}, {1, 2}, {2, 3}, {0, 4}, {4, 5}, {5, 1}, {5, 6}, {6, 2}, {6, 7}, {7, 3}, {7, 4}, {0, 3}
    //     // {0, 1}, {1, 2}, {2, 0}
    //     // {0, 1}, {1, 2}, {2, 3}, {3, 0}
    //     // {0, 1}, {1, 2}, {2, 0}
    // };
    Graph courses(edges, N);
    vector<int> color(N, 0);
    // applies the main algorithm
    kColorable(courses, color, k, 0, N);
    // generates Resumen.txt
    printSummary();
    // generates horarios.txt
    fileManipulation();
    cout << endl << "Archivos generados" << endl;
    return 0;
}