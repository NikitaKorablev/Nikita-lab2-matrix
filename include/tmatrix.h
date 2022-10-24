// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cstring>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_MATRIX_SIZE) throw out_of_range("Exceeding the maximum size");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) // конструктор копирования
  {
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept // конструктор перемещения
  {
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) return *this;

      TDynamicVector tmp(v);
      swap(*this, tmp);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept // перемещающий оператор присваивания
  {
      swap(*this, v);
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind < 0) throw out_of_range("Index must be greater than zero");
      if (ind >= sz) throw out_of_range("Index must be less than zero");
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind < 0) throw out_of_range("Index must be greater than zero");
      if (ind >= sz) throw out_of_range("Index must be less than zero");
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0) throw out_of_range("Index must be greater than zero");
      if (ind >= sz) throw out_of_range("Index must be less than zero");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0) throw out_of_range("Index must be greater than zero");
      if (ind >= sz) throw out_of_range("Index must be less than zero");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;

      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) return false;
      }

      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return true;

      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) return true;
      }

      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp[i] = pMem[i] + val;
      }
      return tmp;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp[i] = pMem[i] - val;
      }
      return tmp;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] * val;
      }
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw out_of_range("Not equal sizes");
      TDynamicVector tmp(sz);
      for (int i = 0; i < sz && i < v.sz; i++) {
          tmp.pMem[i] = pMem[i] + v.pMem[i];
      }
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw out_of_range("Not equal sizes");
      TDynamicVector tmp(sz >= v.sz ? sz : v.sz);
      for (int i = 0; i < sz && i < v.sz; i++) {
          tmp.pMem[i] = pMem[i] - v.pMem[i];
      }
      return tmp;
  }
  T operator*(const TDynamicVector& v)
  {
      if (sz != v.sz) throw out_of_range("Not equal sizes");
      T mul = 0;
      for (int i = 0; i < sz; i++) {
          mul += pMem[i] * v.pMem[i];
      }
      return mul;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& v) : TDynamicVector<TDynamicVector<T>>(v) {};
  using TDynamicVector<TDynamicVector<T>>::operator[];

  size_t size() const noexcept { return sz; }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator==(m); // вызываем конструктор сравнения предка
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)
  {
      return TDynamicVector<TDynamicVector<T>>::operator*(val);
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      TDynamicVector<T> tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] * v;
      }
      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw out_of_range("Not equal sizes");
      TDynamicMatrix tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] + m.pMem[i];
      }
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw out_of_range("Not equal sizes");
      TDynamicMatrix tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] - m.pMem[i];
      }
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw out_of_range("Not equal sizes");
      TDynamicMatrix tmp(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              for (int k = 0; k < sz; k++) {
                  tmp.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
              }
          }
      }
      return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) {
          istr >> v.pMem[i];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) {
          ostr << v.pMem[i] << endl;
      }
      return ostr;
  }
};

#endif
