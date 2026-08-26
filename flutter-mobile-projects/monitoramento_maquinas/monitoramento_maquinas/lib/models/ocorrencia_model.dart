/// Representa um registro de ocorrência/log gerado pelas máquinas.
class OcorrenciaModel {
  final String titulo;
  final String descricao;
  final String gravidade; // 'Crítico', 'Alerta' ou 'Info'
  final DateTime dataHora;
  bool reconhecido;

  OcorrenciaModel({
    required this.titulo,
    required this.descricao,
    required this.gravidade,
    required this.dataHora,
    this.reconhecido = false,
  });
}
