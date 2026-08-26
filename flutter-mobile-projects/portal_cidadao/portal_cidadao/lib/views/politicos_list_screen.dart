import 'package:flutter/material.dart';

import '../database/favorito_dao.dart';
import '../models/nav_args.dart';
import '../models/politico.dart';
import '../services/camara_api_service.dart';
import '../themes/app_theme.dart';
import '../widgets/loading_state_view.dart';
import '../widgets/politico_card.dart';
import 'favoritos_screen.dart';
import 'filtros_screen.dart';
import 'politico_detail_screen.dart';

/// Tela principal do app: listagem paginada de parlamentares.
///
/// Requisitos de performance da especificação:
///  - `ListView.builder` com Lazy Loading (nunca `ListView(children: [...])`)
///  - Paginação incremental disparada ao chegar perto do fim do scroll,
///    evitando carregar milhares de registros de uma vez.
class PoliticosListScreen extends StatefulWidget {
  const PoliticosListScreen({super.key});

  @override
  State<PoliticosListScreen> createState() => _PoliticosListScreenState();
}

class _PoliticosListScreenState extends State<PoliticosListScreen> {
  final _api = CamaraApiService.instance;
  final _favoritoDao = FavoritoDao.instance;
  final _scrollController = ScrollController();

  final List<Politico> _politicos = [];
  final Set<int> _idsFavoritos = {};

  FiltroPoliticos _filtro = const FiltroPoliticos();

  int _pagina = 1;
  bool _isLoadingInicial = true;
  bool _isLoadingMais = false;
  bool _fimDaLista = false;
  String? _erro;

  @override
  void initState() {
    super.initState();
    // Requisito da especificação: requisições de API disparadas em
    // initState(), nunca diretamente no build().
    _scrollController.addListener(_onScroll);
    _carregarFavoritos();
    _carregarPagina(reset: true);
  }

  @override
  void dispose() {
    // Limpeza explícita do controller para evitar leaks de memória.
    _scrollController.removeListener(_onScroll);
    _scrollController.dispose();
    super.dispose();
  }

  void _onScroll() {
    final proximoDoFim = _scrollController.position.pixels >=
        _scrollController.position.maxScrollExtent - 300;

    if (proximoDoFim && !_isLoadingMais && !_fimDaLista && _erro == null) {
      _carregarPagina();
    }
  }

  Future<void> _carregarFavoritos() async {
    final favoritos = await _favoritoDao.listarTodos();
    if (!mounted) return;
    setState(() {
      _idsFavoritos
        ..clear()
        ..addAll(favoritos.map((f) => f.id));
    });
  }

  Future<void> _carregarPagina({bool reset = false}) async {
    if (reset) {
      setState(() {
        _pagina = 1;
        _politicos.clear();
        _fimDaLista = false;
        _isLoadingInicial = true;
        _erro = null;
      });
    } else {
      setState(() => _isLoadingMais = true);
    }

    try {
      final novaPagina = await _api.listarPoliticos(
        uf: _filtro.uf,
        partido: _filtro.partido,
        pagina: _pagina,
      );

      if (!mounted) return;

      setState(() {
        _politicos.addAll(novaPagina);
        _fimDaLista = novaPagina.isEmpty;
        _pagina++;
        _isLoadingInicial = false;
        _isLoadingMais = false;
      });
    } on ApiException catch (e) {
      if (!mounted) return;
      setState(() {
        _erro = e.message;
        _isLoadingInicial = false;
        _isLoadingMais = false;
      });
    }
  }

  Future<void> _toggleFavorito(Politico politico) async {
    final novoEstado = await _favoritoDao.alternar(politico);
    if (!mounted) return;
    setState(() {
      if (novoEstado) {
        _idsFavoritos.add(politico.id);
      } else {
        _idsFavoritos.remove(politico.id);
      }
    });
  }

  Future<void> _abrirFiltros() async {
    final resultado = await Navigator.of(context).push<FiltroPoliticos>(
      MaterialPageRoute(
        builder: (_) => FiltrosScreen(
          args: FiltroScreenArgs(filtroAtual: _filtro),
        ),
      ),
    );

    if (resultado != null && resultado != _filtro) {
      setState(() => _filtro = resultado);
      _carregarPagina(reset: true);
    }
  }

  void _abrirDetalhe(Politico politico) {
    Navigator.of(context).push(
      MaterialPageRoute(
        builder: (_) => PoliticoDetailScreen(
          args: PoliticoDetailArgs(politico: politico),
        ),
      ),
    );
  }

  void _abrirFavoritos() {
    Navigator.of(context).push(
      MaterialPageRoute(builder: (_) => const FavoritosScreen()),
    ).then((_) => _carregarFavoritos());
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Portal Cidadão'),
        actions: [
          if (!_filtro.isEmpty)
            IconButton(
              tooltip: 'Filtros ativos',
              icon: const Icon(Icons.filter_alt),
              onPressed: _abrirFiltros,
            )
          else
            IconButton(
              tooltip: 'Filtrar',
              icon: const Icon(Icons.filter_alt_outlined),
              onPressed: _abrirFiltros,
            ),
          IconButton(
            tooltip: 'Favoritos',
            icon: const Icon(Icons.favorite),
            onPressed: _abrirFavoritos,
          ),
        ],
      ),
      body: LoadingStateView(
        isLoading: _isLoadingInicial,
        errorMessage: _erro,
        onRetry: () => _carregarPagina(reset: true),
        isEmpty: _politicos.isEmpty,
        emptyMessage: 'Nenhum parlamentar encontrado para esse filtro.',
        child: RefreshIndicator(
          onRefresh: () => _carregarPagina(reset: true),
          child: ListView.builder(
            controller: _scrollController,
            padding: const EdgeInsets.symmetric(vertical: AppSpacing.sm),
            // Lazy Loading: só constrói o item quando ele entra na
            // viewport, com reciclagem de memória — essencial para as
            // milhares de linhas que a API pode retornar.
            itemCount: _politicos.length + (_isLoadingMais ? 1 : 0),
            itemBuilder: (context, index) {
              if (index >= _politicos.length) {
                return const Padding(
                  padding: EdgeInsets.all(16),
                  child: Center(child: CircularProgressIndicator()),
                );
              }

              final politico = _politicos[index];
              return PoliticoCard(
                politico: politico,
                isFavorito: _idsFavoritos.contains(politico.id),
                onTap: () => _abrirDetalhe(politico),
                onToggleFavorito: () => _toggleFavorito(politico),
              );
            },
          ),
        ),
      ),
    );
  }
}
