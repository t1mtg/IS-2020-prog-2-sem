#include <iostream>
#include <vector>
#include <fstream>
#include "Cube.h"

using namespace std;
#define Plane vector<vector<MiniCube*>>
#define RightCenter RightPlane[1][1]->RightColor()
#define LeftCenter LeftPlane[1][1]->LeftColor()
#define UpCenter UpPlane[1][1]->UpColor()
#define DownCenter DownPlane[1][1]->DownColor()
#define FrontCenter FrontPlane[1][1]->FrontColor()
#define BackCenter BackPlane[1][1]->BackColor()

int main() {
    system("chcp 65001");
    CubeRubik Cube;
    Cube.ReadCubeRubik(inputStream);
    outputStream << "Изначальное состояние кубика:\n\n";
    Cube.PrintCubeRubik(outputStream);
    outputStream << "\n\nШаги разборки:\n\n";
    Cube.Shuffle(15);
    outputStream << "\n\nСостояние кубика после разборки:\n\n";
    Cube.PrintCubeRubik(outputStream);
    outputStream << "\n\nШаги сборки для первого кубика:\n\n";
    Cube.FindSolution();

    outputStream << "\n\nКубик после 7ми шагов сборки:\n\n";
    (Cube.isCubeCompleted()) ? outputStream << "\tКубик успешно собран\n\n" :
    outputStream << "К сожалению, кубик не собран, прошу понять и простить\n\n";Cube.PrintCubeRubik(outputStream);
    return 0;
}