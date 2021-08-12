#pragma once
#include "Node.h"

// Para manter uma lista com todas os numeros/letras e respetivas posicoes no estado (numbers[26])
struct Letter
{
    char upperLetter;
    char lowerLetter;
    int position;
};

enum class Direction { up = 0, left, right, down };

class NumberLink : public Node
{
    // Variaveis globais
    static int qntLines;
    static int qntColumns;
    static int stateSize;
    static const int totalNumbers = 26;
    static const char outOfBoundsChar = '?';
    static const char maskChar = '%';
    static const int A = 65;
    static const int a = 97;
    // Mantem a lista de numeros/letras e a respetiva posicao no estado
    static Letter numbers[26];


    // Estado atual
    char* state;
    // Mantem a lista de conexoes 
    bool connected[totalNumbers] = {false};
    // Numero/letra da atual procura
    int currentNumber;
    // Posicao onde comecou caminho
    int pathRoot;
    // Posicao atual do caminho
    int pathHead;
    // Mantem as posicoes em redor de pathHead (cima, esquerda, direita, baixo)
    int aroundPathHead[4];
    // Guarda o numero de numeros/letras que falta conectar (atual nao incluida)
    int numbersRemaining;

    
    NumberLink();
    // Prepara o estado para a ligacao do proximo numero/letra
    void setNextNumber(); 
    // Altera a letra atual para outro caracter (evita que se conecte a ele proprio)
    void maskPathRoot();
    // Restaura a letra atual
    void unmaskPathRoot();
    // Altera pathHead para a proxima posicao
    void moveTo(int position);
    // Verifica se o numero/letra atual esta conectado
    bool isConnected();
    // Devolve um apontador para o caracter correspondente a posicao (cima, esquerda, direita, baixo)
    // Para que is360() e canConnect() tambem possam usar esta funcao, e necessario passar um estado e uma posicao inicial.
    // Coloca a posicao final em endPosition
    const char* look(Direction direction, int startPosition, const char* someState, int& endPosition);
    // Preenche as posicoes em redor de pathHead (cima, esquerda, direita, baixo)
    void setPosAroundPathHead();
    // Verifica se o caminho esta em contacto com ele proprio
    bool isSelfConnectingPath();
    // Verifica se o caminho faz curva de 360, com 1 espaco de intervalo (tipo U)
    bool is360();
    // Funcao recursiva que tenta alcancar um caracter apartir de uma posicao.
    // IMPORTANTE: passar uma copia do estado, pois e alterado.
    bool canConnect(char character, char* stateCopy, int startPosition);
    // Verifica se e possivel conectar as restantes letras
    bool isDeadState();
public:
    // Devolve um clone deste estado
    Node* getClone() override;
    NumberLink(char* state, int qntLines, int qntColumns);
    ~NumberLink() override;
    // Devolve uma representa��o visual deste estado.
    std::string toString() override;
    // Compara este estado com outro
    bool operator==(Node& node) override;
    // Verifica se este estado � uma solu��o
    bool isSolution() override;
    // Neste caso, nada faz, pois sao instancias fixas
    void resetState() override;
    // Gera e devolve uma lista de estados sucessores
    void genSuccessors(DLList<Node*>& successors) override;
};
