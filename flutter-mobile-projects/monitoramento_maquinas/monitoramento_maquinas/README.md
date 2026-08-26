# Supervisório de Máquinas — Protótipo Funcional

Desafio de aplicação integrada (Aulas 1 a 5) — Flutter.

Une performance de scroll (`GridView.builder` / `ListView.builder`), fluxo
assíncrono de dados (`Future.delayed`, `await Navigator.push`), gerenciamento
de ciclo de vida (`initState` / `dispose`) e componentização (widgets
reutilizáveis + design system centralizado).

## ▶️ Como rodar

```bash
flutter pub get
flutter run
```

## 🗂️ Estrutura de pastas

```
lib/
├── main.dart
├── models/
│   ├── sensor_model.dart          # Modelo de negócio: sensor da máquina
│   └── ocorrencia_model.dart      # Modelo de negócio: log/ocorrência
├── themes/
│   └── app_theme.dart             # Design system: ThemeData global, cores, raio de borda
├── widgets/
│   ├── custom_action_button.dart  # Botão reutilizável (ícone + label + callback)
│   └── indicator_card.dart        # Card reutilizável de sensor (usado no Grid)
└── screens/
    ├── login_screen.dart          # Tela 1 — Portal de Acesso
    ├── dashboard_screen.dart      # Tela 2 — Dashboard (GridView.builder)
    ├── logs_screen.dart           # Tela 3 — Histórico de Logs (ListView.builder)
    └── filter_screen.dart         # Tela 4 — Filtro Avançado
```

## ✅ Requisitos atendidos

| Requisito | Onde |
|---|---|
| Estrutura de pastas `/models /themes /widgets /screens` | `lib/` |
| Design system centralizado (`ThemeData` global) | `themes/app_theme.dart`, aplicado em `main.dart` |
| 2+ widgets reutilizáveis | `widgets/custom_action_button.dart`, `widgets/indicator_card.dart` |
| Tela de Login com `Navigator.push` | `screens/login_screen.dart` |
| Dashboard com `GridView.builder`, 6+ cards dinâmicos | `screens/dashboard_screen.dart` |
| Histórico com `ListView.builder`, 50+ itens, `ListTile` completo | `screens/logs_screen.dart` |
| Filtro que retorna valor via `Navigator.pop(context, filtro)` | `screens/filter_screen.dart` |
| Retorno assíncrono (`await`) + `SnackBar` | `screens/logs_screen.dart` → `_abrirFiltro()` |
| `CircularProgressIndicator` durante carregamento | `screens/logs_screen.dart` |
| `initState()` + `Future.delayed(2s)` | `screens/logs_screen.dart` |
| `dispose()` liberando controllers | `screens/login_screen.dart` |
| `setState` alterando um item específico da lista | `screens/logs_screen.dart` → `_alternarReconhecimento()` |

## 🎬 Roteiro sugerido para a gravação (≤ 1 min)

1. Abrir o app na tela de Login, digitar algo e tocar em **Entrar**.
2. Mostrar o Dashboard com os 8 cards de sensores, rolando a grade.
3. Tocar no botão **Ver Logs de Ocorrência**.
4. Mostrar o `CircularProgressIndicator` por ~2s até a lista carregar.
5. Rolar a lista de 50 ocorrências e tocar no ícone de "reconhecer alarme"
   de um item (mostrando o `setState` mudando o visual daquela linha).
6. Tocar no ícone de filtro (canto superior direito), escolher **Crítico**.
7. Mostrar a lista filtrada e o `SnackBar`: *"Exibindo apenas logs do tipo: Crítico"*.
