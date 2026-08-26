import 'package:flutter/material.dart';

import '../models/nav_args.dart';
import '../themes/app_theme.dart';

/// Estados brasileiros, usados no filtro de UF.
const _ufs = [
  'AC', 'AL', 'AP', 'AM', 'BA', 'CE', 'DF', 'ES', 'GO', 'MA', 'MT', 'MS',
  'MG', 'PA', 'PB', 'PR', 'PE', 'PI', 'RJ', 'RN', 'RS', 'RO', 'RR', 'SC',
  'SP', 'SE', 'TO',
];

/// Tela de filtros da listagem de parlamentares.
///
/// Usa [PopScope] para interceptar o gesto de "voltar" (físico/gesto
/// do sistema): se o usuário alterou os filtros mas não confirmou,
/// perguntamos antes de descartar a seleção — mitigando a perda
/// acidental de parâmetros exigida pela especificação.
class FiltrosScreen extends StatefulWidget {
  final FiltroScreenArgs args;

  const FiltrosScreen({super.key, required this.args});

  @override
  State<FiltrosScreen> createState() => _FiltrosScreenState();
}

class _FiltrosScreenState extends State<FiltrosScreen> {
  late String? _ufSelecionada;
  late final TextEditingController _partidoController;
  late FiltroPoliticos _filtroOriginal;

  @override
  void initState() {
    super.initState();
    _filtroOriginal = widget.args.filtroAtual;
    _ufSelecionada = _filtroOriginal.uf;
    _partidoController = TextEditingController(text: _filtroOriginal.partido);
  }

  @override
  void dispose() {
    _partidoController.dispose();
    super.dispose();
  }

  FiltroPoliticos get _filtroAtualEmEdicao => FiltroPoliticos(
        uf: _ufSelecionada,
        partido: _partidoController.text.trim().toUpperCase(),
      );

  bool get _houveAlteracaoNaoSalva =>
      _filtroAtualEmEdicao != _filtroOriginal;

  Future<void> _confirmarDescarte(bool didPop) async {
    if (didPop) return;

    final descartar = await showDialog<bool>(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text('Descartar filtros?'),
        content: const Text(
          'Você alterou os filtros mas não aplicou. Deseja sair mesmo assim e perder essa seleção?',
        ),
        actions: [
          TextButton(
            onPressed: () => Navigator.of(context).pop(false),
            child: const Text('Continuar editando'),
          ),
          FilledButton(
            onPressed: () => Navigator.of(context).pop(true),
            child: const Text('Descartar'),
          ),
        ],
      ),
    );

    if (descartar == true && mounted) {
      Navigator.of(context).pop();
    }
  }

  void _aplicarFiltros() {
    Navigator.of(context).pop(_filtroAtualEmEdicao);
  }

  void _limparFiltros() {
    setState(() {
      _ufSelecionada = null;
      _partidoController.clear();
    });
  }

  @override
  Widget build(BuildContext context) {
    return PopScope(
      canPop: !_houveAlteracaoNaoSalva,
      onPopInvokedWithResult: (didPop, result) => _confirmarDescarte(didPop),
      child: Scaffold(
        appBar: AppBar(
          title: const Text('Filtrar parlamentares'),
          actions: [
            TextButton(
              onPressed: _limparFiltros,
              child: const Text('Limpar'),
            ),
          ],
        ),
        body: ListView(
          padding: const EdgeInsets.all(AppSpacing.md),
          children: [
            Text('Estado (UF)', style: Theme.of(context).textTheme.titleMedium),
            const SizedBox(height: AppSpacing.sm),
            Wrap(
              spacing: 8,
              runSpacing: 8,
              children: _ufs.map((uf) {
                final selecionada = _ufSelecionada == uf;
                return ChoiceChip(
                  label: Text(uf),
                  selected: selecionada,
                  onSelected: (value) {
                    setState(() => _ufSelecionada = value ? uf : null);
                  },
                );
              }).toList(),
            ),
            const SizedBox(height: AppSpacing.lg),
            Text('Partido', style: Theme.of(context).textTheme.titleMedium),
            const SizedBox(height: AppSpacing.sm),
            TextField(
              controller: _partidoController,
              textCapitalization: TextCapitalization.characters,
              decoration: const InputDecoration(
                hintText: 'Ex.: PT, PL, MDB...',
                prefixIcon: Icon(Icons.groups_outlined),
              ),
            ),
            const SizedBox(height: AppSpacing.xl),
            FilledButton(
              onPressed: _aplicarFiltros,
              style: FilledButton.styleFrom(
                minimumSize: const Size.fromHeight(48),
              ),
              child: const Text('Aplicar filtros'),
            ),
          ],
        ),
      ),
    );
  }
}
