#include <nn.h>

#include <math.h>

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
