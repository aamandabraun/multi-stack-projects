import 'package:flutter/material.dart';
import '../models/filtro_model.dart';
import 'filtros_avancados_screen.dart';

class ResultadosScreen extends StatefulWidget {
  final FiltroModel filtro;

  const ResultadosScreen({super.key, required this.filtro});

  @override
  State<ResultadosScreen> createState() => _ResultadosScreenState();
}

class _ResultadosScreenState extends State<ResultadosScreen> {
  late FiltroModel _filtroAtual;
  bool _carregando = false;

  @override
  void initState() {
    super.initState();
    _filtroAtual = widget.filtro;

     WidgetsBinding.instance.addPostFrameCallback((_) {
      final argsFiltro = ModalRoute.of(context)?.settings.arguments as FiltroModel?;
      assert(argsFiltro != null && argsFiltro.tipoVeiculo == _filtroAtual.tipoVeiculo,
          'O objeto recebido via arguments deve ser íntegro e igual ao recebido via construtor.');
    });

    _carregarDados();
  }

  Future<void> _carregarDados() async {
    setState(() => _carregando = true);
    // Simulação de requisição de dados de telemetria/ordens de serviço.
    await Future.delayed(const Duration(milliseconds: 600));
    setState(() => _carregando = false);
  }

  Future<void> _abrirFiltrosAvancados() async {
    final Future<bool?> resultadoNavegacao = Navigator.push<bool>(
      context,
      MaterialPageRoute(
        builder: (context) => FiltrosAvancadosScreen(filtroAtual: _filtroAtual),
      ),
    );

    final bool? filtroFoiAplicado = await resultadoNavegacao;

    if (filtroFoiAplicado ?? false) {
      await _carregarDados();
      if (mounted) {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(content: Text('Filtros aplicados! Dados atualizados.')),
        );
      }
    } else {
      if (mounted) {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(content: Text('Filtros não foram alterados.')),
        );
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Resultados'),
        actions: [
          IconButton(
            icon: const Icon(Icons.filter_alt),
            tooltip: 'Ajustar filtros',
            onPressed: _abrirFiltrosAvancados,
          ),
        ],
      ),
      body: _carregando
          ? const Center(child: CircularProgressIndicator())
          : ListView(
              padding: const EdgeInsets.all(16),
              children: [
                Card(
                  child: Padding(
                    padding: const EdgeInsets.all(12),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                        const Text('Filtro aplicado:', style: TextStyle(fontWeight: FontWeight.bold)),
                        Text('Termo: ${_filtroAtual.termoBusca ?? "-"}'),
                        Text('Tipo de veículo: ${_filtroAtual.tipoVeiculo}'),
                        Text('Status: ${_filtroAtual.statusOrdem}'),
                      ],
                    ),
                  ),
                ),
                const SizedBox(height: 16),
                ...List.generate(
                  5,
                  (i) => ListTile(
                    leading: const Icon(Icons.electric_car),
                    title: Text('Ordem de Serviço #${1000 + i}'),
                    subtitle: Text('Status: ${_filtroAtual.statusOrdem} • Veículo: ${_filtroAtual.tipoVeiculo}'),
                  ),
                ),
              ],
            ),
    );
  }
}
