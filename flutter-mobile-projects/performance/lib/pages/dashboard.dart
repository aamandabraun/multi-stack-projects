class SensorDashboard extends StatelessWidget {
  final List<Map<String, dynamic>> sensores = [
    {'nome': 'Temperatura A1', 'valor': '78°C', 'ativo': true},
    {'nome': 'Pressão B2', 'valor': '4.2 bar', 'ativo': true},
    {'nome': 'Umidade C3', 'valor': '55%', 'ativo': false},
    {'nome': 'Vibração D4', 'valor': '0.02g', 'ativo': true},
  ];

  SensorDashboard({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Painel de Sensores')),
      body: GridView.builder(
        padding: const EdgeInsets.all(12),
        gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
          crossAxisCount: 2,
          crossAxisSpacing: 12,
          mainAxisSpacing: 12,
          childAspectRatio: 1.2,
        ),
        itemCount: sensores.length,
        itemBuilder: (context, index) {
          final sensor = sensores[index];
          final bool ativo = sensor['ativo'];

          return Card(
            elevation: 3,
            child: Padding(
              padding: const EdgeInsets.all(12.0),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  Text(
                    sensor['nome'],
                    style: const TextStyle(fontWeight: FontWeight.bold, fontSize: 16),
                  ),
                  Text(
                    sensor['valor'],
                    style: const TextStyle(fontSize: 22),
                  ),
                  Row(
                    children: [
                      Icon(
                        Icons.circle,
                        size: 12,
                        color: ativo ? Colors.green : Colors.red,
                      ),
                      const SizedBox(width: 6),
                      Text(ativo ? 'Ativo' : 'Inativo'),
                    ],
                  ),
                ],
              ),
            ),
          );
        },
      ),
    );
  }
}