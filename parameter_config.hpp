#pragma once

#define SboxBits 5
#define cols 5

inline int NumSbox(int width) {
    return width / SboxBits;
}

inline int LaneSize(int width) {
    return width / (SboxBits * SboxBits);
}

inline int index(int width, int x, int y, int z) {
    return (((x % 5) + 5 * (y % 5)) * (width / 25)
            + (z % (width / 25)));
}

inline int A(int width, int r, int i) {
    return i + width * r * 2 + 1;
}

inline int B(int width, int r, int i) {
    return i + width * r * 2 + width + 1;
}

inline int ColSum(int width, int ROUNDS, int r, int i, int k) {
    return (i % 5) * LaneSize(width) + (k % LaneSize(width))
           + (ROUNDS * 2) * width + r * NumSbox(width) + 1;
}

inline int P(int width, int ROUNDS, int r, int i, int j) {
    return i * 4 + j
           + (ROUNDS * 2) * width
           + ROUNDS * NumSbox(width)
           + 3 * NumSbox(width)
           + r * 4 * NumSbox(width) + 1;
}

inline int P_rev(int width, int ROUNDS, int i, int j) {
    return i * 3 + j
           + (ROUNDS * 2) * width
           + ROUNDS * NumSbox(width) + 1;
}

void modifyFirstLine(const std::string& filename, const std::string& newLine) {
    // 1. 读取所有行
    std::ifstream ifs(filename);
    std::vector<std::string> lines;
    std::string line;
    
    while (std::getline(ifs, line)) {
        lines.push_back(line);
    }
    ifs.close();
    
    // 2. 修改第一行
    if (!lines.empty()) {
        lines[0] = newLine;
    }
    
    // 3. 重写整个文件
    std::ofstream ofs(filename);
    for (const auto& l : lines) {
        ofs << l << "\n";
    }
}