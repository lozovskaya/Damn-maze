#include <iostream>
#include <fstream>
#include <vector>
#include "field.h"
#include "net.h"


using namespace std;

void write_field(const field &F) {
    ofstream output;
    output.open("field");
    F.write_out(output);
    output.close();
}

int main() {
    cout << "type height and width of field" << endl;
    int n, m;
    cin >> n >> m;
    field F(n, m);
    if (init_net()) {
        printf("failed in init_net\n");
        return 0;
    }
    SOCKET client_socket;
    if (connect_with_client(client_socket)) {
        printf("can't connect\n");
        return 0;
    }
    write_field(F);
    update_net(client_socket, F);
}
