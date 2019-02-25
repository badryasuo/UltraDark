#include "layer.h"
namespace u
{
	/* connection implementation */

	constexpr connection::connection()
	{
	}
	constexpr connection::connection(double weight) : weight(weight)
	{
	}
	const bool connection::operator ==(const connection &conn) const
	{
		return weight == conn.weight && delta_weight == conn.delta_weight;
	}
	const bool connection::operator !=(const connection &conn) const
	{
		return weight != conn.weight || delta_weight != conn.delta_weight;
	}

	/* neuron implementation */

	neuron::neuron() {}
	neuron::neuron(unsigned index, unsigned outputs_num) : index(index)
	{
		for (unsigned i = 0; i < outputs_num; ++i)
		{
			output_weights.push_back(connection(random_weight()));
		}
	}
	const bool &neuron::operator ==(const neuron &n)
	{
		unsigned w_size = output_weights.size(),
			n_w_size = n.output_weights.size();
		if (output == n.output && w_size == n_w_size)
		{
			for (unsigned i = 0; i < w_size; ++i)
				if (output_weights[i] != n.output_weights[i])
					return false;
		}
		else
			return false;

		return true;
	}

	void neuron::feed_forward(const layer &prev_layer)
	{
		double sum = 0.;
		size_t prev_Layer_size = prev_layer.size();
		for (unsigned n = 0; n < prev_Layer_size; ++n)
		{
			sum += prev_layer[n].output * prev_layer[n].output_weights[index].weight;
		}
		//this->output = transfer_function();
	}
	double neuron::random_weight()
	{
		//srand(time(0));
		return double(rand()) / RAND_MAX;
	}
}