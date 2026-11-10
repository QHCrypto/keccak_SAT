#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

ofstream ofs;
void add_clause(vector<int> clause)
{
    for (auto i : clause)
    {
        if (abs(i) > (1 << 30)) cout << "error\n";
        if (i < 0)
            ofs << "-" << abs(i) << " ";
        else if (i == 0)
            cout << "find 0\n"; 
        else
            ofs << abs(i) << " ";
    }
    ofs << 0 << "\n";
}
#define Lit(x, sign) ((1 - 2 * sign) * x)
void probDiff(vector<int> x, vector<int> p)
{
    add_clause({Lit(p[2], 0), Lit(p[3], 1)});               // p2 ~p3
    add_clause({Lit(p[3], 0), Lit(x[0], 1)});               // p3 ~x0
    add_clause({Lit(p[3], 0), Lit(x[1], 1)});               // p3 ~x1
    add_clause({Lit(p[3], 0), Lit(x[2], 1)});               // p3 ~x2
    add_clause({Lit(p[3], 0), Lit(x[3], 1)});               // p3 ~x3
    add_clause({Lit(p[3], 0), Lit(x[4], 1)});               // p3 ~x4
    add_clause({Lit(p[1], 0), Lit(x[0], 1), Lit(x[1], 1)}); // p1 ~x0 ~x1
    add_clause({Lit(p[1], 0), Lit(x[0], 1), Lit(x[2], 1)});
    add_clause({Lit(p[1], 0), Lit(x[0], 1), Lit(x[3], 1)});
    add_clause({Lit(p[1], 0), Lit(x[0], 1), Lit(x[4], 1)});
    add_clause({Lit(p[1], 0), Lit(x[1], 1), Lit(x[2], 1)});
    add_clause({Lit(p[1], 0), Lit(x[1], 1), Lit(x[3], 1)});
    add_clause({Lit(p[1], 0), Lit(x[1], 1), Lit(x[4], 1)});
    add_clause({Lit(p[1], 0), Lit(x[2], 1), Lit(x[3], 1)});
    add_clause({Lit(p[1], 0), Lit(x[2], 1), Lit(x[4], 1)});
    add_clause({Lit(p[1], 0), Lit(x[3], 1), Lit(x[4], 1)});
    add_clause({Lit(x[0], 0), Lit(x[2], 0), Lit(p[0], 1)});
    add_clause({Lit(x[0], 0), Lit(x[3], 0), Lit(p[0], 1)});
    add_clause({Lit(x[1], 0), Lit(x[3], 0), Lit(p[0], 1)});
    add_clause({Lit(x[1], 0), Lit(x[4], 0), Lit(p[0], 1)});
    add_clause({Lit(x[2], 0), Lit(x[4], 0), Lit(p[0], 1)});
    add_clause({Lit(p[0], 0), Lit(x[0], 1), Lit(x[1], 1), Lit(x[2], 1)});
    add_clause({Lit(p[0], 0), Lit(x[0], 1), Lit(x[1], 1), Lit(x[4], 1)});
    add_clause({Lit(p[0], 0), Lit(x[0], 1), Lit(x[3], 1), Lit(x[4], 1)});
    add_clause({Lit(p[0], 0), Lit(x[1], 1), Lit(x[2], 1), Lit(x[3], 1)});
    add_clause({Lit(p[0], 0), Lit(x[2], 1), Lit(x[3], 1), Lit(x[4], 1)});
    add_clause({Lit(x[0], 0), Lit(x[1], 0), Lit(x[2], 0), Lit(x[3], 0), Lit(p[1], 1)});
    add_clause({Lit(x[0], 0), Lit(x[1], 0), Lit(x[2], 0), Lit(x[4], 0), Lit(p[1], 1)});
    add_clause({Lit(x[0], 0), Lit(x[1], 0), Lit(x[3], 0), Lit(x[4], 0), Lit(p[1], 1)});
    add_clause({Lit(x[0], 0), Lit(x[2], 0), Lit(x[3], 0), Lit(x[4], 0), Lit(p[1], 1)});
    add_clause({Lit(x[1], 0), Lit(x[2], 0), Lit(x[3], 0), Lit(x[4], 0), Lit(p[1], 1)});
    add_clause({Lit(x[0], 0), Lit(x[1], 0), Lit(x[2], 0), Lit(x[3], 0), Lit(x[4], 0), Lit(p[2], 1)});
}
void chiDiff(vector<int> x, vector<int> y)
{
    add_clause({Lit(x[0], 0), Lit(x[1], 0), Lit(x[2], 0), Lit(y[0], 1)});                                                                       // x0 x1 x2 ~y0
    add_clause({Lit(x[0], 0), Lit(x[1], 0), Lit(x[4], 0), Lit(y[4], 1)});                                                                       // x0 x1 x4 ~y4
    add_clause({Lit(x[0], 0), Lit(x[1], 0), Lit(y[4], 0), Lit(x[4], 1)});                                                                       // x0 x1 y4 ~x4
    add_clause({Lit(x[0], 0), Lit(x[2], 0), Lit(y[1], 0), Lit(y[0], 1)});                                                                       // x0 x2 y1 ~y0
    add_clause({Lit(x[0], 0), Lit(x[3], 0), Lit(x[4], 0), Lit(y[3], 1)});                                                                       // x0 x3 x4 ~y3
    add_clause({Lit(x[0], 0), Lit(x[3], 0), Lit(y[4], 0), Lit(y[3], 1)});                                                                       // x0 x1 y4 ~y3
    add_clause({Lit(x[0], 0), Lit(x[4], 0), Lit(y[3], 0), Lit(x[3], 1)});                                                                       // x0 x4 y3 ~x3
    add_clause({Lit(x[0], 0), Lit(y[3], 0), Lit(y[4], 0), Lit(x[3], 1)});                                                                       // x0 y3 y4 ~x3
    add_clause({Lit(x[1], 0), Lit(x[2], 0), Lit(x[3], 0), Lit(y[1], 1)});                                                                       // x1 x2 x3 ~y1
    add_clause({Lit(x[1], 0), Lit(x[2], 0), Lit(y[0], 0), Lit(x[0], 1)});                                                                       // x1 x2 y0 ~x0
    add_clause({Lit(x[1], 0), Lit(x[3], 0), Lit(y[2], 0), Lit(y[1], 1)});                                                                       // x1 x3 y2 ~y1
    add_clause({Lit(x[1], 0), Lit(x[4], 0), Lit(y[0], 0), Lit(y[4], 1)});                                                                       // x1 x4 y0 ~y4
    add_clause({Lit(x[1], 0), Lit(y[0], 0), Lit(y[4], 0), Lit(x[4], 1)});                                                                       // x1 y0 y4 ~x4
    add_clause({Lit(x[2], 0), Lit(x[3], 0), Lit(x[4], 0), Lit(y[2], 1)});                                                                       // x2 x3 x4 ~y2
    add_clause({Lit(x[2], 0), Lit(x[3], 0), Lit(y[1], 0), Lit(x[1], 1)});                                                                       // x2 x3 y1 ~x1
    add_clause({Lit(x[2], 0), Lit(x[4], 0), Lit(y[3], 0), Lit(y[2], 1)});                                                                       // x2 x4 y3 ~y2
    add_clause({Lit(x[2], 0), Lit(y[0], 0), Lit(y[1], 0), Lit(x[0], 1)});                                                                       // x2 y0 y1 ~x0
    add_clause({Lit(x[3], 0), Lit(x[4], 0), Lit(y[2], 0), Lit(x[2], 1)});                                                                       // x3 x4 y2 ~x2
    add_clause({Lit(x[3], 0), Lit(y[1], 0), Lit(y[2], 0), Lit(x[1], 1)});                                                                       // x3 y1 y2 ~x1
    add_clause({Lit(x[4], 0), Lit(y[2], 0), Lit(y[3], 0), Lit(x[2], 1)});                                                                       // x4 y2 y3 ~x2
    add_clause({Lit(x[0], 0), Lit(x[2], 0), Lit(y[0], 0), Lit(x[1], 1), Lit(x[3], 1), Lit(y[1], 1)});                                           // x0 x2 y0 ~x1 ~x3 ~y1
    add_clause({Lit(x[0], 0), Lit(x[3], 0), Lit(y[3], 0), Lit(x[1], 1), Lit(x[4], 1), Lit(y[4], 1)});                                           // x0 x3 y3 ~x1 ~x4 ~y4
    add_clause({Lit(x[0], 0), Lit(x[1], 1), Lit(x[3], 1), Lit(x[4], 1), Lit(y[3], 1), Lit(y[4], 1)});                                           // x0 ~x1 ~x3 ~x4 ~y3 ~y4
    add_clause({Lit(x[1], 0), Lit(x[3], 0), Lit(y[1], 0), Lit(x[2], 1), Lit(x[4], 1), Lit(y[2], 1)});                                           // x1 x3 y1 ~x2 ~x4 ~y2
    add_clause({Lit(x[1], 0), Lit(x[4], 0), Lit(y[4], 0), Lit(x[0], 1), Lit(x[2], 1), Lit(y[0], 1)});                                           // x1 x4 y4 ~x0 ~x2 ~y0
    add_clause({Lit(x[1], 0), Lit(x[0], 1), Lit(x[2], 1), Lit(x[4], 1), Lit(y[0], 1), Lit(y[4], 1)});                                           // x1 ~x0 ~x2 ~x4 ~y0 ~y4
    add_clause({Lit(x[2], 0), Lit(x[4], 0), Lit(y[2], 0), Lit(x[0], 1), Lit(x[3], 1), Lit(y[3], 1)});                                           // x2 x4 y2 ~x0 ~x3 ~y3
    add_clause({Lit(x[2], 0), Lit(x[0], 1), Lit(x[1], 1), Lit(x[3], 1), Lit(y[0], 1), Lit(y[1], 1)});                                           // x2 ~x0 ~x1 ~x3 ~y0 ~y1
    add_clause({Lit(x[3], 0), Lit(x[1], 1), Lit(x[2], 1), Lit(x[4], 1), Lit(y[1], 1), Lit(y[2], 1)});                                           // x3 ~x1 ~x2 ~x4 ~y1 ~y2
    add_clause({Lit(x[4], 0), Lit(x[0], 1), Lit(x[2], 1), Lit(x[3], 1), Lit(y[2], 1), Lit(y[3], 1)});                                           // x4 ~x0 ~x2 ~x3 ~y2 ~y3
    add_clause({Lit(y[0], 0), Lit(y[1], 0), Lit(y[2], 0), Lit(y[3], 0), Lit(y[4], 0), Lit(x[4], 1)});                                           // y0 y1 y2 y3 y4 x4
    add_clause({Lit(y[0], 0), Lit(y[1], 0), Lit(y[2], 0), Lit(x[1], 1), Lit(x[4], 1), Lit(y[3], 1), Lit(y[4], 1)});                             // y0 y1 y2 ~x1 ~x4 ~y3 ~y4
    add_clause({Lit(y[0], 0), Lit(y[1], 0), Lit(y[4], 0), Lit(x[0], 1), Lit(x[3], 1), Lit(y[2], 1), Lit(y[3], 1)});                             // y0 y1 y4 ~x0 ~x3 ~y2 ~y3
    add_clause({Lit(y[0], 0), Lit(y[3], 0), Lit(y[4], 0), Lit(x[2], 1), Lit(x[4], 1), Lit(y[1], 1), Lit(y[2], 1)});                             // y0 y3 y4 ~x2 ~x4 ~y1 ~y2
    add_clause({Lit(y[1], 0), Lit(y[2], 0), Lit(y[3], 0), Lit(x[0], 1), Lit(x[2], 1), Lit(y[0], 1), Lit(y[4], 1)});                             // y1 y2 y3 ~x0 ~x2 ~y0 ~y4
    add_clause({Lit(y[2], 0), Lit(y[3], 0), Lit(y[4], 0), Lit(x[1], 1), Lit(x[3], 1), Lit(y[0], 1), Lit(y[1], 1)});                             // y2 y3 y4 ~x1 ~x3 ~y0 ~y1
    add_clause({Lit(y[0], 0), Lit(x[1], 1), Lit(x[2], 1), Lit(x[4], 1), Lit(y[1], 1), Lit(y[2], 1), Lit(y[3], 1), Lit(y[4], 1)});               // y0 ~x1 ~x2 ~x4 ~y1 ~y2 ~y3 ~y4
    add_clause({Lit(y[1], 0), Lit(x[0], 1), Lit(x[2], 1), Lit(x[3], 1), Lit(y[0], 1), Lit(y[2], 1), Lit(y[3], 1), Lit(y[4], 1)});               // y1 ~x0 ~x2 ~x3 ~y0 ~y2 ~y3 ~y4
    add_clause({Lit(y[2], 0), Lit(x[1], 1), Lit(x[3], 1), Lit(x[4], 1), Lit(y[0], 1), Lit(y[1], 1), Lit(y[3], 1), Lit(y[4], 1)});               // y2 ~x1 ~x3 ~x4 ~y0 ~y1 ~y3 ~y4
    add_clause({Lit(y[3], 0), Lit(x[0], 1), Lit(x[2], 1), Lit(x[4], 1), Lit(y[0], 1), Lit(y[1], 1), Lit(y[2], 1), Lit(y[4], 1)});               // y3 ~x0 ~x2 ~x4 ~y0 ~y1 ~y2 ~y4
    add_clause({Lit(y[4], 0), Lit(x[0], 1), Lit(x[1], 1), Lit(x[3], 1), Lit(y[0], 1), Lit(y[1], 1), Lit(y[2], 1), Lit(y[3], 1)});               // y4 ~x0 ~x1 ~x3 ~y0 ~y1 ~y2 ~y3
    add_clause({Lit(y[0], 0), Lit(y[1], 0), Lit(y[3], 0), Lit(x[0], 1), Lit(x[1], 1), Lit(x[3], 1), Lit(x[4], 1), Lit(y[2], 1), Lit(y[4], 1)}); // y0 y1 y3 ~x0 ~x1 ~x3 ~x4 ~y2 ~y4
    add_clause({Lit(y[0], 0), Lit(y[2], 0), Lit(y[3], 0), Lit(x[0], 1), Lit(x[1], 1), Lit(x[2], 1), Lit(x[3], 1), Lit(y[1], 1), Lit(y[4], 1)}); // y0 y2 y3 ~x0 ~x1 ~x2 ~x3 ~y1 ~y4
    add_clause({Lit(y[0], 0), Lit(y[2], 0), Lit(y[4], 0), Lit(x[0], 1), Lit(x[2], 1), Lit(x[3], 1), Lit(x[4], 1), Lit(y[1], 1), Lit(y[3], 1)}); // y0 y2 y4 ~x0 ~x2 ~x3 ~x4 ~y1 ~y3
    add_clause({Lit(y[1], 0), Lit(y[2], 0), Lit(y[4], 0), Lit(x[0], 1), Lit(x[1], 1), Lit(x[2], 1), Lit(x[4], 1), Lit(y[0], 1), Lit(y[3], 1)}); // y1 y2 y4 ~x0 ~x1 ~x2 ~x4 ~y0 ~y3
    add_clause({Lit(y[1], 0), Lit(y[3], 0), Lit(y[4], 0), Lit(x[1], 1), Lit(x[2], 1), Lit(x[3], 1), Lit(x[4], 1), Lit(y[0], 1), Lit(y[2], 1)}); // y1 y3 y4 ~x1 ~x2 ~x3 ~x4 ~y0 ~y2
}         
void chiValue(vector<int> x, vector<int> y)
{
    // Y = (a3+b3'+b4')(a3'+b3+b4')(a0'+b0+b1')(a1'+b1+b2')(a2+b2'+b3')(a4'+b0'+b4)(a0+b0'+b1')(a0'+a3+a4+b3)(a1'+a3+b1)(a0+a1+a2'+b0)(a1+a3+b1')(a2+a4+b2')(a2'+a4+b2)(a1+a4'+b4)(a0+a3+b3')(a0+a3'+b3)(a1+a3'+b1+b2)(a1+a4+b4')(a0+a2+b0')(a1'+a4'+b0+b4')(a2'+b2+b3')(a0'+a1+a2'+b0')(a0'+a3'+a4+b3')(a2+a4'+b2+b3)(a2'+a4'+b2'+b3)(a1'+a4+b0+b4)(a0'+b0+b2+b4)(a1'+a3'+b1'+b2)(a0'+a3+b0+b2'+b4');
    add_clause({x[3], -y[3], -y[4]});
    add_clause({-x[3], y[3], -y[4]});
    add_clause({-x[0], y[0], -y[1]});
    add_clause({-x[1], y[1], -y[2]});
    add_clause({x[2], -y[2], -y[3]});
    add_clause({-x[4], -y[0], y[4]});
    add_clause({x[0], -y[0], -y[1]});
    add_clause({-x[0], x[3], x[4], y[3]});
    add_clause({-x[1], x[3], y[1]});
    add_clause({x[0], x[1], -x[2], y[0]});
    add_clause({x[1], x[3], y[1]});
    add_clause({x[2], x[4], -y[2]});
    add_clause({-x[2], x[4], y[2]});
    add_clause({x[1], -x[4], y[4]});
    add_clause({x[0], x[3], -y[3]});
    add_clause({x[0], -x[3], y[3]});
    add_clause({x[1], -x[3], y[1], y[2]});
    add_clause({x[1], x[4], -y[4]});
    add_clause({x[0], x[2], -y[0]});
    add_clause({-x[1], -x[4], y[0], -y[4]});
    add_clause({-x[2], y[2], -y[3]});
    add_clause({-x[0], x[1], -x[2], -y[0]});
    add_clause({-x[0], -x[3], x[4], -y[3]});
    add_clause({x[2], -x[4], y[2], y[3]});
    add_clause({-x[2], -x[4], -y[2], y[3]});
    add_clause({-x[1], x[4], y[0], y[4]});
    add_clause({x[0], -y[0], y[2], y[4]});
    add_clause({-x[1], -x[3], -y[1], y[2]});
    add_clause({-x[0], x[3], -y[0], y[2], y[4]});
}
void xor4(vector<int> x, int sign)
{
    // (x0 | x1 | x2 | ~x3) & (x0 | x1 | x3 | ~x2) & (x0 | x2 | x3 | ~x1) & (x1 | x2 | x3 | ~x0) & (x0 | ~x1 | ~x2 | ~x3)
    // & (x1 | ~x0 | ~x2 | ~x3) & (x2 | ~x0 | ~x1 | ~x3) & (x3 | ~x0 | ~x1 | ~x2)

    assert(x.size() == 4);
    if (sign != 0)
        x[3] = -x[3];
    add_clause({x[0], x[1], x[2], -x[3]});
    add_clause({x[0], x[1], x[3], -x[2]});
    add_clause({x[0], x[2], x[3], -x[1]});
    add_clause({x[1], x[2], x[3], -x[0]});
    add_clause({x[0], -x[1], -x[2], -x[3]});
    add_clause({x[1], -x[0], -x[2], -x[3]});
    add_clause({x[2], -x[0], -x[1], -x[3]});
    add_clause({x[3], -x[0], -x[1], -x[2]});
}
void xor6(vector<int> x, int sign)
{
    assert(x.size() == 6);
    // (x0 | x1 | x2 | x3 | x4 | ~x5) & (x0 | x1 | x2 | x3 | x5 | ~x4) & (x0 | x1 | x2 | x4 | x5 | ~x3) &
    // (x0 | x1 | x3 | x4 | x5 | ~x2) & (x0 | x2 | x3 | x4 | x5 | ~x1) & (x1 | x2 | x3 | x4 | x5 | ~x0) &
    // (x0 | x1 | x2 | ~x3 | ~x4 | ~x5) & (x0 | x1 | x3 | ~x2 | ~x4 | ~x5) & (x0 | x1 | x4 | ~x2 | ~x3 | ~x5)
    // & (x0 | x1 | x5 | ~x2 | ~x3 | ~x4) & (x0 | x2 | x3 | ~x1 | ~x4 | ~x5) & (x0 | x2 | x4 | ~x1 | ~x3 | ~x5) &
    // (x0 | x2 | x5 | ~x1 | ~x3 | ~x4) & (x0 | x3 | x4 | ~x1 | ~x2 | ~x5) & (x0 | x3 | x5 | ~x1 | ~x2 | ~x4) &
    // (x0 | x4 | x5 | ~x1 | ~x2 | ~x3) & (x1 | x2 | x3 | ~x0 | ~x4 | ~x5) & (x1 | x2 | x4 | ~x0 | ~x3 | ~x5) &
    // (x1 | x2 | x5 | ~x0 | ~x3 | ~x4) & (x1 | x3 | x4 | ~x0 | ~x2 | ~x5) & (x1 | x3 | x5 | ~x0 | ~x2 | ~x4) &
    // (x1 | x4 | x5 | ~x0 | ~x2 | ~x3) & (x2 | x3 | x4 | ~x0 | ~x1 | ~x5) & (x2 | x3 | x5 | ~x0 | ~x1 | ~x4) &
    //  (x2 | x4 | x5 | ~x0 | ~x1 | ~x3) & (x3 | x4 | x5 | ~x0 | ~x1 | ~x2) & (x0 | ~x1 | ~x2 | ~x3 | ~x4 | ~x5) &
    // (x1 | ~x0 | ~x2 | ~x3 | ~x4 | ~x5) & (x2 | ~x0 | ~x1 | ~x3 | ~x4 | ~x5) & (x3 | ~x0 | ~x1 | ~x2 | ~x4 | ~x5) &
    // (x4 | ~x0 | ~x1 | ~x2 | ~x3 | ~x5) & (x5 | ~x0 | ~x1 | ~x2 | ~x3 | ~x4)
    if (sign != 0)
        x[0] = -x[0];
    add_clause({x[5], -x[0], -x[1], -x[2], -x[3], -x[4]});
    add_clause({x[4], -x[0], -x[1], -x[2], -x[3], -x[5]});
    add_clause({x[3], -x[0], -x[1], -x[2], -x[4], -x[5]});
    add_clause({x[2], -x[0], -x[1], -x[3], -x[4], -x[5]});
    add_clause({x[1], -x[0], -x[2], -x[3], -x[4], -x[5]});
    add_clause({x[0], -x[1], -x[2], -x[3], -x[4], -x[5]});
    add_clause({x[3], x[4], x[5], -x[0], -x[1], -x[2]});
    add_clause({x[2], x[4], x[5], -x[0], -x[1], -x[3]});
    add_clause({x[2], x[3], x[5], -x[0], -x[1], -x[4]});
    add_clause({x[2], x[3], x[4], -x[0], -x[1], -x[5]});
    add_clause({x[1], x[4], x[5], -x[0], -x[2], -x[3]});
    add_clause({x[1], x[3], x[5], -x[0], -x[2], -x[4]});
    add_clause({x[1], x[3], x[4], -x[0], -x[2], -x[5]});
    add_clause({x[1], x[2], x[5], -x[0], -x[3], -x[4]});
    add_clause({x[0], x[1], x[2], x[3], x[4], -x[5]});
    add_clause({x[0], x[1], x[2], x[3], x[5], -x[4]});
    add_clause({x[0], x[1], x[2], x[4], x[5], -x[3]});
    add_clause({x[0], x[1], x[3], x[4], x[5], -x[2]});
    add_clause({x[0], x[2], x[3], x[4], x[5], -x[1]});
    add_clause({x[1], x[2], x[3], x[4], x[5], -x[0]});
    add_clause({x[0], x[1], x[2], -x[3], -x[4], -x[5]});
    add_clause({x[0], x[1], x[3], -x[2], -x[4], -x[5]});
    add_clause({x[0], x[1], x[4], -x[2], -x[3], -x[5]});
    add_clause({x[0], x[1], x[5], -x[2], -x[3], -x[4]});
    add_clause({x[0], x[2], x[3], -x[1], -x[4], -x[5]});
    add_clause({x[0], x[2], x[4], -x[1], -x[3], -x[5]});
    add_clause({x[0], x[2], x[5], -x[1], -x[3], -x[4]});
    add_clause({x[0], x[3], x[4], -x[1], -x[2], -x[5]});
    add_clause({x[0], x[3], x[5], -x[1], -x[2], -x[4]});
    add_clause({x[0], x[4], x[5], -x[1], -x[2], -x[3]});
    add_clause({x[1], x[2], x[3], -x[0], -x[4], -x[5]});
    add_clause({x[1], x[2], x[4], -x[0], -x[3], -x[5]});
}
void xor_cryptominisat(vector<int> x, int mode)
{
    if (mode == 0) ofs << "x -";
    else if (mode == 1) ofs << "x ";

    for (auto i : x)
        ofs << i << ' ';
    ofs << 0 << '\n';
}

void beta_d(vector<int> x) // beta = edcba
{
    // F1 = (A+C')(A+B')(C+E')(B+D');
    add_clause({x[0], -x[2]});
    add_clause({x[0], -x[1]});
    add_clause({x[2], -x[4]});
    add_clause({x[1], -x[3]});
}
void beta_d160_000xx(vector<int> x)
{
    // 000xx：Y = (a1'+a3)(a0'+a2)(a2'+a3+a4);
    add_clause({-x[0], x[2]});
    add_clause({-x[1], x[3]});
    add_clause({-x[2], x[3], x[4]});
}
void beta_d160_00xxx(vector<int> x)
{
    // 00xxx：Y = (a0'+a2)(a1'+a2+a3);
    add_clause({-x[0], x[2]});
    add_clause({-x[1], x[2], x[3]});
}
void reverse_weight(vector<int> x, vector<int> p) // alpha = edcba
{
    // F0 = (A+B+F')(C+D+F')(A+E+F')(B+C+F')(D+E+F')(B'+D'+E'+F)(B'+C'+E'+F)(A'+C'+E'+F)(A'+C'+D'+F)(A'+B'+D'+F)(E'+H)(D'+H)(G+H')(C'+H)(B'+H)(A'+H)(A+B+C+D+E+G');
    add_clause({x[0], x[1], -p[0]});
    add_clause({x[2], x[3], -p[0]});
    add_clause({x[0], x[4], -p[0]});
    add_clause({x[1], x[2], -p[0]});
    add_clause({x[3], x[4], -p[0]});

    add_clause({-x[1], -x[3], -x[4], p[0]});
    add_clause({-x[1], -x[2], -x[4], p[0]});
    add_clause({-x[0], -x[2], -x[4], p[0]});
    add_clause({-x[0], -x[2], -x[3], p[0]});
    add_clause({-x[0], -x[1], -x[3], p[0]});

    add_clause({-x[4], p[2]});
    add_clause({-x[3], p[2]});
    add_clause({-x[2], p[2]});
    add_clause({-x[1], p[2]});
    add_clause({-x[0], p[2]});
    add_clause({-p[2], p[1]});

    add_clause({x[0], x[1], x[2], x[3], x[4], -p[1]});
}
void active_Sbox(vector<int> x, int t) // t = 1 refers to an active Sbox
{
    // F0 = (E'+F)(D'+F)(C'+F)(B'+F)(A'+F)(A+B+C+D+E+F');;
    add_clause({-x[0], t});
    add_clause({-x[1], t});
    add_clause({-x[2], t});
    add_clause({-x[3], t});
    add_clause({-x[4], t});
    add_clause({x[0], x[1], x[2], x[3], x[4], -t});
}

inline int count_ones(int len, int a) {
    int count{0};
    for (int i{0}; i < len; i++) {
        count += (a >> i) & 1;
    }
    return count;
}

// simple add
#define s_s(i, j) (offset + ((i - 1) * k) + j)
void Cardi_lek(int &offset, vector<int> x, int k, int &cons_num)
{
    int n = x.size();
    add_clause({-x[0], s_s(1, 1)});
    add_clause({-x[n - 1], -s_s(n - 1, k)});
    for (int j = 2; j <= k; ++j)
        add_clause({Lit(s_s(1, j), 1)});
    for (int i = 2; i < n; ++i)
    {
        add_clause({Lit(x[i - 1], 1), Lit(s_s(i, 1), 0)});
        add_clause({Lit(s_s(i - 1, 1), 1), Lit(s_s(i, 1), 0)});
        add_clause({Lit(x[i - 1], 1), Lit(s_s(i - 1, k), 1)});
        for (int j = 2; j <= k; ++j)
        {
            add_clause({Lit(x[i - 1], 1), Lit(s_s(i - 1, j - 1), 1), Lit(s_s(i, j), 0)});
            add_clause({Lit(s_s(i - 1, j), 1), Lit(s_s(i, j), 0)});
        }
    }
    cons_num += (2 * k + 1) * (n - 2) + k + 1;
    offset += (n - 1) * k;
}

void Cardi_gek(int &offset, vector<int> x, int k, int &cons_num)
{
    int n = x.size();
    add_clause({x[0], -s_s(1, 1)});
    for (int j = 2; j <= k; ++j)
        add_clause({-s_s(1, j)});
    cons_num += k;
    for (int i = 2; i <= n; ++i)
    {
        add_clause({x[i - 1], s_s(i - 1, 1), -s_s(i, 1)});
        for (int j = 2; j <= k; ++j)
        {
            add_clause({s_s(i - 1, j - 1), -s_s(i, j)});
            add_clause({x[i - 1], s_s(i - 1, j), -s_s(i, j)});
        }
    }
    cons_num += (2 * k - 1) * (n - 1);
    for (int i{1}; i <= k; i++) add_clause({s_s(n, i)});
    cons_num += k;

    offset += n * k;
}
void Cardi_gek1_lek_e(int &offset, vector<int> x, int k1, int k, int &cons_num)
{
    int n = x.size();
    add_clause({-x[0], s_s(1, 1)});
    add_clause({x[0], -s_s(1, 1)});

    for (int j = 2; j <= k; ++j)
        add_clause({-s_s(1, j)});

    for (int i = 2; i < n; ++i)
    {
        add_clause({-x[i - 1], -s_s(i - 1, k)});

        add_clause({-s_s(i - 1, 1), s_s(i, 1)});
        add_clause({-x[i - 1], s_s(i, 1)});
        add_clause({x[i - 1], s_s(i - 1, 1), -s_s(i, 1)});
        for (int j = 2; j <= k; ++j)
        {
            add_clause({-s_s(i - 1, j), s_s(i, j)});
            add_clause({s_s(i - 1, j - 1), -s_s(i, j)});
            add_clause({-x[i - 1], -s_s(i - 1, j - 1), s_s(i, j)});
            add_clause({x[i - 1], s_s(i - 1, j), -s_s(i, j)});
        }
    }
    add_clause({-x[n - 1], -s_s(n - 1, k)});

    if (k1 == 1) {
        add_clause({x[n - 1], s_s(n - 1, k1)});
    } else {
        add_clause({x[n - 1], s_s(n - 1, k1)});
        add_clause({-x[n - 1], s_s(n - 1, k1 - 1)});
    }

    cons_num += 4 * k * (n - 2) + k + 2;
    if (k1 == 1) cons_num++;
    else cons_num += 2;
    offset += (n - 1) * k;
}

void half_add(int x, int y, int s, int c)
{
    add_clause({x, -y, s});
    add_clause({-x, y, s});
    add_clause({-x, -y, c});
}
void full_add(int x, int y, int z, int s, int c)
{
    add_clause({x, y, -z, s});
    add_clause({x, -y, z, s});
    add_clause({-x, y, z, s});
    add_clause({-x, -y, -z, s});
    add_clause({-x, -y, c});
    add_clause({-x, -z, c});
    add_clause({-y, -z, c});
}

void half_add_exact(int x, int y, int s, int c)
{
    // 6
    // F0 = (A+B+C')(C'+D')(A'+C+D)(A+B'+C)(B+D')(A'+B'+D);
    add_clause({x, y, -s});
    add_clause({-s, -c});
    add_clause({-x, s, c});
    add_clause({x, -y, s});
    add_clause({y, -c});
    add_clause({-x, -y, c});
}
void full_add_exact(int x, int y, int z, int s, int c)
{
    // 10
    // F1 = (A'+B'+C'+D)(A+B+C+D')(B+C+E')(A+D'+E')(B'+C'+E)(A'+D+E)(A'+B+C'+D')(A'+B'+C+D')(A+B+C'+D)(A+B'+C+D);
    add_clause({-x, -y, -z, s});
    add_clause({x, y, z, -s});
    add_clause({y, z, -c});
    add_clause({x, -s, -c});
    add_clause({-y, -z, c});
    add_clause({-x, s, c});
    add_clause({-x, y, -z, -s});
    add_clause({-x, -y, z, -s});
    add_clause({x, y, -z, s});
    add_clause({x, -y, z, s});
}

void half_add_le(int x, int y, int s, int c)
{
    add_clause({x, -c});
    add_clause({y, -c});
    add_clause({x, y, -s});
    add_clause({-c, -s});
}
void full_add_le(int x, int y, int z, int s, int c)
{
    add_clause({x, y, -c});
    add_clause({x, z, -c});
    add_clause({y, z, -c});
    add_clause({x, y, z, -s});
    add_clause({x, -c, -s});
    add_clause({y, -c, -s});
    add_clause({z, -c, -s});
}

void ge(vector<int> sum, int k)
{
    int n = sum.size();
    assert(k <= ((1 << n) - 1));
    vector<vector<int>> L;
    if ((k & 1) == 1)
        L.push_back({sum[0]});
    for (int j = 1; j < n; ++j)
        if (((k >> j) & 1) == 0)
        {
            for (auto &lc : L)
                lc.push_back(sum[j]);
        }
        else
        {
            L.push_back({sum[j]});
        }

    for (auto cluase : L)
        add_clause(cluase);
}
void le(vector<int> sum, int k)
{
    int n = sum.size();
    assert(sum.size() >= 1);
    vector<vector<int>> L;
    if ((k & 1) == 0)
        L.push_back({-sum[0]});
    for (int j = 1; j < n; ++j)
        if ((k >> j) & 1)
        {
            for (auto &lc : L)
                lc.push_back(-sum[j]);
        }
        else
        {
            L.push_back({-sum[j]});
        }

    for (auto cluase : L)
        add_clause(cluase);
}

// parallel count
#define s_p(i, j, k) ((offset) + ((1 << ((m) + 1)) - ((i) + 2) * (1 << ((m) - (i)))) + ((j) * ((i) + 1)) + (k) + 1) 
#define c_p(i, j, k) ((offset) + ((1 << ((m) + 1)) - (m) - 2) + ((1 << ((m) + 1)) - ((i) + 2) * (1 << ((m) - (i)))) + ((j) * ((i) + 1)) + (k) + 1)
#define xloc(i, j) ((((n) >> ((m) - (i))) << ((m) - (i))) + (j))
void parallel_counter_lek(int &offset, vector<int> x, int k, int &cons_num)
{
    int n = x.size(), m = floor(log2(n));
    // assert(x.size() >= 2);
    if ((n >> (m - 1)) & 1)
    {
        for (int j = 0; j < (1 << (m - 1)); j++)
            full_add(x[j], x[(1 << (m - 1)) + j], x[xloc(0, j)], s_p(0, j, 0), c_p(0, j, 0));
    }
    else
    {
        for (int j = 0; j < (1 << (m - 1)); j++)
            half_add(x[j], x[(1 << (m - 1)) + j], s_p(0, j, 0), c_p(0, j, 0));
    }

    for (int i = 1; i < m; i++)
        if ((n >> (m - 1 - i)) & 1)
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                full_add(s_p(i - 1, j * 2, 0), s_p(i - 1, j * 2 + 1, 0), x[xloc(i, j)], s_p(i, j, 0), c_p(i, j, 0));
                for (int k = 1; k < i; k++)
                    full_add(s_p(i - 1, j * 2, k), s_p(i - 1, j * 2 + 1, k), c_p(i, j, k - 1), s_p(i, j, k), c_p(i, j, k));
                full_add(c_p(i - 1, j * 2, i - 1), c_p(i - 1, j * 2 + 1, i - 1), c_p(i, j, i - 1), s_p(i, j, i), c_p(i, j, i));
            }
        }
        else
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                half_add(s_p(i - 1, j * 2, 0), s_p(i - 1, j * 2 + 1, 0), s_p(i, j, 0), c_p(i, j, 0));
                for (int k = 1; k < i; k++)
                    full_add(s_p(i - 1, j * 2, k), s_p(i - 1, j * 2 + 1, k), c_p(i, j, k - 1), s_p(i, j, k), c_p(i, j, k));
                full_add(c_p(i - 1, j * 2, i - 1), c_p(i - 1, j * 2 + 1, i - 1), c_p(i, j, i - 1), s_p(i, j, i), c_p(i, j, i));
            }
        }
    cons_num += 4 * n + 6 * (1 << m) - 10 - 7 * m;

    vector<int> sum{};
    for (int i = 0; i < m; i++) sum.push_back(s_p(m - 1, 0, i));
    sum.push_back(c_p(m - 1, 0, m - 1));

    le(sum, k);
    cons_num += m + 1 - count_ones(m + 1, k);
    offset += 2 * ((1 << (m + 1)) - m - 2);
}

void parallel_counter_gek(int &offset, vector<int> x, int k, int &cons_num)
{
    int n = x.size(), m = floor(log2(n));
    // assert(x.size() >= 2);
    if ((n >> (m - 1)) & 1)
    {
        for (int j = 0; j < (1 << (m - 1)); j++)
            full_add_le(x[j], x[(1 << (m - 1)) + j], x[xloc(0, j)], s_p(0, j, 0), c_p(0, j, 0));
    }
    else
    {
        for (int j = 0; j < (1 << (m - 1)); j++)
            half_add_le(x[j], x[(1 << (m - 1)) + j], s_p(0, j, 0), c_p(0, j, 0));
    }

    for (int i = 1; i < m; i++)
        if ((n >> (m - 1 - i)) & 1)
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                full_add_le(s_p(i - 1, j * 2, 0), s_p(i - 1, j * 2 + 1, 0), x[xloc(i, j)], s_p(i, j, 0), c_p(i, j, 0));
                for (int k = 1; k < i; k++)
                    full_add_le(s_p(i - 1, j * 2, k), s_p(i - 1, j * 2 + 1, k), c_p(i, j, k - 1), s_p(i, j, k), c_p(i, j, k));
                full_add_le(c_p(i - 1, j * 2, i - 1), c_p(i - 1, j * 2 + 1, i - 1), c_p(i, j, i - 1), s_p(i, j, i), c_p(i, j, i));
            }
        }
        else
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                half_add_le(s_p(i - 1, j * 2, 0), s_p(i - 1, j * 2 + 1, 0), s_p(i, j, 0), c_p(i, j, 0));
                for (int k = 1; k < i; k++)
                    full_add_le(s_p(i - 1, j * 2, k), s_p(i - 1, j * 2 + 1, k), c_p(i, j, k - 1), s_p(i, j, k), c_p(i, j, k));
                full_add_le(c_p(i - 1, j * 2, i - 1), c_p(i - 1, j * 2 + 1, i - 1), c_p(i, j, i - 1), s_p(i, j, i), c_p(i, j, i));
            }
        }
    cons_num += 3 * n + 8 * (1 << m) - 11 - 7 * m;

    vector<int> sum{};
    for (int i = 0; i < m; i++) sum.push_back(s_p(m - 1, 0, i));
    sum.push_back(c_p(m - 1, 0, m - 1));

    ge(sum, k);
    cons_num += count_ones(m + 1, k);
    offset += 2 * ((1 << (m + 1)) - m - 2);
}

void parallel_counter_gek1_lek_e(int &offset, vector<int> x, int k1, int k, int &cons_num)
{
    int n = x.size(), m = floor(log2(n));
    // assert(x.size() >= 2);
    if ((n >> (m - 1)) & 1)
    {
        for (int j = 0; j < (1 << (m - 1)); j++) 
            full_add_exact(x[j], x[(1 << (m - 1)) + j], x[xloc(0, j)], s_p(0, j, 0), c_p(0, j, 0));
    }
    else
    {
        for (int j = 0; j < (1 << (m - 1)); j++) 
            half_add_exact(x[j], x[(1 << (m - 1)) + j], s_p(0, j, 0), c_p(0, j, 0));
    }

    for (int i = 1; i < m; i++)
        if ((n >> (m - 1 - i)) & 1)
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                full_add_exact(s_p(i - 1, j * 2, 0), s_p(i - 1, j * 2 + 1, 0), x[xloc(i, j)], s_p(i, j, 0), c_p(i, j, 0));
                for (int k = 1; k < i; k++) 
                    full_add_exact(s_p(i - 1, j * 2, k), s_p(i - 1, j * 2 + 1, k), c_p(i, j, k - 1), s_p(i, j, k), c_p(i, j, k));
                full_add_exact(c_p(i - 1, j * 2, i - 1), c_p(i - 1, j * 2 + 1, i - 1), c_p(i, j, i - 1), s_p(i, j, i), c_p(i, j, i));
            }
        }
        else
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                half_add_exact(s_p(i - 1, j * 2, 0), s_p(i - 1, j * 2 + 1, 0), s_p(i, j, 0), c_p(i, j, 0));
                for (int k = 1; k < i; k++) 
                    full_add_exact(s_p(i - 1, j * 2, k), s_p(i - 1, j * 2 + 1, k), c_p(i, j, k - 1), s_p(i, j, k), c_p(i, j, k));
                full_add_exact(c_p(i - 1, j * 2, i - 1), c_p(i - 1, j * 2 + 1, i - 1), c_p(i, j, i - 1), s_p(i, j, i), c_p(i, j, i));
            }
        }
    cons_num += 4 * n + 12 * (1 << m) - 16 - 10 * m;

    vector<int> sum{};
    for (int i = 0; i < m; i++) sum.push_back(s_p(m - 1, 0, i));
    sum.push_back(c_p(m - 1, 0, m - 1));

    ge(sum, k1);
    cons_num += count_ones(m + 1, k1);
    le(sum, k);
    cons_num += m + 1 - count_ones(m + 1, k);

    offset += 2 * ((1 << (m + 1)) - m - 2);
}

#define s_p_k(i, j, l) ((offset) + ((1 << ((m) + 1)) - ((m1) + 1) * (1 << ((m) - (m1) + 1)) + (m1) * ((1 << ((m) - (m1) + 1)) - (1 << ((m) - (i))))) + ((j) * (m1)) + (l) + 1) 
#define c_p1(i, j, l) ((offset) + ((1 << ((m) + 1)) - (1 << ((m) - (m1) + 1)) - (m1)) + ((1 << ((m) + 1)) - ((i) + 2) * (1 << ((m) - (i)))) + ((j) * ((i) + 1)) + (l) + 1)
#define c_p_k(i, j, l) ((offset) + ((1 << ((m) + 1)) - (1 << ((m) - (m1) + 1)) - (m1)) + ((1 << ((m) + 1)) - ((m1) + 1) * (1 << ((m) - (m1) + 1)) + (m1) * ((1 << ((m) - (m1) + 1)) - (1 << ((m) - (i))))) + ((j) * (m1)) + (l) + 1)
void parallel_counter_ceil_lek(int &offset, vector<int> x, int k, int &cons_num)
{
    int n = x.size(), m = floor(log2(n));
    int m1 = ceil(log2(k + 1));
    assert(m1 >= 2);

    if ((n >> (m - 1)) & 1)
    {
        for (int j = 0; j < (1 << (m - 1)); j++) 
            full_add(x[j], x[(1 << (m - 1)) + j], x[xloc(0, j)], s_p(0, j, 0), c_p1(0, j, 0));
    }
    else
    {
        for (int j = 0; j < (1 << (m - 1)); j++) 
            half_add(x[j], x[(1 << (m - 1)) + j], s_p(0, j, 0), c_p1(0, j, 0));
    }

    for (int i = 1; i < m1; i++)
        if ((n >> (m - 1 - i)) & 1)
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                full_add(s_p(i - 1, j * 2, 0), s_p(i - 1, j * 2 + 1, 0), x[xloc(i, j)], s_p(i, j, 0), c_p1(i, j, 0));
                for (int l = 1; l < i; l++) 
                    full_add(s_p(i - 1, j * 2, l), s_p(i - 1, j * 2 + 1, l), c_p1(i, j, l - 1), s_p(i, j, l), c_p1(i, j, l));
                full_add(c_p1(i - 1, j * 2, i - 1), c_p1(i - 1, j * 2 + 1, i - 1), c_p1(i, j, i - 1), s_p(i, j, i), c_p1(i, j, i));
            }
        }
        else
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                half_add(s_p(i - 1, j * 2, 0), s_p(i - 1, j * 2 + 1, 0), s_p(i, j, 0), c_p1(i, j, 0));
                for (int l = 1; l < i; l++) 
                    full_add(s_p(i - 1, j * 2, l), s_p(i - 1, j * 2 + 1, l), c_p1(i, j, l - 1), s_p(i, j, l), c_p1(i, j, l));
                full_add(c_p1(i - 1, j * 2, i - 1), c_p1(i - 1, j * 2 + 1, i - 1), c_p1(i, j, i - 1), s_p(i, j, i), c_p1(i, j, i));
            }
        }

    for (int j = 0; j < (1 << (m - m1)); j++) 
        add_clause({-c_p1(m1 - 1, j, m1 - 1)});

    for (int i = m1; i < m; i++) {
        if ((n >> (m - 1 - i)) & 1)
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                full_add(s_p_k(i - 1, j * 2, 0), s_p_k(i - 1, j * 2 + 1, 0), x[xloc(i, j)], s_p_k(i, j, 0), c_p_k(i, j, 0));
                for (int l = 1; l < m1; l++) 
                    full_add(s_p_k(i - 1, j * 2, l), s_p_k(i - 1, j * 2 + 1, l), c_p_k(i, j, l - 1), s_p_k(i, j, l), c_p_k(i, j, l));
            }
        }
        else
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                half_add(s_p_k(i - 1, j * 2, 0), s_p_k(i - 1, j * 2 + 1, 0), s_p_k(i, j, 0), c_p_k(i, j, 0));
                for (int l = 1; l < m1; l++) 
                    full_add(s_p_k(i - 1, j * 2, l), s_p_k(i - 1, j * 2 + 1, l), c_p_k(i, j, l - 1), s_p_k(i, j, l), c_p_k(i, j, l));
            }
        }
        
        for (int j = 0; j < (1 << (m - i - 1)); j++) 
            add_clause({-c_p_k(i, j, m1 - 1)});
    }
    cons_num += 4 * n + 6 * (1 << m) - 6 * (1 << (m - m1 + 1)) + 3 - 7 * m1;

    vector<int> sum{};
    for (int i = 0; i < m1; i++) sum.push_back(s_p_k(m - 1, 0, i));

    le(sum, k);
    cons_num += m1 - count_ones(m1, k);
    offset += 2 * ((1 << (m + 1)) - (1 << (m - m1 + 1)) - m1);
}

void parallel_counter_gek1_ceil_lek_e(int &offset, vector<int> x, int k1, int k, int &cons_num)
{
    int n = x.size(), m = floor(log2(n));
    int m1 = ceil(log2(k + 1));
    assert(m1 >= 2);

    if ((n >> (m - 1)) & 1)
    {
        for (int j = 0; j < (1 << (m - 1)); j++) 
            full_add_exact(x[j], x[(1 << (m - 1)) + j], x[xloc(0, j)], s_p(0, j, 0), c_p1(0, j, 0));
    }
    else
    {
        for (int j = 0; j < (1 << (m - 1)); j++) 
            half_add_exact(x[j], x[(1 << (m - 1)) + j], s_p(0, j, 0), c_p1(0, j, 0));
    }

    for (int i = 1; i < m1; i++)
        if ((n >> (m - 1 - i)) & 1)
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                full_add_exact(s_p(i - 1, j * 2, 0), s_p(i - 1, j * 2 + 1, 0), x[xloc(i, j)], s_p(i, j, 0), c_p1(i, j, 0));
                for (int l = 1; l < i; l++) 
                    full_add_exact(s_p(i - 1, j * 2, l), s_p(i - 1, j * 2 + 1, l), c_p1(i, j, l - 1), s_p(i, j, l), c_p1(i, j, l));
                full_add_exact(c_p1(i - 1, j * 2, i - 1), c_p1(i - 1, j * 2 + 1, i - 1), c_p1(i, j, i - 1), s_p(i, j, i), c_p1(i, j, i));
            }
        }
        else
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                half_add_exact(s_p(i - 1, j * 2, 0), s_p(i - 1, j * 2 + 1, 0), s_p(i, j, 0), c_p1(i, j, 0));
                for (int l = 1; l < i; l++) 
                    full_add_exact(s_p(i - 1, j * 2, l), s_p(i - 1, j * 2 + 1, l), c_p1(i, j, l - 1), s_p(i, j, l), c_p1(i, j, l));
                full_add_exact(c_p1(i - 1, j * 2, i - 1), c_p1(i - 1, j * 2 + 1, i - 1), c_p1(i, j, i - 1), s_p(i, j, i), c_p1(i, j, i));
            }
        }

    for (int j = 0; j < (1 << (m - m1)); j++) 
        add_clause({-c_p1(m1 - 1, j, m1 - 1)});

    for (int i = m1; i < m; i++) {
        if ((n >> (m - 1 - i)) & 1)
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                full_add_exact(s_p_k(i - 1, j * 2, 0), s_p_k(i - 1, j * 2 + 1, 0), x[xloc(i, j)], s_p_k(i, j, 0), c_p_k(i, j, 0));
                for (int l = 1; l < m1; l++) 
                    full_add_exact(s_p_k(i - 1, j * 2, l), s_p_k(i - 1, j * 2 + 1, l), c_p_k(i, j, l - 1), s_p_k(i, j, l), c_p_k(i, j, l));
            }
        }
        else
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                half_add_exact(s_p_k(i - 1, j * 2, 0), s_p_k(i - 1, j * 2 + 1, 0), s_p_k(i, j, 0), c_p_k(i, j, 0));
                for (int l = 1; l < m1; l++) 
                    full_add_exact(s_p_k(i - 1, j * 2, l), s_p_k(i - 1, j * 2 + 1, l), c_p_k(i, j, l - 1), s_p_k(i, j, l), c_p_k(i, j, l));
            }
        }

        for (int j = 0; j < (1 << (m - i - 1)); j++) 
            add_clause({-c_p_k(i, j, m1 - 1)});
    }
    cons_num += 4 * n + 12 * (1 << m) - 9 * (1 << (m - m1 + 1)) + 3 - 10 * m1;

    vector<int> sum{};
    for (int i = 0; i < m1; i++) sum.push_back(s_p_k(m - 1, 0, i));

    ge(sum, k1);
    cons_num += count_ones(m1, k1);
    le(sum, k);
    cons_num += m1 - count_ones(m1, k);
    offset += 2 * ((1 << (m + 1)) - (1 << (m - m1 + 1)) - m1);
}

void parallel_counter_strict_lek(int &offset, vector<int> x, int k, int &cons_num)
{
    int n = x.size(), m = floor(log2(n));
    int m1 = ceil(log2(k + 1));
    assert(m1 >= 2);

    if ((n >> (m - 1)) & 1)
    {
        for (int j = 0; j < (1 << (m - 1)); j++) 
            full_add(x[j], x[(1 << (m - 1)) + j], x[xloc(0, j)], s_p(0, j, 0), c_p1(0, j, 0));
    }
    else
    {
        for (int j = 0; j < (1 << (m - 1)); j++) 
            half_add(x[j], x[(1 << (m - 1)) + j], s_p(0, j, 0), c_p1(0, j, 0));
    }

    for (int i = 1; i < m1; i++)
        if ((n >> (m - 1 - i)) & 1)
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                full_add(s_p(i - 1, j * 2, 0), s_p(i - 1, j * 2 + 1, 0), x[xloc(i, j)], s_p(i, j, 0), c_p1(i, j, 0));
                for (int l = 1; l < i; l++) 
                    full_add(s_p(i - 1, j * 2, l), s_p(i - 1, j * 2 + 1, l), c_p1(i, j, l - 1), s_p(i, j, l), c_p1(i, j, l));
                full_add(c_p1(i - 1, j * 2, i - 1), c_p1(i - 1, j * 2 + 1, i - 1), c_p1(i, j, i - 1), s_p(i, j, i), c_p1(i, j, i));
            }
        }
        else
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                half_add(s_p(i - 1, j * 2, 0), s_p(i - 1, j * 2 + 1, 0), s_p(i, j, 0), c_p1(i, j, 0));
                for (int l = 1; l < i; l++) 
                    full_add(s_p(i - 1, j * 2, l), s_p(i - 1, j * 2 + 1, l), c_p1(i, j, l - 1), s_p(i, j, l), c_p1(i, j, l));
                full_add(c_p1(i - 1, j * 2, i - 1), c_p1(i - 1, j * 2 + 1, i - 1), c_p1(i, j, i - 1), s_p(i, j, i), c_p1(i, j, i));
            }
        }

    for (int j = 0; j < (1 << (m - m1)); j++) 
        add_clause({-c_p1(m1 - 1, j, m1 - 1)});
    for (int j = 0; j < (1 << (m - m1)); j++) {
        vector<int> sum{};
        for (int k = 0; k < m1; k++) sum.push_back(s_p_k(m1 - 1, j, k));
        le(sum, k);
    }

    for (int i = m1; i < m; i++) {
        if ((n >> (m - 1 - i)) & 1)
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                full_add(s_p_k(i - 1, j * 2, 0), s_p_k(i - 1, j * 2 + 1, 0), x[xloc(i, j)], s_p_k(i, j, 0), c_p_k(i, j, 0));
                for (int l = 1; l < m1; l++) 
                    full_add(s_p_k(i - 1, j * 2, l), s_p_k(i - 1, j * 2 + 1, l), c_p_k(i, j, l - 1), s_p_k(i, j, l), c_p_k(i, j, l));
            }
        }
        else
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                half_add(s_p_k(i - 1, j * 2, 0), s_p_k(i - 1, j * 2 + 1, 0), s_p_k(i, j, 0), c_p_k(i, j, 0));
                for (int l = 1; l < m1; l++) 
                    full_add(s_p_k(i - 1, j * 2, l), s_p_k(i - 1, j * 2 + 1, l), c_p_k(i, j, l - 1), s_p_k(i, j, l), c_p_k(i, j, l));
            }
        }
        
        for (int j = 0; j < (1 << (m - i - 1)); j++) 
            add_clause({-c_p_k(i, j, m1 - 1)});
        for (int j = 0; j < (1 << (m - i - 1)); j++) {
            vector<int> sum{};
            for (int k = 0; k < m1; k++) sum.push_back(s_p_k(i, j, k));
            le(sum, k);
        }
    }
    cons_num += 4 * n + 6 * (1 << m) - 6 * (1 << (m - m1 + 1)) + 3 - 7 * m1;
    cons_num += ((1 << (m - m1 + 1)) - 1) * (m1 - count_ones(m1, k));

    offset += 2 * ((1 << (m + 1)) - (1 << (m - m1 + 1)) - m1);
}

void parallel_counter_gek1_strict_lek_e(int &offset, vector<int> x, int k1, int k, int &cons_num)
{
    int n = x.size(), m = floor(log2(n));
    int m1 = ceil(log2(k + 1));
    assert(m1 >= 2);

    if ((n >> (m - 1)) & 1)
    {
        for (int j = 0; j < (1 << (m - 1)); j++) 
            full_add_exact(x[j], x[(1 << (m - 1)) + j], x[xloc(0, j)], s_p(0, j, 0), c_p1(0, j, 0));
    }
    else
    {
        for (int j = 0; j < (1 << (m - 1)); j++) 
            half_add_exact(x[j], x[(1 << (m - 1)) + j], s_p(0, j, 0), c_p1(0, j, 0));
    }

    for (int i = 1; i < m1; i++)
        if ((n >> (m - 1 - i)) & 1)
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                full_add_exact(s_p(i - 1, j * 2, 0), s_p(i - 1, j * 2 + 1, 0), x[xloc(i, j)], s_p(i, j, 0), c_p1(i, j, 0));
                for (int l = 1; l < i; l++) 
                    full_add_exact(s_p(i - 1, j * 2, l), s_p(i - 1, j * 2 + 1, l), c_p1(i, j, l - 1), s_p(i, j, l), c_p1(i, j, l));
                full_add_exact(c_p1(i - 1, j * 2, i - 1), c_p1(i - 1, j * 2 + 1, i - 1), c_p1(i, j, i - 1), s_p(i, j, i), c_p1(i, j, i));
            }
        }
        else
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                half_add_exact(s_p(i - 1, j * 2, 0), s_p(i - 1, j * 2 + 1, 0), s_p(i, j, 0), c_p1(i, j, 0));
                for (int l = 1; l < i; l++) 
                    full_add_exact(s_p(i - 1, j * 2, l), s_p(i - 1, j * 2 + 1, l), c_p1(i, j, l - 1), s_p(i, j, l), c_p1(i, j, l));
                full_add_exact(c_p1(i - 1, j * 2, i - 1), c_p1(i - 1, j * 2 + 1, i - 1), c_p1(i, j, i - 1), s_p(i, j, i), c_p1(i, j, i));
            }
        }

    for (int j = 0; j < (1 << (m - m1)); j++) 
        add_clause({-c_p1(m1 - 1, j, m1 - 1)});
    for (int j = 0; j < (1 << (m - m1)); j++) {
        vector<int> sum{};
        for (int k = 0; k < m1; k++) sum.push_back(s_p_k(m1 - 1, j, k));
        le(sum, k);
    }

    for (int i = m1; i < m; i++) {
        if ((n >> (m - 1 - i)) & 1)
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                full_add_exact(s_p_k(i - 1, j * 2, 0), s_p_k(i - 1, j * 2 + 1, 0), x[xloc(i, j)], s_p_k(i, j, 0), c_p_k(i, j, 0));
                for (int l = 1; l < m1; l++) 
                    full_add_exact(s_p_k(i - 1, j * 2, l), s_p_k(i - 1, j * 2 + 1, l), c_p_k(i, j, l - 1), s_p_k(i, j, l), c_p_k(i, j, l));
            }
        }
        else
        {
            for (int j = 0; j < (1 << (m - i - 1)); j++)
            {
                half_add_exact(s_p_k(i - 1, j * 2, 0), s_p_k(i - 1, j * 2 + 1, 0), s_p_k(i, j, 0), c_p_k(i, j, 0));
                for (int l = 1; l < m1; l++) 
                    full_add_exact(s_p_k(i - 1, j * 2, l), s_p_k(i - 1, j * 2 + 1, l), c_p_k(i, j, l - 1), s_p_k(i, j, l), c_p_k(i, j, l));
            }
        }
        
        for (int j = 0; j < (1 << (m - i - 1)); j++) 
            add_clause({-c_p_k(i, j, m1 - 1)});
        for (int j = 0; j < (1 << (m - i - 1)); j++) {
            vector<int> sum{};
            for (int k = 0; k < m1; k++) sum.push_back(s_p_k(i, j, k));
            le(sum, k);
        }
    }
    cons_num += 4 * n + 12 * (1 << m) - 9 * (1 << (m - m1 + 1)) + 3 - 10 * m1;
    cons_num += ((1 << (m - m1 + 1)) - 1) * (m1 - count_ones(m1, k));

    vector<int> sum{};
    for (int i = 0; i < m1; i++) sum.push_back(s_p_k(m - 1, 0, i));

    ge(sum, k1);
    cons_num += count_ones(m1, k1);
    offset += 2 * ((1 << (m + 1)) - (1 << (m - m1 + 1)) - m1);
}

auto times2plus(int offset, vector<int> sum1, vector<int> sum2)
{
    int n1 = sum1.size(), n2 = sum2.size();
    assert(sum1.size() >= 1);
    assert(sum2.size() >= 2);
    if (n1 + 1 >= n2)
    {
        half_add(sum1[0], sum2[1], offset + 1, offset + n1 + 1);
        for (int i = 1; i < n2 - 1; i++)
            full_add(sum1[i], sum2[i + 1], offset + n1 + i, offset + i + 1, offset + n1 + i + 1);
        for (int i = n2 - 1; i < n1; i++)
            half_add(sum1[i], offset + n1 + i, offset + i + 1, offset + n1 + i + 1);
    }
    else
    {
        half_add(sum1[0], sum2[1], offset + 1, offset + n2);
        for (int i = 1; i < n1; i++)
            full_add(sum1[i], sum2[i + 1], offset + n2 - 1 + i, offset + i + 1, offset + n2 - 1 + i + 1);
        for (int i = n1; i < n2 - 1; i++)
            half_add(sum2[i + 1], offset + n2 - 1 + i, offset + i + 1, offset + n2 - 1 + i + 1);
    }

    vector<int> sum{};
    sum.push_back(sum2[0]);
    if (n1 + 1 >= n2)
    {
        for (int j = 1; j < n1 + 1; ++j)
            sum.push_back(offset + j);
        sum.push_back(offset + n1 + n1);
    }
    else
    {
        for (int j = 1; j < n2; ++j)
            sum.push_back(offset + j);
        sum.push_back(offset + n2 - 1 + n2 - 1);
    }

    return sum;
}
