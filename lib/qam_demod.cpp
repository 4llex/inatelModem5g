
//#include <stdio.h>
//#include <iostream>
#define ARMA_DONT_USE_WRAPPER
#include "qam_demod.h"
#include <armadillo>
#include <bits/stdc++.h>
using namespace std;
using namespace arma;

vector<complex<float>> qamllr(vector<complex<float>> r, 
                              vector<complex<float>> constel,
                              vector<int> map, 
                              vector<float> noise){

    int M = constel.size();
    int mu = log2 (M);
    int n = r.size();

    // ######### Converting vectors to armadillo matrix ###########################
    arma::cx_mat arm_r = conv_to<cx_mat>::from(r);
    arma::cx_mat arm_constel = conv_to<cx_mat>::from(constel);
    arma::fmat arm_map = conv_to<fmat>::from(map);
    arma::fmat arm_noise = conv_to<fmat>::from(noise);
    
    // ######### Hard Decision ####################################################
    arma::mat dist = abs(repmat(arm_r, 1, M) - repmat(strans(arm_constel), n, 1));
    arma::umat index = index_min(strans(dist));

    std::vector<int> d_hat = conv_to<std::vector<int>>::from(index);
    
    vector<complex<float>> m_hat(index.n_elem);
    #pragma simd
    for(uword i=0; i<index.n_elem; ++i) { 
        m_hat[i] = arm_constel[index[i]];
    }
    
    // ######### LLR - Soft Decision ##############################################
    #pragma simd
    for(uword i=0; i<arm_noise.n_elem; ++i) { 
        if (arm_noise[i] < 0.0001)
            arm_noise[i] = 0.00001;
    }

    dist = pow(dist, 2);
    arm_noise = pow(arm_noise, -1);

    arma::mat exp_mat;
    if(arm_noise.n_elem!=1){
        exp_mat = trans(exp(-(repmat(arm_noise,1,M) % dist)));     
    }else{
        exp_mat = trans(exp(-((1/noise[0]) * dist)));
    }
    
    arma::mat llr = zeros<mat>(mu,n);

    #pragma simd
    for (int pos=0; pos<mu; pos++){
        arma::mat matrix1 = log(sum(exp_mat.rows(find((getBit(map,pos)== 0)== 1)),0));
        arma::mat matrix2 = log(sum(exp_mat.rows(find((getBit(map,pos)== 1)== 1)),0));
        llr.row(mu-pos-1) = matrix1 - matrix2;
    } 

    llr = vectorise(llr);
    llr.replace(datum::nan, 0);
    llr.elem(find(llr > 14)).fill(14);
    llr.elem(find(llr < -14)).fill(-14);

    arma::imat b_hat = conv_to<imat>::from(llr);
    b_hat.elem(find(b_hat > 0)).fill(0);
    b_hat.elem(find(b_hat < 0)).ones();

    return m_hat;

}

arma::mat getBit(vector<int> map, int position)
{
    vector<int> bitgetvec(map.size());
    #pragma simd
    for(int i=0; i<map.size(); i++){
        bitgetvec[i] = (map[i]>>position) & 1;
    }
    arma::mat t = conv_to<mat>::from(bitgetvec);
    return t;
}