#ifndef ARROW_NN_H
#define ARROW_NN_H

struct neuron {
	size_t num_ins;
	struct neuron *ins;
	float *in_weights;
	float out;
};

float sigmoid(float x);
void evaluate(struct neuron *neuron);

struct neuron *alloc_layer(size_t size);

void free_neuron(struct neuron *neuron);
void free_layer(struct neuron *layer, size_t size);

#endif
