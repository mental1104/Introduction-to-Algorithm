/****************************************************************************
 > File Name: Matrix.h
 > Author: Netcan
 > Blog: http://www.netcan666.com/
 > Mail: netcan1996@gmail.com
 > Created Time: 2018-05-25 -- 17:08
 ****************************************************************************/

#ifndef LINALG_H
#define LINALG_H

#include <vector>
#include <cstdio>
#include <iostream>
using std::pair;
using std::vector;

namespace LinAlg {
	struct RetType;

	enum class VecType {
		Row = 0,
		Col
	};

	const static double eps = 1e-12;
	bool Eq(double a, double b);
	bool isZero(double a);

	class Vector;
	class Matrix;

	RetType operator*(const Vector &lhs, const Vector &rhs);
	Matrix operator*(Matrix lhs, const Matrix &rhs);

	class Vector {
	private:
		vector<double> data;
		VecType type;
	public:
		friend class Matrix;
		friend RetType;
		

		Vector(size_t n = 1, VecType type = VecType::Col): data(n, 0.0), type(type) {}
		Vector(const vector<double>&& data, VecType type = VecType::Col): data(data), type(type) {}
		Vector(const vector<double>& data, VecType type = VecType::Col): data(data), type(type) {}

		VecType getType() const { return type; }
		void setType(VecType type) { Vector::type = type; }
		size_t getSize() const { return data.size(); } // 获取大小
		void show();
		Vector T();

		Vector& operator+=(const Vector &rhs);
		Vector& operator-=(const Vector &rhs);
		double &operator[](size_t i) { return data[i]; }
		const double &operator[](size_t i) const { return data[i]; }

		Vector& operator*=(double c);

		friend Vector operator*(Vector lhs, double c) { lhs *= c; return lhs; }
		friend Vector operator*(double c, Vector lhs) { lhs *= c; return lhs; }
		friend Vector operator+(Vector lhs, const Vector &rhs) { lhs += rhs; return lhs; }
		friend Vector operator-(Vector lhs, const Vector &rhs) { lhs -= rhs; return lhs; }
		friend RetType operator*(const Vector &lhs, const Vector &rhs);

	};

	class Matrix {
	public:
		friend RetType;
		friend RetType operator*(const Vector &lhs, const Vector &rhs);

		using PLUType = pair<vector<size_t>, Matrix>;

		Matrix(size_t row = 1, size_t col = 1): data(row, vector<double>(col, 0.0)) {}
		Matrix(const vector<vector<double>> & data): data(data) {}
		~Matrix(){}
		Matrix& operator=(const vector<vector<double>>& data){
			this->data = data;
			return *this;
		}

		
		bool isSquare() const { return getRowSize() == getColSize(); }
		bool isSymmetric() const;
		size_t getRowSize() const { return data.size(); } // 获取行数
		size_t getColSize() const { return data[0].size(); } // 获取列数
		Vector getNRowVec(size_t n) const;
		Vector getNColVec(size_t n) const;
		Matrix LUdecomp() const;
		PLUType PLUdecomp() const;
		Vector LUsolve(const Vector &y) const;
		double det() const; // 行列式
		Matrix inv() const; // 逆矩阵
		vector<double> Jacobi() const; // 求出**实对称**矩阵的所有特征值
		void show();
		double & at(size_t i, size_t j) { return data[i][j]; }
		double at(size_t i, size_t j) const { return data[i][j]; }
		void resize(size_t i, size_t j) {  
			vector<double> vec(j, 0.0);
			data.clear();
			data.resize(i, vec);
		}

		Matrix T();
		Matrix& operator+=(const Matrix &rhs);
		Matrix& operator-=(const Matrix &rhs);
		Matrix& operator*=(double c);

		friend Matrix operator*(Matrix lhs, double c) { lhs *= c; return lhs; }
		friend Matrix operator*(double c, Matrix lhs) { lhs *= c; return lhs; }
		friend Matrix operator+(Matrix lhs, const Matrix &rhs) { lhs += rhs; return lhs; }
		friend Matrix operator-(Matrix lhs, const Matrix &rhs) { lhs -= rhs; return lhs; }
		friend Matrix operator*(Matrix lhs, const Matrix &rhs);

	private:
		vector<vector<double>> data;
		// PLU分解的选主元，每次选择绝对值最大的一行
		void PLU_P_update(vector<size_t> &P, const Matrix &mat, size_t k) const;
		Vector LUsolve_L(const Matrix &LU, const Vector &y) const;
		Vector LUsolve_U(const Matrix &LU, const Vector &z) const;
		void R(double cosphi, size_t p, size_t q, bool T = true);
	};

	struct RetType {
		enum class DType {
			DOUBLE, VECTOR, MATRIX
		};
		DType dtype = DType::DOUBLE;
		union {
			double val;
			Vector *vecVal;
			Matrix *matVal;
		} _data;

		void show() {
			if(dtype == DType::DOUBLE) printf("%f\n", _data.val);
			else if(dtype == DType::VECTOR) _data.vecVal->show();
			else _data.matVal->show();
		}
		~RetType() { // 可能会出问题...若不是double类型就释放
			if(dtype == DType::VECTOR) delete( _data.vecVal);
			else if(dtype == DType::MATRIX) delete _data.matVal;
		}
	};

}


#endif //LINALG_H