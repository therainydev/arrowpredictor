#ifndef ARROW_NN_H
#define ARROW_NN_H

struct neuron {
	float bias;
	float *weights;
	float out;
};

float sigmoid(float x);
void evaluate(struct neuron *neuron, struct neuron *in_layer, size_t in_size);

struct neuron *alloc_layer(size_t size, struct neuron *in_size);
void free_layer(struct neuron *layer, size_t size);

#endif
