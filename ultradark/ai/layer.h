#pragma once
#include "neuron.h"
#include <initializer_list>
namespace ultra
{
	struct neuron;
	struct layer
	{
		//construct/copy/destroy:

		layer() noexcept;
		explicit layer(unsigned n);
		layer(unsigned n, const neuron &val);
		layer(std::initializer_list<neuron> lst);
		layer(const layer &other);
		layer(layer &&other) noexcept;
		~layer();
		layer &operator = (const layer &other);
		layer &operator = (layer &&other);
		layer &operator = (std::initializer_list<neuron> lst);

		// capacity:

		unsigned size() const noexcept;

		// element access

		neuron &operator [](const unsigned idx) const;
		neuron &back();
		const neuron &back() const;

		// data access:

		neuron * data() noexcept;
		const neuron * data() const noexcept;

		// modifiers:

		neuron &add(const neuron &n);
		neuron &add(const neuron &&n);
		void remove(unsigned i);
		void remove(neuron &n);
		void pop();
		neuron &last();

	private:
		unsigned rsrv_sz = 4;
		unsigned sz = 0;
		neuron *arr;

		inline void reallocate();
	};
}