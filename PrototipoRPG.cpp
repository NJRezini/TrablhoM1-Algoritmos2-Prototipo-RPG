#include <iostream>
#include <stdlib.h>
#include <time.h>
//#include "header.h"
using namespace std;

enum Genero {
    F,
    M
};

struct Arma {
    string nome;
    int danoMinimo;
    int danoMaximo;
    Genero genero;
};

struct Inimigo {
    string nome;
    int vida;
    Arma arma;
};

struct Fase {
    string nome;
    Inimigo inimigos[5];
};

struct Jogador {
    int nivel;
    int vida;
    string nome;
    Arma arma;
};

template<typename T>
bool morreu(T personagem) {
    if (personagem.vida <= 0) {
        return 1;
    } else {
        return 0;
    }
}

template<typename T>
int dano(T personagem) {
    int resultado = (rand() % ((personagem.arma.danoMaximo + 1) - personagem.arma.danoMinimo)) + personagem.arma.danoMinimo;
    cout << endl << personagem.nome << " deu " << resultado << " de dano com ";
    if (personagem.arma.genero == F){
        cout << "sua ";
    } else {
        cout << "seu ";
    }
    cout << personagem.arma.nome << ". ";
    return resultado;
}

template<typename T, typename T2>
T2 ataque(T personagem1, T2 personagem2) {
    personagem2.vida -= dano(personagem1);
    morreu(personagem2);
    if (morreu(personagem2)) {
        cout << "\nO " << personagem2.nome << " MORREU!\n";
    } else {
        cout << "\nO " << personagem2.nome << " ficou com " << personagem2.vida << " pontos de vida continua vivo.\n";
    }
    return personagem2;
}

void jogarFase(Jogador protagonista, Fase fase) {
  int quantidadeInimigos = sizeof(fase.inimigos)/sizeof(fase.inimigos[0]);
  for(int i = 0; i < quantidadeInimigos; i++){
      Inimigo inimigo = fase.inimigos[i];
      cout << inimigo.nome << endl;
      while (inimigo.vida > 0) {
          inimigo = ataque<Jogador, Inimigo>(protagonista, inimigo);

          protagonista = ataque<Inimigo, Jogador>(inimigo, protagonista);
          if(protagonista.vida <= 0 ){
              return;
          }
      }
  }
};


int main() {

    Arma machado = {"Machado", 1, 11, M}, adaga = {"Adaga", 4, 8, F};
    Jogador protagonista = {1, 100, "player", machado};
    Inimigo inimigo1 = {"Goberto", 10, adaga};
    Inimigo inimigo2 = {"Juao", 10, adaga};
    Inimigo inimigo3 = {"Roberto", 10, adaga};
    Inimigo inimigo4 = {"Ronielson", 10, adaga};
    Inimigo inimigo5 = {"Chefe 1", 10, adaga};

    Fase fase1;
    fase1.nome = "Green Hill Zone";
    fase1.inimigos[0] = inimigo1;
    fase1.inimigos[1] = inimigo2;
    fase1.inimigos[2] = inimigo3;
    fase1.inimigos[3] = inimigo4;
    fase1.inimigos[4] = inimigo5;

    jogarFase( protagonista, fase1);

    srand(time(NULL));

    /*
    inimigo1 = ataque<Jogador, Inimigo>(protagonista, inimigo1);
    inimigo1 = ataque<Jogador, Inimigo>(protagonista, inimigo1);
    inimigo1 = ataque<Jogador, Inimigo>(protagonista, inimigo1);
    */

    /*
    do{
    cout << dano(protagonista) << endl;
    ataque<Jogador, Inimigo>(protagonista, inimigo1);
    } while (inimigo1.vida > 0);
    */

}