import 'package:flutter/material.dart';

/// Representa um sensor de máquina monitorado no dashboard.
class SensorModel {
  final String nome;
  final String localizacao;
  final double valor;
  final String unidade;
  final String status; // 'Normal', 'Alerta' ou 'Critico'
  final IconData icone;

  SensorModel({
    required this.nome,
    required this.localizacao,
    required this.valor,
    required this.unidade,
    required this.status,
    required this.icone,
  });
}
