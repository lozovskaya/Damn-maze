#include <iostream>
#include <fstream>
#include <vector>
#include "field.h"
using namespace std;

void write_field(const field &F) {
    ofstream output;
    output.open("field");
    F.write_out(output);
    output.close();
}

int main() {
    int n, m;
    cin >> n >> m;
    write_field(field(n, m));
}
