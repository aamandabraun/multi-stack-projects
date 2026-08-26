import 'package:path/path.dart';
import 'package:sqflite/sqflite.dart';

/// Responsável exclusivamente por abrir/migrar o banco SQLite local.
/// Toda a lógica de CRUD de domínio fica no `FavoritoDao`, mantendo
/// esta classe restrita à infraestrutura de persistência.
class DatabaseHelper {
  DatabaseHelper._internal();
  static final DatabaseHelper instance = DatabaseHelper._internal();

  static Database? _database;

  static const String tableFavoritos = 'favoritos';

  Future<Database> get database async {
    if (_database != null) return _database!;
    _database = await _initDatabase();
    return _database!;
  }

  Future<Database> _initDatabase() async {
    final path = join(await getDatabasesPath(), 'portal_cidadao.db');

    return openDatabase(
      path,
      version: 1,
      onCreate: _onCreate,
    );
  }

  Future<void> _onCreate(Database db, int version) async {
    await db.execute('''
      CREATE TABLE $tableFavoritos (
        id INTEGER PRIMARY KEY,
        nome TEXT NOT NULL,
        siglaPartido TEXT,
        siglaUf TEXT,
        urlFoto TEXT,
        email TEXT,
        idLegislatura INTEGER,
        dataFavoritado TEXT NOT NULL
      )
    ''');
  }
}
