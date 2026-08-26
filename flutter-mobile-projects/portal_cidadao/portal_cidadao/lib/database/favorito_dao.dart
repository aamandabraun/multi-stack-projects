import 'package:sqflite/sqflite.dart';

import '../models/politico.dart';
import 'database_helper.dart';

/// Data Access Object responsável pelo CRUD da tabela de Favoritos.
/// Garante que o cidadão consiga consultar perfis salvos mesmo sem
/// conexão à internet (requisito central da rubrica de Persistência).
class FavoritoDao {
  FavoritoDao._internal();
  static final FavoritoDao instance = FavoritoDao._internal();

  Future<Database> get _db async => DatabaseHelper.instance.database;

  Future<void> adicionar(Politico politico) async {
    final db = await _db;
    final map = politico.toMap();
    map['dataFavoritado'] = DateTime.now().toIso8601String();

    await db.insert(
      DatabaseHelper.tableFavoritos,
      map,
      conflictAlgorithm: ConflictAlgorithm.replace,
    );
  }

  Future<void> remover(int idPolitico) async {
    final db = await _db;
    await db.delete(
      DatabaseHelper.tableFavoritos,
      where: 'id = ?',
      whereArgs: [idPolitico],
    );
  }

  Future<bool> isFavorito(int idPolitico) async {
    final db = await _db;
    final resultado = await db.query(
      DatabaseHelper.tableFavoritos,
      where: 'id = ?',
      whereArgs: [idPolitico],
      limit: 1,
    );
    return resultado.isNotEmpty;
  }

  Future<List<Politico>> listarTodos() async {
    final db = await _db;
    final resultado = await db.query(
      DatabaseHelper.tableFavoritos,
      orderBy: 'dataFavoritado DESC',
    );
    return resultado.map((map) => Politico.fromMap(map)).toList();
  }

  /// Alterna o estado de favorito (usado pelo botão de coração nos
  /// cards). Retorna o novo estado (true = favoritado).
  Future<bool> alternar(Politico politico) async {
    final jaFavoritado = await isFavorito(politico.id);
    if (jaFavoritado) {
      await remover(politico.id);
      return false;
    } else {
      await adicionar(politico);
      return true;
    }
  }
}
