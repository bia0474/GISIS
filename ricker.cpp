#include <fstream>
#include <iostream>
#include <cmath>

void export_binary_float(std::string path, float * array, int n){

    std::ofstream file(path, std::ios::out);
    file.write((char *) array, n * sizeof(float));
    file.close();
}

void build_ricker(float * array, float fcorte, float dt, int nt){

    float fc = fcorte / 3.0f * sqrt(M_PI);

    for(int n = 0; n< nt; n++){
        float td = n * dt - (2.0f * sqrt(M_PI))/(fc);

        float arg = -M_PI * (M_PI * fc * td) * (M_PI * fc * td);
        array[n] = (1.0f + 2.0f * arg) * expf(arg);

        std::cout << array[n] << std::endl;
    }

}

int main(){

    float fcorte = 60.0f;
    float dt = 0.002f;
    int nt = 101;

    float * array = new float[nt];

    build_ricker(array, fcorte, dt, nt);
    
    export_binary_float("fonte_sismica.bin", array, nt);
}