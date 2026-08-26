/// Model que representa uma despesa (verba de gabinete / reembolso) de
/// um parlamentar, retornada pelo endpoint `/deputados/{id}/despesas`.
///
/// Pontos críticos de robustez, identificados no Log de Debugging
/// (ver docs/PROMPT_LOG.md):
///  - `valorDocumento` e `valorLiquido` às vezes vêm como `String`
///    (ex.: "1234.56") e às vezes como `double`.
///  - `dataDocumento` nem sempre segue o formato ISO estrito e pode
///    vir nula em registros históricos antigos.
class Despesa {
  final int ano;
  final int mes;
  final String tipoDespesa;
  final String tipoDocumento;
  final DateTime? dataDocumento;
  final double valorDocumento;
  final double valorLiquido;
  final double valorGlosa;
  final String nomeFornecedor;
  final String? cnpjCpfFornecedor;
  final String? urlDocumento;

  const Despesa({
    required this.ano,
    required this.mes,
    required this.tipoDespesa,
    required this.tipoDocumento,
    required this.valorDocumento,
    required this.valorLiquido,
    required this.valorGlosa,
    required this.nomeFornecedor,
    this.dataDocumento,
    this.cnpjCpfFornecedor,
    this.urlDocumento,
  });

  static double _parseDouble(dynamic value, {double fallback = 0.0}) {
    if (value == null) return fallback;
    if (value is double) return value;
    if (value is int) return value.toDouble();
    if (value is String) {
      // Normaliza formatos como "1.234,56" para "1234.56" antes do parse,
      // já que alguns registros legados vêm no padrão pt-BR.
      final normalized = value.contains(',')
          ? value.replaceAll('.', '').replaceAll(',', '.')
          : value;
      return double.tryParse(normalized) ?? fallback;
    }
    return fallback;
  }

  static int _parseInt(dynamic value, {int fallback = 0}) {
    if (value == null) return fallback;
    if (value is int) return value;
    if (value is String) return int.tryParse(value) ?? fallback;
    return fallback;
  }

  static DateTime? _parseDate(dynamic value) {
    if (value == null) return null;
    final str = value.toString();
    if (str.isEmpty) return null;
    return DateTime.tryParse(str);
  }

  factory Despesa.fromJson(Map<String, dynamic> json) {
    return Despesa(
      ano: _parseInt(json['ano']),
      mes: _parseInt(json['mes']),
      tipoDespesa:
          (json['tipoDespesa'] as String?)?.trim() ?? 'Não especificado',
      tipoDocumento: (json['tipoDocumento'] as String?) ?? '—',
      dataDocumento: _parseDate(json['dataDocumento']),
      valorDocumento: _parseDouble(json['valorDocumento']),
      valorLiquido: _parseDouble(json['valorLiquido']),
      valorGlosa: _parseDouble(json['valorGlosa']),
      nomeFornecedor:
          (json['nomeFornecedor'] as String?)?.trim() ?? 'Fornecedor não informado',
      cnpjCpfFornecedor: json['cnpjCpfFornecedor'] as String?,
      urlDocumento: json['urlDocumento'] as String?,
    );
  }

  String get mesAnoFormatado => '${mes.toString().padLeft(2, '0')}/$ano';
}
