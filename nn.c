#include <nn.h>

#include <math.h>
#include <stdlib.h>

float sigmoid(float x) {
	return 1 / (1+expf(x))
}

void evaluate(struct neuron *neuron, struct neuron *in_layer, size_t in_size) {
	float rt = neuron->bias;
	for (size_t i=0; i<in_size; i++) {
		rt += in_layer[i].out * neuron->weights[i];
	}
	neuron->out = sigmoid(rt);
}

struct neuron *alloc_layer(size_t size, struct neuron *in_size) {
	struct neuron *layer = (struct neuron *) malloc(size * sizeof(struct neuron));
	for (size_t i=0; i<size; i++) {
		layer[i].weights[j] = (float *) malloc(in_size * sizeof(float));
		for (size_t j=0; j<in_size; j++) {
			layer[i].weights[j] = 1.0f;
			layer[i].bias = 0.0f;
		}
	}
	return layer;
}

void free_layer(struct neuron *layer, size_t size) {
	for (size_t i=0; i<size; i++) {
		free(layer[i]->weights);
	}
	free(layer);
}
