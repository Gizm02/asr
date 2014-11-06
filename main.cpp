#include <iostream>

using namespace std;

/** \brief This function sums up floats that are not zero.
 *
 * \param   a This is a float.
 * \param   b This is a float too.
 * \return  a <b>if</b> a is zero, a+b otherwise.
 *
 */
float summ(float a, float b) {
    if(a>0 || a<0) {
        return a+b;
    }
    return a;
}

float give() {
    float a=summ(0,1);
    return a;
}
/** \brief cool struct
 *
 * \param
 * \param
 * \return
 *
 */
struct beta{int x;int y;};



int main()
{

    float a; /*!< Detailed description after the member */
    cout << "Hello world!" << endl;
    return 0;
}
