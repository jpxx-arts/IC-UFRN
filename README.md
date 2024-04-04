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
