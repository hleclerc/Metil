// #pragma cpp_flag -fprofile-arcs

void f() {
    for(int i = 0; i < 100000; ++i)
        for(int j = 0; j < 100000; ++j);
}
int main() {
     f();	
}
