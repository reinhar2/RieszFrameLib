#pragma once

#include <iostream>
#include <vector>

namespace frame
{

  template <typename T>
  class FrameMat
  {
  public:
    // rule of five:
    FrameMat(const FrameMat<T>& that) noexcept
    {

    }
    FrameMat(FrameMat<T>&& that) noexcept
    {

    }
    ~FrameMat<T>()
    {

    }
    FrameMat<T>& operator=(const FrameMat<T>& that)
    {

    }
    FrameMat<T>& operator=(FrameMat<T>&& that)
    {

    }
    // more constructors
    FrameMat(T value, unsigned int rows, unsigned int cols)
    {
      data = std::vector<T>(rows * cols);
      fill(data.begin(), data.end(), value);
    }

  private:
    std::vector<T> data;
  }; // class FrameMat

}