import 'package:flutter/material.dart';

import '../database/favorito_dao.dart';
import '../models/despesa.dart';
import '../models/nav_args.dart';
import '../models/proposicao.dart';
import '../services/camara_api_service.dart';
import '../themes/app_theme.dart';
import '../widgets/despesa_badge.dart';
import '../widgets/loading_state_view.dart';

/// Tela de detalhe de um parlamentar: gastos de gabinete (despesas) e
/// proposições legislativas recentes, organizadas em abas.
class PoliticoDetailScreen extends StatefulWidget {
  final PoliticoDetailArgs args;

  const PoliticoDetailScreen({super.key, required this.args});

  @override
  State<PoliticoDetailScreen> createState() => _PoliticoDetailScreenState();
}

class _PoliticoDetailScreenState extends State<PoliticoDetailScreen>
    with SingleTickerProviderStateMixin {
  final _api = CamaraApiService.instance;
  final _favoritoDao = FavoritoDao.instance;

  late final TabController _tabController;

  List<Despesa> _despesas = [];
  List<Proposicao> _proposicoes = [];

  bool _isLoadingDespesas = true;
  bool _isLoadingProposicoes = true;
  String? _erroDespesas;
  String? _erroProposicoes;
  bool _isFavorito = false;

  @override
  void initState() {
    super.initState();
    // Todas as chamadas de API/DB são disparadas em initState(), nunca
    // no build(), conforme exigido na especificação.
    _tabController = TabController(length: 2, vsync: this);
    _carregarDespesas();
    _carregarProposicoes();
    _verificarFavorito();
  }

  @override
  void dispose() {
    // Limpeza explícita de controllers para evitar leaks de memória.
    _tabController.dispose();
    super.dispose();
  }

  Future<void> _verificarFavorito() async {
    final favorito = await _favoritoDao.isFavorito(widget.args.politico.id);
    if (!mounted) return;
    setState(() => _isFavorito = favorito);
  }

  Future<void> _toggleFavorito() async {
    final novoEstado = await _favoritoDao.alternar(widget.args.politico);
    if (!mounted) return;
    setState(() => _isFavorito = novoEstado);
  }

  Future<void> _carregarDespesas() async {
    setState(() {
      _isLoadingDespesas = true;
      _erroDespesas = null;
    });
    try {
      final despesas = await _api.listarDespesas(widget.args.politico.id);
      if (!mounted) return;
      setState(() {
        _despesas = despesas;
        _isLoadingDespesas = false;
      });
    } on ApiException catch (e) {
      if (!mounted) return;
      setState(() {
        _erroDespesas = e.message;
        _isLoadingDespesas = false;
      });
    }
  }

  Future<void> _carregarProposicoes() async {
    setState(() {
      _isLoadingProposicoes = true;
      _erroProposicoes = null;
    });
    try {
      final proposicoes = await _api.listarProposicoes(widget.args.politico.id);
      if (!mounted) return;
      setState(() {
        _proposicoes = proposicoes;
        _isLoadingProposicoes = false;
      });
    } on ApiException catch (e) {
      if (!mounted) return;
      setState(() {
        _erroProposicoes = e.message;
        _isLoadingProposicoes = false;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    final politico = widget.args.politico;

    return Scaffold(
      appBar: AppBar(
        title: Text(politico.nome, overflow: TextOverflow.ellipsis),
        actions: [
          IconButton(
            icon: Icon(
              _isFavorito ? Icons.favorite : Icons.favorite_border,
              color: _isFavorito ? AppColors.alerta : null,
            ),
            onPressed: _toggleFavorito,
          ),
        ],
        bottom: TabBar(
          controller: _tabController,
          tabs: const [
            Tab(text: 'Despesas', icon: Icon(Icons.receipt_long)),
            Tab(text: 'Proposições', icon: Icon(Icons.gavel)),
          ],
        ),
      ),
      body: Column(
        children: [
          _Cabecalho(politico: politico),
          Expanded(
            child: TabBarView(
              controller: _tabController,
              children: [
                _AbaDespesas(
                  despesas: _despesas,
                  isLoading: _isLoadingDespesas,
                  erro: _erroDespesas,
                  onRetry: _carregarDespesas,
                ),
                _AbaProposicoes(
                  proposicoes: _proposicoes,
                  isLoading: _isLoadingProposicoes,
                  erro: _erroProposicoes,
                  onRetry: _carregarProposicoes,
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }
}

class _Cabecalho extends StatelessWidget {
  final politico;
  const _Cabecalho({required this.politico});

  @override
  Widget build(BuildContext context) {
    return Container(
      width: double.infinity,
      padding: const EdgeInsets.all(AppSpacing.md),
      color: Theme.of(context).colorScheme.surfaceContainerHighest.withOpacity(0.3),
      child: Row(
        children: [
          CircleAvatar(
            radius: 32,
            backgroundImage: politico.urlFoto.isNotEmpty
                ? NetworkImage(politico.urlFoto)
                : null,
          ),
          const SizedBox(width: AppSpacing.md),
          Expanded(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(politico.nome, style: Theme.of(context).textTheme.titleMedium),
                const SizedBox(height: 4),
                Text(
                  '${politico.siglaPartido} · ${politico.siglaUf}',
                  style: Theme.of(context).textTheme.bodySmall,
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }
}

class _AbaDespesas extends StatelessWidget {
  final List<Despesa> despesas;
  final bool isLoading;
  final String? erro;
  final VoidCallback onRetry;

  const _AbaDespesas({
    required this.despesas,
    required this.isLoading,
    required this.erro,
    required this.onRetry,
  });

  @override
  Widget build(BuildContext context) {
    return LoadingStateView(
      isLoading: isLoading,
      errorMessage: erro,
      onRetry: onRetry,
      isEmpty: despesas.isEmpty,
      emptyMessage: 'Nenhuma despesa registrada no período consultado.',
      child: ListView.builder(
        padding: const EdgeInsets.symmetric(vertical: 8),
        itemCount: despesas.length,
        itemBuilder: (context, index) {
          final despesa = despesas[index];
          return ListTile(
            title: Text(
              despesa.nomeFornecedor,
              maxLines: 1,
              overflow: TextOverflow.ellipsis,
            ),
            subtitle: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text('${despesa.tipoDespesa} · ${despesa.mesAnoFormatado}'),
                const SizedBox(height: 4),
                DespesaBadge(despesa: despesa),
              ],
            ),
            isThreeLine: true,
            trailing: Text(
              'R\$ ${despesa.valorLiquido.toStringAsFixed(2)}',
              style: const TextStyle(fontWeight: FontWeight.bold),
            ),
          );
        },
      ),
    );
  }
}

class _AbaProposicoes extends StatelessWidget {
  final List<Proposicao> proposicoes;
  final bool isLoading;
  final String? erro;
  final VoidCallback onRetry;

  const _AbaProposicoes({
    required this.proposicoes,
    required this.isLoading,
    required this.erro,
    required this.onRetry,
  });

  @override
  Widget build(BuildContext context) {
    return LoadingStateView(
      isLoading: isLoading,
      errorMessage: erro,
      onRetry: onRetry,
      isEmpty: proposicoes.isEmpty,
      emptyMessage: 'Nenhuma proposição de autoria encontrada.',
      child: ListView.builder(
        padding: const EdgeInsets.symmetric(vertical: 8),
        itemCount: proposicoes.length,
        itemBuilder: (context, index) {
          final proposicao = proposicoes[index];
          return ListTile(
            leading: const Icon(Icons.description_outlined),
            title: Text(proposicao.identificacao),
            subtitle: Text(
              proposicao.ementa,
              maxLines: 2,
              overflow: TextOverflow.ellipsis,
            ),
          );
        },
      ),
    );
  }
}
