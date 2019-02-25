#include "layer.h"
#include <cassert> // assert
#include <vector>
namespace u
{
	struct neural_net
	{
		neural_net()
		{

		}
		neural_net(const std::vector<unsigned> &layers)
		{
			unsigned layers_num = layers.size();
			for (unsigned i = 0; i < layers_num; ++i)
			{
				this->layers.push_back(layer());
				unsigned outputs_num = (i == layers_num - 1) ? 0 : layers[i + 1];
				for (unsigned neuron_num = 0; neuron_num <= layers[i]; ++neuron_num)
				{
					this->layers.back().add(neuron(neuron_num, outputs_num));
					std::cout << "Made a neuron.\n";
				}
			}
		}
		void feed_forward(const std::vector<double> &inputs) const
		{
			size_t inputs_size = inputs.size(),
			layers_size =  this->layers.size();
			// Make sure inputs number is equal to
			// the number of neurons in the input layer which is the 1st layer.
			assert(inputs_size == this->layers[0].size() - 1); // bias doesn't count.
			// latch the input values into the input layer.
			for (unsigned i = 0; i < inputs_size; ++i) // `i` for 'input'.
			{
				this->layers[0][i].output = inputs[i];
			}
			/*     Feed Propagate     */
			/*------------------------*/
			for (unsigned l = 1; l < layers_size; ++l) // `l` for 'layer'.
			{
				const layer &prev_layer = layers[l - 1];
				for (unsigned n = 0; n < layers[l].size() - 1; ++n) // `n` for 'neuron'.
				{
					this->layers[l][n].feed_forward(prev_layer);
				}
			}
		}
		void back_prop(const std::vector<double> &targets) const
		{

		}
		std::vector<double> get_results() const
		{
			std::vector<double> results;
			/* ...do stuff... */
			return results;
		}
	private:
		std::vector<layer> layers;
	};
}