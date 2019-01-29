#include <iostream> // cont , endl
#include <vector>  // vector
#include <algorithm> // copy
#include <iterator> // ostream_iterator
#include <utility> //swap

//MERGE SORT


//Compara valores inteiros
bool
compare( int a, int b )
{
    return ( a < b );
}


template<typename T>
std::vector<typename T::value_type> intercala(const T left, const T middle, const T right,  bool (*cmp)(int, int))
{
    std::vector<typename T::value_type> a; // Cria um vetor auxiliar 
    T com1( left ), fim1( middle ); // it_l = aponta para o comeco da amostra , it_r = aponta para o meio da amostra (final da primeira metade)
    const T com2( middle ), fim2( right ); // it_m = aponta para o meio da amostra (comeco da segunda metade) , it_e = aponta para o final da amostra 

    while (com1 != com2 && fim1 != fim2) 
    {
        /*  
        Ele testa e pega o menor valor e insere no final do vetor, depois incrementa a posiçao do ponteiro.    
         */
        a.push_back((cmp(*com1 , *fim1)) ? *com1++ : *fim1++);  
    }

    //Pega os valores "restantes" e insere no final do vetor. 
    a.insert(a.end(), com1, com2);
    a.insert(a.end(), fim1, fim2);

    return std::move(a); // Move o valor do vetor para a outra função e "deleta" dessa função .
}

template<typename T>
void merge_sort(T first, T last,  bool (*cmp)(int, int))
{
    auto size = std::distance(first, last); // calcula o tamanho da amostra
    if (size < 2) //caso base, se o tamanho da amostra for menor que 2. 
        return;

    auto meio = std::next(first, size / 2); // acha o "meio", dividindo por 2.
    merge_sort(first, meio,cmp); // chama a função com a primeira metade
    merge_sort(meio, last,cmp); // chama a função com a primeira metade

    
    auto &&a = intercala(first, meio, last,cmp); // referencia para uma referencia , em decorrer do move. 
    std::move(a.begin(), a.end(), first);
}


int const N{10}; //usando um vetor de 10 elementos como exemplo 
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
    merge_sort(A.begin(),A.end() , compare);

    std::cout << ">>> After, A: ";
    std::copy( A.begin(), A.end(), std::ostream_iterator<int>(std::cout, " ") );
    std::cout << "\n";

    return EXIT_SUCCESS;
}
