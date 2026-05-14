#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


//----------------------------------
// CFL condition
//----------------------------------


bool CFL(float c, float dt, float dx){ //function about stability condition is also called the Courant–Friedrichs–Lewy

    float ef; //estability factor

    ef = c * (dt/dx); //definition

    if(ef <= 1){ //
        return true;
    }
    else{
        std::cout << "ERROR! NOT STABLE" << std::endl;//if has a problema the simulation explode numericaly 
        return false;
    }
}

//----------------------------------
// Ricker source Juan
//----------------------------------

std::vector<float> source(float f0, const std::vector<float>& t){

    int nt = t.size(); //número total de amostras no tempo

    std::vector<float> s(nt);

    float t0 = 1.0 / f0; //atraso temporal da wavelet

    for(int n = 0; n < nt; n++){

        float a = M_PI * M_PI * f0 * f0 * pow(t[n] - t0, 2);

        s[n] = (1.0 - 2.0 * a) * std::exp(-a); //equation
    }

    return s;
}

//----------------------------------
// Wave equation
//----------------------------------


std::vector<float>  derivates(float c, float dt, float dx, const std::vector<float>& fonte, int nx, int nt){

    
     std::vector<float> u_old(nx, 0.0); //passed field
     std::vector<float> u_curr(nx, 0.0); //present field
     std::vector<float> u_next(nx, 0.0); //future field

    
    float e = c * dt / dx; 
    int is = nx/2; //fonte no centro

//----------------------------------
// time loop
//----------------------------------

    for(int n = 1; n < nt; n++){ //cada iteração calcula a onda no proximo instante

        std::fill(u_next.begin(), u_next.end(), 0.0); //zera o campo futuro antes do calculo

        //----------------------------------
        // space loop
        //----------------------------------


        for(int j = 1; j < nx - 1; j++){ //percorre todos os pontos da malha

        u_next[j] = pow(e, 2) * (u_curr[j + 1] - 2 * u_curr[j] + u_curr[j - 1]) + 2 * u_curr[j] - u_old[j];
       
        }

        //----------------------------------
        // source injection
        //----------------------------------

        u_next[is] += fonte[n]; //adiciona energia à malha (a fonte é somada no centro)

        //----------------------------------
        // SAVE SNAPSHOT HERE
        //----------------------------------

        if(n % 50 == 0){ //a cada 50 passos um snapshot é salvoS

            std::ofstream file("snapshot_" + std::to_string(n) + ".bin", std::ios::binary); //abre o arquivo binário

            file.write(reinterpret_cast<char*>(u_next.data()), nx * sizeof(float)); //grava os floats discretamente em binário

            //reinterpret_cas -> converte o ponteiro do vetor float para bytes

            file.close();
        }
        
        
        //----------------------------------
        // ABSORBING LAYER HERE
        //----------------------------------

        int nabs = 50; //espessura da camada

        for(int j = 0; j < nabs; j++){ //loop das bordas

            float x = (float)(nabs - j) / nabs; //distância normalizada

            float damp = std::exp(-15.0 * x * x); //fator de amortecimento

            u_next[j] *= damp;

            u_next[nx - 1 - j] *= damp;
        }
        
        //----------------------------------
        // advance in time
        //----------------------------------

        u_old = u_curr;
        u_curr = u_next;
    }

    return u_curr;
}

//----------------------------------
// MAIN
//----------------------------------

int main(){
    
//----------------------------------
// model parameters
//----------------------------------
    //parametros
    float L = 1000.0; //tamanho do modelo
    int T = 1; // tempo total da simulação

    float dx = 0.5; //passo espacial
    float dt = 0.0002; //passo temporal
    float f0 = 30.0; //frequencia dominante

    int nx = int(L/dx) + 1; //número de pontos espaciais
    int nt = int(T/dt) + 1; //número de passos temporais

    
    std::vector<float> x(nx);
    std::vector<float> t(nt);

    for(int i = 0; i < nx; i++){
        x[i] = i * dx;
    }

    for(int i = 0; i < nt; i++){
        t[i] = i * dt;
    }

    //velocidade
    float c = 1500.0; //velocidade do meio

    std::vector<float> fonte;

    fonte = source(f0, t);

//----------------------------------
// SAVE SOURCE
//----------------------------------

    std::ofstream file_source("source.bin", std::ios::binary);

    file_source.write(reinterpret_cast<char*>(fonte.data()), nt * sizeof(float));

    file_source.close();

//----------------------------------
// CFL check
//----------------------------------

    if(CFL(c, dt, dx)){

        std::cout << "Stable simulation" << std::endl;
    }
    else{

        return 1;
    }

//----------------------------------
// simulation 
//----------------------------------

    std::vector<float> wavefield;

    wavefield = derivates(c, dt, dx, fonte, nx, nt); 

//----------------------------------
// save binary document
//----------------------------------

    std::ofstream file("wave.bin", std::ios::binary);

    file.write(reinterpret_cast<char*>( wavefield.data()), nx * sizeof(float));

    file.close();

    std::cout << "Binary file saved!" << std::endl;

    return 0;

}