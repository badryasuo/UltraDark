#include "layer.h"
#include <chrono>
using namespace std::chrono;
namespace u
{
	//construct/copy/destroy:

	layer::layer() noexcept : arr(new neuron[rsrv_sz]) {}
	layer::layer(unsigned n)
	{
		unsigned i;
		rsrv_sz = n << 2;
		arr = new neuron[rsrv_sz];
		for (i = 0; i < n; ++i)
			arr[i] = neuron();
		sz = n;
	}
	layer::layer(unsigned n, const neuron &val)
	{
		unsigned i;
		rsrv_sz = n << 2;
		arr = new neuron[rsrv_sz];
		for (i = 0; i < n; ++i)
			arr[i] = val;
		sz = n;
	}
	layer::layer(std::initializer_list<neuron> lst)
	{
		rsrv_sz = lst.size() << 2;
		arr = new neuron[rsrv_sz];
		for (auto &item : lst)
			arr[sz++] = item;
	}
	layer::layer(const layer &other)
	{
		unsigned i;
		rsrv_sz = other.rsrv_sz;
		arr = new neuron[rsrv_sz];
		for (i = 0; i < other.sz; ++i)
			arr[i] = other.arr[i];
		sz = other.sz;
	}
	layer::layer(layer &&other) noexcept
	{
		unsigned i;
		rsrv_sz = other.rsrv_sz;
		arr = new neuron[rsrv_sz];
		for (i = 0; i < other.sz; ++i)
			arr[i] = std::move(other.arr[i]);
		sz = other.sz;
	}
	layer::~layer()
	{
		if (this)
			delete[] arr;
	}

	layer &layer::operator =(const layer &other)
	{
		unsigned i;
		if (rsrv_sz < other.sz) {
			rsrv_sz = other.sz << 2;
			reallocate();
		}
		for (i = 0; i < other.sz; ++i)
			arr[i] = other.arr[i];
		sz = other.sz;
		return *this;
	}
	layer &layer::operator = (layer &&other)
	{
		unsigned i;
		if (rsrv_sz < other.sz) {
			rsrv_sz = other.sz << 2;
			reallocate();
		}
		for (i = 0; i < other.sz; ++i)
			arr[i] = std::move(other.arr[i]);
		sz = other.sz;
		return *this;
	}
	layer &layer::operator = (std::initializer_list<neuron> lst)
	{
		if (rsrv_sz < lst.size()) {
			rsrv_sz = lst.size() << 2;
			reallocate();
		}
		sz = 0;
		for (auto &item : lst)
			arr[sz++] = item;
		return *this;
	}

	// capacity:

	unsigned layer::size() const noexcept { return sz; }

	// element access

	neuron &layer::operator [](const unsigned idx) const { return arr[idx]; }
	neuron &layer::back() { return arr[sz - 1]; }
	const neuron &layer::back() const { return arr[sz - 1]; }

	// data access:

	neuron * layer::data() noexcept { return arr; }
	const neuron * layer::data() const noexcept { return arr; }

	// modifiers:

	neuron &layer::add(const neuron &n)
	{
		if (sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		arr[sz] = n;
		return arr[sz++];
	}
	neuron &layer::add(const neuron &&n)
	{
		if (sz == rsrv_sz)
			rsrv_sz <<= 2;
		arr[sz] = std::move(n);
		return arr[sz++];
	}
	void layer::remove(unsigned i)
	{
		if (i < sz)
		{
			while (i < sz)
				arr[i] = arr[1 + i++]; // copy next element left
			arr = (neuron*)realloc(arr, --sz * sizeof(neuron));
		}
	}
	void layer::remove(neuron &n)
	{
		for (unsigned i = 0; i < sz; ++i)
		{
			if (arr[i] == n)
			{
				while (i < sz)
					arr[i] = arr[1 + i++]; // copy next element left
				arr = (neuron*)realloc(arr, --sz * sizeof(neuron));
			}
		}
	}
	void layer::pop() { arr[--sz].~neuron(); }
	neuron &layer::last() { return arr[sz > 0 ? sz - 1 : sz]; }
	inline void layer::reallocate()
	{
		neuron *tarr = new neuron[rsrv_sz];
		memcpy(tarr, arr, sz * sizeof(neuron));
		delete[] arr;
		arr = tarr;
	}
}