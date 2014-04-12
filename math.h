/* math.h
 * Namespace capaz de manipular matrizez e vetores.
 *
 * TODO: documentar matriz e vetor
 *
 * Parâmetros do template:
 *  M - quantidade de linhas
 *  N - quantidade de colunas
 */
namespace Math {

template <int M, int N>
class Matrix {
}; //TODO: implementar

template <int N>
using Vector = Matrix<N, 1>;

} //namespace Math
