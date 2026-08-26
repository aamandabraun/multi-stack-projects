import 'politico.dart';

/// Objetos de navegação tipados.
///
/// A especificação proíbe a passagem de dados entre telas via
/// argumentos soltos/strings puras (`Navigator.pushNamed(context, '/x',
/// arguments: {'id': 3})`). Todo argumento trafega encapsulado em uma
/// classe própria, permitindo checagem em tempo de compilação.

/// Argumentos recebidos pela tela de Detalhe do Político.
class PoliticoDetailArgs {
  final Politico politico;

  const PoliticoDetailArgs({required this.politico});
}

/// Filtros aplicáveis à listagem de parlamentares. Imutável e
/// comparável por valor, para permitir `==` direto entre estados de
/// filtro (usado pelo PopScope da tela de filtros).
class FiltroPoliticos {
  final String? uf;
  final String? partido;

  const FiltroPoliticos({this.uf, this.partido});

  bool get isEmpty => (uf == null || uf!.isEmpty) &&
      (partido == null || partido!.isEmpty);

  FiltroPoliticos copyWith({String? uf, String? partido}) {
    return FiltroPoliticos(
      uf: uf ?? this.uf,
      partido: partido ?? this.partido,
    );
  }

  @override
  bool operator ==(Object other) =>
      other is FiltroPoliticos && other.uf == uf && other.partido == partido;

  @override
  int get hashCode => Object.hash(uf, partido);
}

/// Argumentos enviados para a tela de Filtros: o filtro atualmente
/// aplicado, para que a UI abra já pré-preenchida.
class FiltroScreenArgs {
  final FiltroPoliticos filtroAtual;

  const FiltroScreenArgs({required this.filtroAtual});
}
