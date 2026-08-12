import 'package:flutter/material.dart';
import '../models/filtro_model.dart';
import 'resultados_screen.dart';

class PesquisaScreen extends StatefulWidget {
  const PesquisaScreen({super.key});

  @override
  State<PesquisaScreen> createState() => _PesquisaScreenState();
}

class _PesquisaScreenState extends State<PesquisaScreen> {
  final _termoController = TextEditingController();
  String _tipoVeiculo = 'Todos';
  String _statusOrdem = 'Todos';

  final List<String> _tiposVeiculo = ['Todos', 'Carro Elétrico', 'Van Elétrica', 'Ônibus Elétrico'];
  final List<String> _statusOptions = ['Todos', 'Aberta', 'Em Andamento', 'Concluída'];

  @override
  void dispose() {
    _termoController.dispose();
    super.dispose();
  }

  void _pesquisar() {
    final filtro = FiltroModel(
      termoBusca: _termoController.text.isEmpty ? null : _termoController.text,
      tipoVeiculo: _tipoVeiculo,
      statusOrdem: _statusOrdem,
    );

    Navigator.push(
      context,
      MaterialPageRoute(
        settings: RouteSettings(arguments: filtro),
        builder: (context) => ResultadosScreen(filtro: filtro),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Orquestrador de Dados - Pesquisa')),
      body: Padding(
        padding: const EdgeInsets.all(16),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            TextField(
              controller: _termoController,
              decoration: const InputDecoration(
                labelText: 'Termo de busca (ID do veículo, placa, etc.)',
                border: OutlineInputBorder(),
              ),
            ),
            const SizedBox(height: 16),
            DropdownButtonFormField<String>(
              value: _tipoVeiculo,
              decoration: const InputDecoration(labelText: 'Tipo de veículo', border: OutlineInputBorder()),
              items: _tiposVeiculo.map((v) => DropdownMenuItem(value: v, child: Text(v))).toList(),
              onChanged: (v) => setState(() => _tipoVeiculo = v ?? 'Todos'),
            ),
            const SizedBox(height: 16),
            DropdownButtonFormField<String>(
              value: _statusOrdem,
              decoration: const InputDecoration(labelText: 'Status da ordem de serviço', border: OutlineInputBorder()),
              items: _statusOptions.map((v) => DropdownMenuItem(value: v, child: Text(v))).toList(),
              onChanged: (v) => setState(() => _statusOrdem = v ?? 'Todos'),
            ),
            const SizedBox(height: 24),
            ElevatedButton.icon(
              onPressed: _pesquisar,
              icon: const Icon(Icons.search),
              label: const Text('Pesquisar'),
            ),
          ],
        ),
      ),
    );
  }
}
