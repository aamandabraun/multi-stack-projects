# Prompt Log & Code Review — Portal Cidadão

Documento obrigatório (item 7 da especificação). Registra os prompts
usados para gerar código com IA, os bugs identificados na saída
gerada e as correções manuais aplicadas para atender aos padrões de
arquitetura (MVC/MVVM) e Null Safety do projeto.

---

## 1. Registro de Prompts

### 1.1 Geração dos Models (`Politico`, `Despesa`, `Proposicao`)

**Prompt utilizado:**
> "Crie uma classe Dart `Despesa` para representar o retorno do
> endpoint `/deputados/{id}/despesas` da API da Câmara dos Deputados,
> com um construtor `fromJson`. Os campos são: ano, mes, tipoDespesa,
> tipoDocumento, dataDocumento, valorDocumento, valorLiquido,
> valorGlosa, nomeFornecedor, cnpjCpfFornecedor, urlDocumento."

**Prompt utilizado:**
> "Crie uma classe Dart `Politico` para o endpoint `/deputados`,
> incluindo um segundo construtor `fromDetailJson` para o payload do
> endpoint de detalhe, que vem aninhado em `dados.ultimoStatus`."

### 1.2 Lógica de filtragem e paginação

**Prompt utilizado:**
> "Escreva um método `listarPoliticos` usando Dio que aceite filtros
> opcionais de UF e partido, além de parâmetros de paginação (`pagina`,
> `itens`), e trate erros de rede lançando uma exceção customizada."

### 1.3 Persistência SQLite

**Prompt utilizado:**
> "Implemente um DAO em Dart com `sqflite` para favoritar/desfavoritar
> um Político, com os métodos `adicionar`, `remover`, `isFavorito` e
> `listarTodos`."

---

## 2. Log de Debugging — Bugs Identificados na Saída da IA

### Bug 1 — Erro de tipagem em `valorDocumento`/`valorLiquido` (crash em runtime)

**Sintoma:** A primeira versão gerada pela IA para `Despesa.fromJson`
fazia um cast direto:

```dart
// Código original gerado pela IA (com bug)
valorDocumento: json['valorDocumento'] as double,
```

Ao testar contra a API real, alguns registros retornam
`valorDocumento` como `String` (ex.: `"137.50"`) em vez de `double`,
principalmente em despesas antigas. O cast direto `as double`
lançava `TypeError: type 'String' is not a subtype of type 'double'`
e derrubava a tela de detalhe assim que o usuário abria um
parlamentar com despesas nesse formato.

**Causa raiz:** a IA assumiu tipagem consistente com base no nome do
campo, sem considerar que APIs de dados abertos governamentais não
garantem tipos estáveis entre registros históricos e recentes.

### Bug 2 — `dataDocumento` nulo quebrando o parsing de data

**Sintoma:** o código gerado usava:

```dart
// Código original gerado pela IA (com bug)
dataDocumento: DateTime.parse(json['dataDocumento']),
```

Registros de despesas de anos anteriores a 2015 frequentemente vêm
com `dataDocumento: null`. `DateTime.parse(null)` lança exceção de
tipo em tempo de compilação/execução (o parâmetro não aceita `null`),
e mesmo quando a string vinha vazia (`""`), `DateTime.parse` lançava
`FormatException`.

**Causa raiz:** a IA não tratou o caso de campo omitido, comum em
dados históricos, conforme já alertado na própria especificação do
projeto (seção 6 — Null Safety e Resiliência).

### Bug 3 (bônus) — Lista renderizada sem Lazy Loading

**Sintoma:** a primeira sugestão da IA para a listagem de
parlamentares usava `Column(children: politicos.map(...).toList())`
dentro de um `SingleChildScrollView`, o que renderiza todos os itens
de uma vez — inviável para os milhares de registros que a API pode
retornar (a paginação por si só não resolve o problema se a tela
recarregar tudo em memória a cada página).

---

## 3. Refatoração Manual

| Bug | Correção aplicada manualmente |
|---|---|
| #1 — Tipagem de valores monetários | Criado o helper estático `_parseDouble(dynamic value)` em `Despesa`, que trata `double`, `int` e `String` (inclusive strings no padrão pt-BR com vírgula decimal), com fallback seguro em vez de lançar exceção. Aplicado o mesmo padrão em `Politico._parseInt` e `Proposicao._parseInt`. |
| #2 — Datas nulas | Substituído `DateTime.parse` por `DateTime.tryParse`, com checagem prévia de nulidade/string vazia via `_parseDate(dynamic value)`, retornando `DateTime?` em vez de forçar não-nulo. O model passou a expor `dataDocumento` como campo opcional (`DateTime?`), e a UI trata a ausência de data sem quebrar a interface. |
| #3 — Performance de lista | Reescrita a tela `PoliticosListScreen` para usar `ListView.builder` com `ScrollController` monitorando a proximidade do fim da lista (`_onScroll`) para disparar a próxima página sob demanda, em vez de montar todos os widgets de uma vez. |
| Geral — Arquitetura | O código gerado pela IA originalmente misturava chamadas HTTP diretamente dentro do `build()` dos widgets. Foi manualmente extraído para a camada `services/camara_api_service.dart`, isolando toda a lógica de rede da camada de apresentação (MVC/MVVM), e as Views passaram a depender apenas de métodos assíncronos chamados em `initState()`. |
| Geral — Navegação tipada | A IA sugeria inicialmente `Navigator.pushNamed(context, '/detalhe', arguments: {'id': politico.id})`. Isso foi substituído por `MaterialPageRoute` com objetos tipados (`PoliticoDetailArgs`, `FiltroScreenArgs`) definidos em `models/nav_args.dart`, eliminando o risco de erros de runtime por chaves de mapa incorretas. |

---

## 4. Observações finais

Todo o código gerado com auxílio de IA foi lido, testado
mentalmente contra os formatos reais de resposta da API de Dados
Abertos da Câmara dos Deputados e ajustado para respeitar Null
Safety estrita, a estrutura de pastas obrigatória e os critérios de
performance definidos na especificação. Nenhum trecho foi copiado
sem revisão.
