#pragma once

using namespace std;
#define Plane vector<vector<MiniCube*>>
#define RightCenter RightPlane[1][1]->RightColor()
#define LeftCenter LeftPlane[1][1]->LeftColor()
#define UpCenter UpPlane[1][1]->UpColor()
#define DownCenter DownPlane[1][1]->DownColor()
#define FrontCenter FrontPlane[1][1]->FrontColor()
#define BackCenter BackPlane[1][1]->BackColor()

ifstream inputStream("input.txt");
ofstream outputStream("output.txt");

void PrintColor(const string &color, ostream &outputStreamTemp = cout) {
    outputStreamTemp << color << " ";
}

class CubeRubik {
private:
    class MiniCube {
    private:
        string up = "black", down = "black", left = "black", right = "black", front = "black", back = "black";
    public:
        MiniCube() = default;
        explicit MiniCube(string &up, string &down, string &left, string &right, string &front, string &back) :
                up(up), down(down), left(left), right(right), front(front), back(back) {}

        [[nodiscard]] string UpColor() const { return this->up; }
        [[nodiscard]] string DownColor() const { return this->down; }
        [[nodiscard]] string LeftColor() const { return this->left; }
        [[nodiscard]] string RightColor() const { return this->right; }
        [[nodiscard]] string FrontColor() const { return this->front; }
        [[nodiscard]] string BackColor() const { return this->back; }

        void setUpColor(string color) { this->up = move(color); }
        void setDownColor(string color) { this->down = move(color); }
        void setLeftColor(string color) { this->left = move(color); }
        void setRightColor(string color) { this->right = move(color); }
        void setFrontColor(string color) { this->front = move(color); }
        void setBackColor(string color) { this->back = move(color); }
    };

    unsigned int FirstStepCounter = 0, SecondStepCounter = 0, ThirdStepCounter = 0,
            FourthStepCounter = 0, FifthStepCounter = 0, SixthStepCounter = 0, SeventhStepCounter = 0;

    unsigned int RotatesCounter = 0;

    vector<vector<vector<MiniCube>>> arr;

    Plane UpPlane;
    Plane DownPlane;
    Plane LeftPlane;
    Plane RightPlane;
    Plane FrontPlane;
    Plane BackPlane;

    void FillPlaneArr(Plane &curPlane) {
        for (int i = 0; i < 3; ++i) {
            vector<MiniCube *> tempArr(3);
            for (int j = 0; j < 3; ++j)
                tempArr[j] = &arr[i][2][j];
            curPlane.push_back(tempArr);
        }
    }

    void PushInPlaneVector() {
        FillPlaneArr(UpPlane);
        FillPlaneArr(DownPlane);
        FillPlaneArr(LeftPlane);
        FillPlaneArr(RightPlane);
        FillPlaneArr(FrontPlane);
        FillPlaneArr(BackPlane);
    }

public:
    [[nodiscard]] bool CheckIfCubeCorrect() const {
        bool ifUpAndDownCentersCorrect = UpCenter == "W" && DownCenter == "Y" || UpCenter == "Y" && DownCenter == "W";

        bool ifOtherCentersCorrect =
                LeftCenter == "O" && FrontCenter == "G" && RightCenter == "R" && BackCenter == "B" ||
                LeftCenter == "B" && FrontCenter == "O" && RightCenter == "G" && BackCenter == "R" ||
                LeftCenter == "R" && FrontCenter == "B" && RightCenter == "O" && BackCenter == "G" ||
                LeftCenter == "G" && FrontCenter == "R" && RightCenter == "B" && BackCenter == "O";

        bool result = ifUpAndDownCentersCorrect && ifOtherCentersCorrect;

        return result;
    }

    CubeRubik() {
        arr.resize(3, vector<vector<MiniCube >>(3, vector<MiniCube>(3)));
        PushInPlaneVector();
        CreateCubeRubik();
    }

    ~CubeRubik() = default;

    void CreateCubeRubik() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                UpPlane[i][j]->setUpColor("W");
                DownPlane[i][j]->setDownColor("Y");
                LeftPlane[i][j]->setLeftColor("O");
                RightPlane[i][j]->setRightColor("R");
                FrontPlane[i][j]->setFrontColor("G");
                BackPlane[i][j]->setBackColor("B");
            }
    }

    void RotateUpPlane(const char degree) {
        RotatesCounter++;
        string right_0_0 = RightPlane[0][0]->RightColor(),
                right_0_1 = RightPlane[0][1]->RightColor(), right_0_2 = RightPlane[0][2]->RightColor();

        if (degree == '+') {
            outputStream << "U ";

            string up_0_0 = UpPlane[0][0]->UpColor(),
                    up_1_0 = UpPlane[1][0]->UpColor();

            UpPlane[0][0]->setUpColor(UpPlane[2][0]->UpColor());
            UpPlane[1][0]->setUpColor(UpPlane[2][1]->UpColor());
            UpPlane[2][0]->setUpColor(UpPlane[2][2]->UpColor());
            UpPlane[2][1]->setUpColor(UpPlane[1][2]->UpColor());
            UpPlane[2][2]->setUpColor(UpPlane[0][2]->UpColor());
            UpPlane[1][2]->setUpColor(UpPlane[0][1]->UpColor());
            UpPlane[0][2]->setUpColor(up_0_0);
            UpPlane[0][1]->setUpColor(up_1_0);

            RightPlane[0][0]->setRightColor(BackPlane[0][0]->BackColor());
            RightPlane[0][1]->setRightColor(BackPlane[0][1]->BackColor());
            RightPlane[0][2]->setRightColor(BackPlane[0][2]->BackColor());

            BackPlane[0][0]->setBackColor(LeftPlane[0][0]->LeftColor());
            BackPlane[0][1]->setBackColor(LeftPlane[0][1]->LeftColor());
            BackPlane[0][2]->setBackColor(LeftPlane[0][2]->LeftColor());

            LeftPlane[0][0]->setLeftColor(FrontPlane[0][0]->FrontColor());
            LeftPlane[0][1]->setLeftColor(FrontPlane[0][1]->FrontColor());
            LeftPlane[0][2]->setLeftColor(FrontPlane[0][2]->FrontColor());

            FrontPlane[0][0]->setFrontColor(right_0_0);
            FrontPlane[0][1]->setFrontColor(right_0_1);
            FrontPlane[0][2]->setFrontColor(right_0_2);

        } else if (degree == '-') {
            outputStream << "U' ";

            string up_0_2 = UpPlane[0][2]->UpColor(),
                    up_1_2 = UpPlane[1][2]->UpColor();

            UpPlane[0][2]->setUpColor(UpPlane[2][2]->UpColor());
            UpPlane[1][2]->setUpColor(UpPlane[2][1]->UpColor());
            UpPlane[2][2]->setUpColor(UpPlane[2][0]->UpColor());
            UpPlane[2][1]->setUpColor(UpPlane[1][0]->UpColor());
            UpPlane[2][0]->setUpColor(UpPlane[0][0]->UpColor());
            UpPlane[1][0]->setUpColor(UpPlane[0][1]->UpColor());
            UpPlane[0][1]->setUpColor(up_1_2);
            UpPlane[0][0]->setUpColor(up_0_2);

            RightPlane[0][0]->setRightColor(FrontPlane[0][0]->FrontColor());
            RightPlane[0][1]->setRightColor(FrontPlane[0][1]->FrontColor());
            RightPlane[0][2]->setRightColor(FrontPlane[0][2]->FrontColor());

            FrontPlane[0][0]->setFrontColor(LeftPlane[0][0]->LeftColor());
            FrontPlane[0][1]->setFrontColor(LeftPlane[0][1]->LeftColor());
            FrontPlane[0][2]->setFrontColor(LeftPlane[0][2]->LeftColor());

            LeftPlane[0][0]->setLeftColor(BackPlane[0][0]->BackColor());
            LeftPlane[0][1]->setLeftColor(BackPlane[0][1]->BackColor());
            LeftPlane[0][2]->setLeftColor(BackPlane[0][2]->BackColor());

            BackPlane[0][0]->setBackColor(right_0_0);
            BackPlane[0][1]->setBackColor(right_0_1);
            BackPlane[0][2]->setBackColor(right_0_2);
        }
    }

    void RotateDownPlane(const char degree) {
        RotatesCounter++;
        string right_2_0 = RightPlane[2][0]->RightColor(),
                right_2_1 = RightPlane[2][1]->RightColor(), right_2_2 = RightPlane[2][2]->RightColor();

        if (degree == '+') {
            outputStream << "D ";

            string down_0_0 = DownPlane[0][0]->DownColor(),
                    down_1_0 = DownPlane[1][0]->DownColor();

            DownPlane[0][0]->setDownColor(DownPlane[2][0]->DownColor());
            DownPlane[1][0]->setDownColor(DownPlane[2][1]->DownColor());
            DownPlane[2][0]->setDownColor(DownPlane[2][2]->DownColor());
            DownPlane[2][1]->setDownColor(DownPlane[1][2]->DownColor());
            DownPlane[2][2]->setDownColor(DownPlane[0][2]->DownColor());
            DownPlane[1][2]->setDownColor(DownPlane[0][1]->DownColor());
            DownPlane[0][2]->setDownColor(down_0_0);
            DownPlane[0][1]->setDownColor(down_1_0);

            RightPlane[2][0]->setRightColor(FrontPlane[2][0]->FrontColor());
            RightPlane[2][1]->setRightColor(FrontPlane[2][1]->FrontColor());
            RightPlane[2][2]->setRightColor(FrontPlane[2][2]->FrontColor());

            FrontPlane[2][0]->setFrontColor(LeftPlane[2][0]->LeftColor());
            FrontPlane[2][1]->setFrontColor(LeftPlane[2][1]->LeftColor());
            FrontPlane[2][2]->setFrontColor(LeftPlane[2][2]->LeftColor());

            LeftPlane[2][0]->setLeftColor(BackPlane[2][0]->BackColor());
            LeftPlane[2][1]->setLeftColor(BackPlane[2][1]->BackColor());
            LeftPlane[2][2]->setLeftColor(BackPlane[2][2]->BackColor());

            BackPlane[2][0]->setBackColor(right_2_0);
            BackPlane[2][1]->setBackColor(right_2_1);
            BackPlane[2][2]->setBackColor(right_2_2);

        } else if (degree == '-') {
            outputStream << "D' ";

            string down_0_2 = DownPlane[0][2]->DownColor(),
                    down_1_2 = DownPlane[1][2]->DownColor();

            DownPlane[0][2]->setDownColor(DownPlane[2][2]->DownColor());
            DownPlane[1][2]->setDownColor(DownPlane[2][1]->DownColor());
            DownPlane[2][2]->setDownColor(DownPlane[2][0]->DownColor());
            DownPlane[2][1]->setDownColor(DownPlane[1][0]->DownColor());
            DownPlane[2][0]->setDownColor(DownPlane[0][0]->DownColor());
            DownPlane[1][0]->setDownColor(DownPlane[0][1]->DownColor());
            DownPlane[0][1]->setDownColor(down_1_2);
            DownPlane[0][0]->setDownColor(down_0_2);

            RightPlane[2][0]->setRightColor(BackPlane[2][0]->BackColor());
            RightPlane[2][1]->setRightColor(BackPlane[2][1]->BackColor());
            RightPlane[2][2]->setRightColor(BackPlane[2][2]->BackColor());

            BackPlane[2][0]->setBackColor(LeftPlane[2][0]->LeftColor());
            BackPlane[2][1]->setBackColor(LeftPlane[2][1]->LeftColor());
            BackPlane[2][2]->setBackColor(LeftPlane[2][2]->LeftColor());

            LeftPlane[2][0]->setLeftColor(FrontPlane[2][0]->FrontColor());
            LeftPlane[2][1]->setLeftColor(FrontPlane[2][1]->FrontColor());
            LeftPlane[2][2]->setLeftColor(FrontPlane[2][2]->FrontColor());

            FrontPlane[2][0]->setFrontColor(right_2_0);
            FrontPlane[2][1]->setFrontColor(right_2_1);
            FrontPlane[2][2]->setFrontColor(right_2_2);
        }
    }

    void RotateLeftPlane(const char degree) {
        RotatesCounter++;
        string front_0_0 = FrontPlane[0][0]->FrontColor(),
                front_1_0 = FrontPlane[1][0]->FrontColor(), front_2_0 = FrontPlane[2][0]->FrontColor();

        if (degree == '+') {
            outputStream << "L ";

            string left_0_0 = LeftPlane[0][0]->LeftColor(),
                    left_1_0 = LeftPlane[1][0]->LeftColor();

            LeftPlane[0][0]->setLeftColor(LeftPlane[2][0]->LeftColor());
            LeftPlane[1][0]->setLeftColor(LeftPlane[2][1]->LeftColor());
            LeftPlane[2][0]->setLeftColor(LeftPlane[2][2]->LeftColor());
            LeftPlane[2][1]->setLeftColor(LeftPlane[1][2]->LeftColor());
            LeftPlane[2][2]->setLeftColor(LeftPlane[0][2]->LeftColor());
            LeftPlane[1][2]->setLeftColor(LeftPlane[0][1]->LeftColor());
            LeftPlane[0][2]->setLeftColor(left_0_0);
            LeftPlane[0][1]->setLeftColor(left_1_0);

            FrontPlane[0][0]->setFrontColor(UpPlane[0][0]->UpColor());
            FrontPlane[1][0]->setFrontColor(UpPlane[1][0]->UpColor());
            FrontPlane[2][0]->setFrontColor(UpPlane[2][0]->UpColor());

            UpPlane[0][0]->setUpColor(BackPlane[2][2]->BackColor());
            UpPlane[1][0]->setUpColor(BackPlane[1][2]->BackColor());
            UpPlane[2][0]->setUpColor(BackPlane[0][2]->BackColor());

            BackPlane[0][2]->setBackColor(DownPlane[2][0]->DownColor());
            BackPlane[1][2]->setBackColor(DownPlane[1][0]->DownColor());
            BackPlane[2][2]->setBackColor(DownPlane[0][0]->DownColor());

            DownPlane[0][0]->setDownColor(front_0_0);
            DownPlane[1][0]->setDownColor(front_1_0);
            DownPlane[2][0]->setDownColor(front_2_0);

        } else if (degree == '-') {
            outputStream << "L' ";

            string left_0_0 = LeftPlane[0][0]->LeftColor(),
                    left_0_1 = LeftPlane[0][1]->LeftColor();

            LeftPlane[0][0]->setLeftColor(LeftPlane[0][2]->LeftColor());
            LeftPlane[0][1]->setLeftColor(LeftPlane[1][2]->LeftColor());
            LeftPlane[0][2]->setLeftColor(LeftPlane[2][2]->LeftColor());
            LeftPlane[1][2]->setLeftColor(LeftPlane[2][1]->LeftColor());
            LeftPlane[2][2]->setLeftColor(LeftPlane[2][0]->LeftColor());
            LeftPlane[2][1]->setLeftColor(LeftPlane[1][0]->LeftColor());
            LeftPlane[2][0]->setLeftColor(left_0_0);
            LeftPlane[1][0]->setLeftColor(left_0_1);

            FrontPlane[0][0]->setFrontColor(DownPlane[0][0]->DownColor());
            FrontPlane[1][0]->setFrontColor(DownPlane[1][0]->DownColor());
            FrontPlane[2][0]->setFrontColor(DownPlane[2][0]->DownColor());

            DownPlane[0][0]->setDownColor(BackPlane[2][2]->BackColor());
            DownPlane[1][0]->setDownColor(BackPlane[1][2]->BackColor());
            DownPlane[2][0]->setDownColor(BackPlane[0][2]->BackColor());

            BackPlane[0][2]->setBackColor(UpPlane[2][0]->UpColor());
            BackPlane[1][2]->setBackColor(UpPlane[1][0]->UpColor());
            BackPlane[2][2]->setBackColor(UpPlane[0][0]->UpColor());

            UpPlane[0][0]->setUpColor(front_0_0);
            UpPlane[1][0]->setUpColor(front_1_0);
            UpPlane[2][0]->setUpColor(front_2_0);
        }
    }

    void RotateRightPlane(const char degree) {
        RotatesCounter++;
        string front_0_2 = FrontPlane[0][2]->FrontColor(),
                front_1_2 = FrontPlane[1][2]->FrontColor(), front_2_2 = FrontPlane[2][2]->FrontColor();

        if (degree == '+') {
            outputStream << "R ";

            string right_0_0 = RightPlane[0][0]->RightColor(),
                    right_1_0 = RightPlane[1][0]->RightColor();

            RightPlane[0][0]->setRightColor(RightPlane[2][0]->RightColor());
            RightPlane[1][0]->setRightColor(RightPlane[2][1]->RightColor());
            RightPlane[2][0]->setRightColor(RightPlane[2][2]->RightColor());
            RightPlane[2][1]->setRightColor(RightPlane[1][2]->RightColor());
            RightPlane[2][2]->setRightColor(RightPlane[0][2]->RightColor());
            RightPlane[1][2]->setRightColor(RightPlane[0][1]->RightColor());
            RightPlane[0][2]->setRightColor(right_0_0);
            RightPlane[0][1]->setRightColor(right_1_0);

            FrontPlane[0][2]->setFrontColor(DownPlane[0][2]->DownColor());
            FrontPlane[1][2]->setFrontColor(DownPlane[1][2]->DownColor());
            FrontPlane[2][2]->setFrontColor(DownPlane[2][2]->DownColor());

            DownPlane[0][2]->setDownColor(BackPlane[2][0]->BackColor());
            DownPlane[1][2]->setDownColor(BackPlane[1][0]->BackColor());
            DownPlane[2][2]->setDownColor(BackPlane[0][0]->BackColor());

            BackPlane[0][0]->setBackColor(UpPlane[2][2]->UpColor());
            BackPlane[1][0]->setBackColor(UpPlane[1][2]->UpColor());
            BackPlane[2][0]->setBackColor(UpPlane[0][2]->UpColor());

            UpPlane[0][2]->setUpColor(front_0_2);
            UpPlane[1][2]->setUpColor(front_1_2);
            UpPlane[2][2]->setUpColor(front_2_2);

        } else if (degree == '-') {
            outputStream << "R' ";

            string right_0_1 = RightPlane[0][1]->RightColor(),
                    right_0_2 = RightPlane[0][2]->RightColor();

            RightPlane[0][1]->setRightColor(RightPlane[1][2]->RightColor());
            RightPlane[0][2]->setRightColor(RightPlane[2][2]->RightColor());
            RightPlane[1][2]->setRightColor(RightPlane[2][1]->RightColor());
            RightPlane[2][2]->setRightColor(RightPlane[2][0]->RightColor());
            RightPlane[2][1]->setRightColor(RightPlane[1][0]->RightColor());
            RightPlane[2][0]->setRightColor(RightPlane[0][0]->RightColor());
            RightPlane[1][0]->setRightColor(right_0_1);
            RightPlane[0][0]->setRightColor(right_0_2);

            FrontPlane[0][2]->setFrontColor(UpPlane[0][2]->UpColor());
            FrontPlane[1][2]->setFrontColor(UpPlane[1][2]->UpColor());
            FrontPlane[2][2]->setFrontColor(UpPlane[2][2]->UpColor());

            UpPlane[0][2]->setUpColor(BackPlane[2][0]->BackColor());
            UpPlane[1][2]->setUpColor(BackPlane[1][0]->BackColor());
            UpPlane[2][2]->setUpColor(BackPlane[0][0]->BackColor());

            BackPlane[0][0]->setBackColor(DownPlane[2][2]->DownColor());
            BackPlane[1][0]->setBackColor(DownPlane[1][2]->DownColor());
            BackPlane[2][0]->setBackColor(DownPlane[0][2]->DownColor());

            DownPlane[0][2]->setDownColor(front_0_2);
            DownPlane[1][2]->setDownColor(front_1_2);
            DownPlane[2][2]->setDownColor(front_2_2);
        }
    }

    void RotateFrontPlane(const char degree) {
        RotatesCounter++;
        string up_2_0 = UpPlane[2][0]->UpColor(),
                up_2_1 = UpPlane[2][1]->UpColor(), up_2_2 = UpPlane[2][2]->UpColor();

        if (degree == '+') {
            outputStream << "F ";

            string front_0_0 = FrontPlane[0][0]->FrontColor(),
                    front_1_0 = FrontPlane[1][0]->FrontColor();

            FrontPlane[0][0]->setFrontColor(FrontPlane[2][0]->FrontColor());
            FrontPlane[1][0]->setFrontColor(FrontPlane[2][1]->FrontColor());
            FrontPlane[2][0]->setFrontColor(FrontPlane[2][2]->FrontColor());
            FrontPlane[2][1]->setFrontColor(FrontPlane[1][2]->FrontColor());
            FrontPlane[2][2]->setFrontColor(FrontPlane[0][2]->FrontColor());
            FrontPlane[1][2]->setFrontColor(FrontPlane[0][1]->FrontColor());
            FrontPlane[0][2]->setFrontColor(front_0_0);
            FrontPlane[0][1]->setFrontColor(front_1_0);

            UpPlane[2][0]->setUpColor(LeftPlane[2][2]->LeftColor());
            UpPlane[2][1]->setUpColor(LeftPlane[1][2]->LeftColor());
            UpPlane[2][2]->setUpColor(LeftPlane[0][2]->LeftColor());

            LeftPlane[0][2]->setLeftColor(DownPlane[0][0]->DownColor());
            LeftPlane[1][2]->setLeftColor(DownPlane[0][1]->DownColor());
            LeftPlane[2][2]->setLeftColor(DownPlane[0][2]->DownColor());

            DownPlane[0][0]->setDownColor(RightPlane[2][0]->RightColor());
            DownPlane[0][1]->setDownColor(RightPlane[1][0]->RightColor());
            DownPlane[0][2]->setDownColor(RightPlane[0][0]->RightColor());

            RightPlane[0][0]->setRightColor(up_2_0);
            RightPlane[1][0]->setRightColor(up_2_1);
            RightPlane[2][0]->setRightColor(up_2_2);

        } else if (degree == '-') {
            outputStream << "F' ";

            string front_0_0 = FrontPlane[0][0]->FrontColor(),
                    front_0_1 = FrontPlane[0][1]->FrontColor();

            FrontPlane[0][0]->setFrontColor(FrontPlane[0][2]->FrontColor());
            FrontPlane[0][1]->setFrontColor(FrontPlane[1][2]->FrontColor());
            FrontPlane[0][2]->setFrontColor(FrontPlane[2][2]->FrontColor());
            FrontPlane[1][2]->setFrontColor(FrontPlane[2][1]->FrontColor());
            FrontPlane[2][2]->setFrontColor(FrontPlane[2][0]->FrontColor());
            FrontPlane[2][1]->setFrontColor(FrontPlane[1][0]->FrontColor());
            FrontPlane[2][0]->setFrontColor(front_0_0);
            FrontPlane[1][0]->setFrontColor(front_0_1);

            UpPlane[2][0]->setUpColor(RightPlane[0][0]->RightColor());
            UpPlane[2][1]->setUpColor(RightPlane[1][0]->RightColor());
            UpPlane[2][2]->setUpColor(RightPlane[2][0]->RightColor());

            RightPlane[0][0]->setRightColor(DownPlane[0][2]->DownColor());
            RightPlane[1][0]->setRightColor(DownPlane[0][1]->DownColor());
            RightPlane[2][0]->setRightColor(DownPlane[0][0]->DownColor());

            DownPlane[0][0]->setDownColor(LeftPlane[0][2]->LeftColor());
            DownPlane[0][1]->setDownColor(LeftPlane[1][2]->LeftColor());
            DownPlane[0][2]->setDownColor(LeftPlane[2][2]->LeftColor());

            LeftPlane[0][2]->setLeftColor(up_2_2);
            LeftPlane[1][2]->setLeftColor(up_2_1);
            LeftPlane[2][2]->setLeftColor(up_2_0);
        }
    }

    void RotateBackPlane(const char degree) {
        RotatesCounter++;
        string up_0_0 = UpPlane[0][0]->UpColor(),
                up_0_1 = UpPlane[0][1]->UpColor(), up_0_2 = UpPlane[0][2]->UpColor();

        if (degree == '+') {
            outputStream << "B ";

            string back_0_0 = BackPlane[0][0]->BackColor(),
                    back_1_0 = BackPlane[1][0]->BackColor();

            BackPlane[0][0]->setBackColor(BackPlane[2][0]->BackColor());
            BackPlane[1][0]->setBackColor(BackPlane[2][1]->BackColor());
            BackPlane[2][0]->setBackColor(BackPlane[2][2]->BackColor());
            BackPlane[2][1]->setBackColor(BackPlane[1][2]->BackColor());
            BackPlane[2][2]->setBackColor(BackPlane[0][2]->BackColor());
            BackPlane[1][2]->setBackColor(BackPlane[0][1]->BackColor());
            BackPlane[0][2]->setBackColor(back_0_0);
            BackPlane[0][1]->setBackColor(back_1_0);

            UpPlane[0][0]->setUpColor(RightPlane[0][2]->RightColor());
            UpPlane[0][1]->setUpColor(RightPlane[1][2]->RightColor());
            UpPlane[0][2]->setUpColor(RightPlane[2][2]->RightColor());

            RightPlane[0][2]->setRightColor(DownPlane[2][2]->DownColor());
            RightPlane[1][2]->setRightColor(DownPlane[2][1]->DownColor());
            RightPlane[2][2]->setRightColor(DownPlane[2][0]->DownColor());

            DownPlane[2][0]->setDownColor(LeftPlane[0][0]->LeftColor());
            DownPlane[2][1]->setDownColor(LeftPlane[1][0]->LeftColor());
            DownPlane[2][2]->setDownColor(LeftPlane[2][0]->LeftColor());

            LeftPlane[2][0]->setLeftColor(up_0_0);
            LeftPlane[1][0]->setLeftColor(up_0_1);
            LeftPlane[0][0]->setLeftColor(up_0_2);

        } else if (degree == '-') {
            outputStream << "B' ";

            string back_0_0 = BackPlane[0][0]->BackColor(),
                    back_0_1 = BackPlane[0][1]->BackColor();

            BackPlane[0][0]->setBackColor(BackPlane[0][2]->BackColor());
            BackPlane[0][1]->setBackColor(BackPlane[1][2]->BackColor());
            BackPlane[0][2]->setBackColor(BackPlane[2][2]->BackColor());
            BackPlane[1][2]->setBackColor(BackPlane[2][1]->BackColor());
            BackPlane[2][2]->setBackColor(BackPlane[2][0]->BackColor());
            BackPlane[2][1]->setBackColor(BackPlane[1][0]->BackColor());
            BackPlane[2][0]->setBackColor(back_0_0);
            BackPlane[1][0]->setBackColor(back_0_1);

            UpPlane[0][0]->setUpColor(LeftPlane[2][0]->LeftColor());
            UpPlane[0][1]->setUpColor(LeftPlane[1][0]->LeftColor());
            UpPlane[0][2]->setUpColor(LeftPlane[0][0]->LeftColor());

            LeftPlane[0][0]->setLeftColor(DownPlane[2][0]->DownColor());
            LeftPlane[1][0]->setLeftColor(DownPlane[2][1]->DownColor());
            LeftPlane[2][0]->setLeftColor(DownPlane[2][2]->DownColor());

            DownPlane[2][0]->setDownColor(RightPlane[2][2]->RightColor());
            DownPlane[2][1]->setDownColor(RightPlane[1][2]->RightColor());
            DownPlane[2][2]->setDownColor(RightPlane[0][2]->RightColor());

            RightPlane[0][2]->setRightColor(up_0_0);
            RightPlane[1][2]->setRightColor(up_0_1);
            RightPlane[2][2]->setRightColor(up_0_2);
        }
    }

    void RotateMany(string commandsSeq) {
        int size = commandsSeq.size();
        for (int i = 0; i < size; i += 2) {
            if (commandsSeq[i] == 'U') {
                if ( commandsSeq[i + 1] == ' ')
                    RotateUpPlane('+');
                else RotateUpPlane('-');
            }

            if (commandsSeq[i] == 'D') {
                if (commandsSeq[i + 1] == ' ')
                    RotateDownPlane('+');
                else RotateDownPlane('-');
            }

            if (commandsSeq[i] == 'L') {
                if (commandsSeq[i + 1] == ' ')
                    RotateLeftPlane('+');
                else RotateLeftPlane('-');
            }

            if (commandsSeq[i] == 'R') {
                if (commandsSeq[i + 1] == ' ')
                    RotateRightPlane('+');
                else
                    RotateRightPlane('-');
            }

            if (commandsSeq[i] == 'F') {
                if (commandsSeq[i + 1] == ' ')
                    RotateFrontPlane('+');
                else RotateFrontPlane('-');
            }

            if (commandsSeq[i] == 'B') {
                if (commandsSeq[i + 1] == ' ')
                    RotateBackPlane('+');
                else RotateBackPlane('-');
            }
        }
    }

    void RightAlgorithm() {
        this->RotateRightPlane('+');
        this->RotateUpPlane('+');
        this->RotateRightPlane('-');
        this->RotateUpPlane('-');
    }

    void LeftAlgorithm() {
        this->RotateLeftPlane('+');
        this->RotateUpPlane('+');
        this->RotateLeftPlane('-');
        this->RotateUpPlane('-');
    }

    void UpAlgorithm() {
        this->RotateUpPlane('+');
        this->RotateLeftPlane('+');
        this->RotateUpPlane('-');
        this->RotateLeftPlane('-');
    }

    void DownAlgorithm() {
        this->RotateDownPlane('-');
        this->RotateRightPlane('-');
        this->RotateDownPlane('+');
        this->RotateLeftPlane('+');
    }

    void Shuffle(int count_turns = 10 + rand() % 5) {
        for (int i = 0; i < count_turns; ++i) {
            int temp = 1 + rand() % 4;
            switch (temp) {
                case (1):
                    RightAlgorithm();
                    break;
                case (2):
                    LeftAlgorithm();
                    break;
                case (3):
                    UpAlgorithm();
                    break;
                case (4):
                    DownAlgorithm();
                    break;
                default:
                    break;
            }
        }
    }


    [[nodiscard]] bool isFirstStepCompleted() const {
        bool isDownCompleted = (DownPlane[1][0]->DownColor() == DownCenter) &&
                               (DownPlane[1][2]->DownColor() == DownCenter) &&
                               (DownPlane[0][1]->DownColor() == DownCenter) &&
                               (DownPlane[2][1]->DownColor() == DownCenter);

        bool isLeftCompleted = LeftCenter == LeftPlane[2][1]->LeftColor();
        bool isRightCompleted = RightCenter == RightPlane[2][1]->RightColor();
        bool isFrontCompleted = FrontCenter == FrontPlane[2][1]->FrontColor();
        bool isBackCompleted = BackCenter == BackPlane[2][1]->BackColor();

        bool isCompleted =
                isDownCompleted && isLeftCompleted && isRightCompleted && isFrontCompleted && isBackCompleted;

        return isCompleted;
    }

    [[nodiscard]] bool isSecondStepCompleted() const {

        bool isFirstCompleted = isFirstStepCompleted();

        bool isDownCompleted = (DownPlane[0][0]->DownColor() == DownCenter) &&
                               (DownPlane[0][2]->DownColor() == DownCenter) &&
                               (DownPlane[2][0]->DownColor() == DownCenter) &&
                               (DownPlane[2][2]->DownColor() == DownCenter);

        bool isLeftCompleted = LeftPlane[2][0]->LeftColor() == LeftCenter &&
                               LeftPlane[2][2]->LeftColor() == LeftCenter;

        bool isRightCompleted = RightPlane[2][0]->RightColor() == RightCenter &&
                                RightPlane[2][2]->RightColor() == RightCenter;

        bool isFrontCompleted = FrontPlane[2][0]->FrontColor() == FrontCenter &&
                                FrontPlane[2][2]->FrontColor() == FrontCenter;

        bool isBackCompleted = BackPlane[2][0]->BackColor() == BackCenter &&
                               BackPlane[2][2]->BackColor() == BackCenter;

        bool isCompleted =
                isFirstCompleted && isDownCompleted && isLeftCompleted && isRightCompleted && isFrontCompleted &&
                isBackCompleted;

        return isCompleted;
    }

    [[nodiscard]] bool isThirdStepCompleted() const {

        bool isSecondCompleted = isSecondStepCompleted();

        bool isLeftCompleted = LeftPlane[1][0]->LeftColor() == LeftCenter &&
                               LeftPlane[1][2]->LeftColor() == LeftCenter;

        bool isFrontCompleted = FrontPlane[1][0]->FrontColor() == FrontCenter &&
                                FrontPlane[1][2]->FrontColor() == FrontCenter;

        bool isRightCompleted = RightPlane[1][0]->RightColor() == RightCenter &&
                                RightPlane[1][2]->RightColor() == RightCenter;

        bool isBackCompleted = BackPlane[1][0]->BackColor() == BackCenter &&
                               BackPlane[1][2]->BackColor() == BackCenter;

        bool isCompleted =
                isSecondCompleted && isLeftCompleted && isRightCompleted && isFrontCompleted && isBackCompleted;

        return isCompleted;
    }

    [[nodiscard]] bool isFourthStepCompleted() const {
        bool isThirdCompleted = isThirdStepCompleted();

        bool isUpCompleted =
                UpPlane[0][1]->UpColor() == UpCenter && UpPlane[1][0]->UpColor() == UpCenter &&
                UpPlane[1][2]->UpColor() == UpCenter && UpPlane[2][1]->UpColor() == UpCenter;

        bool isCompleted = isThirdCompleted && isUpCompleted;

        return isCompleted;
    }

    [[nodiscard]] bool isFifthStepCompleted() const {
        bool isFourthCompleted = isFourthStepCompleted();

        bool isLeftCompleted = LeftPlane[0][1]->LeftColor() == LeftCenter;

        bool isRightCompleted = RightPlane[0][1]->RightColor() == RightCenter;

        bool isFrontCompleted = FrontPlane[0][1]->FrontColor() == FrontCenter;

        bool isBackCompleted = BackPlane[0][1]->BackColor() == BackCenter;

        bool isCompleted =
                isFourthCompleted && isLeftCompleted && isRightCompleted && isFrontCompleted && isBackCompleted;

        return isCompleted;
    }

    [[nodiscard]] bool isSixthStepCompleted() const {
        bool isFifthCompleted = isFifthStepCompleted();

        bool isLeftCornersCompleted = LeftPlane[0][0]->LeftColor() == LeftCenter ||
                                      LeftPlane[0][0]->LeftColor() == BackCenter ||
                                      LeftPlane[0][0]->LeftColor() == UpCenter &&
                                      LeftPlane[0][2]->LeftColor() == LeftCenter ||
                                      LeftPlane[0][2]->LeftColor() == FrontCenter ||
                                      LeftPlane[0][2]->LeftColor() == UpCenter;

        bool isBackCornersCompleted = BackPlane[0][0]->BackColor() == BackCenter ||
                                      BackPlane[0][0]->BackColor() == RightCenter ||
                                      BackPlane[0][0]->BackColor() == UpCenter &&
                                      BackPlane[0][2]->BackColor() == BackCenter ||
                                      BackPlane[0][2]->BackColor() == LeftCenter ||
                                      BackPlane[0][2]->BackColor() == UpCenter;

        bool isRightCornersCompleted = RightPlane[0][0]->RightColor() == RightCenter ||
                                       RightPlane[0][0]->RightColor() == FrontCenter ||
                                       RightPlane[0][0]->RightColor() == UpCenter &&
                                       RightPlane[0][2]->RightColor() == RightCenter ||
                                       RightPlane[0][2]->RightColor() == BackCenter ||
                                       RightPlane[0][2]->RightColor() == UpCenter;

        bool isFrontCornersCompleted = FrontPlane[0][0]->FrontColor() == FrontCenter ||
                                       FrontPlane[0][0]->FrontColor() == LeftCenter ||
                                       FrontPlane[0][0]->FrontColor() == UpCenter &&
                                       FrontPlane[0][2]->FrontColor() == FrontCenter ||
                                       FrontPlane[0][2]->FrontColor() == RightCenter ||
                                       FrontPlane[0][2]->FrontColor() == UpCenter;

        bool isUpCornersCompleted =
                UpPlane[0][0]->UpColor() != FrontCenter && UpPlane[0][0]->UpColor() != RightCenter &&
                (UpPlane[0][0]->UpColor() == LeftCenter || UpPlane[0][0]->UpColor() == BackCenter ||
                 UpPlane[0][0]->UpColor() == UpCenter) &&
                UpPlane[0][2]->UpColor() != FrontCenter && UpPlane[0][2]->UpColor() != LeftCenter &&
                (UpPlane[0][2]->UpColor() == RightCenter || UpPlane[0][2]->UpColor() == BackCenter ||
                 UpPlane[0][2]->UpColor() == UpCenter) &&
                UpPlane[2][0]->UpColor() != BackCenter && UpPlane[2][0]->UpColor() != RightCenter &&
                (UpPlane[2][0]->UpColor() == LeftCenter || UpPlane[2][0]->UpColor() == FrontCenter ||
                 UpPlane[2][0]->UpColor() == UpCenter) &&
                UpPlane[2][2]->UpColor() != BackCenter && UpPlane[2][2]->UpColor() != LeftCenter &&
                (UpPlane[2][2]->UpColor() == RightCenter || UpPlane[2][2]->UpColor() == FrontCenter ||
                 UpPlane[2][2]->UpColor() == UpCenter);

        bool isCompleted =
                isFifthCompleted && isLeftCornersCompleted && isRightCornersCompleted && isFrontCornersCompleted &&
                isBackCornersCompleted && isUpCornersCompleted;

        return isCompleted;
    }

    [[nodiscard]] bool isCubeCompleted() const {
        if (!CheckIfCubeCorrect())
            throw exception();

        bool isFifthCompleted = isFifthStepCompleted();

        bool isFrontCornersCompleted =
                FrontPlane[0][0]->FrontColor() == FrontCenter && FrontPlane[0][2]->FrontColor() == FrontCenter;

        bool isBackCornersCompleted =
                BackPlane[0][0]->BackColor() == BackCenter && BackPlane[0][2]->BackColor() == BackCenter;

        bool isLeftCornersCompleted =
                LeftPlane[0][0]->LeftColor() == LeftCenter && LeftPlane[0][2]->LeftColor() == LeftCenter;

        bool isRightCornersCompleted =
                RightPlane[0][0]->RightColor() == RightCenter && RightPlane[0][2]->RightColor() == RightCenter;

        bool isCompleted =
                isFifthCompleted && isFrontCornersCompleted && isBackCornersCompleted && isLeftCornersCompleted &&
                isRightCornersCompleted;

        return isCompleted;

    }

    void FirstStep(int count = 0) {
        if (FirstStepCounter++ > 1024)
            throw exception();

        if (!isFirstStepCompleted()) {
            if (FrontCenter == FrontPlane[0][1]->FrontColor() && UpPlane[2][1]->UpColor() == DownCenter) {
                RotateMany("F F ");
                FirstStep(0);
            }
            if (RightCenter == RightPlane[0][1]->RightColor() && UpPlane[1][2]->UpColor() == DownCenter) {
                RotateMany("R R ");
                FirstStep(0);
            }
            if (LeftCenter == LeftPlane[0][1]->LeftColor() && UpPlane[1][0]->UpColor() == DownCenter) {
                RotateMany("L L ");
                FirstStep(0);
            }
            if (BackCenter == BackPlane[0][1]->BackColor() && UpPlane[0][1]->UpColor() == DownCenter) {
                RotateMany("B B ");
                FirstStep(0);
            }
            if (FrontPlane[0][1]->FrontColor() == DownCenter && UpPlane[2][1]->UpColor() == FrontCenter) {
                RotateMany("U'R'F R ");
                FirstStep(0);
            }
            if (UpPlane[1][2]->UpColor() == RightCenter && RightPlane[0][1]->RightColor() == DownCenter) {
                RotateMany("U'B'R B ");
                FirstStep(0);
            }
            if (LeftPlane[0][1]->LeftColor() == DownCenter && UpPlane[1][0]->UpColor() == LeftCenter) {
                RotateMany("U'F'L F ");
                FirstStep(0);
            }
            if (BackPlane[0][1]->BackColor() == DownCenter && UpPlane[0][1]->UpColor() == BackCenter) {
                RotateMany("U'L'B L ");
                FirstStep(0);
            }
            if (FrontPlane[1][2]->FrontColor() == DownCenter) {
                RotateMany("F'U'F ");
                FirstStep(0);
            }
            if (RightPlane[1][2]->RightColor() == DownCenter) {
                RotateMany("R'U'R ");
                FirstStep(0);
            }
            if (LeftPlane[1][2]->LeftColor() == DownCenter) {
                RotateMany("L'U'L ");
                FirstStep(0);
            }
            if (BackPlane[1][2]->BackColor() == DownCenter) {
                RotateMany("B'U'B ");
                FirstStep(0);
            }
            if (FrontPlane[1][0]->FrontColor() == DownCenter) {
                RotateMany("F U'F'");
                FirstStep(0);
            }
            if (RightPlane[1][0]->RightColor() == DownCenter) {
                RotateMany("R U'R'");
                FirstStep(0);
            }
            if (LeftPlane[1][0]->LeftColor() == DownCenter) {
                RotateMany("L U'L'");
                FirstStep(0);
            }
            if (BackPlane[1][0]->BackColor() == DownCenter) {
                RotateMany("B U'B'");
                FirstStep(0);
            }
            if (FrontPlane[2][1]->FrontColor() == DownCenter) {
                RotateMany("F F U'F F ");
                FirstStep(0);
            }
            if (RightPlane[2][1]->RightColor() == DownCenter) {
                RotateMany("R R U'R R ");
                FirstStep(0);
            }
            if (LeftPlane[2][1]->LeftColor() == DownCenter) {
                RotateMany("L L U'L L ");
                FirstStep(0);
            }
            if (BackPlane[2][1]->BackColor() == DownCenter) {
                RotateMany("B B U'B B ");
                FirstStep(0);
            }
            if (DownPlane[0][1]->DownColor() == DownCenter && FrontPlane[2][1]->FrontColor() != FrontCenter) {
                RotateMany("F'F'U'F'F'");
                FirstStep(0);
            }
            if (DownPlane[1][2]->DownColor() == DownCenter && RightPlane[2][1]->RightColor() != RightCenter) {
                RotateMany("R'R'U'R'R'");
                FirstStep(0);
            }
            if (DownPlane[1][0]->DownColor() == DownCenter && LeftPlane[2][1]->LeftColor() != LeftCenter) {
                RotateMany("L'L'U'L'L'");
                FirstStep(0);
            }
            if (DownPlane[2][1]->DownColor() == DownCenter && BackPlane[2][1]->BackColor() != BackCenter) {
                RotateMany("B'B'U'B'B'");
                FirstStep(0);
            }
            if (!isFirstStepCompleted() && count < 4) {
                RotateMany("U ");
                FirstStep(++count);
            } else if (!isFirstStepCompleted() && count == 4) {
                Shuffle( 3);
                FirstStep(0);
            }
        }
    }

    void SecondStep(int count = 0) {
        if (SecondStepCounter++ > 1024)
            throw exception();

        if (!isSecondStepCompleted()) {
            if (FrontPlane[2][1]->FrontColor() == FrontCenter && FrontPlane[0][2]->FrontColor() == DownCenter &&
                UpPlane[2][2]->UpColor() == FrontCenter && RightPlane[0][0]->RightColor() == RightCenter &&
                RightPlane[2][1]->RightColor() == RightCenter) {
                RotateMany("F'U'F ");
                SecondStep(0);
            }
            if (FrontPlane[0][0]->FrontColor() == FrontCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                UpPlane[2][0]->UpColor() == LeftCenter && LeftPlane[0][2]->LeftColor() == DownCenter &&
                LeftPlane[2][1]->LeftColor() == LeftCenter) {
                RotateMany("L'U'L ");
                SecondStep(0);
            }
            if (BackPlane[0][0]->BackColor() == BackCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                UpPlane[0][2]->UpColor() == RightCenter && RightPlane[0][2]->RightColor() == DownCenter &&
                RightPlane[2][1]->RightColor() == RightCenter) {
                RotateMany("R'U'R ");
                SecondStep(0);
            }
            if (BackPlane[0][2]->BackColor() == DownCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                LeftPlane[0][0]->LeftColor() == LeftCenter && LeftPlane[2][1]->LeftColor() == LeftCenter &&
                UpPlane[0][0]->UpColor() == BackCenter) {
                RotateMany("B'U'B ");
                SecondStep(0);
            }
            if (FrontPlane[0][2]->FrontColor() == FrontCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                RightPlane[0][0]->RightColor() == DownCenter && RightPlane[2][1]->RightColor() == RightCenter &&
                UpPlane[2][2]->UpColor() == RightCenter) {
                RotateMany("R U R'");
                SecondStep(0);
            }
            if (FrontPlane[0][0]->FrontColor() == DownCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                UpPlane[2][0]->UpColor() == FrontCenter && LeftPlane[0][2]->LeftColor() == LeftCenter &&
                LeftPlane[2][1]->LeftColor() == LeftCenter) {
                RotateMany("F U F'");
                SecondStep(0);
            }
            if (BackPlane[0][0]->BackColor() == DownCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                UpPlane[0][2]->UpColor() == BackCenter && RightPlane[0][2]->RightColor() == RightCenter &&
                RightPlane[2][1]->RightColor() == RightCenter) {
                RotateMany("B U B'");
                SecondStep(0);
            }
            if (BackPlane[0][2]->BackColor() == BackCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                LeftPlane[0][0]->LeftColor() == DownCenter && LeftPlane[2][1]->LeftColor() == LeftCenter &&
                UpPlane[0][0]->UpColor() == LeftCenter) {
                RotateMany("L U L'");
                SecondStep(0);
            }
            if (FrontPlane[0][2]->FrontColor() == RightCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                RightPlane[0][0]->RightColor() == FrontCenter && RightPlane[2][1]->RightColor() == RightCenter &&
                UpPlane[2][2]->UpColor() == DownCenter) {
                RotateMany("R U'R'U U R U R'");
                SecondStep(0);
            }
            if (FrontPlane[0][0]->FrontColor() == LeftCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                UpPlane[2][0]->UpColor() == DownCenter && RightPlane[0][2]->RightColor() == FrontCenter &&
                RightPlane[2][1]->RightColor() == RightCenter) {
                RotateMany("F U'F'U U F U F'");
                SecondStep(0);
            }
            if (BackPlane[0][0]->BackColor() == RightCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                UpPlane[0][2]->UpColor() == DownCenter && RightPlane[0][2]->RightColor() == BackCenter &&
                RightPlane[2][1]->RightColor() == RightCenter) {
                RotateMany("B U'B'U U B U B'");
                SecondStep(0);
            }
            if (BackPlane[0][2]->BackColor() == LeftCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                LeftPlane[0][0]->LeftColor() == BackCenter && LeftPlane[2][1]->LeftColor() == LeftCenter &&
                UpPlane[0][0]->UpColor() == DownCenter) {
                RotateMany("L U'L'U U L U L'");
                SecondStep(0);
            }
            if (FrontPlane[2][1]->FrontColor() == FrontCenter && RightPlane[2][1]->RightColor() == RightCenter &&
                (FrontPlane[2][2]->FrontColor() == DownCenter || RightPlane[2][0]->RightColor() == DownCenter)) {
                RotateMany("F'U'F ");
                SecondStep(0);
            }
            if (FrontPlane[2][1]->FrontColor() == FrontCenter && LeftPlane[2][1]->LeftColor() == LeftCenter &&
                (LeftPlane[2][2]->LeftColor() == DownCenter || FrontPlane[2][0]->FrontColor() == DownCenter)) {
                RotateMany("L'U'L ");
                SecondStep(0);
            }
            if (BackPlane[2][1]->BackColor() == BackCenter && RightPlane[2][1]->RightColor() == RightCenter &&
                (RightPlane[2][2]->RightColor() == DownCenter || BackPlane[2][0]->BackColor() == DownCenter)) {
                RotateMany("R'U'R ");
                SecondStep(0);
            }
            if (BackPlane[2][1]->BackColor() == BackCenter && LeftPlane[2][1]->LeftColor() == LeftCenter &&
                (BackPlane[2][2]->BackColor() == DownCenter || LeftPlane[2][0]->LeftColor() == DownCenter)) {
                RotateMany("B'U'B ");
                SecondStep(0);
            }
            if (LeftPlane[2][1]->LeftColor() == LeftCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                DownPlane[0][0]->DownColor() == DownCenter && DownPlane[0][1]->DownColor() == DownCenter &&
                DownPlane[1][0]->DownColor() == DownCenter && DownPlane[1][2]->DownColor() == DownCenter &&
                DownPlane[2][1]->DownColor() == DownCenter && (FrontPlane[2][0]->FrontColor() != FrontCenter ||
                                                               LeftPlane[2][2]->LeftColor() != LeftCenter)) {
                RotateMany("F U'F'");
                SecondStep(0);
            }
            if (RightPlane[2][1]->RightColor() == RightCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                DownPlane[0][1]->DownColor() == DownCenter && DownPlane[0][2]->DownColor() == DownCenter &&
                DownPlane[1][0]->DownColor() == DownCenter && DownPlane[1][2]->DownColor() == DownCenter &&
                DownPlane[2][1]->DownColor() == DownCenter && (FrontPlane[2][2]->FrontColor() != FrontCenter ||
                                                               RightPlane[2][0]->RightColor() != RightCenter)) {
                RotateMany("R U'R'");
                SecondStep(0);
            }
            if (BackPlane[2][1]->BackColor() == BackCenter && RightPlane[2][1]->RightColor() == RightCenter &&
                DownPlane[2][2]->DownColor() == DownCenter && DownPlane[2][1]->DownColor() == DownCenter &&
                DownPlane[1][2]->DownColor() == DownCenter && DownPlane[1][0]->DownColor() == DownCenter &&
                DownPlane[0][1]->DownColor() == DownCenter && (BackPlane[2][0]->BackColor() != BackCenter ||
                                                               RightPlane[2][2]->RightColor() != RightCenter)) {
                RotateMany("B U'B'");
                SecondStep(0);
            }
            if (BackPlane[2][1]->BackColor() == BackCenter && LeftPlane[2][1]->LeftColor() == LeftCenter &&
                DownPlane[2][0]->DownColor() == DownCenter && DownPlane[2][1]->DownColor() == DownCenter &&
                DownPlane[1][2]->DownColor() == DownCenter && DownPlane[1][0]->DownColor() == DownCenter &&
                DownPlane[0][1]->DownColor() == DownCenter && (BackPlane[2][2]->BackColor() != BackCenter ||
                                                               LeftPlane[2][0]->LeftColor() != LeftCenter)) {
                RotateMany("L U'L'");
                SecondStep(0);
            }
            if (!isSecondStepCompleted() && count < 4) {
                RotateMany("U ");
                SecondStep(++count);
            } else if (!isSecondStepCompleted() && count == 4) {
                Shuffle( 3);
                FirstStep(0);
                SecondStep(0);
            }
        }
    }

    void ThirdStep(int count = 0) {
        if (ThirdStepCounter++ > 1024)
            throw exception();

        if (!isThirdStepCompleted()) {
            if (FrontPlane[2][2]->FrontColor() == FrontCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                FrontPlane[2][0]->FrontColor() == FrontCenter && FrontPlane[0][1]->FrontColor() == FrontCenter &&
                LeftPlane[2][2]->LeftColor() == LeftCenter && LeftPlane[2][1]->LeftColor() == LeftCenter &&
                LeftPlane[2][0]->LeftColor() == LeftCenter && UpPlane[2][1]->UpColor() == LeftCenter) {
                RotateMany("U'L'U L U F U'F'");
                ThirdStep(0);
            }
            if (FrontPlane[2][2]->FrontColor() == FrontCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                FrontPlane[2][0]->FrontColor() == FrontCenter && RightPlane[2][2]->RightColor() == RightCenter &&
                RightPlane[2][1]->RightColor() == RightCenter && RightPlane[2][0]->RightColor() == RightCenter &&
                RightPlane[0][1]->RightColor() == RightCenter && UpPlane[1][2]->UpColor() == FrontCenter) {
                RotateMany("U'F'U F U R U'R'");
                ThirdStep(0);
            }
            if (BackPlane[2][2]->BackColor() == BackCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                BackPlane[2][0]->BackColor() == BackCenter && BackPlane[0][1]->BackColor() == BackCenter &&
                RightPlane[2][2]->RightColor() == RightCenter && RightPlane[2][1]->RightColor() == RightCenter &&
                RightPlane[2][0]->RightColor() == RightCenter && UpPlane[0][1]->UpColor() == RightCenter) {
                RotateMany("U'R'U R U B U'B'");
                ThirdStep(0);
            }
            if (BackPlane[2][2]->BackColor() == BackCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                BackPlane[2][0]->BackColor() == BackCenter && LeftPlane[0][1]->LeftColor() == LeftCenter &&
                LeftPlane[2][2]->LeftColor() == LeftCenter && LeftPlane[2][1]->LeftColor() == LeftCenter &&
                LeftPlane[2][0]->LeftColor() == LeftCenter && UpPlane[1][0]->UpColor() == BackCenter) {
                RotateMany("U'B'U B U L U'L'");
                ThirdStep(0);
            }
            if (RightPlane[2][2]->RightColor() == RightCenter && RightPlane[2][1]->RightColor() == RightCenter &&
                RightPlane[2][0]->RightColor() == RightCenter && FrontPlane[0][1]->FrontColor() == FrontCenter &&
                FrontPlane[2][2]->FrontColor() == FrontCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                FrontPlane[2][0]->FrontColor() == FrontCenter && UpPlane[2][1]->UpColor() == RightCenter) {
                RotateMany("U R U'R'U'F'U F ");
                ThirdStep(0);
            }
            if (FrontPlane[2][2]->FrontColor() == FrontCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                FrontPlane[2][0]->FrontColor() == FrontCenter && LeftPlane[0][1]->LeftColor() == LeftCenter &&
                LeftPlane[2][2]->LeftColor() == LeftCenter && LeftPlane[2][1]->LeftColor() == LeftCenter &&
                LeftPlane[2][0]->LeftColor() == LeftCenter && UpPlane[1][0]->UpColor() == FrontCenter) {
                RotateMany("U F U'F'U'L'U L ");
                ThirdStep(0);
            }
            if (LeftPlane[2][2]->LeftColor() == LeftCenter && LeftPlane[2][1]->LeftColor() == LeftCenter &&
                LeftPlane[2][0]->LeftColor() == LeftCenter && BackPlane[0][1]->BackColor() == BackCenter &&
                BackPlane[2][2]->BackColor() == BackCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                BackPlane[2][0]->BackColor() == BackCenter && UpPlane[0][1]->UpColor() == LeftCenter) {
                RotateMany("U L U'L'U'B'U B ");
                ThirdStep(0);
            }
            if (BackPlane[2][2]->BackColor() == BackCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                BackPlane[2][0]->BackColor() == BackCenter && RightPlane[0][1]->RightColor() == RightCenter &&
                RightPlane[2][2]->RightColor() == RightCenter && RightPlane[2][1]->RightColor() == RightCenter &&
                RightPlane[2][0]->RightColor() == RightCenter && UpPlane[1][2]->UpColor() == BackCenter) {
                RotateMany("U B U'B'U'R'U R ");
                ThirdStep(0);
            }
            if (!isThirdStepCompleted() && count < 4) {
                RotateMany("U ");
                ThirdStep(++count);
            } else if (count == 4 && !isThirdStepCompleted()) {
                if (FrontPlane[2][2]->FrontColor() == FrontCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                    FrontPlane[2][0]->FrontColor() == FrontCenter && RightPlane[2][2]->RightColor() == RightCenter &&
                    RightPlane[2][1]->RightColor() == RightCenter && RightPlane[2][0]->RightColor() == RightCenter &&
                    (FrontPlane[1][2]->FrontColor() != FrontCenter || RightPlane[1][0]->RightColor() != RightCenter)) {
                    RotateMany("U R U'R'U'F'U F ");
                    ThirdStep(0);
                } else if (
                        FrontPlane[2][2]->FrontColor() == FrontCenter &&
                        FrontPlane[2][1]->FrontColor() == FrontCenter &&
                        FrontPlane[2][0]->FrontColor() == FrontCenter && LeftPlane[2][2]->LeftColor() == LeftCenter &&
                        LeftPlane[2][1]->LeftColor() == LeftCenter && LeftPlane[2][0]->LeftColor() == LeftCenter &&
                        (FrontPlane[1][0]->FrontColor() != FrontCenter || LeftPlane[1][2]->LeftColor() != LeftCenter)) {
                    RotateMany("U F U'F'U'L'U L ");
                    ThirdStep(0);
                } else if (
                        BackPlane[2][2]->BackColor() == BackCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                        BackPlane[2][0]->BackColor() == BackCenter && LeftPlane[2][2]->LeftColor() == LeftCenter &&
                        LeftPlane[2][1]->LeftColor() == LeftCenter && LeftPlane[2][0]->LeftColor() == LeftCenter &&
                        (BackPlane[1][2]->BackColor() != BackCenter || LeftPlane[1][0]->LeftColor() != LeftCenter)) {
                    RotateMany("U L U'L'U'B'U B ");
                    ThirdStep(0);
                } else if (
                        BackPlane[2][2]->BackColor() == BackCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                        BackPlane[2][0]->BackColor() == BackCenter && RightPlane[2][2]->RightColor() == RightCenter &&
                        RightPlane[2][1]->RightColor() == RightCenter &&
                        RightPlane[2][0]->RightColor() == RightCenter &&
                        (BackPlane[1][0]->BackColor() != BackCenter || RightPlane[1][2]->RightColor() != RightCenter)) {
                    RotateMany("U B U'B'U'R'U R ");
                    ThirdStep(0);
                }
            }

            if (!isThirdStepCompleted() && count == 4) {
                Shuffle( 3);
                SecondStep(0);
                ThirdStep(0);
            }
        }
    }

    void FourthStep() {
        if (FourthStepCounter++ > 1024)
            throw exception();

        if (!isFourthStepCompleted()) {
            if (FrontPlane[0][1]->FrontColor() == UpCenter && FrontPlane[1][0]->FrontColor() == FrontCenter &&
                FrontPlane[1][2]->FrontColor() == FrontCenter && FrontPlane[2][0]->FrontColor() == FrontCenter &&
                FrontPlane[2][1]->FrontColor() == FrontCenter && FrontPlane[2][2]->FrontColor() == FrontCenter &&
                RightPlane[0][1]->RightColor() == UpCenter && RightPlane[1][0]->RightColor() == RightCenter &&
                RightPlane[1][2]->RightColor() == RightCenter && RightPlane[2][0]->RightColor() == RightCenter &&
                RightPlane[2][1]->RightColor() == RightCenter && RightPlane[2][2]->RightColor() == RightCenter &&
                UpPlane[0][1]->UpColor() == UpCenter && UpPlane[1][0]->UpColor() == UpCenter) {
                RotateMany("F U R U'R'F'");
                FourthStep();
            }
            if (FrontPlane[0][1]->FrontColor() == UpCenter && FrontPlane[1][0]->FrontColor() == FrontCenter &&
                FrontPlane[1][2]->FrontColor() == FrontCenter && FrontPlane[2][0]->FrontColor() == FrontCenter &&
                FrontPlane[2][1]->FrontColor() == FrontCenter && FrontPlane[2][2]->FrontColor() == FrontCenter &&
                LeftPlane[0][1]->LeftColor() == UpCenter && LeftPlane[1][0]->LeftColor() == LeftCenter &&
                LeftPlane[1][2]->LeftColor() == LeftCenter && LeftPlane[2][0]->LeftColor() == LeftCenter &&
                LeftPlane[2][1]->LeftColor() == LeftCenter && LeftPlane[2][2]->LeftColor() == LeftCenter &&
                UpPlane[0][1]->UpColor() == UpCenter && UpPlane[1][2]->UpColor() == UpCenter) {
                RotateMany("L U F U'F'L'");
                FourthStep();
            }
            if (BackPlane[0][1]->BackColor() == UpCenter && BackPlane[1][0]->BackColor() == BackCenter &&
                BackPlane[1][2]->BackColor() == BackCenter && BackPlane[2][0]->BackColor() == BackCenter &&
                BackPlane[2][1]->BackColor() == BackCenter && BackPlane[2][2]->BackColor() == BackCenter &&
                RightPlane[0][1]->RightColor() == UpCenter && RightPlane[1][0]->RightColor() == RightCenter &&
                RightPlane[1][2]->RightColor() == RightCenter && RightPlane[2][0]->RightColor() == RightCenter &&
                RightPlane[2][1]->RightColor() == RightCenter && RightPlane[2][2]->RightColor() == RightCenter &&
                UpPlane[1][0]->UpColor() == UpCenter && UpPlane[2][1]->UpColor() == UpCenter) {
                RotateMany("R U B U'B'R'");
                FourthStep();
            }
            if (BackPlane[0][1]->BackColor() == UpCenter && BackPlane[1][0]->BackColor() == BackCenter &&
                BackPlane[1][2]->BackColor() == BackCenter && BackPlane[2][0]->BackColor() == BackCenter &&
                BackPlane[2][1]->BackColor() == BackCenter && BackPlane[2][2]->BackColor() == BackCenter &&
                LeftPlane[0][1]->LeftColor() == UpCenter && LeftPlane[1][0]->LeftColor() == LeftCenter &&
                LeftPlane[1][2]->LeftColor() == LeftCenter && LeftPlane[2][0]->LeftColor() == LeftCenter &&
                LeftPlane[2][1]->LeftColor() == LeftCenter && LeftPlane[2][2]->LeftColor() == LeftCenter &&
                UpPlane[1][2]->UpColor() == UpCenter && UpPlane[2][1]->UpColor() == UpCenter) {
                RotateMany("B U L U'L'B'");
                FourthStep();
            }
            if (FrontPlane[0][1]->FrontColor() == UpCenter && FrontPlane[1][0]->FrontColor() == FrontCenter &&
                FrontPlane[1][2]->FrontColor() == FrontCenter && FrontPlane[2][0]->FrontColor() == FrontCenter &&
                FrontPlane[2][1]->FrontColor() == FrontCenter && FrontPlane[2][2]->FrontColor() == FrontCenter &&
                RightPlane[1][0]->RightColor() == RightCenter && RightPlane[1][2]->RightColor() == RightCenter &&
                RightPlane[2][0]->RightColor() == RightCenter && RightPlane[2][1]->RightColor() == RightCenter &&
                RightPlane[2][2]->RightColor() == RightCenter && UpPlane[1][0]->UpColor() == UpCenter &&
                UpPlane[1][2]->UpColor() == UpCenter && BackPlane[0][1]->BackColor() == UpCenter) {
                RotateMany("F R U R'U'F'");
                FourthStep();
            }
            if (FrontPlane[1][0]->FrontColor() == FrontCenter && FrontPlane[1][2]->FrontColor() == FrontCenter &&
                FrontPlane[2][0]->FrontColor() == FrontCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                FrontPlane[2][2]->FrontColor() == FrontCenter && RightPlane[0][1]->RightColor() == UpCenter &&
                RightPlane[1][0]->RightColor() == RightCenter && RightPlane[1][2]->RightColor() == RightCenter &&
                RightPlane[2][0]->RightColor() == RightCenter && RightPlane[2][1]->RightColor() == RightCenter &&
                RightPlane[2][2]->RightColor() == RightCenter && UpPlane[0][1]->UpColor() == UpCenter &&
                UpPlane[2][1]->UpColor() == UpCenter && LeftPlane[0][1]->LeftColor() == UpCenter) {
                RotateMany("R B U B'U'R'");
                FourthStep();
            }
            if (FrontPlane[1][0]->FrontColor() == FrontCenter && FrontPlane[1][2]->FrontColor() == FrontCenter &&
                FrontPlane[2][0]->FrontColor() == FrontCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                FrontPlane[2][2]->FrontColor() == FrontCenter && RightPlane[1][0]->RightColor() == RightCenter &&
                RightPlane[1][2]->RightColor() == RightCenter && RightPlane[2][0]->RightColor() == RightCenter &&
                RightPlane[2][1]->RightColor() == RightCenter && RightPlane[2][2]->RightColor() == RightCenter &&
                FrontPlane[0][1]->FrontColor() == UpCenter && RightPlane[0][1]->RightColor() == UpCenter &&
                LeftPlane[0][1]->LeftColor() == UpCenter && BackPlane[0][1]->BackColor() == UpCenter) {
                RotateMany("F U R U'R'F'R B U B'U'R'");
                FourthStep();
            }

            if (!isFourthStepCompleted()) {
                Shuffle( 3);
                ThirdStep(0);
                FourthStep();
            }
        }
    }

    void FifthStep(int count = 0) {
        if (FifthStepCounter++ > 1024)
            throw exception();

        if (!isFifthStepCompleted()) {
            if (FrontPlane[1][0]->FrontColor() == FrontCenter && FrontPlane[1][2]->FrontColor() == FrontCenter &&
                FrontPlane[2][0]->FrontColor() == FrontCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                FrontPlane[2][2]->FrontColor() == FrontCenter && RightPlane[1][0]->RightColor() == RightCenter &&
                RightPlane[1][2]->RightColor() == RightCenter && RightPlane[2][0]->RightColor() == RightCenter &&
                RightPlane[2][1]->RightColor() == RightCenter && RightPlane[2][2]->RightColor() == RightCenter &&
                RightPlane[0][1]->RightColor() == FrontCenter && UpPlane[0][1]->UpColor() == UpCenter &&
                UpPlane[1][0]->UpColor() == UpCenter && UpPlane[1][2]->UpColor() == UpCenter &&
                UpPlane[2][1]->UpColor() == UpCenter) {
                RotateMany("U L'U'U'L U L'U L ");
                FifthStep(0);
            }
            if (FrontPlane[1][0]->FrontColor() == FrontCenter && FrontPlane[1][2]->FrontColor() == FrontCenter &&
                FrontPlane[2][0]->FrontColor() == FrontCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                FrontPlane[2][2]->FrontColor() == FrontCenter && LeftPlane[1][0]->LeftColor() == LeftCenter &&
                LeftPlane[1][2]->LeftColor() == LeftCenter && LeftPlane[2][0]->LeftColor() == LeftCenter &&
                LeftPlane[2][1]->LeftColor() == LeftCenter && LeftPlane[2][2]->LeftColor() == LeftCenter &&
                LeftPlane[0][1]->LeftColor() == FrontCenter && UpPlane[0][1]->UpColor() == UpCenter &&
                UpPlane[1][0]->UpColor() == UpCenter && UpPlane[1][2]->UpColor() == UpCenter &&
                UpPlane[2][1]->UpColor() == UpCenter) {
                RotateMany("U B'U'U'B U B'U B ");
                FifthStep(0);
            }
            if (FrontPlane[1][0]->FrontColor() == FrontCenter && FrontPlane[1][2]->FrontColor() == FrontCenter &&
                FrontPlane[2][0]->FrontColor() == FrontCenter && FrontPlane[2][1]->FrontColor() == FrontCenter &&
                FrontPlane[2][2]->FrontColor() == FrontCenter && RightPlane[1][0]->RightColor() == RightCenter &&
                RightPlane[1][2]->RightColor() == RightCenter && RightPlane[2][0]->RightColor() == RightCenter &&
                RightPlane[2][1]->RightColor() == RightCenter && RightPlane[2][2]->RightColor() == RightCenter &&
                BackPlane[0][1]->BackColor() == FrontCenter && UpPlane[0][1]->UpColor() == UpCenter &&
                UpPlane[1][0]->UpColor() == UpCenter && UpPlane[1][2]->UpColor() == UpCenter &&
                UpPlane[2][1]->UpColor() == UpCenter) {
                RotateMany("U R'U'U'R U R'U R U B'U'U'B U B'U B U R'U'U'R U R'U R ");
                FifthStep(0);
            }
            if (BackPlane[1][0]->BackColor() == BackCenter && BackPlane[1][2]->BackColor() == BackCenter &&
                BackPlane[2][0]->BackColor() == BackCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                BackPlane[2][2]->BackColor() == BackCenter && BackPlane[0][1]->BackColor() == RightCenter &&
                RightPlane[1][0]->RightColor() == RightCenter && RightPlane[1][2]->RightColor() == RightCenter &&
                RightPlane[2][0]->RightColor() == RightCenter && RightPlane[2][1]->RightColor() == RightCenter &&
                RightPlane[2][2]->RightColor() == RightCenter && UpPlane[0][1]->UpColor() == UpCenter &&
                UpPlane[1][0]->UpColor() == UpCenter && UpPlane[1][2]->UpColor() == UpCenter &&
                UpPlane[2][1]->UpColor() == UpCenter) {
                RotateMany("U F'U'U'F U F'U F ");
                FifthStep(0);
            }
            if (BackPlane[1][0]->BackColor() == BackCenter && BackPlane[1][2]->BackColor() == BackCenter &&
                BackPlane[2][0]->BackColor() == BackCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                BackPlane[2][2]->BackColor() == BackCenter && RightPlane[1][0]->RightColor() == RightCenter &&
                RightPlane[1][2]->RightColor() == RightCenter && RightPlane[2][0]->RightColor() == RightCenter &&
                RightPlane[2][1]->RightColor() == RightCenter && RightPlane[2][2]->RightColor() == RightCenter &&
                LeftPlane[0][1]->LeftColor() == RightCenter && UpPlane[0][1]->UpColor() == UpCenter &&
                UpPlane[1][0]->UpColor() == UpCenter && UpPlane[1][2]->UpColor() == UpCenter &&
                UpPlane[2][1]->UpColor() == UpCenter) {
                RotateMany("U B'U'U'B U B'U B U L'U'U'L U L'U L U B'U'U'B U B'U B ");
                FifthStep(0);
            }
            if (BackPlane[1][0]->BackColor() == BackCenter && BackPlane[1][2]->BackColor() == BackCenter &&
                BackPlane[2][0]->BackColor() == BackCenter && BackPlane[2][1]->BackColor() == BackCenter &&
                BackPlane[2][2]->BackColor() == BackCenter && LeftPlane[1][0]->LeftColor() == LeftCenter &&
                LeftPlane[1][2]->LeftColor() == LeftCenter && LeftPlane[2][0]->LeftColor() == LeftCenter &&
                LeftPlane[2][1]->LeftColor() == LeftCenter && LeftPlane[2][2]->LeftColor() == LeftCenter &&
                LeftPlane[0][1]->LeftColor() == BackCenter && UpPlane[0][1]->UpColor() == UpCenter &&
                UpPlane[1][0]->UpColor() == UpCenter && UpPlane[1][2]->UpColor() == UpCenter &&
                UpPlane[2][1]->UpColor() == UpCenter) {
                RotateMany("U R'U'U'R U R'U R ");
                FifthStep(0);
            }

            if (!isFifthStepCompleted() && count < 4) {
                FifthStep(++count);
            } else if (!isFifthStepCompleted() && count == 4) {
                Shuffle( 3);
                FourthStep();
                FifthStep(0);
            }
        }
    }

    void SixthStep(int count = 0) {
        if (SixthStepCounter++ > 1024)
            throw exception();

        if (!isSixthStepCompleted()) {
            if (FrontPlane[0][1]->FrontColor() == FrontCenter && FrontPlane[1][0]->FrontColor() == FrontCenter &&
                FrontPlane[1][2]->FrontColor() == FrontCenter && FrontPlane[2][0]->FrontColor() == FrontCenter &&
                FrontPlane[2][1]->FrontColor() == FrontCenter && FrontPlane[2][2]->FrontColor() == FrontCenter &&
                LeftPlane[0][1]->LeftColor() == LeftCenter && LeftPlane[1][0]->LeftColor() == LeftCenter &&
                LeftPlane[1][2]->LeftColor() == LeftCenter && LeftPlane[2][0]->LeftColor() == LeftCenter &&
                LeftPlane[2][1]->LeftColor() == LeftCenter && LeftPlane[2][2]->LeftColor() == LeftCenter &&
                UpPlane[0][1]->UpColor() == UpCenter && UpPlane[0][1]->UpColor() == UpCenter &&
                UpPlane[1][2]->UpColor() == UpCenter && UpPlane[2][1]->UpColor() == UpCenter &&
                (LeftPlane[0][2]->LeftColor() == FrontCenter || LeftPlane[0][2]->LeftColor() == RightCenter ||
                 LeftPlane[0][2]->LeftColor() == UpCenter) && (FrontPlane[0][0]->FrontColor() == RightCenter ||
                                                               FrontPlane[0][0]->FrontColor() == UpCenter ||
                                                               FrontPlane[0][0]->FrontColor() == FrontCenter) &&
                (UpPlane[2][0]->UpColor() == UpCenter || UpPlane[2][0]->UpColor() == RightCenter ||
                 UpPlane[2][0]->UpColor() == FrontCenter)) {

                RotateMany("F'L'F R'F'L F R ");
                SixthStep(0);
            }
            if (BackPlane[0][1]->BackColor() == BackCenter && BackPlane[1][0]->BackColor() == BackCenter &&
                BackPlane[1][2]->BackColor() == BackCenter && BackPlane[2][0]->BackColor() == BackCenter &&
                BackPlane[2][1]->BackColor() == BackCenter && BackPlane[2][2]->BackColor() == BackCenter &&
                RightPlane[0][1]->RightColor() == RightCenter && RightPlane[1][0]->RightColor() == RightCenter &&
                RightPlane[1][2]->RightColor() == RightCenter && RightPlane[2][0]->RightColor() == RightCenter &&
                RightPlane[2][1]->RightColor() == RightCenter && RightPlane[2][2]->RightColor() == RightCenter &&
                UpPlane[0][1]->UpColor() == UpCenter && UpPlane[0][1]->UpColor() == UpCenter &&
                UpPlane[1][2]->UpColor() == UpCenter && UpPlane[2][1]->UpColor() == UpCenter &&
                (RightPlane[0][2]->RightColor() == FrontCenter ||
                 RightPlane[0][2]->RightColor() == RightCenter ||
                 RightPlane[0][2]->RightColor() == UpCenter) &&
                (BackPlane[0][0]->BackColor() == RightCenter || BackPlane[0][0]->BackColor() == UpCenter ||
                 BackPlane[0][0]->BackColor() == FrontCenter) &&
                (UpPlane[0][2]->UpColor() == UpCenter || UpPlane[0][2]->UpColor() == RightCenter ||
                 UpPlane[0][2]->UpColor() == FrontCenter)) {
                RotateMany("R'F'L'F R F'L F ");
                SixthStep(0);
            }
            if (BackPlane[0][1]->BackColor() == BackCenter && BackPlane[1][0]->BackColor() == BackCenter &&
                BackPlane[1][2]->BackColor() == BackCenter && BackPlane[2][0]->BackColor() == BackCenter &&
                BackPlane[2][1]->BackColor() == BackCenter && BackPlane[2][2]->BackColor() == BackCenter &&
                LeftPlane[0][1]->LeftColor() == LeftCenter && LeftPlane[1][0]->LeftColor() == LeftCenter &&
                LeftPlane[1][2]->LeftColor() == LeftCenter && LeftPlane[2][0]->LeftColor() == LeftCenter &&
                LeftPlane[2][1]->LeftColor() == LeftCenter && LeftPlane[2][2]->LeftColor() == LeftCenter &&
                UpPlane[0][1]->UpColor() == UpCenter && UpPlane[0][1]->UpColor() == UpCenter &&
                UpPlane[1][2]->UpColor() == UpCenter && UpPlane[2][1]->UpColor() == UpCenter &&
                (BackPlane[0][2]->BackColor() == FrontCenter || BackPlane[0][2]->BackColor() == UpCenter ||
                 BackPlane[0][2]->BackColor() == RightCenter) &&
                (LeftPlane[0][0]->LeftColor() == RightCenter || LeftPlane[0][0]->LeftColor() == UpCenter ||
                 LeftPlane[0][0]->LeftColor() == FrontCenter) &&
                (UpPlane[0][0]->UpColor() == UpCenter || UpPlane[0][0]->UpColor() == RightCenter ||
                 UpPlane[0][0]->UpColor() == FrontCenter)) {
                RotateMany("F'L'B'L F L'B L ");
                SixthStep(0);
            }
            if (FrontPlane[0][1]->FrontColor() == FrontCenter &&
                FrontPlane[1][0]->FrontColor() == FrontCenter &&
                FrontPlane[1][2]->FrontColor() == FrontCenter &&
                FrontPlane[2][0]->FrontColor() == FrontCenter &&
                FrontPlane[2][1]->FrontColor() == FrontCenter &&
                FrontPlane[2][2]->FrontColor() == FrontCenter &&
                LeftPlane[0][1]->LeftColor() == LeftCenter && LeftPlane[1][0]->LeftColor() == LeftCenter &&
                LeftPlane[1][2]->LeftColor() == LeftCenter && LeftPlane[2][0]->LeftColor() == LeftCenter &&
                LeftPlane[2][1]->LeftColor() == LeftCenter && LeftPlane[2][2]->LeftColor() == LeftCenter &&
                UpPlane[0][1]->UpColor() == UpCenter && UpPlane[0][1]->UpColor() == UpCenter &&
                UpPlane[1][2]->UpColor() == UpCenter && UpPlane[2][1]->UpColor() == UpCenter &&
                (LeftPlane[0][2]->LeftColor() == RightCenter || LeftPlane[0][2]->LeftColor() == BackCenter ||
                 LeftPlane[0][2]->LeftColor() == UpCenter) &&
                (FrontPlane[0][0]->FrontColor() == BackCenter || FrontPlane[0][0]->FrontColor() == RightCenter ||
                 FrontPlane[0][0]->FrontColor() == UpCenter) &&
                (UpPlane[2][0]->UpColor() == UpCenter || UpPlane[2][0]->UpColor() == RightCenter ||
                 UpPlane[2][0]->UpColor() == BackCenter)) {
                RotateMany("B'R'B L'B'R B L ");
                SixthStep(0);
            }
            if (BackPlane[0][1]->BackColor() == BackCenter && BackPlane[1][0]->BackColor() == BackCenter &&
                BackPlane[1][2]->BackColor() == BackCenter && BackPlane[2][0]->BackColor() == BackCenter &&
                BackPlane[2][1]->BackColor() == BackCenter && BackPlane[2][2]->BackColor() == BackCenter &&
                LeftPlane[0][1]->LeftColor() == LeftCenter && LeftPlane[1][0]->LeftColor() == LeftCenter &&
                LeftPlane[1][2]->LeftColor() == LeftCenter && LeftPlane[2][0]->LeftColor() == LeftCenter &&
                LeftPlane[2][1]->LeftColor() == LeftCenter && LeftPlane[2][2]->LeftColor() == LeftCenter &&
                UpPlane[0][1]->UpColor() == UpCenter && UpPlane[0][1]->UpColor() == UpCenter &&
                UpPlane[1][2]->UpColor() == UpCenter && UpPlane[2][1]->UpColor() == UpCenter &&
                (BackPlane[0][2]->BackColor() == RightCenter || BackPlane[0][2]->BackColor() == BackCenter ||
                 BackPlane[0][2]->BackColor() == UpCenter) &&
                (LeftPlane[0][0]->LeftColor() == BackCenter || LeftPlane[0][0]->LeftColor() == UpCenter ||
                 LeftPlane[0][0]->LeftColor() == RightCenter) &&
                (UpPlane[0][0]->UpColor() == UpCenter || UpPlane[0][0]->UpColor() == BackCenter ||
                 UpPlane[0][0]->UpColor() == RightCenter)) {
                RotateMany("L'B'R'B L B'R B ");
                SixthStep(0);
            }

            if (!isSixthStepCompleted() && count < 4) {
                SixthStep(++count);
            } else if (!isSixthStepCompleted() && count == 4) {
                Shuffle( 3);
                FifthStep(0);
                SixthStep(0);
            }

        }
    }

    void SeventhStep(int count = 0, bool isSequenceStarted = false) {
        if (SeventhStepCounter++ > 64)
            throw exception();

        if (!isCubeCompleted()) {
            if (UpPlane[0][1]->UpColor() == UpCenter && UpPlane[1][0]->UpColor() == UpCenter &&
                UpPlane[1][2]->UpColor() == UpCenter & UpPlane[2][1]->UpColor() == UpCenter &&
                RightPlane[0][0]->RightColor() == UpCenter) {
                RotateMany("F'R F R'F'R F R'");
                if (isSequenceStarted)
                    RotateMany("U ");
                else isSequenceStarted = true;

            } else if (UpPlane[0][1]->UpColor() == UpCenter && UpPlane[1][0]->UpColor() == UpCenter &&
                       UpPlane[1][2]->UpColor() == UpCenter && UpPlane[2][1]->UpColor() == UpCenter &&
                       FrontPlane[0][2]->FrontColor() == UpCenter) {
                RotateMany("R F'R'F R F'R'F ");
                if (isSequenceStarted)
                    RotateMany("U ");
                else isSequenceStarted = true;
            }

            if (!isCubeCompleted() && count < 16) {
                RotateMany("U ");
                SeventhStep(++count, isSequenceStarted);
            } else if (!isCubeCompleted() && count == 16) {
                Shuffle( 3);
                SixthStep(0);
                SeventhStep(0, false);
            }
        }
    }

    void FindSolution() {
        if (!CheckIfCubeCorrect())
            throw exception();
        RotatesCounter = 0;
        FirstStep(0);
        SecondStep(0);
        ThirdStep(0);
        FourthStep();
        FifthStep(0);
        SixthStep(0);
        SeventhStep(0, false);
    }

    void ReadCubeRubik(istream &streamIn = cin) const {
        string color;

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                streamIn >> color;
                UpPlane[i][j]->setUpColor(color);
            }

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                streamIn >> color;
                LeftPlane[i][j]->setLeftColor(color);
            }

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                streamIn >> color;
                FrontPlane[i][j]->setFrontColor(color);
            }

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                streamIn >> color;
                RightPlane[i][j]->setRightColor(color);
            }

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                streamIn >> color;
                BackPlane[i][j]->setBackColor(color);
            }

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                streamIn >> color;
                DownPlane[i][j]->setDownColor(color);
            }
    }

    void PrintCubeRubik(ostream &streamOut = cout) const {

        for (int i = 0; i < 3; ++i) {
            streamOut << "\t\t | ";
            for (int j = 0; j < 3; ++j)
                PrintColor(UpPlane[i][j]->UpColor(), streamOut);
            streamOut << "| \n";
        }

        streamOut << "\n | ";
        for (int j = 0; j < 3; ++j)
            PrintColor(LeftPlane[0][j]->LeftColor(), streamOut);
        streamOut << "| ";

        for (int j = 0; j < 3; ++j)
            PrintColor(FrontPlane[0][j]->FrontColor(), streamOut);
        streamOut << "| ";

        for (int j = 0; j < 3; ++j)
            PrintColor(RightPlane[0][j]->RightColor(), streamOut);
        streamOut << "| ";

        for (int j = 0; j < 3; ++j)
            PrintColor(BackPlane[0][j]->BackColor(), streamOut);
        streamOut << "| \n | ";

        for (int j = 0; j < 3; ++j)
            PrintColor(LeftPlane[1][j]->LeftColor(), streamOut);
        streamOut << "| ";

        for (int j = 0; j < 3; ++j)
            PrintColor(FrontPlane[1][j]->FrontColor(), streamOut);
        streamOut << "| ";

        for (int j = 0; j < 3; ++j)
            PrintColor(RightPlane[1][j]->RightColor(), streamOut);
        streamOut << "| ";

        for (int j = 0; j < 3; ++j)
            PrintColor(BackPlane[1][j]->BackColor(), streamOut);
        streamOut << "| \n | ";

        for (int j = 0; j < 3; ++j)
            PrintColor(LeftPlane[2][j]->LeftColor(), streamOut);
        streamOut << "| ";

        for (int j = 0; j < 3; ++j)
            PrintColor(FrontPlane[2][j]->FrontColor(), streamOut);
        streamOut << "| ";

        for (int j = 0; j < 3; ++j)
            PrintColor(RightPlane[2][j]->RightColor(), streamOut);
        streamOut << "| ";

        for (int j = 0; j < 3; ++j)
            PrintColor(BackPlane[2][j]->BackColor(), streamOut);
        streamOut << "| " << "\n\n";

        for (int i = 0; i < 3; ++i) {
            streamOut << "\t\t | ";
            for (int j = 0; j < 3; ++j)
                PrintColor(DownPlane[i][j]->DownColor(), streamOut);
            streamOut << "| \n";
        }
        streamOut << "\n";

    }
};


