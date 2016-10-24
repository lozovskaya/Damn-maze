#include <cstring>
#include <vector>


void write_int(int* to, char* &from) {
    memcpy(to, from, sizeof(int));
    from += sizeof(int);
}

template <typename T>
void write_vector(std::vector<T> &to, char* &from) {
    int vec_size = -1;
    write_int(&vec_size, from);
    to.resize(vec_size);
    for (auto &elem : to) {
        memcpy(&elem, from, sizeof(T));
        from += sizeof(T);
    }
}
