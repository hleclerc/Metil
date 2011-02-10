// #pragma cpp_flag -fprofile-arcs
#include <BasicVec.h>
#include <MetilString.h>

//void f() {
//    for(int i = 0; i < 100000; ++i)
//        for(int j = 0; j < 100000; ++j);
//}
int main() {
    Metil::BasicVec<int > v;
    v << 10 << 20 << 30;
    PRINT( v );
}

