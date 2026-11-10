#include <cassert>
#include <vector>
#include <print>
#include <numeric>
#include <random>
#include <ranges>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include "../keccak_linear.hpp"
#include "../keccak_SAT_model.hpp"
#include "../parameter_config.hpp"
using namespace std;

int main()
{
    int width{1600};
    int ROUNDS{3};
    int limit_k{133};
    string mode{"s"};
    int k_loc{0};

    string filename{std::to_string(width) + "_b1+" + std::to_string(ROUNDS) + "r_" + std::to_string(limit_k) + "_" + mode + "_k" + std::to_string(k_loc) + "ge1.cnf"};
    ofs.open(filename);
    ofs << "p cnf " << 0 << " " << 0 << endl;

    int constraints_num{0};
    // linearlayer
    vector<int> xor_clause;
    for (int r = 0; r < ROUNDS; ++r)
        for (int i = 0; i < SboxBits; ++i)
            for (int k = 0; k < LaneSize(width); ++k)
            {
                vector<int> columnsum(6);
                for (int j = 0; j < 5; ++j)
                    columnsum[j] = A(width, r, index(width, i, j, k));
                columnsum[5] = ColSum(width, ROUNDS, r, i, k);
                // xor6(columnsum, 0);
                xor_cryptominisat(columnsum, 0);
            }
    for (int r = 0; r < ROUNDS; ++r)
        for (int i = 0; i < width; ++i)
        {
            vector<int> xor4clause;
            xor4clause.clear();
            xor4clause.resize(4);
            xor4clause[0] = B(width, r, i);
            int row = (linearlayer_CPs.at(width)[i] / LaneSize(width)) % cols;
            int ko = linearlayer_CPs.at(width)[i] % LaneSize(width);
            xor4clause[1] = A(width, r, linearlayer_CPs.at(width)[i]);
            xor4clause[2] = ColSum(width, ROUNDS, r, (row - 1 + 5) % 5, ko);
            xor4clause[3] = ColSum(width, ROUNDS, r, (row + 1) % 5, (ko - 1 + LaneSize(width)) % LaneSize(width));
            // xor4(xor4clause, 0);
            xor_cryptominisat(xor4clause, 0);
        }
    constraints_num += ROUNDS * (width + NumSbox(width));

    // nonlinear
    for (int r = 0; r < ROUNDS - 1; ++r)
        for (int j = 0; j < cols; ++j)
            for (int k = 0; k < LaneSize(width); ++k)
            {
                vector<int> alpha(5), beta(5), pvar(4);
                for (int i = 0; i < 5; ++i)
                {
                    beta[i] = B(width, r, index(width, i, j, k));
                    alpha[i] = A(width, r + 1, index(width, i, j, k));
                }
                chiDiff(beta, alpha);
                for (int i = 0; i < 4; ++i)
                    pvar[i] = P(width, ROUNDS, r, (j * LaneSize(width) + k), i);
                probDiff(beta, pvar);
            }
    for (int j{0}; j < 5; j++)
        for (int k = 0; k < LaneSize(width); ++k)
        {
            vector<int> beta(5), pvar(4);
            for (int i = 0; i < 5; ++i)
            {
                beta[i] = B(width, ROUNDS - 1, index(width, i, j, k));
            }
            for (int i = 0; i < 4; ++i)
                pvar[i] = P(width, ROUNDS, ROUNDS - 1, (j * (width / 25) + k), i);
            probDiff(beta, pvar);
        }
    constraints_num += (ROUNDS - 1) * (46 + 32) * NumSbox(width);
    constraints_num += 32 * NumSbox(width);

    // alpha_reverse_weight
    for (int j = 0; j < cols; ++j)
        for (int k = 0; k < LaneSize(width); ++k)
        {
            vector<int> alpha(5), pvar(3);
            for (int i = 0; i < 5; ++i)
                alpha[i] = A(width, 0, index(width, i, j, k));
            for (int i = 0; i < 3; ++i)
                pvar[i] = P_rev(width, ROUNDS, j * LaneSize(width) + k, i);
            reverse_weight(alpha, pvar);
        }
    constraints_num += 17 * NumSbox(width);

    // constraint of 4r sum weight
    int offset = P(width, ROUNDS, ROUNDS, 0, 0) - 1;
    int length = ((3 + 4 * ROUNDS) * NumSbox(width));
    vector<int> sumvar(length);
    std::iota(sumvar.begin(), sumvar.end(), P_rev(width, ROUNDS, 0, 0));
    if (mode == "s") {
        Cardi_lek(offset, sumvar, limit_k, constraints_num);
    } else if (mode == "p0") {
        parallel_counter_lek(offset, sumvar, limit_k, constraints_num);
    } else if (mode == "p1") {
        parallel_counter_ceil_lek(offset, sumvar, limit_k, constraints_num);
    } else if (mode == "p2") {
        parallel_counter_strict_lek(offset, sumvar, limit_k, constraints_num);
    }

    // constraint of 1r sum weight
    if (k_loc == 0) {
        int length1 = (3 * NumSbox(width));
        vector<int> sumvar1(length1);
        std::iota(sumvar1.begin(), sumvar1.end(), P_rev(width, ROUNDS, 0, 0));
        if (mode == "s") Cardi_gek(offset, sumvar1, 1, constraints_num);
        else parallel_counter_gek(offset, sumvar1, 1, constraints_num);
    } 
    for (int i{0}; i < ROUNDS; i++) {
        if (k_loc == i + 1) {
            int length1 = (4 * NumSbox(width));
            vector<int> sumvar1(length1);
            std::iota(sumvar1.begin(), sumvar1.end(), P(width, ROUNDS, i, 0, 0));
            if (mode == "s") Cardi_gek(offset, sumvar1, 1, constraints_num);
            else parallel_counter_gek(offset, sumvar1, 1, constraints_num);
        }
    }

    ofs << flush;
    ofs.close();

    std::string firstline;
    std::string str1 = std::to_string(offset);
    std::string str2 = std::to_string(constraints_num);
    firstline = "p cnf " + str1 + " " + str2;
    modifyFirstLine(filename, firstline);
    return 0;
}