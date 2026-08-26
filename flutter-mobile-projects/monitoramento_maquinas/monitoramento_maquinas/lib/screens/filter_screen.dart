import 'package:flutter/material.dart';
import '../themes/app_theme.dart';

/// Tela 4 - Filtro Avançado.
/// Não retorna via botão "voltar" comum: cada opção, ao ser tocada,
/// fecha a tela e devolve o valor escolhido via Navigator.pop.
/// A tela anterior (Logs) aguarda esse retorno com `await`.
class FilterScreen extends StatelessWidget {
  const FilterScreen({super.key});

  static const List<Map<String, dynamic>> _categorias = [
    {'label': 'Crítico', 'icone': Icons.error, 'cor': AppTheme.critico},
    {'label': 'Alerta', 'icone': Icons.warning_amber, 'cor': AppTheme.alerta},
    {'label': 'Info', 'icone': Icons.info_outline, 'cor': AppTheme.info},
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Filtrar por Gravidade')),
      body: Padding(
        padding: const EdgeInsets.all(16),
        child: Column(
          children: [
            Text(
              'Selecione a gravidade que deseja visualizar no histórico:',
              style: Theme.of(context).textTheme.bodySmall,
            ),
            const SizedBox(height: 16),
            ..._categorias.map((categoria) {
              return Padding(
                padding: const EdgeInsets.only(bottom: 12),
                child: Card(
                  child: ListTile(
                    leading: Icon(
                      categoria['icone'] as IconData,
                      color: categoria['cor'] as Color,
                    ),
                    title: Text(categoria['label'] as String),
                    trailing: const Icon(Icons.chevron_right),
                    onTap: () {
                      // Fecha a Tela 4 devolvendo o filtro escolhido
                      // para quem chamou Navigator.push (Tela 3).
                      Navigator.pop(context, categoria['label'] as String);
                    },
                  ),
                ),
              );
            }),
          ],
        ),
      ),
    );
  }
}
