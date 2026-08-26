import 'package:flutter/material.dart';

import '../database/favorito_dao.dart';
import '../models/nav_args.dart';
import '../models/politico.dart';
import '../widgets/loading_state_view.dart';
import '../widgets/politico_card.dart';
import 'politico_detail_screen.dart';

/// Tela de Favoritos: lê exclusivamente do SQLite local, portanto
/// funciona mesmo sem conexão — este é o "cartão de fiscalização
/// offline" descrito na justificativa de UX da especificação.
class FavoritosScreen extends StatefulWidget {
  const FavoritosScreen({super.key});

  @override
  State<FavoritosScreen> createState() => _FavoritosScreenState();
}

class _FavoritosScreenState extends State<FavoritosScreen> {
  final _favoritoDao = FavoritoDao.instance;
  List<Politico> _favoritos = [];
  bool _isLoading = true;

  @override
  void initState() {
    super.initState();
    _carregar();
  }

  Future<void> _carregar() async {
    setState(() => _isLoading = true);
    final favoritos = await _favoritoDao.listarTodos();
    if (!mounted) return;
    setState(() {
      _favoritos = favoritos;
      _isLoading = false;
    });
  }

  Future<void> _remover(Politico politico) async {
    await _favoritoDao.remover(politico.id);
    if (!mounted) return;
    setState(() => _favoritos.removeWhere((p) => p.id == politico.id));

    if (!mounted) return;
    ScaffoldMessenger.of(context).showSnackBar(
      SnackBar(content: Text('${politico.nome} removido dos favoritos.')),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Meus Favoritos'),
      ),
      body: LoadingStateView(
        isLoading: _isLoading,
        isEmpty: _favoritos.isEmpty,
        emptyMessage:
            'Você ainda não salvou nenhum parlamentar.\nToque no ícone de coração na listagem para consultar offline.',
        child: ListView.builder(
          padding: const EdgeInsets.symmetric(vertical: 8),
          itemCount: _favoritos.length,
          itemBuilder: (context, index) {
            final politico = _favoritos[index];
            return PoliticoCard(
              politico: politico,
              isFavorito: true,
              onTap: () => Navigator.of(context).push(
                MaterialPageRoute(
                  builder: (_) => PoliticoDetailScreen(
                    args: PoliticoDetailArgs(politico: politico),
                  ),
                ),
              ),
              onToggleFavorito: () => _remover(politico),
            );
          },
        ),
      ),
    );
  }
}
