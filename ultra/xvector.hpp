#pragma once
#include <cstddef>
#include <cstring>
#include <utility>
#include <iterator>
#include <stdexcept>

#define LNI_VECTOR_MAX_SZ 1000000000
namespace u {
	typedef unsigned size_t;
	template <typename T>
	class xvector {
		size_t rsrv_sz = 4;
		size_t vec_sz = 0;
		T *arr;

		inline void reallocate();
		public:
			// types:
			typedef T                                     value_type;
			typedef T &                                   reference;
			typedef const T &                             const_reference;
			typedef T *                                   pointer;
			typedef const T *                             const_pointer;
			typedef T *                                   iterator;
			typedef const T *                             const_iterator;
			typedef std::reverse_iterator<iterator>       reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef ptrdiff_t                             difference_type;

			// 23.3.11.2, construct/copy/destroy:
			xvector() noexcept;
			explicit xvector(size_t n);
			xvector(size_t n, const T &val);
			xvector(typename xvector<T>::iterator first, typename xvector<T>::iterator last);
			xvector(std::initializer_list<T>);
			xvector(const xvector<T> &);
			xvector(xvector<T> &&) noexcept;
			~xvector();
			xvector<T> & operator = (const xvector<T> &);
			xvector<T> & operator = (xvector<T> &&);
			xvector<T> & operator = (std::initializer_list<T>);
			void assign(size_t, const T &value);
			void assign(typename xvector<T>::iterator, typename xvector<T>::iterator);
			void assign(std::initializer_list<T>);

			// iterators:
			iterator begin() noexcept;
			const_iterator cbegin() const noexcept;
			iterator end() noexcept;
			const_iterator cend() const noexcept;
			reverse_iterator rbegin() noexcept;
			const_reverse_iterator crbegin() const noexcept;
			reverse_iterator rend() noexcept;
			const_reverse_iterator crend() const noexcept;

			// 23.3.11.3, capacity:
			bool empty() const noexcept;
			size_t size() const noexcept;
			size_t max_size() const noexcept;
			size_t capacity() const noexcept;
			void resize(size_t);
			void resize(size_t, const T &);
			void reserve(size_t);
			void shrink_to_fit();

			// element access
			reference operator [](size_t);
			const_reference operator [](size_t) const;
			reference at(size_t);
			const_reference at(size_t) const;
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;

			// 23.3.11.4, data access:
			T * data() noexcept;
			const T * data() const noexcept; 

			// 23.3.11.5, modifiers:
			template <class ... Args> void emplace_back(Args && ... args);
			void push_back(const T &);
			void push_back(T &&);
			void pop_back();
	
			template <class ... Args> iterator emplace(const_iterator, Args && ...); 
			iterator insert(const_iterator, const T &);
			iterator insert(const_iterator, T &&);
			iterator insert(const_iterator, size_t, const T&);
			template <class InputIt> iterator insert(const_iterator, InputIt, InputIt);
			iterator insert(const_iterator, std::initializer_list<T>);
			iterator erase(const_iterator);
			iterator erase(const_iterator, const_iterator);
			void swap(xvector<T> &);
			void clear() noexcept;

			bool operator == (const xvector<T> &) const;
			bool operator != (const xvector<T> &) const;
			bool operator < (const xvector<T> &) const;
			bool operator <= (const xvector<T> &) const;
			bool operator > (const xvector<T> &) const;
			bool operator >= (const xvector<T> &) const;

	};


	
	template <typename T>
	xvector<T>::xvector() noexcept {
		arr = new T[rsrv_sz];
	}

	template <typename T>
	xvector<T>::xvector(size_t n) {
		size_t i;
		rsrv_sz = n << 2;
		arr = new T[rsrv_sz];
		for (i = 0; i < n; ++i)
			arr[i] = T();
		vec_sz = n;
	}

	template <typename T>
	xvector<T>::xvector(size_t n, const T &value) {
		size_t i;
		rsrv_sz = n << 2;
		arr = new T[rsrv_sz];
		for (i = 0; i < n; ++i)
			arr[i] = value;
		vec_sz = n;
	}

	template <typename T>
	xvector<T>::xvector(typename xvector<T>::iterator first, typename xvector<T>::iterator last) {
		size_t i, count = last - first;
		rsrv_sz = count << 2;
		arr = new T[rsrv_sz];
		for (i = 0; i < count; ++i, ++first)
			arr[i] = *first;
		vec_sz = count;
	}

	template <typename T>
	xvector<T>::xvector(std::initializer_list<T> lst) {
		rsrv_sz = lst.size() << 2;
		arr = new T[rsrv_sz];
		for (auto &item: lst)
			arr[vec_sz++] = item;
	}

	template <typename T>
	xvector<T>::xvector(const xvector<T> &other) {
		size_t i;
		rsrv_sz = other.rsrv_sz;
		arr = new T[rsrv_sz];
		for (i = 0; i < other.vec_sz; ++i)
			arr[i] = other.arr[i];
		vec_sz = other.vec_sz;
	}

	template <typename T>
	xvector<T>::xvector(xvector<T> &&other) noexcept {
		size_t i;
		rsrv_sz = other.rsrv_sz;
		arr = new T[rsrv_sz];
		for (i = 0; i < other.vec_sz; ++i)
			arr[i] = std::move(other.arr[i]);
		vec_sz = other.vec_sz;
	}

	template <typename T>
	xvector<T>::~xvector() {
		delete [] arr;
	}

	template <typename T>
	xvector<T> & xvector<T>::operator = (const xvector<T> &other) {
		size_t i;
		if (rsrv_sz < other.vec_sz) {
			rsrv_sz = other.vec_sz << 2;
			reallocate();
		}
		for (i = 0; i < other.vec_sz; ++i)
			arr[i] = other.arr[i];
		vec_sz = other.vec_sz;
	}

	template <typename T>
	xvector<T> & xvector<T>::operator = (xvector<T> &&other) {
		size_t i;
		if (rsrv_sz < other.vec_sz) {
			rsrv_sz = other.vec_sz << 2;
			reallocate();
		}
		for (i = 0; i < other.vec_sz; ++i)
			arr[i] = std::move(other.arr[i]);
		vec_sz = other.vec_sz;
	}

	template <typename T>
	xvector<T> & xvector<T>::operator = (std::initializer_list<T> lst) {
		if (rsrv_sz < lst.size()) {
			rsrv_sz = lst.size() << 2;
			reallocate();
		}
		vec_sz = 0;
		for (auto &item: lst)
			arr[vec_sz++] = item;
		return *this;
	}

	template <typename T>
	void xvector<T>::assign(size_t count, const T &value) {
		size_t i;
		if (count > rsrv_sz) {
			rsrv_sz = count << 2;
			reallocate();
		}
		for (i = 0; i < count; ++i)
			arr[i] = value;
		vec_sz = count;
	}

	template <typename T>
	void xvector<T>::assign(typename xvector<T>::iterator first, typename xvector<T>::iterator last) {
		size_t i, count = last - first;
		if (count > rsrv_sz) {
			rsrv_sz = count << 2;
			reallocate();
		}
		for (i = 0; i < count; ++i, ++first)
			arr[i] = *first;
		vec_sz = count;
	}

	template <typename T>
	void xvector<T>::assign(std::initializer_list<T> lst) {
		size_t i, count = lst.size();
		if (count > rsrv_sz) {
			rsrv_sz = count << 2;
			reallocate();
		}
		i = 0;
		for (auto &item: lst)
			arr[i++] = item;
	}


	template <typename T>
	typename xvector<T>::iterator xvector<T>::begin() noexcept {
		return arr;
	}

	template <typename T>
	typename xvector<T>::const_iterator xvector<T>::cbegin() const noexcept {
		return arr;
	}

	template <typename T>
	typename xvector<T>::iterator xvector<T>::end() noexcept {
		return arr + vec_sz;
	}

	template <typename T>
	typename xvector<T>::const_iterator xvector<T>::cend() const noexcept {
		return arr + vec_sz;
	}

	template <typename T>
	typename xvector<T>::reverse_iterator xvector<T>::rbegin() noexcept {
		return reverse_iterator(arr + vec_sz);
	}

	template <typename T>
	typename xvector<T>::const_reverse_iterator xvector<T>::crbegin() const noexcept {
		return reverse_iterator(arr + vec_sz);
	}

	template <typename T>
	typename xvector<T>::reverse_iterator xvector<T>::rend() noexcept {
		return reverse_iterator(arr);
	}
	
	template <typename T>
	typename xvector<T>::const_reverse_iterator xvector<T>::crend() const noexcept {
		return reverse_iterator(arr);
	}


	template <typename T>
	inline void xvector<T>::reallocate() {
		T *tarr = new T[rsrv_sz];
		memcpy(tarr, arr, vec_sz * sizeof(T));
		delete [] arr;
		arr = tarr;
	}


	template <typename T>
	bool xvector<T>::empty() const noexcept {
		return vec_sz == 0;
	}
	
	template <typename T>
	size_t xvector<T>::size() const noexcept{
		return vec_sz;
	}

	template <typename T>
	size_t xvector<T>::max_size() const noexcept {
		return LNI_VECTOR_MAX_SZ;
	}

	template <typename T>
	size_t xvector<T>::capacity() const noexcept {
		return rsrv_sz;
	}
	
	template <typename T>
	void xvector<T>::resize(size_t sz) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
		} else {
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i].~T();
		}
		vec_sz = sz;
	}

	template <typename T>
	void xvector<T>::resize(size_t sz, const T &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		} else {
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i].~T();
		}
		vec_sz = sz;
	}

	template <typename T>
	void xvector<T>::reserve(size_t _sz) {
		if (_sz > rsrv_sz) {
			rsrv_sz = _sz;
			reallocate();
		}
	}

	template <typename T>
	void xvector<T>::shrink_to_fit() {
		rsrv_sz = vec_sz;
		reallocate();
	}

	
	template <typename T>
	typename xvector<T>::reference xvector<T>::operator [](size_t idx) {
		return arr[idx];
	}

	template <typename T>
	typename xvector<T>::const_reference xvector<T>::operator [](size_t idx) const {
		return arr[idx];
	}

	template <typename T>
	typename xvector<T>::reference xvector<T>::at(size_t pos) {
		if (pos < vec_sz)
			return arr[pos];
		else
			throw std::out_of_range("accessed position is out of range");
	}

	template <typename T>
	typename xvector<T>::const_reference xvector<T>::at(size_t pos) const {
		if (pos < vec_sz)
			return arr[pos];
		else
			throw std::out_of_range("accessed position is out of range");
	}

	template <typename T>
	typename xvector<T>::reference xvector<T>::front() {
		return arr[0];
	}

	template <typename T>
	typename xvector<T>::const_reference xvector<T>::front() const {
		return arr[0];
	}

	template <typename T>
	typename xvector<T>::reference xvector<T>::back() {
		return arr[vec_sz - 1];
	}

	template <typename T>
	typename xvector<T>::const_reference xvector<T>::back() const {
		return arr[vec_sz - 1];
	}

	
	template <typename T>
	T * xvector<T>::data() noexcept {
		return arr;
	}

	template <typename T>
	const T * xvector<T>::data() const noexcept {
		return arr;
	}


	template <typename T>
	template <class ... Args>
	void xvector<T>::emplace_back(Args && ... args) {
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		arr[vec_sz] = std::move( T( std::forward<Args>(args) ... ) );
		++vec_sz;
	}

	template <typename T>
	void xvector<T>::push_back(const T &val) {
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		arr[vec_sz] = val;
		++vec_sz;
	}

	template <typename T>
	void xvector<T>::push_back(T &&val) {
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		arr[vec_sz] = std::move(val);
		++vec_sz;
	}

	template <typename T>
	void xvector<T>::pop_back() {
		--vec_sz;
		arr[vec_sz].~T();
	}


	template <typename T>
	template <class ... Args>
	typename xvector<T>::iterator xvector<T>::emplace(typename xvector<T>::const_iterator it, Args && ... args) {
		iterator iit = &arr[it - arr];
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		memmove(iit + 1, iit, (vec_sz - (it - arr)) * sizeof(T));
		(*iit) = std::move( T( std::forward<Args>(args) ... ) );
		++vec_sz;
		return iit;
	}

	template <typename T>
	typename xvector<T>::iterator xvector<T>::insert(typename xvector<T>::const_iterator it, const T &val) {
		iterator iit = &arr[it - arr];
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		memmove(iit + 1, iit, (vec_sz - (it - arr)) * sizeof(T));
		(*iit) = val;
		++vec_sz;
		return iit;
	}

	template <typename T>
	typename xvector<T>::iterator xvector<T>::insert(typename xvector<T>::const_iterator it, T &&val) {
		iterator iit = &arr[it - arr];
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		memmove(iit + 1, iit, (vec_sz - (it - arr)) * sizeof(T));
		(*iit) = std::move(val);
		++vec_sz;
		return iit;
	}

	template <typename T>
	typename xvector<T>::iterator xvector<T>::insert(typename xvector<T>::const_iterator it, size_t cnt, const T &val) {
		iterator f = &arr[it - arr];
		if (!cnt) return f;
		if (vec_sz + cnt > rsrv_sz) {
			rsrv_sz = (vec_sz + cnt) << 2;
			reallocate();
		}
		memmove(f + cnt, f, (vec_sz - (it - arr)) * sizeof(T));
		vec_sz += cnt;
		for (iterator it = f; cnt--; ++it)
			(*it) = val;
		return f;
	}

	template <typename T>
	template <class InputIt>
	typename xvector<T>::iterator xvector<T>::insert(typename xvector<T>::const_iterator it, InputIt first, InputIt last) {
		iterator f = &arr[it - arr];
		size_t cnt = last - first;
		if (!cnt) return f;
		if (vec_sz + cnt > rsrv_sz) {
			rsrv_sz = (vec_sz + cnt) << 2;
			reallocate();
		}
		memmove(f + cnt, f, (vec_sz - (it - arr)) * sizeof(T));
		for (iterator it = f; first != last; ++it, ++first)
			(*it) = *first;
		vec_sz += cnt;
		return f;
	}

	template <typename T>
	typename xvector<T>::iterator xvector<T>::insert(typename xvector<T>::const_iterator it, std::initializer_list<T> lst) {
		size_t cnt = lst.size();
		iterator f = &arr[it - arr];
		if (!cnt) return f;
		if (vec_sz + cnt > rsrv_sz) {
			rsrv_sz = (vec_sz + cnt) << 2;
			reallocate();
		}
		memmove(f + cnt, f, (vec_sz - (it - arr)) * sizeof(T));
		iterator iit = f;
		for (auto &item: lst) {
			(*iit) = item;
			++iit;
		}
		vec_sz += cnt;
		return f;
	}

	template <typename T>
	typename xvector<T>::iterator xvector<T>::erase(typename xvector<T>::const_iterator it) {
		iterator iit = &arr[it - arr];
		(*iit).~T();
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(T));
		--vec_sz;
		return iit;
	}

	template <typename T>
	typename xvector<T>::iterator xvector<T>::erase(typename xvector<T>::const_iterator first, typename xvector<T>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		for ( ; first != last; ++first)
			(*first).~T();
		memmove(f, last, (vec_sz - (last - arr)) * sizeof(T));
		vec_sz -= last - first;
		return f;
	}

	template <typename T>
	void xvector<T>::swap(xvector<T> &rhs) {
		size_t tvec_sz = vec_sz,
			   trsrv_sz = rsrv_sz;
		T *tarr = arr;

		vec_sz = rhs.vec_sz;
		rsrv_sz = rhs.rsrv_sz;
		arr = rhs.arr;

		rhs.vec_sz = tvec_sz;
		rhs.rsrv_sz = trsrv_sz;
		rhs.arr = tarr;
	}

	template <typename T>
	void xvector<T>::clear() noexcept {
		size_t i;
		for (i = 0; i < vec_sz; ++i)
			arr[i].~T();
		vec_sz = 0;
	}

	
	template <typename T>
	bool xvector<T>::operator == (const xvector<T> &rhs) const {
		if (vec_sz != rhs.vec_sz) return false;
		size_t i;
		for (i = 0; i < vec_sz; ++i)
			if (arr[i] != rhs.arr[i])
				return false;
		return true;
	}

	template <typename T>
	bool xvector<T>::operator != (const xvector<T> &rhs) const {
		if (vec_sz != rhs.vec_sz) return true;
		size_t i;
		for (i = 0; i < vec_sz; ++i)
			if (arr[i] != rhs.arr[i])
				return true;
		return false;
	}

	template <typename T>
	bool xvector<T>::operator < (const xvector<T> &rhs) const {
		size_t i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] < rhs.arr[i];
		return vec_sz < rhs.vec_sz;
	}

	template <typename T>
	bool xvector<T>::operator <= (const xvector<T> &rhs) const {
		size_t i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] < rhs.arr[i];
		return vec_sz <= rhs.vec_sz;
	}

	template <typename T>
	bool xvector<T>::operator > (const xvector<T> &rhs) const {
		size_t i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] > rhs.arr[i];
		return vec_sz > rhs.vec_sz;
	}

	template <typename T>
	bool xvector<T>::operator >= (const xvector<T> &rhs) const {
		size_t i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] > rhs.arr[i];
		return vec_sz >= rhs.vec_sz;
	}



	template <>
	void xvector<bool>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void xvector<signed char>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void xvector<unsigned char>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void xvector<char>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void xvector<short int>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void xvector<unsigned short int>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void xvector<int>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void xvector<unsigned int>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void xvector<long int>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void xvector<unsigned long int>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void xvector<long long int>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void xvector<unsigned long long int>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void xvector<float>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void xvector<double>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void xvector<long double>::resize(size_t sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}


	template <>
	void xvector<bool>::resize(size_t sz, const bool &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void xvector<signed char>::resize(size_t sz, const signed char &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void xvector<unsigned char>::resize(size_t sz, const unsigned char &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void xvector<char>::resize(size_t sz, const char &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void xvector<short int>::resize(size_t sz, const short int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void xvector<unsigned short int>::resize(size_t sz, const unsigned short int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void xvector<int>::resize(size_t sz, const int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void xvector<unsigned int>::resize(size_t sz, const unsigned int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void xvector<long int>::resize(size_t sz, const long int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void xvector<unsigned long int>::resize(size_t sz, const unsigned long int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void xvector<long long int>::resize(size_t sz, const long long int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void xvector<unsigned long long int>::resize(size_t sz, const unsigned long long int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void xvector<float>::resize(size_t sz, const float &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void xvector<double>::resize(size_t sz, const double &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void xvector<long double>::resize(size_t sz, const long double &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_t i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}


	template <>
	void xvector<bool>::pop_back() {
		--vec_sz;
	}

	template <>
	void xvector<signed char>::pop_back() {
		--vec_sz;
	}

	template <>
	void xvector<unsigned char>::pop_back() {
		--vec_sz;
	}

	template <>
	void xvector<char>::pop_back() {
		--vec_sz;
	}

	template <>
	void xvector<short int>::pop_back() {
		--vec_sz;
	}

	template <>
	void xvector<unsigned short int>::pop_back() {
		--vec_sz;
	}

	template <>
	void xvector<int>::pop_back() {
		--vec_sz;
	}

	template <>
	void xvector<unsigned int>::pop_back() {
		--vec_sz;
	}

	template <>
	void xvector<long int>::pop_back() {
		--vec_sz;
	}

	template <>
	void xvector<unsigned long int>::pop_back() {
		--vec_sz;
	}

	template <>
	void xvector<long long int>::pop_back() {
		--vec_sz;
	}

	template <>
	void xvector<unsigned long long int>::pop_back() {
		--vec_sz;
	}

	template <>
	void xvector<float>::pop_back() {
		--vec_sz;
	}

	template <>
	void xvector<double>::pop_back() {
		--vec_sz;
	}

	template <>
	void xvector<long double>::pop_back() {
		--vec_sz;
	}


	template <>
	typename xvector<bool>::iterator xvector<bool>::erase(typename xvector<bool>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(bool));
		--vec_sz;
		return iit;
	}

	template <>
	typename xvector<signed char>::iterator xvector<signed char>::erase(typename xvector<signed char>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(signed char));
		--vec_sz;
		return iit;
	}

	template <>
	typename xvector<unsigned char>::iterator xvector<unsigned char>::erase(typename xvector<unsigned char>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(unsigned char));
		--vec_sz;
		return iit;
	}

	template <>
	typename xvector<char>::iterator xvector<char>::erase(typename xvector<char>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(char));
		--vec_sz;
		return iit;
	}

	template <>
	typename xvector<short int>::iterator xvector<short int>::erase(typename xvector<short int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(short int));
		--vec_sz;
		return iit;
	}

	template <>
	typename xvector<unsigned short int>::iterator xvector<unsigned short int>::erase(typename xvector<unsigned short int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(unsigned short int));
		--vec_sz;
		return iit;
	}

	template <>
	typename xvector<int>::iterator xvector<int>::erase(typename xvector<int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(int));
		--vec_sz;
		return iit;
	}

	template <>
	typename xvector<unsigned int>::iterator xvector<unsigned int>::erase(typename xvector<unsigned int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(unsigned int));
		--vec_sz;
		return iit;
	}

	template <>
	typename xvector<long int>::iterator xvector<long int>::erase(typename xvector<long int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(long int));
		--vec_sz;
		return iit;
	}

	template <>
	typename xvector<unsigned long int>::iterator xvector<unsigned long int>::erase(typename xvector<unsigned long int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(unsigned long int));
		--vec_sz;
		return iit;
	}

	template <>
	typename xvector<long long int>::iterator xvector<long long int>::erase(typename xvector<long long int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(long long int));
		--vec_sz;
		return iit;
	}

	template <>
	typename xvector<unsigned long long int>::iterator xvector<unsigned long long int>::erase(typename xvector<unsigned long long int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(unsigned long long int));
		--vec_sz;
		return iit;
	}

	template <>
	typename xvector<float>::iterator xvector<float>::erase(typename xvector<float>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(float));
		--vec_sz;
		return iit;
	}

	template <>
	typename xvector<double>::iterator xvector<double>::erase(typename xvector<double>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(double));
		--vec_sz;
		return iit;
	}

	template <>
	typename xvector<long double>::iterator xvector<long double>::erase(typename xvector<long double>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(long double));
		--vec_sz;
		return iit;
	}


	template <>
	typename xvector<bool>::iterator xvector<bool>::erase(typename xvector<bool>::const_iterator first, typename xvector<bool>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vec_sz - (last - arr)) * sizeof(bool));
		vec_sz -= last - first;
		return f;
	}

	template <>
	typename xvector<signed char>::iterator xvector<signed char>::erase(typename xvector<signed char>::const_iterator first, typename xvector<signed char>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vec_sz - (last - arr)) * sizeof(signed char));
		vec_sz -= last - first;
		return f;
	}

	template <>
	typename xvector<unsigned char>::iterator xvector<unsigned char>::erase(typename xvector<unsigned char>::const_iterator first, typename xvector<unsigned char>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vec_sz - (last - arr)) * sizeof(unsigned char));
		vec_sz -= last - first;
		return f;
	}

	template <>
	typename xvector<char>::iterator xvector<char>::erase(typename xvector<char>::const_iterator first, typename xvector<char>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vec_sz - (last - arr)) * sizeof(char));
		vec_sz -= last - first;
		return f;
	}

	template <>
	typename xvector<short int>::iterator xvector<short int>::erase(typename xvector<short int>::const_iterator first, typename xvector<short int>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vec_sz - (last - arr)) * sizeof(short int));
		vec_sz -= last - first;
		return f;
	}

	template <>
	typename xvector<unsigned short int>::iterator xvector<unsigned short int>::erase(typename xvector<unsigned short int>::const_iterator first, typename xvector<unsigned short int>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vec_sz - (last - arr)) * sizeof(unsigned short int));
		vec_sz -= last - first;
		return f;
	}

	template <>
	typename xvector<int>::iterator xvector<int>::erase(typename xvector<int>::const_iterator first, typename xvector<int>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vec_sz - (last - arr)) * sizeof(int));
		vec_sz -= last - first;
		return f;
	}

	template <>
	typename xvector<unsigned int>::iterator xvector<unsigned int>::erase(typename xvector<unsigned int>::const_iterator first, typename xvector<unsigned int>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vec_sz - (last - arr)) * sizeof(unsigned int));
		vec_sz -= last - first;
		return f;
	}

	template <>
	typename xvector<long long int>::iterator xvector<long long int>::erase(typename xvector<long long int>::const_iterator first, typename xvector<long long int>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vec_sz - (last - arr)) * sizeof(long long int));
		vec_sz -= last - first;
		return f;
	}

	template <>
	typename xvector<unsigned long long int>::iterator xvector<unsigned long long int>::erase(typename xvector<unsigned long long int>::const_iterator first, typename xvector<unsigned long long int>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vec_sz - (last - arr)) * sizeof(unsigned long long int));
		vec_sz -= last - first;
		return f;
	}

	template <>
	typename xvector<float>::iterator xvector<float>::erase(typename xvector<float>::const_iterator first, typename xvector<float>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vec_sz - (last - arr)) * sizeof(float));
		vec_sz -= last - first;
		return f;
	}

	template <>
	typename xvector<double>::iterator xvector<double>::erase(typename xvector<double>::const_iterator first, typename xvector<double>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vec_sz - (last - arr)) * sizeof(double));
		vec_sz -= last - first;
		return f;
	}

	template <>
	typename xvector<long double>::iterator xvector<long double>::erase(typename xvector<long double>::const_iterator first, typename xvector<long double>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vec_sz - (last - arr)) * sizeof(long double));
		vec_sz -= last - first;
		return f;
	}


	template <>
	void xvector<bool>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void xvector<signed char>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void xvector<unsigned char>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void xvector<char>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void xvector<short int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void xvector<unsigned short int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void xvector<int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void xvector<unsigned int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void xvector<long int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void xvector<unsigned long int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void xvector<long long int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void xvector<unsigned long long int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void xvector<float>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void xvector<double>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void xvector<long double>::clear() noexcept {
		vec_sz = 0;
	}


}
