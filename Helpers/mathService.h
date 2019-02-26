#ifndef __MATH_SERVICE
#define __MATH_SERVICE

class MathService
{
public:
  static int pow(int a, int b)
  {
    int result = 1;

    for (int i = 1; i <= b; i++)
    {
      result *= a;
    }

    return result;
  }
};

#endif