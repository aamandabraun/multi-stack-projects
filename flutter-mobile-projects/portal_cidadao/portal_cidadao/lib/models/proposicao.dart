/// Model que representa uma proposição legislativa (PL, PEC, MPV etc.)
/// de autoria do parlamentar, obtida via `/proposicoes?idDeputadoAutor={id}`.
class Proposicao {
  final int id;
  final String siglaTipo;
  final int numero;
  final int ano;
  final String ementa;
  final DateTime? dataApresentacao;

  const Proposicao({
    required this.id,
    required this.siglaTipo,
    required this.numero,
    required this.ano,
    required this.ementa,
    this.dataApresentacao,
  });

  static int _parseInt(dynamic value, {int fallback = 0}) {
    if (value == null) return fallback;
    if (value is int) return value;
    if (value is String) return int.tryParse(value) ?? fallback;
    return fallback;
  }

  factory Proposicao.fromJson(Map<String, dynamic> json) {
    return Proposicao(
      id: _parseInt(json['id']),
      siglaTipo: (json['siglaTipo'] as String?) ?? '—',
      numero: _parseInt(json['numero']),
      ano: _parseInt(json['ano']),
      ementa: (json['ementa'] as String?)?.trim() ?? 'Ementa não disponível',
      dataApresentacao: json['dataApresentacao'] != null
          ? DateTime.tryParse(json['dataApresentacao'].toString())
          : null,
    );
  }

  String get identificacao => '$siglaTipo $numero/$ano';
}
