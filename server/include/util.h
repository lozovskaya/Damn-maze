#include <cstring>
#include <vector>

template <typename T>
void write_value(T* to, char* &from) {
    memcpy(to, from, sizeof(T));
    from += sizeof(T);
}

template <typename T>
void write_vector(std::vector<T> &to, char* &from) {
    int vec_size = -1;
    write_value(&vec_size, from);
    to.resize(vec_size);
    for (auto &elem : to) {
        memcpy(&elem, from, sizeof(T));
        from += sizeof(T);
    }
}
