import 'package:flutter/material.dart';
import '../models/sensor_model.dart';
import '../themes/app_theme.dart';
import '../widgets/indicator_card.dart';
import 'logs_screen.dart';

/// Tela 2 - Dashboard de Sensores.
/// Usa GridView.builder para rolagem suave e performática de cartões
/// de sensores com dados dinâmicos.
class DashboardScreen extends StatelessWidget {
  const DashboardScreen({super.key});

  // Dados simulados dos sensores (poderiam vir de uma API/stream real).
  List<SensorModel> get _sensores => [
        SensorModel(
          nome: 'Temperatura Motor 01',
          localizacao: 'Linha A',
          valor: 78.4,
          unidade: '°C',
          status: 'Alerta',
          icone: Icons.thermostat,
        ),
        SensorModel(
          nome: 'Pressão Hidráulica',
          localizacao: 'Linha A',
          valor: 142.0,
          unidade: 'bar',
          status: 'Normal',
          icone: Icons.speed,
        ),
        SensorModel(
          nome: 'Vibração Eixo X',
          localizacao: 'Linha B',
          valor: 3.2,
          unidade: 'mm/s',
          status: 'Critico',
          icone: Icons.vibration,
        ),
        SensorModel(
          nome: 'Corrente Elétrica',
          localizacao: 'Painel 02',
          valor: 12.7,
          unidade: 'A',
          status: 'Normal',
          icone: Icons.bolt,
        ),
        SensorModel(
          nome: 'Nível de Óleo',
          localizacao: 'Linha B',
          valor: 61.0,
          unidade: '%',
          status: 'Alerta',
          icone: Icons.oil_barrel,
        ),
        SensorModel(
          nome: 'Velocidade Esteira',
          localizacao: 'Linha C',
          valor: 1.8,
          unidade: 'm/s',
          status: 'Normal',
          icone: Icons.moving,
        ),
        SensorModel(
          nome: 'Umidade do Ambiente',
          localizacao: 'Galpão 1',
          valor: 55.0,
          unidade: '%',
          status: 'Normal',
          icone: Icons.water_drop,
        ),
        SensorModel(
          nome: 'Pressão Pneumática',
          localizacao: 'Linha C',
          valor: 6.4,
          unidade: 'bar',
          status: 'Critico',
          icone: Icons.compress,
        ),
      ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Dashboard de Sensores')),
      body: Padding(
        padding: const EdgeInsets.all(16),
        child: GridView.builder(
          // GridView.builder constrói os itens sob demanda, garantindo
          // rolagem suave mesmo com muitos sensores.
          physics: const BouncingScrollPhysics(),
          gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
            crossAxisCount: 2,
            mainAxisSpacing: 16,
            crossAxisSpacing: 16,
            childAspectRatio: 0.95,
          ),
          itemCount: _sensores.length,
          itemBuilder: (context, index) {
            return IndicatorCard(sensor: _sensores[index]);
          },
        ),
      ),
      floatingActionButton: FloatingActionButton.extended(
        backgroundColor: AppTheme.primary,
        foregroundColor: Colors.black,
        icon: const Icon(Icons.list_alt),
        label: const Text('Ver Logs de Ocorrência'),
        onPressed: () {
          Navigator.push(
            context,
            MaterialPageRoute(builder: (_) => const LogsScreen()),
          );
        },
      ),
    );
  }
}
