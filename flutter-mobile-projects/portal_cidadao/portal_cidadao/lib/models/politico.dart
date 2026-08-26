/// Model que representa um parlamentar (Deputado) retornado pela API
/// da Câmara dos Deputados.
///
/// A API governamental é inconsistente na tipagem de alguns campos
/// (ex.: `id` às vezes vem como int, às vezes como String em endpoints
/// diferentes). Por isso todo o parsing é feito por helpers defensivos
/// em vez de casts diretos (`as int`, `as String`), que quebrariam o
/// app em tempo de execução.
class Politico {
  final int id;
  final String nome;
  final String siglaPartido;
  final String siglaUf;
  final String urlFoto;
  final String? email;
  final int idLegislatura;

  // Campos presentes apenas no detalhe (endpoint /deputados/{id})
  final String? dataNascimento;
  final String? municipioNascimento;
  final String? ufNascimento;
  final String? escolaridade;
  final String? condicaoEleitoral;
  final String? situacao;

  const Politico({
    required this.id,
    required this.nome,
    required this.siglaPartido,
    required this.siglaUf,
    required this.urlFoto,
    required this.idLegislatura,
    this.email,
    this.dataNascimento,
    this.municipioNascimento,
    this.ufNascimento,
    this.escolaridade,
    this.condicaoEleitoral,
    this.situacao,
  });

  /// Parser resiliente: aceita `int` ou `String` numérica vinda da API.
  static int _parseInt(dynamic value, {int fallback = 0}) {
    if (value == null) return fallback;
    if (value is int) return value;
    if (value is double) return value.toInt();
    if (value is String) return int.tryParse(value) ?? fallback;
    return fallback;
  }

  static String _parseString(dynamic value, {String fallback = ''}) {
    if (value == null) return fallback;
    return value.toString();
  }

  /// Construtor a partir do JSON da listagem (`/deputados`).
  factory Politico.fromJson(Map<String, dynamic> json) {
    return Politico(
      id: _parseInt(json['id']),
      nome: _parseString(json['nome'], fallback: 'Nome não informado'),
      siglaPartido: _parseString(json['siglaPartido'], fallback: '—'),
      siglaUf: _parseString(json['siglaUf'], fallback: '—'),
      urlFoto: _parseString(json['urlFoto']),
      email: json['email'] as String?,
      idLegislatura: _parseInt(json['idLegislatura']),
    );
  }

  /// Construtor a partir do JSON detalhado (`/deputados/{id}`), cujo
  /// payload real vem aninhado em `dados` -> `ultimoStatus`.
  factory Politico.fromDetailJson(Map<String, dynamic> json) {
    final dados = json['dados'] as Map<String, dynamic>? ?? json;
    final ultimoStatus =
        dados['ultimoStatus'] as Map<String, dynamic>? ?? const {};

    return Politico(
      id: _parseInt(dados['id']),
      nome: _parseString(
        ultimoStatus['nome'] ?? dados['nomeCivil'],
        fallback: 'Nome não informado',
      ),
      siglaPartido: _parseString(ultimoStatus['siglaPartido'], fallback: '—'),
      siglaUf: _parseString(ultimoStatus['siglaUf'], fallback: '—'),
      urlFoto: _parseString(ultimoStatus['urlFoto']),
      email: ultimoStatus['gabinete']?['email'] as String?,
      idLegislatura: _parseInt(ultimoStatus['idLegislatura']),
      dataNascimento: dados['dataNascimento'] as String?,
      municipioNascimento: dados['municipioNascimento'] as String?,
      ufNascimento: dados['ufNascimento'] as String?,
      escolaridade: dados['escolaridade'] as String?,
      condicaoEleitoral: ultimoStatus['condicaoEleitoral'] as String?,
      situacao: ultimoStatus['situacao'] as String?,
    );
  }

  /// Serialização para persistência local (tabela `favoritos`).
  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'nome': nome,
      'siglaPartido': siglaPartido,
      'siglaUf': siglaUf,
      'urlFoto': urlFoto,
      'email': email,
      'idLegislatura': idLegislatura,
    };
  }

  factory Politico.fromMap(Map<String, dynamic> map) {
    return Politico(
      id: _parseInt(map['id']),
      nome: _parseString(map['nome']),
      siglaPartido: _parseString(map['siglaPartido']),
      siglaUf: _parseString(map['siglaUf']),
      urlFoto: _parseString(map['urlFoto']),
      email: map['email'] as String?,
      idLegislatura: _parseInt(map['idLegislatura']),
    );
  }

  @override
  bool operator ==(Object other) => other is Politico && other.id == id;

  @override
  int get hashCode => id.hashCode;
}
