#include <iostream>
#include <queue>
#include <stack>

using namespace std;

class graph {
protected:
    int size;
    int **arr;
    int *name;
public:
    //Конструктор
    graph() {
        size = 0;
        arr = new int *[size];
        for (int i = 0; i < size; i++) {
            arr[i] = new int[size];
            for (int j = 0; j < size; j++)
                arr[i][j] = 0;
        }
        name = new int[size];
        for (int i = 0; i < size; i++) {
            name[i] = 0;
        }
    }

    //Конструктор для создание графа определенной размерности
    graph(int n) {
        size = n;
        arr = new int *[size];
        for (int i = 0; i < size; i++) {
            arr[i] = new int[size];
            for (int j = 0; j < size; j++)
                arr[i][j] = 0;
        }
        name = new int[size];
        for (int i = 0; i < size; i++) {
            name[i] = i;
        }
    }

//Конструктор копирования
    graph(const graph &other) {
        this->arr = other.arr;
        this->size = other.size;
        this->name = other.name;
    }

protected:
    //Поиск индекса вершины
    int GetIdVer(int k) {
        for (int i = 0; i < size; i++) {
            if (k == name[i])
                return i;
        }
    }

public:
    //Поиск дуги
    bool SearchArc(int k, int l) {
        if (this->arr[GetIdVer(k)][GetIdVer(l)])
            return true;
        return false;
    }

    //Поиск вершины
    bool SearchVer(int nam) {
        for (int i = 0; i < size; i++) {
            if (this->name[i] == nam)
                return true;
        }
        return false;
    }

    //Добавление дуги
    void AddArc(int k, int l) {
        if (!SearchVer(k) || !SearchVer(l))
            cout << "В графе нет вершин для добавления дуги " << k << " " << l << endl;
        else if (SearchArc(k, l))
            cout << "Дуга из вершины " << k << " в " << l << " уже существует!" << endl;
        else
            this->arr[GetIdVer(k)][GetIdVer(l)] = 1;
    }

    //Удаление дуги
    void SubArc(int k, int l) {
        if (!SearchVer(k) || !SearchVer(l))
            cout << "В графе нет вершин для удаления дуги " << k << " " << l << endl;
        else if (!SearchArc(k, l))
            cout << "Дуга из вершины " << k << " в " << l << " не существует!" << endl;
        else
            this->arr[GetIdVer(k)][GetIdVer(l)] = 0;
    }

    //Печать графа
    void PrintGraph() {
        cout << "----------------------------------------" << endl;
        cout << "     ";
        for (int i = 0; i < size; i++)
            cout << name[i] << " | ";
        cout << endl;

        for (int i = 0; i < size; i++) {
            if (name[i] <= 9)
                cout << name[i] << "  | ";
            else
                cout << name[i] << " | ";
            for (int j = 0; j < size; j++) {
                if (name[j]  > 9)
                    cout << arr[i][j] << "  | ";
                else
                    cout << arr[i][j] << " | ";
            }
            cout << endl;
        }
        cout << "----------------------------------------" << endl;
    }

    //Добавление вершины
    void AddV(int nam) {
        if (!this->SearchVer(nam)) {
            graph G(this->size + 1);
            G.name[this->size]=nam;
            for (int i = 0; i < this->size; i++) {
                G.name[i]=this->name[i];;
                for (int j = 0; j < this->size; j++)
                    G.arr[i][j] = this->arr[i][j];
            }
            for (int i = 0; i < G.size; i++) {
                G.arr[this->size][i]=0;
                G.arr[i][this->size]=0;
            }
            this->arr = G.arr;
            this->size = G.size;
            this->name = G.name;
        } else
            cout << "Вершина " << nam << " уже существует!" << endl;
    }

    //Удаление вершины
    void SubV(int nam) {
        if (this->SearchVer(nam)) {
            bool t = true, m = true;
            graph G(this->size - 1);
            for (int i = 0; i < G.size; i++) {
                if (i != this->GetIdVer(nam) && t) {
                    G.name[i]=this->name[i];
                    for (int j = 0; j < G.size; j++) {
                        if (j != this->GetIdVer(nam) && m)
                            G.arr[i][j] = this->arr[i][j];
                        else {
                            m = false;
                            G.arr[i][j]=this->arr[i][j + 1];
                        }
                    }
                    m = true;
                } else {
                    G.name[i]=this->name[i+1];
                    t = false;
                    for (int j = 0; j < G.size; j++) {
                        if (j != this->GetIdVer(nam) && m)
                            G.arr[i][j]=this->arr[i+1][j];
                        else {
                            G.arr[i][j]=this->arr[i+1][j + 1];
                            m = false;
                        }
                    }
                    m = true;
                }
            }
            this->arr = G.arr;
            this->size = G.size;
            this->name = G.name;
        } else
            cout << "Вершины " << nam << " не существует!" << endl;
    }

    //Проверка графа на связность
    int *Obj(int t, int *ar) {
        ar[t] = 1;
        for (int i = 0; i < this->size; i++) {
            if (this->arr[t][i] == 1 && t != i && ar[i] == 0) {
                ar = this->Obj(i, ar);
            }
        }
        return ar;
    }

//Обход графа
    void Traversing() {
        int *ar;
        ar = new int[this->size];
        graph G(this->size);
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                G.arr[i][j] = this->arr[i][j];
            }
        }
        queue<int> q;
        int p = 0, t;
        bool check;

        cout << "----------------------------------------" << endl;
        //Проверка на связность
        for (int i = 0; i < this->size; i++)
            ar[i] = 0;
        ar = this->Obj(0, ar);
        for (int i = 0; i < this->size; i++) {
            p = p + ar[i];
            ar[i] = 0;
        }
       /* if (p != this->size)
            cout << "Граф не связный, обход не может быть совершен!" << endl;
        else {*/
       cout << "Обход в ширину(дуги)" << endl;

        cout << "{ ";
       for(int k=0; k< this->size; k++) {
           p = k;

           if(ar[k]==0) {

               for (int i = 0; i < this->size; i++) {
                   if (G.arr[p][i] == 1) {
                       q.push(p);
                       q.push(i);
                       cout << this->name[p] << "->" << this->name[i] << " ";
                       G.arr[p][i] = 0;
                   }
               }
               ar[p] = 1;
               p = q.front();
               q.pop();
               p = q.front();
               q.pop();
              // cout << "}" << endl;
//Закончили перебор исходящих из вершины дуг

//Проверка на заход во все вершины
/*                t = 0;
                for (int i = 0; i < this->size; i++) {
                    if (ar[i] == 1)
                        t = t + 1;
                }
                if (t == this->size) {
                    check = true;

                }*/
           }
       }
        cout <<endl<< "----------------------------------------" << endl;
    }

//Поиск в глубину сильных компонентов
    graph Stackk(int i, graph ar, int z) {
        ar.name[i]=1;
        ar.arr[z][z]=1;
        for (int j = 0; j < this->size; j++) {
            if (this->arr[i][j] == 1 ) {
                ar.arr[z][j] = 1;
                if (i != j && ar.name[j] == 0)
                    ar = Stackk(j, ar, z);
            }
        }
        return ar;
    }

//Сильные компоненты
    void Algoritgm() {
        graph ar(this->size);
        graph R(this->size);
        int k =0;

        for (int i = 0; i < this->size; i++) {
            ar.name[i] = 0;
            R.name[i]=1;
        }

        cout << "----------------------------------------" << endl;
        cout << "Сильные компоненты" << endl;
        for (int i = 0; i < this->size; i++) {
                ar = this->Stackk(i, ar, i);
                for(int j=0;j< this->size;j++)
                    ar.name[j]=0;
        }

        for (int i = 0; i < this->size; i++) {
            k = 0;
            for(int j=0;j< this->size;j++){
                R.arr[i][j]=ar.arr[i][j]*ar.arr[j][i];
                if(R.arr[i][j]==1) k++;
            }
            if(k==0) R.name[i]=0;
        }

        for (int i = 0; i < this->size; i++) {
            if(R.name[i]==1) {
                cout << "{ ";
                for (int j = 0; j < this->size; j++) {
                    if (R.arr[i][j] == 1) {
                        cout << this->name[j] << " ";
                        R.name[j] = 0;
                    }
                }
                cout << "} ";
            }
        }
        cout << endl << "----------------------------------------" << endl;
    }
};
// Created by PC on 30.03.2022.
//

#ifndef UNTITLED23_GRAPH_H
#define UNTITLED23_GRAPH_H

#endif //UNTITLED23_GRAPH_H
