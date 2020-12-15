# lab-2_atividade-1
Programa que calcula a multiplicação entre duas matrizes por meio de threads, onde cada thread calcula um número determinado de linhas da matriz resultante, dependendo do número de threads escolhido. Foram comentados os printf(); do código para que a exibição das matrizes não afetasse o desempenho do programa e, consequentemente, no tempo de execução.

Utilizando o processador Ryzen 7 2700X (8 núcleos e 16 threads), operando no clock base de 3.7GHz, foi observado o seguinte cenário:

Usando apenas 1 thread obtive o seguinte desempenho nos respectivos cenários:
500:      0,474079
1000:    3.859432
2000:    40.081604

Usando 2 threads:
500:      0.232319    
1000:    1.912460
2000:    19.164423

O que dá uma aceleração (de 1 para 2 threads) de:
500:       2,040638088146041
1000:     2,01804586762599
2000:     2,091458949742447

Usando 4 threads:
500:      0.117175    
1000:    0.993595
2000:    9.622557

O que dá uma aceleração (de 1 para 4 threads) de:
500:       4,045905696607638
1000:     3,884311012032065
2000:     4,165379742619347
