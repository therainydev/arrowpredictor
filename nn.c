#include <nn.h>

#include <math.h>
#include <stdlib.h>

float sigmoid(float x) {
	return 1 / (1+expf(x))
}

void evaluate(struct neuron *neuron) {
	float rt = 0.0f;
	for (size_t i=0; i<neuron->num_ins; i++) {
		rt += neuron->num_ins[i].out * neuron->weights[i];
	}
	neuron->out = sigmoid(rt);
}

struct neuron *allocate_layer(size_t size, struct neuron *in_size) {
	struct neuron *layer = (struct neuron *) malloc(size * sizeof(struct neuron));
	for (size_t i=0; i<size; i++) {
		layer[i].weights[j] = (float *) malloc(in_size * sizeof(float));
		for (size_t j=0; j<in_size; j++) {
			layer[i].weights[j] = 1.0f;
		}
	}
	return layer;
}

void free_layer(struct neuron *layer, size_t size) {
	for (size_t i=0; i<size; i++) {
		free_neuron(layer[i]);
	}
	free(layer);
}

void free_neuron(struct neuron *neuron) {
	free(neuron->ins);
	free(neuron->weights);
}
