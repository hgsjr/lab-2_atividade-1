# lab-2_atividade-1
Programa que calcula a multiplicação entre duas matrizes por meio de threads, onde cada thread calcula um número determinado de linhas da matriz resultante, dependendo do número de threads escolhido.
Executando em média 5 vezes para cada cenário, obtive o seguinte desempenho com meu Ryzen 7 2700X (que possui 8 núcleos e 16 threads):

Dim	    1 thread		 2 threads		        aceleração
500     0.474079	     0.232319	         2,040638088146041
1000	3.859432	     1.912460	         2,01804586762599
2000	40.081604	     19.164423	         2,091458949742447

Dim	    1 thread		 4 threads		        aceleração
500	    0.474079	     0.117175	         4,045905696607638
1000	3.859432	     0.993595	         3,884311012032065
2000	40.081604	     9.622557	         4,165379742619347

onde "Dim" representa a dimensão das matrizes.
