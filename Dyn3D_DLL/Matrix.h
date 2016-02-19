#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include <exception>
#include <type_traits>

typedef unsigned __int32 Index_t;
typedef unsigned __int8 Dimension_t;

/*
Behaves just like a mathematical matrix as well as a single dimensional array
of Type.*/
template<typename Type, Dimension_t Rows, Dimension_t Columns>
class Matrix {
public:
	static const bool Type_ptr = std::_Is_pointer<Type>::value,
		Type_dest = !std::_Is_member_object_pointer<Type>::value && !std::is_member_function_pointer<Type>::value;
	static const Index_t Length = Rows * Columns;
	static const Dimension_t Rows = Rows, Columns = Columns;
	
	Matrix() {
		if (Type_ptr)
			for each (Type& e in values)
				e = NULL;
	}
	Matrix(const Type(&orig)[Length]) {
		for (Index_t index = 0; index < Length; index++)
			values[index] = orig[index];
	}
	Matrix(const Matrix& orig) {
		for (Index_t i = 0; i < Length; i++)
			values[i] = orig.values[i];
	}
	virtual ~Matrix() {}
	/*
	Calls the destructor of all elements in this Matrix or deletes the objects
	pointed to if the elements are object pointers.*/
	inline void clear() {
		Destruct<Type, Length, Type_ptr, Type_dest>::_call(values);
	}
	/*
	Convertes the (row, column) position to the corresponding index inside this Matrix.*/
	inline Index_t toIndex(const Dimension_t row, const Dimension_t column) {
		return (row * Columns) + column;
	}
	/*
	Returns a reference to the object at the specified (row, column) position.*/
	inline Type& get(const Dimension_t row, const Dimension_t column) {
		return values[toIndex(row, column)];
	}
	/*
	Sets the value at the specified (row, column) position and returns a
	reference to the previous value.*/
	Type& set(const Dimension_t row, const Dimension_t column, const Type& value) {
		const Index_t& index = toIndex(row, column);
		Type& res = values[index];
		values[index] = value;
		return res;
	}
	/*
	Inverts the values of this Matrix.*/
	inline Matrix& invert() {
		for each (Type& e in values)
			e = -e;
		return *this;
	}

	inline Type& operator[](const Index_t& index) {
		if (index < Length)
			return values[index];
		throw std::out_of_range("\"Index\" was greater than the length of this Matrix.");
	}
	Matrix& operator=(const Matrix& mat) {
		for (Index_t i = 0; i < Length; i++)
			values[i] = mat.values[i];
		return *this;
	}
	bool operator==(const Matrix& mat) {
		if (&mat == this) //The Matrixes are equal byref.
			return true;
		for (Index_t i = 0; i < Length; i++) //Loop over each value in
			//the Matrixes.
			if (values[i] != mat.values[i]) //The values are not equal.
				return false;
		return true; //The Matrixes are equal byval.
	}
	inline bool operator!=(const Matrix& mat) {
		return !operator==(mat);
	}
	inline Matrix operator-() {
		return copy().invert();
	}
	Matrix operator+(const Matrix& mat) {
		Matrix res = copy(); //The result of the opperation.
		for (Index_t i = 0; i < Length; i++) //Loop over each element in the Matrixes.
			res.values[i] += mat.values[i]; //Add the value of mat onto res.
		return res;
	}
	Matrix operator-(const Matrix& mat) {
		Matrix& res = copy(); //The result of the opperation.
		for (Index_t i = 0; i < Length; i++) //Loop over each element in the Matrixes.
			res.values[i] -= mat.values[i]; //Add the value of mat onto res.
		return res;
	}
	Matrix operator*(const double scalar) {
		Matrix& res = copy();
		for each (Type& e in res.values)
			e *= scalar;
		return res;
	}
	Matrix operator/(const double scalar) {
		Matrix& res = copy();
		for each (Type& e in res.values)
			e /= scalar;
		return res;
	}
	Matrix& operator+=(const Matrix& mat) {
		for (Index_t i = 0; i < Length; i++) //Loop over each element in the Matrixes.
			values[i] += mat.values[i]; //Add the value of mat onto res.
		return *this;
	}
	Matrix& operator-=(const Matrix& mat) {
		for (Index_t i = 0; i < Length; i++) //Loop over each element in the Matrixes.
			values[i] -= mat.values[i]; //Add the value of mat onto res.
		return *this;
	}
	Matrix& operator*=(const double scalar) {
		for each (Type& e in values)
			e *= scalar;
		return *this;
	}
	Matrix& operator/=(const double scalar) {
		for each (Type& e in values)
			e /= scalar;
		return *this;
	}
	Matrix operator*=(Matrix<Type, Columns, Columns>& mat) {
		Matrix<Type, Rows, Columns> res; //The result of the opperation.
		for (Index_t row = 0, column, index; row < Rows; row++)
			for (column = 0; column < Columns; column++) {
				for (index = 0; index < Columns; index++) //Iterate of the set of multiplications.
					res.get(row, column) += get(row, index) * mat.get(index, column);
			}
		return operator=(res); //Return the result.
	}
	template<Dimension_t C>
	Matrix<Type, Rows, C> operator*(Matrix<Type, Columns, C>& mat) {
		Matrix<Type, Rows, C> res; //The result of the opperation.
		for (Index_t row = 0, column, index; row < Rows; row++)
			for (column = 0; column < C; column++) {
				for (index = 0; index < Columns; index++) //Iterate of the set of multiplications.
					res.get(row, column) += get(row, index) * mat.get(index, column);
			}
		return res; //Return the result.
	}
	template<typename _T>
	inline explicit operator _T() {
		return dynamic_cast< _T& >(*this);
	}
protected:
	Type values[Length];

	inline virtual Matrix copy() {
		return Matrix(*this);
	}
};

template<typename Type, Index_t Length, bool Is_Pointer, bool Destroy>
struct Destruct {
	static inline void _Call() = 0;
};

template<typename Type, Index_t Length>
struct Destruct<Type, Length, true, true> {
	static inline void _Call(Type(&val)[Length]) {
		for each (Type& e in val)
			delete e;
	}
};

template<typename Type, Index_t Length>
struct Destruct<Type, Length, false, true> {
	static inline void _Call(Type(&val)[Length]) {
		for each (Type& e in val)
			e.~Type();
	}
};

template<typename Type, Index_t Length, bool Is_Pointer>
struct Destruct<Type, Length, Is_Pointer, false> {
	static inline void _Call(Type(&val)[Length]) {}
};

#endif
