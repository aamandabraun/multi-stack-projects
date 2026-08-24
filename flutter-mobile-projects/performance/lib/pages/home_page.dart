// pages/home_page.dart
import 'package:flutter/material.dart';
import 'listview_otimizada_page.dart';
import 'dashboard_sensores_page.dart';
import 'guardiao_memoria_page.dart';

class HomePage extends StatelessWidget {
  const HomePage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Exercícios Flutter')),
      body: ListView(
        padding: const EdgeInsets.all(16),
        children: [
          _buildItem(context, '1. Otimizador de Listas', const ListViewOtimizadaPage()),
          _buildItem(context, '2. Dashboard em Grade', const DashboardSensoresPage()),
          _buildItem(context, '3. Guardião de Memória', const GuardiaoMemoriaPage()),
        ],
      ),
    );
  }

  Widget _buildItem(BuildContext context, String titulo, Widget page) {
    return Card(
      child: ListTile(
        title: Text(titulo),
        trailing: const Icon(Icons.arrow_forward_ios),
        onTap: () => Navigator.push(
          context,
          MaterialPageRoute(builder: (_) => page),
        ),
      ),
    );
  }
}