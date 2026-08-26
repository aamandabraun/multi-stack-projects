# Portal Cidadão 🏛️

App Flutter de fiscalização e transparência pública, consumindo a
[API de Dados Abertos da Câmara dos Deputados](https://dadosabertos.camara.leg.br/).

## Funcionalidades

- **Listagem de parlamentares** com filtros por UF e partido (lazy
  loading via `ListView.builder` + paginação incremental).
- **Detalhes de gastos**: despesas de gabinete/reembolso por
  parlamentar, com indicação visual de glosa.
- **Favoritos offline**: persistência local em SQLite para consulta
  sem internet.
- **Proposições**: projetos de lei de autoria do parlamentar.
- **Dark / Light Mode** via `ThemeData` centralizado.

## Estrutura de pastas

```
lib/
  models/       # Politico, Despesa, Proposicao, objetos de navegação tipados
  views/        # Telas: listagem, detalhe, filtros, favoritos
  widgets/      # PoliticoCard, DespesaBadge, LoadingStateView (reutilizáveis)
  themes/       # AppTheme (Light/Dark) e design tokens
  services/     # CamaraApiService (consumo HTTP via Dio)
  database/     # DatabaseHelper + FavoritoDao (SQLite)
docs/
  PROMPT_LOG.md # Governança de IA — prompts, bugs e refatorações manuais
```

## Como rodar

1. Instale o [Flutter SDK](https://docs.flutter.dev/get-started/install) (canal stable).
2. Na raiz do projeto:
   ```bash
   flutter pub get
   flutter run
   ```
3. Não é necessária nenhuma chave de API — os endpoints da Câmara dos
   Deputados são públicos e não exigem autenticação.

## Dependências principais

| Pacote | Uso |
|---|---|
| `dio` | Cliente HTTP para consumo da API |
| `sqflite` + `path` | Persistência local de favoritos |

## Documento de Governança de IA

Ver [`docs/PROMPT_LOG.md`](docs/PROMPT_LOG.md) para o checklist
completo exigido pela especificação (registro de prompts, bugs
encontrados e refatoração manual).
