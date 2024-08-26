- Lê o board do ficheiro [Board](assets/board.minesweeper) e uma AI resolve o jogo
    - Se na primeira rodada carregar numa bomba, o jogo aceita e muda a bomba
    - Se carregar num local sem bombas próximas, mostrar todos aqules que não têm bombas próximas que estão colados ao local escolhido
    - Calcular quantas bombas tem próximo apenas depois da 1ª jogada 
    - A AI vai marcar os 'Tile' com:
        - 'B' se tiver a certeza que existe uma bomba
        - 'C' para os que sabe que não têm bomba
        - 'M' para os que podem ter bomba
        - '?' para os que não tem informação

- extensão .minesweeper. O exemplo no ficheiro corresponde a [Exemplo](assets/example.png):
    - Primeira linha são as dimensões "dimensão do tabuleiro"
    - 'X' representam as bombas e ' ' espaço livre


- O board é constituído por Tiles, que por sua vez guardam:
    - num -> número de bombas próximas
    - info -> Informação utilizada pela AI para guardar se naquele Tile tem uma bomba, não tem, pode ter ou não sabe nada
    - show -> Boleano que é usado para saber se a AI escolheu aquele Tile, o que implica que vai ser mostrada a sua informação quando o board for mostrado

- A AI tem acesso ao board o que significa que poderia verificar se o Tile tem ou não uma bomba, mas só usa os Tile que estão com 'show' a true, ou seja, que foram escolhidos.



- Função que joga:
    1. Sempre que um Tile é jogado, esse Tile é removido de todas as Sentence e os Tiles próximos em que a AI não conhece nada sobre eles (marcados com NO_CLUE), isto é, não sabe se são seguros ou se são bombas, são marcados como MAYBE.
    2. Para cada Tile é criada uma Sentence. São utilizados os Tiles próximos que estão marcados como MAYBE e é tido em consideração os Tiles próximos que a AI sabe que tem bombas, isto porque se o Tile escolhido estiver rodiado de 2 bombas e dos seguintes Tiles: A, B, C, D, E e a AI sabe que A e B são bombas, então a Sentence criada deve ser {C, D, E} = 0. 
    3. Para cada Sentece é depois aplicado:
        1. Se o nº de bombas = nº de Tiles que podem ter bomba, então são todos bombas
        2. Se o nº de bombas for 0, nenhum dos tiles é uma bomba
        3. Se o conjunto A tem 1 bomba e é um subconjunto de B que tem 2 bombas, então B - A tem uma bomba
