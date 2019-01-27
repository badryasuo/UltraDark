#include <vector>
namespace ultra
{
	struct connection
	{
		double weight = 0.;
		double delta_weight = 0.;
		constexpr connection();
		constexpr connection(double weight);
		const bool operator ==(const connection &conn) const;
		const bool operator !=(const connection &conn) const;
	};
	struct layer;
	struct neuron
	{
		double output = 0.;
		unsigned index = 0;
		std::vector<connection> output_weights;
		neuron();
		neuron(unsigned index, unsigned outputs_num);
		const bool &operator ==(const neuron &n);
		void feed_forward(const layer &prev_layer);
		static double random_weight();
	};
}