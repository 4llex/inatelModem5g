// file: qam_demod.h
#pragma once
#ifndef __QAM_DEMOD_H__
#define __QAM_DEMOD_H__

#include <bits/stdc++.h>
#include <armadillo>
using namespace std;
using namespace arma;

// Protótipos de funções
vector<complex<float>> qamllr(vector<complex<float> > r,
                                vector<complex<float> > constel, 
                                vector<int> map, 
                                vector<float> noise);

arma::mat getBit(vector<int> map, int position);

#endif
