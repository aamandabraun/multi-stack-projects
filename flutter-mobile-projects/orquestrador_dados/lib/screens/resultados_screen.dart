import 'package:flutter/material.dart';
import '../models/filtro_model.dart';
import 'filtros_avancados_screen.dart';

/// Tela que exibe os resultados da telemetria/ordens de serviço filtradas.
/// Recebe o FiltroModel completo enviado pela tela de pesquisa.
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

    // Validação da integridade do objeto recebido também via RouteSettings,
    // demonstrando a segunda forma de acesso exigida pelo desafio.
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

  /// CONTROLE DE FLUXO DE RETORNO + ASSINCRONISMO
  /// Navigator.push é tipado explicitamente como Future<bool?> pois a tela
  /// de filtros avançados pode retornar true (aplicado), false (cancelado)
  /// ou null (fechada pelo botão nativo de voltar do Android, por exemplo).
  /// O await garante que só decidimos se uma nova requisição é necessária
  /// depois que o usuário efetivamente terminou de interagir com a tela.
  Future<void> _abrirFiltrosAvancados() async {
    final Future<bool?> resultadoNavegacao = Navigator.push<bool>(
      context,
      MaterialPageRoute(
        builder: (context) => FiltrosAvancadosScreen(filtroAtual: _filtroAtual),
      ),
    );

    final bool? filtroFoiAplicado = await resultadoNavegacao;

    // TRATAMENTO DE NULIDADE (NULL-SAFETY):
    // Se o usuário fechar a tela sem tocar em "Aplicar" ou "Cancelar"
    // (ex.: botão físico/gesto de voltar), o retorno pode ser null.
    // Usamos "?? false" para tratar esse caso com segurança, sem lançar
    // exceções, e sem disparar uma nova requisição desnecessária.
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
