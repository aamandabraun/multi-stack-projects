class FiltroModel {
  final String? termoBusca;
  final String tipoVeiculo;
  final String statusOrdem;
  final DateTime? dataInicio;
  final DateTime? dataFim;

  const FiltroModel({
    this.termoBusca,
    required this.tipoVeiculo,
    required this.statusOrdem,
    this.dataInicio,
    this.dataFim,
  });

  FiltroModel copyWith({
    String? termoBusca,
    String? tipoVeiculo,
    String? statusOrdem,
    DateTime? dataInicio,
    DateTime? dataFim,
  }) {
    return FiltroModel(
      termoBusca: termoBusca ?? this.termoBusca,
      tipoVeiculo: tipoVeiculo ?? this.tipoVeiculo,
      statusOrdem: statusOrdem ?? this.statusOrdem,
      dataInicio: dataInicio ?? this.dataInicio,
      dataFim: dataFim ?? this.dataFim,
    );
  }

  @override
  String toString() {
    return 'FiltroModel(termoBusca: $termoBusca, tipoVeiculo: $tipoVeiculo, '
        'statusOrdem: $statusOrdem, dataInicio: $dataInicio, dataFim: $dataFim)';
  }
}
