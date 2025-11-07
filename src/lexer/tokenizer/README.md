# Tokenizer

## Sintaxe com Redirect `>`

Neste exemplo, ele criará os arquivos `testes7`, `testes8`, `testes9`, `testes10`, e não escreverá nada em nenhum, porque dará `testes6: command not found`
```bash
testes6 > testes7 > testes8 > testes9 echo ola > testes10
```

Neste exemplo ele criará os arquivos `testes6`, `testes7`, `testes8`, `testes9`, `testes10`, escreverá `ola` apenas no arquivo `testes10`
```bash
> testes6 > testes7 > testes8 > testes9 echo ola > testes10
```

Neste exemplo ele criará os arquivos `testes6`, `testes7`, `testes8`, `testes9`, escreverá `OLA-OLA echo ola` apenas no arquivo `testes9`
```bash
echo OLA-OLA > testes6 > testes7 > testes8 > testes9 echo ola
```

Neste exemplo ele criará os arquivos `testes6`, `testes7`, `testes8`, `testes9`, `testes10`, escreverá `OLA-OLA echo ola` apenas no arquivo `testes10`
```bash
echo OLA-OLA > testes6 > testes7 > testes8 > testes9 echo ola > testes10
```

## Sintaxe com Append `>>`
