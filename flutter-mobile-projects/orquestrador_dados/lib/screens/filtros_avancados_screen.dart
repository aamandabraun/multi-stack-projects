import 'package:flutter/material.dart';
import '../models/filtro_model.dart';

class FiltrosAvancadosScreen extends StatefulWidget {
  final FiltroModel filtroAtual;

  const FiltrosAvancadosScreen({super.key, required this.filtroAtual});

  @override
  State<FiltrosAvancadosScreen> createState() => _FiltrosAvancadosScreenState();
}

class _FiltrosAvancadosScreenState extends State<FiltrosAvancadosScreen> {
  late String _statusOrdem;

  final List<String> _statusOptions = ['Todos', 'Aberta', 'Em Andamento', 'Concluída'];

  @override
  void initState() {
    super.initState();
    _statusOrdem = widget.filtroAtual.statusOrdem;
  }

  void _confirmar() {
    Navigator.pop(context, true);
  }

  void _cancelar() {
    Navigator.pop(context, false);
  }

  @override
  Widget build(BuildContext context) {
    return PopScope(
      canPop: false,
      onPopInvokedWithResult: (bool didPop, bool? result) {
        if (!didPop) {
          Navigator.pop(context, false);
        }
      },
      child: Scaffold(
        appBar: AppBar(title: const Text('Filtros Avançados')),
        body: Padding(
          padding: const EdgeInsets.all(16),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.stretch,
            children: [
              DropdownButtonFormField<String>(
                value: _statusOrdem,
                decoration: const InputDecoration(labelText: 'Status da ordem', border: OutlineInputBorder()),
                items: _statusOptions.map((v) => DropdownMenuItem(value: v, child: Text(v))).toList(),
                onChanged: (v) => setState(() => _statusOrdem = v ?? 'Todos'),
              ),
              const SizedBox(height: 24),
              Row(
                children: [
                  Expanded(
                    child: OutlinedButton(onPressed: _cancelar, child: const Text('Cancelar')),
                  ),
                  const SizedBox(width: 12),
                  Expanded(
                    child: ElevatedButton(onPressed: _confirmar, child: const Text('Aplicar')),
                  ),
                ],
              ),
            ],
          ),
        ),
      ),
    );
  }
}
