import 'package:flutter/material.dart';
import 'screens/pesquisa_screen.dart';

void main() {
  runApp(const OrquestradorDadosApp());
}

class OrquestradorDadosApp extends StatelessWidget {
  const OrquestradorDadosApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Orquestrador de Dados',
      theme: ThemeData(colorSchemeSeed: Colors.green, useMaterial3: true),
      home: const PesquisaScreen(),
    );
  }
}
