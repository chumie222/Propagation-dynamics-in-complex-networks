/*
 * double_layer_infection.h
 *
 *  Created on: 2017-8-11
 *      Author: Administrator
 */

#ifndef DOUBLE_LAYER_INFECTION_H_
#define DOUBLE_LAYER_INFECTION_H_

#include "total.h"
#include "network/network_total.h"
#include "network/network_basic_ops.h"

void double_layer_infection(Node A[], Node B[], float alpha_A, float r_A, float alpha_B, float r_B, float p_AB, int k, int network_size);


#endif /* DOUBLE_LAYER_INFECTION_H_ */
