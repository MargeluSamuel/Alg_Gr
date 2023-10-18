#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef struct Node 
{
    int data;
    struct Node *next;
}Node;

Node* new_node(int data)
{
    Node* temp = (Node*)malloc(sizeof(Node));

    temp->data = data;                                  //Functie pentru crearea unui nou node
    temp->next = NULL;

    return temp;
}

typedef struct Queue
{
    struct Node *front, *rear;
}Queue;


Queue* create_queue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));               //Functie pentru crearea unei cozi vide
    q->front = NULL;
    q->rear = NULL;

    return q;
}

void en_queue(Queue *q, int x)
{
    Node *temp = new_node(x);

    if (q->front == NULL)
    {                                                       //Functie pentru adaugarea unui nou nod;
        q->front = temp;
        q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

void de_queue(Queue *q)
{
    if (q->front == NULL)
    {
        printf("Coada este goala\n");
        return;
    }
    else                                                  //Functie pentru eliminarea unui nod;
    {
        Node *temp = q->front;

        q->front = q->front->next;

        if (q->front == NULL)
        {
            q->rear = q->front;
            return;
        }
        if (q->front->next == NULL)
            q->rear = q->front;

        free(temp);
    }
}

void print_queue(Queue *q)
{
    Node* temp = q->front;
    while (temp != NULL)
    {
        printf("%d | ", temp->data);
        temp = temp->next;
    }
    printf("\n\n");
}

bool is_queue_empty(Queue *q)
{
    if ((q->front == NULL) && (q->rear == NULL))
        return true;
    else
        return false;
}
void print_matrix(int **a, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int **create_matrix(int n, int m)
{
    int **matrix = (int**)malloc(sizeof(int*) * n);

    for (int i = 0; i < m; i++)
        matrix[i] = (int*)malloc(sizeof(int) * m);

    return matrix;
}

void BFS(int **matrice_adiacenta, int n, int m, int nod_start)
{
    Queue *q;
    q = create_queue();
    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    en_queue(q, nod_start); // Parametrii: coada si nodul din care se incepe cautarea
    print_queue(q);
    visited[nod_start] = 1; //Se marcheaza nodul de start ca vizitat

    while (is_queue_empty(q) == false)
    {
        for (int i = 0; i < m; i++)
        {
            if (matrice_adiacenta[q->front->data][i] == 1 && visited[i] == 0) // Cautam vecinii nodului si verificam daca sunt sau nu vizitati
            {
                visited[i] = 1;
                en_queue(q, i);
                //print_queue(q);
            }
        }
        de_queue(q);
        print_queue(q);
    }
}

int main()
{
    Queue *q = create_queue();

    FILE *fin, *fout;

    fin = fopen("D:\\Exercitii\\Facultate\\an2\\Grafuri\\Bfs\\Coada\\Resources\\muchii.txt", "r");
    if (fin == NULL)
    { 
        printf("Fisierul nu s-a putut deschide");
        return 0;
    }
    int n;
    fscanf(fin, "%d", &n);

    int **matrice_de_adiacenta = create_matrix(n, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrice_de_adiacenta[i][j] = 0;

    //print_matrix(matrice_de_adiacenta, n, n);


    while(!feof(fin))
    {
        int node1, node2;
        fscanf(fin, "%d %d", &node1, &node2);
        matrice_de_adiacenta[node1][node2] = matrice_de_adiacenta[node2][node1] = 1;
        //print_matrix(matrice_de_adiacenta, n, n);
    }

    //print_matrix(matrice_de_adiacenta, n, n);

    BFS(matrice_de_adiacenta, n, n, 3);

}