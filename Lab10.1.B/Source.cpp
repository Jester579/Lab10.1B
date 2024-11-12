#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Specialty { KOMP_NAUKY, INFORMATYKA, MATEMATYKA_EKONOMIKA, FIZYKA_INFORMATYKA, TRUDOVE_NAVCHANNYA };
string specialtyStr[] = { "��������� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

struct Student
{
    string prizv;
    unsigned course;
    Specialty specialty;
    int evaluations_physics;
    int evaluations_mathematics;
    union
    {
        int evaluations_programming;      
        int evaluations_numerical_methods; 
        int evaluations_pedagogy;       
    };
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
double ExcellentStudents(Student* p, const int N);
void PhysicsExcellent(Student* p, const int N);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "������ ������� �������� N: "; cin >> N;

    Student* p = new Student[N];
    int menuItem;
    do {
        cout << endl << "������� ��:" << endl;
        cout << " [1] - �������� ����� � ���������" << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ���������� ������� ��������" << endl;
        cout << " [4] - ��������� ��������, �� �������� � ������ ������ �5�" << endl;
        cout << " [0] - ����� �� ���������� ������ ��������" << endl;
        cout << "������ ��������: "; cin >> menuItem;
        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            cout << "³������ ��������, �� ���������� �� �������: "
                << ExcellentStudents(p, N) << "%" << endl;
            break;
        case 4:
            PhysicsExcellent(p, N);
            break;
        case 0:
            break;
        default:
            cout << "�� ����� ��������� ��������! "
                "��� ������ ����� - ����� ��������� ������ ����" << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}

void Create(Student* p, const int N)
{
    int specialty;
    for (int i = 0; i < N; i++)
    {
        cout << "������� � " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();

        cout << " �������: "; getline(cin, p[i].prizv);
        cout << " ����: "; cin >> p[i].course;
        cout << " ������������ (0 - ��������� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        cin >> specialty;
        p[i].specialty = (Specialty)specialty;
        cout << " ������ ������: "; cin >> p[i].evaluations_physics;
        cout << " ������ ����������: "; cin >> p[i].evaluations_mathematics;

        if (p[i].specialty == KOMP_NAUKY)
        {
            cout << " ������ � �������������: "; cin >> p[i].evaluations_programming;
        }
        else if (p[i].specialty == INFORMATYKA)
        {
            cout << " ������ � ��������� ������: "; cin >> p[i].evaluations_numerical_methods;
        }
        else
        {
            cout << " ������ � ���������: "; cin >> p[i].evaluations_pedagogy;
        }
    }
}

void Print(Student* p, const int N)
{
    cout << "===============================================================================================================================================" << endl;
    cout << "| � | �������        | ���� | ������������            |    Գ����     |   ����������    |   �������������   |  ������� ������ | ��������� |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << i + 1 << " | "
            << setw(14) << left << p[i].prizv
            << "| " << setw(4) << right << p[i].course << " | "
            << setw(24) << left << specialtyStr[p[i].specialty] << " | "
            << setw(13) << right << p[i].evaluations_physics << " | "
            << setw(16) << right << p[i].evaluations_mathematics << " | ";

        if (p[i].specialty == KOMP_NAUKY)
            cout << setw(14) << right << p[i].evaluations_programming << " | " << setw(15) << " " << " | " << setw(10) << " ";
        else if (p[i].specialty == INFORMATYKA)
            cout << setw(14) << " " << " | " << setw(15) << right << p[i].evaluations_numerical_methods << " | " << setw(10) << " ";
        else
            cout << setw(14) << " " << " | " << setw(15) << " " << " | " << setw(10) << right << p[i].evaluations_pedagogy;

        cout << " |" << endl;
    }
    cout << "===============================================================================================================================================" << endl;
}

double ExcellentStudents(Student* p, const int N)
{
    int countExcellent = 0;
    for (int i = 0; i < N; i++)
    {
        bool isExcellent = p[i].evaluations_physics == 5 && p[i].evaluations_mathematics == 5;
        if (p[i].specialty == KOMP_NAUKY)
            isExcellent = isExcellent && (p[i].evaluations_programming == 5);
        else if (p[i].specialty == INFORMATYKA)
            isExcellent = isExcellent && (p[i].evaluations_numerical_methods == 5);
        else
            isExcellent = isExcellent && (p[i].evaluations_pedagogy == 5);

        if (isExcellent)
            countExcellent++;
    }
    return (double)countExcellent / N * 100;
}

void PhysicsExcellent(Student* p, const int N)
{
    cout << "��������, �� �������� � ������ ������ �5�:" << endl;
    bool found = false;
    for (int i = 0; i < N; i++)
    {
        if (p[i].evaluations_physics == 5)
        {
            cout << p[i].prizv << endl;
            found = true;
        }
    }
    if (!found)
        cout << "���� �������� � ������� �5� � ������." << endl;
}
