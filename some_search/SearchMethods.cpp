#include <iostream> // std::cout std::endl std::cerr
#include <random>   // random stuff
#include <sstream>  // std:stringstream
#include <iterator> // std::begin std::end
#include <algorithm>// std::shuffle
#include <numeric>  // std::iota
#include <chrono>
#include <fstream>

using namespace std;

void printArray( int * left_, int * right_ )
{
    std::cout << "[ ";
    for( auto i( left_ ) ; i != right_ ; ++i )
    {
        std::cout << *i << " ";
    }
    std::cout << "], Size = " << std::distance(left_, right_) << "\n";
}

long int linearSearch( int x_, int A_[], int left_, int right_) // SEQUENCIAL ITERATIVA
{
    for (auto i(left_); i<= right_ ; i++) // i<=right_ and x_ < A_[i]
    {
        //std::cout << " Comparando com " << A_[i] << "\n";
        if (A_[i] == x_)
        {
            return i;
        }
       
        
           
        }
         return -1;
    }



long int linearSearchSorted( int x_, int A_[], int left_, int right_) // SEQUENCIAL RECURSIVA
{
    long i = (right_ - left_); // pega o tamanho do vetor
    if (i >= 0) // testa se e maior q 0 e ainda tem indices
    {
        if (A_[i] == x_) return i;

        else
            return linearSearchSorted(x_, A_, left_, i-1); // chama a funcao d novo
    }
    return -1;
}


long int binSearch_iterativa (int x_ , int A_[], int left_, int right_) //BINARIA ITERATIVA
{
    while (left_ <= right_)
    {
        long  m = (left_ + right_) / 2; // divide ao meio
        // if ( x_ == A_[m]) return m; // confere se o numero do meio e igual
        if (x_ > A_[m]) left_ = m+1; // testa se e maior
        else if (x_ < A_[m]) right_ = m-1; // testa se e menor
        else // se for igual
            return m;
    }
    return -1;
}

long int binSearch (int x_ , int A_[], int left_, int right_)  //BINARIA RECURSIVA
{
    // 0)  se nao houver elementos em A, retornar -1
    if ( left_ > right_) return -1;
    // 1) calcular indice do meio
    //long m = left_ + (right_ - left_) / 2
    long m = (left_ + right_) / 2;

    // 2) Verificar se o elemento do meio eh o alvo
    if ( x_ == A_[m]) return m;

    // 3) s nao for identificar s vai p esquerda ou direita
    // 3.1) S esquerda , chamar com ( x, A, left, m-1)
    else if ( x_ < A_[m]) // esquerda
        return binSearch (x_, A_, left_, m-1);
    else //direita
        return binSearch (x_, A_ , m+1 , right_);

}

long int ternarySearch (int x_ , int A_[], int left_, int right_) // TERNARIA SEQUENCIAL
{
    int middle1, middle2; // cria duas metades


    while (left_ <= right_)
    {
        middle1=(right_ - left_)/3 + left_; // divide o tamanho do vetor por 3

        middle2=((right_-left_)/3)*2 + left_; // cria uma nova metade

        if(x_==A_[middle1]) // testa se o valor esta na primeira divisao
            return middle1;
        if(x_==A_[middle2]) // testa se o valor esta na segunda divisao
            return middle2;

        if(x_<A_[middle1]) // testa se esta antes da primeira divisao
        {
            right_= middle1-1;
        }
        if (x_>A_[middle1] && x_< A_[middle2]) // testa se esta entre a primeira e a segunda divisao
        {
            left_=middle1+1;
            right_=middle2 -1;
        }
        else if(x_>A_[middle2]) // testa se esta depois da segunda divisao
        {
            left_=middle2+1;
        }

    }
    return -1;

}


long int ternarySearchRecursive( int x_ ,int A_[], int left_, int right_ )
{
   if (right_ >= left_)
   {
        int middle1 = left_ + (right_ - left_)/3; 
        int middle2 = middle1 + (right_ - left_)/3;  // Como a iterativa,  foram criadas duas metades
                                                 // Sendo uma 
        
        if (A_[middle1] == x_)  return middle1; // Teste para saber se o x est· no middle1
 
        
        if (A_[middle2] == x_)  return middle2; // Teste para saber se o x est· no middle2
 
      
        if (A_[middle1] > x_) return ternarySearchRecursive(x_,A_, left_, middle1-1); // Teste para saber se o x est· a esquerda
        // If x is present in right one-third
        if (A_[middle2] < x_) return ternarySearchRecursive(x_, A_, middle2+1, right_); // teste para saber se o x t· na direira
 
        // If x is present in middle one-third
        return ternarySearchRecursive(x_,A_, middle1+1, middle2-1); // teste para saber se o x est· no meio
   }
        // Se n„o entrar em nenhum dos casos anteriores
   return -1;
}
const auto N = 536870912  ;  //   li 2097152      li 4194304      li 8388608       Li 16777216        li 33554432     li 67108864

 



int main( )
{
		std::ofstream arquivo( "536870912.txt");
    //std::vector< int > V( N ); //guarda sequ√™ncias de matrizes din√¢micas
   //int A[ N ]; // = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 }; //array

    int *A = new int[N]; //para testar o tamanho da maquina
    

    std::iota( A, A + N, 1 ); //preenche desde o come√ßo do array A at√© o fim dele, inicia com 1 e vai de 1 em 1.


    std::cout << ">>> Before, A: ";
    //printArray( std::begin(A), std::end(A) ); //mostra o array desde o begin e do end
    std::cout << "\n";


#ifdef RANDOM // diferente - Definindo diferente
    std::random_device rd; //gera n√∫meros aleat√≥rios
    std::mt19937 g(rd()); 
    
    
#else
    std::mt19937 g( 1 );
#endif
    //std::shuffle( std::begin( A ), std::end( A ), g ); //reordena aleatoriamente

   // std::cout << ">>> After, A: ";
    //printArray( std::begin(A), std::end(A) );
    //std::cout << "\n";

    auto target( 10000000000000000); //alvo de busca]
    //auto resp = linearSearch( target, A, 1, N); 
    //auto resp = linearSearchSorted( target, A, 1, N);
    //auto resp = binSearch_iterativa( target, A, 1, N);
    //auto resp = binSearch( target, A, 1, N);
    //auto resp = ternariaSearch( target, A, 1, N);
    for(auto i(0) ; i<100 ; ++i ){
	
    auto start = chrono::steady_clock::now(); // tempo
    auto resp = std::binary_search(A, N+A, target);// chamada funÁ„o
   auto end = chrono::steady_clock::now();
   auto diff = end - start;
   arquivo << chrono::duration <double, milli> (diff).count() << " ms" << endl;
}
delete [] A;
/*
    auto resp = std::find(std::begin(A), std::end(A), target); // std find
   
    if (resp != std::end(A)) {
        std::cout << "A contains: " << target << '\n';
    } else {
        std::cout << "A does not contain: " << target << '\n';
    }
*/
  
   /* auto resp = std::binary_search(std::begin(A), std::end(A), target);
    if (std::binary_search (begin(A), end(A), 4))
    
    */
    
 //   auto resp = ternarySearch( target, A, 1, N);

    //std::cout << std::boolalpha << "Result (" << target << "): na posicao " << resp << std::endl; //chama boolalpha que escreve 1 como 'true' e 0 como 'false'
    //target = 20;
    //std::cout << std::boolalpha << "A[" << resp << "] = " << A[resp] << std::endl;
    //std::cout << " Posicao: " << resp - A << " \n";
    std::cout << "\n>>> Normal exiting...\n";

    return EXIT_SUCCESS;
}
