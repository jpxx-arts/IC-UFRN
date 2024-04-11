#Versão Paralela de Memória Compartilhada
- Para compilar na versão sequencial:
```console
foo@bar:~$ gcc *.c -o out
```
- Para executar (substitua os comandos segundo suas matrizes de interesse):
```console
foo@bar:~$ ./out <m1_linhas> <m1_colunas> <m2_linhas> <m2_colunas>
```

- Para compilar na versão paralela:
```console
foo@bar:~$ gcc -fopenmp *.c -o out
```

- Para executar (substitua os comandos segundo suas matrizes de interesse):
```console
foo@bar:~$ ./out <m1_linhas> <m1_colunas> <m2_linhas> <m2_colunas>
```
#Versão Paralela de Memória Distribúida
- Para compilar os testes:
```console
foo@bar:~$ mpicc -o <nome_arquivo_binario> *.c
```
- Para executar (substitua os comandos segundo suas matrizes de interesse):
```console
foo@bar:~$ mpirun -np <numero_processos> ./<nome_arquivo_binario> <argumentos_adicionais_caso_precise>
```