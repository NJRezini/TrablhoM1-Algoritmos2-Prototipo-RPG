| Universidade do Vale do Itajaí Escola do Mar Ciência e TecnologiaNEI - EMCT |

Disciplina: Algoritmos e Programação II

Professor: Rodrigo Lyra

**Protótipo de RPG – Structs e Templates**

Um jogo de RPG precisa começar de algum lugar, e uma parte essencial são as batalhas contra inimigos, e para isso precisamos de armas. Claro que neste momento não iremos fazer um jogo completo, faremos somente a simulação do combate de uma fase, para isso utilizaremos o que aprendemos de structs e templates. Abaixo estão listados os itens **obrigatórios** do trabalho:

**Structs**

O trabalho deverá conter pelo menos as seguintes **structs** :

    - Fase – Que deverá ter um nome e 5 inimigos.
    - Jogador – Que deverá ter um nível, vida e uma arma.
    - Inimigo – Que deverá ter um nome, vida, e uma arma.
    - Arma – Que deverá ter dano mínimo e dano máximo

**Template**

O trabalho deverá conter pelo menos as seguintes funções com template, o objetivo é que o template deixe genérico se as variáveis são de jogador ou inimigo ( **NÃO**  **deve ser utilizado sobrecarga e nem passagem por referência nessas funções** ).

- morreu – Que deve receber um parâmetro, que será o jogador ou um inimigo, e deve retornar um bool simbolizando se ele morreu ou não. A função deve verificar se a vida de quem foi passado por parâmetro é menor ou igual a 0, e retornar true em caso afirmativo e false caso contrário.

- ataque – Que deve receber dois parâmetros, o atacante e quem vai sofrer o ataque (que pode ser um jogador ou inimigo), e deve retornar quem sofreu o ataque com a vida atualizada. A vida de quem foi atacado deve ser diminuída de um valor aleatório entre o dano mínimo e o dano máximo da arma do atacante.

**Lógica**

Além do uso de templates e structs, pelo menos mais uma função de lógica deverá ser implementada.

- jogarFase – Essa função deve receber por parâmetro o jogador e uma fase e deve seguir a seguinte lógica:
  - Escrever o nome da fase;
  - Para cada inimigo da fase:
    - Enquanto o inimigo não morrer:
      - Inimigo ataca o jogador
      - Jogador ataca o inimigo
      - Se o jogador morrer:
        - O jogo acaba
      - Se o inimigo morrer:
        - Passa para o próximo inimigo
  - Se acabarem os inimigos, o jogo acaba
