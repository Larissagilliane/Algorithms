#include <iostream> // cont , endl
#include <vector>  // vector
#include <algorithm> // copy
#include <iterator> // ostream_iterator
#include <utility> //swap

//QUICK SORT


typedef std::vector<int>::iterator T; 

//Compara valores inteiros
bool
compare( int a, int b )
{
    return ( a < b );
}


T particao( T first, T last,  bool (*cmp)(int, int))
{
    T i  = first-1; // i "aponta" para fora do vetor inicialmente
    T hp = first;   // hp "aponta" para o inicio do vetor inicialmente

    //Percorre enquanto "hp" for menor que o final do vetor, ou seja, o valor a qual hp aponta seja menor que o pivot (ultimo elemento inicialmente)
    while ( hp < last ) 
        {
            if (cmp(*hp , *last)) 
            {
                ++i;
                std::swap(*i,*hp);  // troca os elementos 
            }
            ++hp;
        }
    std::swap(*(i+1),*last); // caso "hp" seja maior do que "last" ele , ele insere lest antes do valor "hp"
    return ++i; //retorna a posicao onde o pivot esta
}



void quick_sort( T first, T last, bool (*cmp)(int, int) )
{

    if (first < last)
    {
        T p = particao(first, last, cmp); 
        quick_sort (first, p-1, cmp);  // ordena na primeira metade
        quick_sort ( p+1, last, cmp);  //ordea na segunda metade
    }
    return;
}


int const N{10}; //usando um vector de 10 elementos como exemplo 
int main()
{
    std::vector< int > A( N );
     
    std::iota( std::begin( A ), std::end( A ), 1 ); // Gera valores

#ifdef RANDOM
    std::random_device rd;
    std::mt19937 g(rd());
#else
    std::mt19937 g( 1 );
#endif
    std::shuffle( std::begin( A ), std::end( A ), g ); // "Embaralha" valores
    
    std::cout << ">>> Before, A: ";
    std::copy( A.begin(), A.end(), std::ostream_iterator<int>(std::cout, " ") );
    std::cout << "\n";

    // CHAMADAS DAS FUNÇÕES
    quick_sort(A.begin(),A.end()-1, compare );

    std::cout << ">>> After, A: ";
    std::copy( A.begin(), A.end(), std::ostream_iterator<int>(std::cout, " ") );
    std::cout << "\n";

    return EXIT_SUCCESS;
}